import json

f = open('testing.json', 'r')
data = json.load(f)

cuerpo = data['ext'][0]['body']['block_items']
declaracion = data['ext'][0]['decl']

def getText(dict):
    if 'value' in dict.keys():
        return dict['value']
    elif 'name' in dict.keys():
        return dict['name']
    elif '_nodetype' in dict.keys() and dict['_nodetype'] == 'UnaryOp':
        if 'value' in dict.keys():
            return f"{dict['op']}{dict['expr']['value']}"
        elif 'name' in dict.keys():
            return f"{dict['op']}{dict['expr']['name']}"


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
            print(altura, f"{i['expr']['name']}{i['op'][1:]}")
        elif i['_nodetype'] == 'Compound':
            blockItems(i['block_items'], altura)
        else:
            print('No se encontro ninguna coincidencia')
            print(i)

print('-1 EOF')
print('0',declaracion['type']['type']['declname'])
blockItems(cuerpo, 0)
