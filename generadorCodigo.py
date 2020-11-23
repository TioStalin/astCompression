import random
import sys

class codigos:
    def __init__(self, seed = 0):
        self.codigo = ''
        self.lineas = 0
        self.altura = 0
        self.seed = seed

    def inicioFuncion(self):
        self.codigo += '0 func['
        i = 0
        types = ['int', 'char', 'float', 'void', '']
        eleccion = random.choices(types, weights=[70-20*i, 70-20*i, 70-20*i, 70-20*i, 60+i*20])
        while eleccion[0] != '':
            self.codigo += f'{eleccion[0]};'
            i += 1
            if i >= 2:
                self.codigo += ']\n'
                return
            eleccion = random.choices(types, weights=[70-20*i, 70-20*i, 70-20*i, 70-20*i, 60+i*20])
        self.codigo += ']\n'

    def agregarVariable(self):
        self.codigo += f'{self.altura} var\n'
        self.lineas += 1

    def agregarFor(self):
        self.codigo += f'{self.altura} For\n'
        self.altura += 1
        self.lineas += 1

    def agregarIf(self):
        self.codigo += f'{self.altura} If\n'
        self.altura += 1
        self.lineas += 1

    def agregarWhile(self):
        self.codigo += f'{self.altura} While\n'
        self.altura += 1
        self.lineas += 1

    def agregarFunciones(self):
        funciones = random.choices(['printf', 'scanf', ''], weights=[30, 30, 70])
        if funciones[0] != '':
            self.codigo += f'{self.altura} {funciones[0]}\n'
            self.lineas += 1

    def bajarAltura(self):
        if self.altura != 0:
            self.altura -= 1

    def agregarAritmetica(self):
        aritmetica = ['+', '-', '/', '*']
        eleccion = random.choices(aritmetica, weights=[65, 65, 35, 35])
        self.codigo += f'{self.altura} =\n'
        self.altura += 1
        self.codigo += f'{self.altura} var\n'
        self.codigo += f'{self.altura} {eleccion[0]}\n'
        self.altura += 1
        valor = random.choices(['var', '1'], weights=[60, 40])
        self.codigo += f'{self.altura} var\n'
        self.codigo += f'{self.altura} {valor[0]}\n'
        self.altura -= 2
        self.lineas += 5

    def agregarUnario(self):
        eleccion = random.choices(['++', '--'], weights=[50,50])
        self.codigo += f'{self.altura} \n'
        self.lineas += 1

    def agregarReturn(self):
        self.codigo += f'{self.altura} return\n'
        if self.altura == 0:
            opciones = [0, 1, 'var']
            eleccion = random.choices(opciones, weights=[80, 80, 30])
            self.codigo += f'{self.altura + 1} {eleccion[0]}\n'
            self.lineas += 1
        else:
            opciones = [0, 1, 'var']
            eleccion = random.choices(opciones, weights=[30, 30, 70])
            self.codigo += f'{self.altura + 1} {eleccion[0]}\n'
            self.lineas += 1


    def __str__(self):
        return f'{self.codigo}'

    def __repr__(self):
        return '<Codigo>'

def crearCodigo():
    texto = codigos()
    texto.inicioFuncion()
    opciones = ['return', 'while', 'for', 'var', 'if', 'arit', 'bajar']
    pesos = [1, 1, 1, 70, 20, 5, 0]
    eleccion = random.choices(opciones, weights=pesos)
    while texto.lineas < 25 and (eleccion[0] != 'return' or texto.altura != 0):
        if eleccion[0] == 'return':
            texto.agregarReturn()
            pesos = [0, 0, 0, 0, 0, 0, 100]
        elif eleccion[0] == 'while':
            texto.agregarWhile()
            pesos = [0, 10/(texto.altura+1), 10/(texto.altura+1), 50, 20/(texto.altura+1), 80, 0]
        elif eleccion[0] == 'for':
            texto.agregarFor()
            pesos = [0, 5/(texto.altura+1), 10/(texto.altura+1), 50, 35/(texto.altura+1), 50, 0]
        elif eleccion[0] == 'var':
            texto.agregarVariable()
            pesos = [15, 60/(texto.altura+1), 40/(texto.altura+1), 40, 60/(texto.altura+1), 80, 0]
        elif eleccion[0] == 'if':
            texto.agregarIf()
            pesos = [0, 5/(texto.altura+1), 10/(texto.altura+1), 40, 45/(texto.altura+1), 50, 0]
        elif eleccion[0] == 'arit':
            texto.agregarAritmetica()
            pesos = [30, 10/(texto.altura+1), 10/(texto.altura+1), 10, 45/(texto.altura+1), 40, 60]
        elif eleccion[0] == 'bajar':
            texto.bajarAltura()
            pesos = [50, 20/(texto.altura+1), 20/(texto.altura+1), 30, 30/(texto.altura+1), 30, 70]
        if 5 < texto.altura < 9:
            texto.agregarFunciones()
        eleccion = random.choices(opciones, weights=pesos)


    texto.codigo += '0 return\n'
    opciones = [0, 1, 'var']
    eleccion = random.choices(opciones, weights=[80, 80, 30])
    texto.codigo += f'1 {eleccion[0]}\n'
    return texto

def main():
    for i in range(int(sys.argv[1])):
        with open(f'./ejemplos/{i}.txt', 'w') as fp:
            texto = crearCodigo()
            fp.write(texto.codigo)

main()
