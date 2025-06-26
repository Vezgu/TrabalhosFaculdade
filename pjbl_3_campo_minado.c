#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void criarMatriz();
void criarMatrizVisual();
void mostrarMapaCampoMinado();
void escolhaDificuldade();
void revelar(int, int);
int bombasEmVolta(int, int);
void bombasMatriz(int, int);
void colocarBandeira(int , int);

int linha, coluna, bombas, casas_reveladas;
char m[30][16], m_visual[30][16];

int main() {
    int t,x,y,bombas_clicadas = 0, primeira_jogada = 1;

    srand(time(NULL));
    escolhaDificuldade();
    criarMatriz();
    criarMatrizVisual();

    while (bombas_clicadas == 0) {

        mostrarMapaCampoMinado();

        printf("Quer colocar/retirar uma bandeira? (1) ou revelar um local? (2)\n");
        scanf("%d", &t);

        switch (t) {
            case 1:
                printf("\nEscolha uma linha:");
                scanf("%d", &x);

                printf("\nEscolha uma coluna:");
                scanf("%d", &y);

                x--;
                y--;

                colocarBandeira(x, y);
            break;

            case 2:
                printf("\nEscolha uma linha:");
                scanf("%d", &x);

                printf("\nEscolha uma coluna:");
                scanf("%d", &y);

                x--;
                y--;

                if (primeira_jogada == 1) {
                   bombasMatriz(x,y);
                   primeira_jogada = 0;
                }

                if (x < 0 || x > linha || y < 0 || y > coluna) {
                    printf("Posicao invalida!\n");
                    continue;
                }

                if (m[x][y] == '*') {
                    bombas_clicadas++;
                    printf("\nVoce perdeu!!!\n");

                    // Revelar todas as bombas
                    for (int i = 0; i < linha; i++) {
                        for (int j = 0; j < coluna; j++) {
                            if (m[i][j] == '*')
                                m_visual[i][j] = '*';
                        }
                    }

                mostrarMapaCampoMinado(); // Mostrar o mapa final
            }

            if (casas_reveladas == linha * coluna - bombas) {
                printf("Parabéns! Você venceu!\n");
                break;
            }
            revelar(x, y);
        }
    }
    return 0;
}

void colocarBandeira(int x, int y) {
    if (m_visual[x][y] != '>') {
        m_visual[x][y] = '>';
    }
    else {
        m_visual[x][y] = 254;
    }
}
//cria a matriz "real", que fica escondida
void criarMatriz() {
    int i, j;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            m[i][j] = '#';
        }
    }
}

//cria a matriz que vai ser mostrada ao jogador
void criarMatrizVisual() {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            m_visual[i][j] = 254; //
        }
    }
}

void escolhaDificuldade() {
    int diff;
    printf(
        "Bem vindo ao Campo minado!!\n\n"
        "Qual dificuldade voce gostaria de jogar? Digite o numero entre parenteses \n\n"
        "Principiante:[9x9]; 10 bombas --> (1)\n"
        "Intermediario: [16x16]; 40 bombas --> (2)\n"
        "Especialista: [30x16]; 99 bombas --> (3)\n"
        "Desisto de jogar... (0)\n");

    scanf("%d",&diff);
    if (diff > 3 || diff < 0) {
        printf("Erro!! digite um numero entre 0 e 3");
        exit(0);
    }

    switch (diff) {
        case 0:
            printf("Saindo do jogo...");
        exit(0);
        case 1:
            linha = 9, coluna = 9, bombas = 10; //principiante
        break;
        case 2:
            linha = 16, coluna = 16, bombas = 40; //intermediario
        break;
        case 3:
            linha = 30, coluna = 16, bombas = 99; //especialista
        break;
    }
}

//printf de toda a matriz a ser mostrada para o jogador
void mostrarMapaCampoMinado() {
    int i, j;

    // Linha separadora
    printf("    +");
    for (j = 0; j < coluna; j++) {
        printf("---");
    }
    printf("+\n");

    // Corpo da matriz
    for (i = 0; i < linha; i++) {
        printf("%3d |", i + 1);  // Índice da linha
        for (j = 0; j < coluna; j++) {
            printf(" %c ", m_visual[i][j]);  // Conteúdo do campo
        }
        printf("|\n");
    }

    // Linha final de fechamento
    printf("    +");
    for (j = 0; j < coluna; j++) {
        printf("---");
    }
    printf("+\n");
}

//inicializa todas as bombas, aleatóriamente, na matriz
void bombasMatriz(int x_ignorar, int y_ignorar) {
    int colocadas = 0;
    while (colocadas < bombas) {
        int x = rand() % linha;
        int y = rand() % coluna;

        if (m[x][y] == '*') {
            continue;
        }

        if (abs(x - x_ignorar) <= 1 && abs(y - y_ignorar) <= 1) { // Evita colocar mina na casa clicada ou vizinha
            continue;
        }

        m[x][y] = '*';
        colocadas++;
    }
}

//analisa se/quantas bombas o quadrado tem em volta
int bombasEmVolta(int x, int y) { //analisa se/quantas bombas o quadrado tem em volta
    int contador = 0;
    for (int x1 = -1; x1 <= 1; x1++) {
        for (int y1 = -1; y1 <= 1; y1++) {
            int x2 = x1 + x;
            int y2 = y1 + y;
            if (x2 >= 0 && x2 < linha && y2 >= 0 && y2 < coluna && m[x2][y2] == '*') {
                contador++;
            }
        }
    }
    return contador;
}

//coloca na matriz mostrada para o jogador o número de bombas em volta, usando a matriz acima
void revelar(int x, int y) {
    if (x < 0 || x > linha || y < 0 || y > coluna || m[x][y] != '#')
        return;

    m[x][y] = '.';
    casas_reveladas++;

    int contador = bombasEmVolta(x, y);
    if (contador > 0) {
        m_visual[x][y] = '0' + contador;
    }
    else { // se não existir nenhuma bomba em volta, mostra para o jogador as casas em volta automáticamente
        m_visual[x][y] = ' ';
        for (int x1 = -1; x1 <= 1; x1++) {
            for (int y1 = -1; y1 <= 1; y1++) {
                int x2 = x1 + x, y2 = y1 + y;
                revelar(x2, y2);
            }
        }
    }
}