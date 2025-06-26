from PIL import Image

import math

caracteres = "@$%#WM8BHAOQ0ZXNEK*&§+=/|~^-_<>:;'`., "
arrayCaracteres = list(caracteres)
charLenght = len(arrayCaracteres)
intervalo = charLenght / 256

tamanhorelativo = 1

def getChar(inputInt):
    return arrayCaracteres[math.floor(inputInt * intervalo)]

resultado = open("asciiart.txt", "w")

foto = Image.open('kanye.jpg')

largura, altura = foto.size
foto = foto.resize((int(tamanhorelativo * 2 * largura), int(tamanhorelativo * altura)), Image.NEAREST)
largura, altura = foto.size

pix = foto.load()

for i in range(altura):
    for j in range(largura):
        r, g, b = pix[j,i]
        c = int(r/3 + g/3 + b/3)
        pix[j,i] = (c, c, c)
        resultado.write(getChar(c))

    resultado.write('\n')







