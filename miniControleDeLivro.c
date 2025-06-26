#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LITERATURA 0
#define POESIA     1
#define ENGENHARIA 2
#define COMPUTACAO 3
#define OUTROS     4


struct Livro{
    char nome[50], data[11];
    float custo;
    int tipo;
};

void mostrarMenu();
void cadastrarLivro();
void mostrarBiblioteca();
void mostrarEstatisticas();

const char* definenome(int tipo) {
    switch (tipo) {
        case LITERATURA:
            return "Literatura";
        case POESIA:
            return "Poesia";
        case ENGENHARIA:
            return "Engenharia";
        case COMPUTACAO:
            return "Computacao";
        case OUTROS:
            return "Outros";
        default:
            return "";
    }
}

int main() {
    int opcao = 1;
    while (opcao != 0) {
        mostrarMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 0:
                break;
            case 1:
                cadastrarLivro();
                break;
            case 2:
                mostrarBiblioteca();
                break;
            case 3:
                mostrarEstatisticas();
                break;
            default:
                printf("Opcao invalida");
                break;
        }
    }
    return 0;
}

void mostrarMenu() {
    printf("===============================================\n"
    "Digite o numero respectivo a opcao desejada\n"
    "0 --> Sair\n"
    "1 --> Cadastrar livro\n"
    "2 --> Listar biblioteca\n"
    "3 --> Consultar estatisticas\n"
    "===============================================\n");
    }

void cadastrarLivro() {
    struct Livro temp;
    int tipo;

    FILE *arquivo = fopen("biblioteca.bin","ab+");
    printf("Cadastro do novo livro\n");
    printf("Titulo: ");
    scanf("%49[^\n]", temp.nome);
    fflush(stdin);

    printf("Data da compra (xx/xx/xxxx): \n");
    scanf("%10s", temp.data);
    fflush(stdin);

    printf("Preco: RS \n");
    scanf("%f", &temp.custo);
    fflush(stdin);

    printf("Tipo do livro:\n"
           "1- Literatura, 2- Poesia, 3- Engenharia, 4- Computacao, 5- Outros\n");
    while (tipo < 1 || tipo > 5) {
        printf("Digite o numero correspondente: \n");
        scanf("%d", &tipo);
    }

    temp.tipo = tipo - 1;

    fwrite(&temp, sizeof(struct Livro), 1, arquivo);

    fclose(arquivo);

    printf("Livro cadastrado.\n");
}

void mostrarBiblioteca() {
    struct Livro livro;
    int contador = 0;

    FILE *arquivo = fopen("biblioteca.bin","rb");

    printf("Biblioteca");
    while (fread(&livro, sizeof(struct Livro), 1, arquivo) == 1) {
        contador++;
        printf("===============================================\n"
                "Titulo: %s\n", livro.nome);
        printf("Data da compra: %10s\n", livro.data);
        printf("Preco: RS %.2f\n", livro.custo);
        printf("Tipo: %s\n", definenome(livro.tipo));
        printf("===============================================\n");
    }

    if (contador == 0) {
        printf("Sem livros cadastrados.");
    }
    fclose(arquivo);
}

void mostrarEstatisticas() {

    struct Livro livro;
    int totalLivrosTipo[5] = {0}, totalLivros = 0;;
    float precoGasto[5] = {0.0}, valorTotal = 0.0;

    FILE *arquivo = fopen("biblioteca.bin","rb");

    while (fread(&livro, sizeof(struct Livro), 1, arquivo) == 1) {
        if (livro.tipo >= 0 && livro.tipo <= 4) {
            totalLivrosTipo[livro.tipo]++;
            precoGasto[livro.tipo] += livro.custo;
        }
        totalLivros++;
        valorTotal += livro.custo;
    }
    fclose(arquivo);

    printf("Estatísticas\n");
    for (int i = 0; i < 5; i++) {
        printf("Livros de %s -- Quantidade: %d -- Valor Gasto: RS %.2f\n", definenome(i),totalLivrosTipo[i], precoGasto[i]);
    }
    printf("Total de Livros: %d\n", totalLivros);
    printf("Valor total gasto: %f\n", valorTotal);
}

