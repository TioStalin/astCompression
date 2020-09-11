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
    return f'{left} {op} {right}'


def blockItems(block):
    for i in block:
        if i['_nodetype'] == 'Decl':
            print(i['type']['declname'])
        elif i['_nodetype'] == 'FuncCall':
            print('Function' + ' ' + i['name']['name'])
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
            print(valueI + ' ' + op + ' ' + valueD)
        elif i['_nodetype'] == 'BinaryOp':
            print(getText(der['left']) + ' ' + der['op'] + ' ' + getText(der['right']))
        elif i['_nodetype'] == 'For':
            print('For')
            blockItems(i['stmt']['block_items'])
            print('endFor')
        elif i['_nodetype'] == 'While':
            print('While')
            blockItems(i['stmt']['block_items'])
            print('endWhile')
        elif i['_nodetype'] == 'If':
            print('If')
            if i['iftrue'] != None:
                blockItems([i['iftrue']])
            if i['iffalse'] != None:
                blockItems([i['iffalse']])
            print('endIf')
        elif i['_nodetype'] == 'Return':
            print('return', getText(i['expr']))
        else:
            print('No se encontro ninguna coincidencia')
            print(i)

print(declaracion['type']['type']['declname'])
blockItems(cuerpo)
