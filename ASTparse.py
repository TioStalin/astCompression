import json
import os



def getText(dict):
    if 'value' in dict.keys():
        return dict['value']
    elif 'name' in dict.keys():
        return 'var'
    elif '_nodetype' in dict.keys() and dict['_nodetype'] == 'UnaryOp':
        if 'value' in dict['expr'].keys():
            return f"{dict['op']}{dict['expr']['value']}"
        elif 'name' in dict['expr'].keys():
            return f"{dict['op']}var"


def printOperation(altura, tupla):
    if isinstance(tupla, str):
        print(altura, tupla)
        return
    if len(tupla) == 1:
        print(altura, tupla)
        return
    print(altura, tupla[1])
    printOperation(altura+1, tupla[0])
    printOperation(altura+1, tupla[2])

def BinOp(block):
    left = block['left']
    op = block['op']
    right = block['right']
    if left['_nodetype'] == 'BinaryOp':
        left = BinOp(left)
    if right['_nodetype'] == 'BinaryOp':
        right = BinOp(right)
    if isinstance(left, dict):
        left = getText(left)
    if isinstance(right, dict):
        right = getText(right)
    return (left, op, right)


def blockItems(block, altura):
    for i in block:
        if i['_nodetype'] == 'Decl':
            if 'name' in i.keys():
                print(altura, 'var')
            else:
                print(altura, i['type']['declname'])
        elif i['_nodetype'] == 'FuncCall':
            print(altura, i['name']['name'])
        elif i['_nodetype'] == 'Assignment':
            texto = ''
            izq = i['lvalue']
            der = i['rvalue']
            op = i['op']
            valueI = getText(izq)
            valueD = getText(der)
            if isinstance(valueI, dict):
                valueI = getText(valueI)
            if isinstance(valueD, dict):
                valueD = getText(valueD)
            if der['_nodetype'] == 'BinaryOp':
                valueD = BinOp(der)
            print(altura, op)
            print(altura+1, valueI)
            printOperation(altura+1, valueD)
        elif i['_nodetype'] == 'BinaryOp':
            print(getText(i['left']) + ' ' + i['op'] + ' ' + getText(i['right']))
        elif i['_nodetype'] == 'For':
            print(altura, 'For')
            blockItems(i['stmt']['block_items'], altura+1)
        elif i['_nodetype'] == 'While':
            print(altura,'While')
            blockItems(i['stmt']['block_items'], altura+1)
        elif i['_nodetype'] == 'If':
            print(altura,'If')
            if i['iftrue'] != None:
                blockItems([i['iftrue']], altura+1)
            if i['iffalse'] != None:
                blockItems([i['iffalse']], altura+1)
        elif i['_nodetype'] == 'Return':
            print(altura, 'return')
            print(altura+1, getText(i['expr']))
        elif i['_nodetype'] == 'UnaryOp':
            print(altura, f"var{i['op'][1:]}")
        elif i['_nodetype'] == 'Compound':
            blockItems(i['block_items'], altura)
        elif i['_nodetype'] == 'Break':
            print(altura, 'Break')
        else:
            print('No se encontro ninguna coincidencia')
            print(i)


def getTreeList(file):
    lista = []
    with open(file, 'r') as fp:
        for line in fp:
            lista.append(line.strip().split(' '))
    return lista

def toTree(lista):
    for i in range(len(lista)):
        if i+1 == len(lista):
            break
        if int(lista[i][0]) == int(lista[i+1][0]):
            print(lista[i][1] + ',', end="")
        if int(lista[i][0]) < int(lista[i+1][0]):
            print(lista[i][1] + '(', end="")
        if int(lista[i][0]) > int(lista[i+1][0]):
            print(lista[i][1], end="")
            for j in range(int(lista[i][0]) - int(lista[i+1][0])):
                print(')', end="")
    print(lista[i][1], end="")
    for j in range(abs(int(lista[i-1][0]) - int(lista[i][0]))):
        print(')', end="")
    print()

f = open('./jsons/triangleNum.json', 'r')
data = json.load(f)

cuerpo = data['ext'][0]['body']['block_items']
declaracion = data['ext'][0]['decl']
aux = ''

try:
    for i in declaracion['type']['args']['params']:
        aux += i['type']['type']['names'][0] + ','
except:
    print('No tiene parametros')

# print('0', f'func[{aux}]')
# blockItems(cuerpo, 0)


lista_c = os.listdir('./ejemplos')
print(len(lista_c))
for i in range(len(lista_c)):
    # with open(f'./txt/{lista_c[i]}') as fp:
    #     # data = json.load(fp)
    #     # cuerpo = data['ext'][0]['body']['block_items']
    #     # declaracion = data['ext'][0]['decl']
    #     # with open(f'./txt/{lista_c[i][:len(lista_c[i])-5]}.txt', 'w') as fp:
    #         # string = f"0 {declaracion['type']['type']['declname']}"
    #         # fp.write(string)
    #     print(lista_c[i])
    #     blockItems(cuerpo, 0)
    #     print('\n\n\n')
        lista = getTreeList(f'./ejemplos/{lista_c[i]}')
        toTree(lista)
