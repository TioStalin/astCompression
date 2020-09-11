# AST space

Este espacio contiene archivos necesarios para la ejecución de arboles sintacticos en C en la libreria [SISAP](http://www.sisap.org/metricspaceslibrary.html).

El archivo *ASTparse.py* utilza los archivos JSON entregados por la libreria [*pycparser* -> examples -> *c_json.py*](https://github.com/eliben/pycparser/blob/master/examples/c_json.py).
Actualmente soporta declaraciones, asignaciones, while, for, if y algunas funciones. Este archivo se puede modificar a disposición y necesidad de cada usuario, queda libre de editar.

El archivo *astStructure.c* tiene las funciones basicas de un arbol no binario.
