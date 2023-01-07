# sadokun
Sadokun es un programa de C++ que permite generar, resolver y jugar con otra persona a Sudokus de 12x12. Los caracteres por defecto usados en este programa son los números del 1 al 9, A, B  y C.

## Solucionador
El método usado en este programa para solucionar los Sudokus es backtracking, que funciona probando sistemáticamente cada posibilidad y retrocediendo (backtracking) las opciones que conducen a un resultado que no es válido. 

Implementamos la función recursiva resolverSudoku() que funciona usando el backtracking del siguiente modo:

1. Comienza eligiendo una casilla vacio.
2. Intenta llenar la casilla con uno de los caracteres.
3. Comprueba si el caracter es una opción válida para esa casilla.
4. Si el caracter no es una opción válida, vuelve al paso 2 e intenta con el siguiente caracter.
5. Si el número es una opción válida, pasa a la siguiente casilla y repite el proceso.
6. Si llega a un punto en el que no hay más casillas para completar y se han cumplido todas las reglas del sudoku, se ha encontrado la solución.
7. Si llega a un punto en el que no hay más casillas para completar pero las reglas del sudoku no se han cumplido, vuelva a la última casilla que llenó e intenta con el siguiente número.
8. Si llega a un punto en el que no hay más casillas para completar ni más números para probar, no hay solución y se debe retroceder.

## Generador
El generador consiste en 3 sencillos pasos.

1. Rellenar rectangulos 3x4 que estén ubicados diagonalmente (ya que no generarán problemas, al no compartir filas ni columnas) para ser usado como seed.
2. Resolver el Sudoku que resulte del paso 1 usando el mismo método de Backtracking mencionado anteriormente.
3. Vaciar el numero de casillas que se quiera por medio de un ciclo, comprobando en cada iteración que el número de soluciones siempre sea 1: si no lo es, volver a rellenar la casilla y seguir con el ciclo.

## Archivos

* main.cpp: interfaz usada para interactuar con el usuario.
* Sudoku.hpp: header en el que se implementa la clase de Sudoku y una función requerida en el main.
* HelperFunc.hpp: header en el que se implementan algunas constantes usadas y funciones que son necesarias en la clase Sudoku, pero no requieren acceso directo al objeto (this).
