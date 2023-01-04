#ifndef HELPERFUNC_H_INCLUDED
#define HELPERFUNC_H_INCLUDED

#include <iostream>
#include <algorithm>
#include "Sudoku.hpp"

using namespace std;

const int N = 12;
const int MAX_FIL = 3;
const int MAX_COL = 4;
const char VACIO = '0';
array<char, N> caracts = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

int genRand(int limiteMax)
{
    return rand()%limiteMax;
}

//TODO: Barajar Array = random_shuffle()
//TODO: Copiar Array = copy()

void genRandPos(array<int, N*N> &pos)
{
    for(int i = 0; i < N*N; i++)
        pos[i] = i;
    random_shuffle(begin(pos), end(pos), genRand);
}

bool HallarVacio(array<array<char, N>, N> tabla, int &fil, int &col)
{
    for(fil = 0; fil < N; fil++)
        for(col = 0; col < N; col++)
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

bool UsadoCol(array<array<char, N>, N> tabla, int col, char car)
{
    for(int fil = 0; fil < N; fil++)
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

bool esSeguro(array<array<char, N>, N> tabla, int fil, int col, char car)
{
    /* Revisa si el espacio es vacio y el caracter no esta ya en
    la fila, columna o en la caja 3x4 del espacio
    en el que queremos asignarlo*/
    return !UsadoFil(tabla, fil, car)
           && !UsadoCol(tabla, col, car)
           && !UsadoCaj(tabla, fil - fil % MAX_FIL, col - col % MAX_COL, car)
           && tabla[fil][col] == VACIO;
}

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

void imprimirTabla(array<array<char, N>, N> tabla)
{
    for(int i = 0; i < N; i++)
    {
        for(int j=0; j < N; j++)
        {
            if(tabla[i][j] == 0)
                cout<<" ";
            else
                cout<< tabla[i][j];
            cout<<"|";
        }
        cout<<endl;
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

void contarSoluciones(array<array<char, N>, N> tabla, int &cont, char excl)
{
    imprimirTabla(tabla);
    int fil, col;

    if(!HallarVacio(tabla, fil, col))
        cont++;

    for(char car : caracts)
    {
        cout << fil << " " << col << " " << car << endl;
        if(cont > 2)
            break;

        if(car != excl && esSeguro(tabla, fil, col, car))
        {
            tabla[fil][col] = car;
            contarSoluciones(tabla, cont, excl);
        }

        tabla[fil][col] = VACIO;
    }
}


#endif // HELPERFUNC_H_INCLUDED
