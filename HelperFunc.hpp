#ifndef HELPERFUNC_H_INCLUDED
#define HELPERFUNC_H_INCLUDED

#include <array>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int N = 12;
const int MAX_FIL = 3;
const int MAX_COL = 4;
const char VACIO = '0';
array<char, N> caracts = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

int genRand(int limiteMax)
{
    srand(time(0));
    return rand()%limiteMax;
}

/*
    genRandPos es una función que genera un array
    con números del 1-144 en una posición aleatoria
    que describen una posicion en la matriz del sudoku
*/
void genRandPos(array<int, N*N> &pos)
{
    for(int i = 0; i < N*N; i++)
        pos[i] = i;
    random_shuffle(begin(pos), end(pos), genRand);
}

/*
    Revisa toda la tabla y por medio de referencias almacena el valor de
    la fila y columna de la primer casilla vacia que encuentre.
*/
bool HallarVacio(array<array<char, N>, N> tabla, int &fil, int &col)
{
    for(fil = 0; fil < N; fil++)
        for(col = 0; col < N; col++)
            if(tabla[fil][col] == VACIO)
                return true;
    return false;
}

bool HallarVacio(array<array<char, N>, N> tabla)
{
    for(int fil = 0; fil < N; fil++)
        for(int col = 0; col < N; col++)
            if(tabla[fil][col] == VACIO)
                return true;
    return false;
}

bool UsadoFil(array<array<char, N>, N> tabla, int fil, char car)
{
    for(int col = 0; col < N; col++)
        if(tabla[fil][col] == car)
            return true;
    return false;
}

bool UsadoFil(array<array<char, N>, N> tabla, int fil, char car, int &col)
{
    for(col = 0; col < N; col++)
        if(tabla[fil][col] == car)
            return true;
    return false;
}

bool UsadoCol(array<array<char, N>, N> tabla, int col, char car)
{
    for(int fil = 0; fil < N; fil++)
        if(tabla[fil][col] == car)
            return true;
    return false;
}

bool UsadoCol(array<array<char, N>, N> tabla, int col, char car, int &fil)
{
    for(fil = 0; fil < N; fil++)
        if(tabla[fil][col] == car)
            return true;
    return false;
}

bool UsadoCaj(array<array< char, N>, N> tabla, int inicioFila, int inicioCol, char car)
{
    for(int fil = 0; fil < MAX_FIL; fil++)
        for(int col = 0; col < MAX_COL; col++)
            if(tabla[inicioFila + fil][inicioCol + col] == car)
                return true;
    return false;
}

bool UsadoCaj(array<array< char, N>, N> tabla, int inicioFila, int inicioCol, char car, int &fil, int &col)
{
    for(fil = 0; fil < MAX_FIL; fil++)
        for(col = 0; col < MAX_COL; col++)
            if(tabla[inicioFila + fil][inicioCol + col] == car)
                return true;
    return false;
}

/*
    Revisa si la casilla esta vacia y el caracter no esta ya en
    la fila, columna o en la caja 3x4 de la casilla
    en el que queremos asignarlo
*/
bool esSeguro(array<array<char, N>, N> tabla, int fil, int col, char car)
{
    return !UsadoFil(tabla, fil, car)
           && !UsadoCol(tabla, col, car)
           && !UsadoCaj(tabla, fil - fil % MAX_FIL, col - col % MAX_COL, car)
           && tabla[fil][col] == VACIO;
}

/*
    Revisa el caracter no esta ya en la fila, columna o
    en la caja 3x4 de la casilla en el que queremos asignarlo
    y devuelve valores de fila y columna del valor con el que tiene conflicto
    por medio de referencias.
*/
bool esPosible(array<array<char, N>, N> tabla, int &fil, int &col, char car)
{
    return !UsadoFil(tabla, fil, car, col)
           && !UsadoCol(tabla, col, car, fil)
           && !UsadoCaj(tabla, fil - fil % MAX_FIL, col - col % MAX_COL, car, fil, col);
}

/*
    llenarDiagionales() llena los rectangulos 3x4 que no generarán conflicto
    entre ellos mismos ya que no comparten filas ni columnas
*/
void llenarDiagonales(array<array<char, N>, N> &tabla)
{
    int inicCol, inicFil;
    /* Lista de caracteres que será randomizada para no generar
    el mismo sudoku cada vez */
    array<char, N> randCaracts;
    copy(begin(caracts), end(caracts), begin(randCaracts));
    for(int x = 0; x < 3; x++)
    {
        inicFil = 3 * x;
        inicCol = 4 * x;
        random_shuffle(begin(randCaracts), end(randCaracts), genRand);
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 4; j++)
                tabla[inicFil + i][inicCol + j] = randCaracts[i*4 + j];
    }
}

void contarSoluciones(array<array<char, N>, N> tabla, int &cont)
{
    int fil, col;

    if(!HallarVacio(tabla, fil, col)){
        cont++;
        return ;
    }

    for(int i = 0; i < 9 && cont < 2; i++)
    {
        if(esSeguro(tabla, fil, col, caracts[i]))
        {
            tabla[fil][col] = caracts[i];
            contarSoluciones(tabla, cont);
        }

        tabla[fil][col] = VACIO;
    }
}

#endif // HELPERFUNC_H_INCLUDED
