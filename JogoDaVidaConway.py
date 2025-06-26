import time

nomeArquivo = input("Digite o nome do arquivo: ")
with open(f'{nomeArquivo}', 'r', encoding='utf-8') as arquivo: #abre arquivo
    # Lê número de linhas e colunas e as "pula"
    numLinhas = int(arquivo.readline().strip())
    numColunas = int(arquivo.readline().strip())

    lerMatriz = [arquivo.readline().strip() for _ in range(numLinhas)] #lê o resto do arquivo

matriz = [[0 for _ in range(numColunas)] for _ in range(numLinhas)] #cria uma matriz do tamanho desejado

def leEmVolta(x,y): #funçao leitura casas em volta
    contador = 0
    for i in range(-1,2):
        for j in range(-1,2):
            x1 = x + i
            y1 = y + j
            if (i != 0 or j != 0) and 0 <= x1 < numLinhas and 0 <= y1 < numColunas:
                if matriz[x1][y1] == 1:
                    contador += 1
    return contador

def matrizVizinhanca(): #transforma funcao leEmVolta em matriz
    matrizEmVolta = [[0 for _ in range(numColunas)] for _ in range(numLinhas)]
    for i in range(numLinhas):
        for j in range(numColunas):
            matrizEmVolta[i][j] = int(leEmVolta(i,j))
    return matrizEmVolta

def matrizPreenche():
    for i in range(numLinhas): #loop para preencher a matriz com os valores lidos
        for j in range(numColunas):
            matriz[i][j] = int(lerMatriz[i][j])
    return matriz

def proxGeracao(): #muda os valores da matriz de acordo com as regras
    global matriz
    vizinhos = matrizVizinhanca() #cria variavel interna
    novaMatriz = [[0 for _ in range(numColunas)] for _ in range(numLinhas)] #matriz temporaria
    for i in range(numLinhas):
        for j in range(numColunas):
            if (matriz[i][j]) == 1:
                if vizinhos[i][j] < 2 or vizinhos[i][j] > 3:
                    novaMatriz[i][j] = 0
                else:
                    novaMatriz[i][j] = 1
            else:
                if vizinhos[i][j] == 3:
                    novaMatriz[i][j] = 1
    matriz = novaMatriz #atualiza a matriz globalmente

def matrizVisual(): #printa a matriz de um jeito bonito legal
    global matriz
    for i in range(numLinhas):
        for j in range(numColunas):
            if matriz[i][j] == 0:
                print(' ', end = ' ')
            else:
                print('#', end = ' ')
        print()

def numCelulasVivas():
    contador = 0
    for i in range(numLinhas):
        for j in range(numColunas):
            if matriz[i][j] == 1:
                contador += 1
    return contador

numGeracoes = int(input("Digite o numero de geracoes: "))

matrizPreenche()
for i in range(numGeracoes):
    print(f"Geracao {i+1}")
    print(f"Num celulas vivas: {numCelulasVivas()}")
    matrizVisual()
    time.sleep(0.5)
    print("\n" * 30)

    proxGeracao()

















