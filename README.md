# sadokun
Sadokun es un programa de C++ que permite generar, resolver y jugar con otra persona a Sudokus de 12x12. Los caracteres por defecto usados en este programa son los números del 1 al 9, A, B  y C.

## Solucionador
El método usado en este programa para solucionar los Sudokus es backtracking, que funciona probando sistemáticamente cada posibilidad y retrocediendo (backtracking) las opciones que conducen a un resultado que no es válido. 

Implementamos la función recursiva resolverSudoku() que funciona usando el backtracking del siguiente modo:

1. Comienza eligiendo un cuadro vacio.
2. Intenta llenar el cuadro con uno de los caracteres.
3. Comprueba si el caracter es una opción válida para esa casilla.
4. Si el caracter no es una opción válida, vuelve al paso 2 e intenta con el siguiente caracter.
5. Si el número es una opción válida, pasa a la siguiente casilla y repite el proceso.
6. Si llega a un punto en el que no hay más casillas para completar y se han cumplido todas las reglas del sudoku, se ha encontrado la solución.
7. Si llega a un punto en el que no hay más casillas para completar pero las reglas del sudoku no se han cumplido, vuelva a la última casilla que llenó e intente con el siguiente número.
8. Si llega a un punto en el que no hay más casillas para completar ni más números para probar, no hay solución y se debe retroceder.
