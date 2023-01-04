#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include <iostream>
#include "HelperFunc.hpp"

using namespace std;

class Sudoku
{
public:
    string nombre;

    Sudoku(string nombre);
    void mostrarTabla();
    void resetearTabla();
    void cambiarTabla(int fil, int col, char car);
    bool solucionarTabla();
    void generarTabla(int dific);

private:
    array<array< char, N>, N > tabla;
    array<array< char, N>, N > tablaSol;
    bool generarSudoku(int vacMin, int vacMax);
    void crearTablaSol();
    bool resolverSudoku(array<array< char, N>, N> tabla);
};

//      --FUNCIONES PUBLICAS--

Sudoku::Sudoku(string nombre)
{
    resetearTabla();
    this->nombre = nombre;
}

void Sudoku::mostrarTabla()
{
    for(int i = 0; i < N; i++)
    {
        for(int j=0; j < N; j++)
        {
            if(this->tabla[i][j] == VACIO)
                cout<<" ";
            else
                cout<< this->tabla[i][j];
            cout<<"|";
        }
        cout<<endl;
    }
}

void Sudoku::resetearTabla()
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            this->tabla[i][j] = VACIO;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            this->tablaSol[i][j] = VACIO;
}

void Sudoku::cambiarTabla(int fil, int col, char car)
{
    this->tabla[fil][col] = car;
}

bool Sudoku::solucionarTabla()
{
    return resolverSudoku(this->tabla);
}

void Sudoku::generarTabla(int dific)
{
    int vacMin, vacMax; // Número de casillas vacias
    switch(dific)
    {
        case 0:
            vacMin = 5;
            vacMax = 144;
            break;
        case 1:
            vacMin = 14;
            vacMax = 34;
            break;
        case 2:
            vacMin = 34;
            vacMax = 54;
            break;
        case 3:
            vacMin = 54;
            vacMax = 74;
            break;
    }

    do
    {
        crearTablaSol();
        copy(begin(this->tablaSol), end(this->tablaSol), begin(this->tabla));
    }while(!generarSudoku(vacMin, vacMax));
}

//      --FUNCIONES PRIVADAS--

bool Sudoku::generarSudoku(int vacMin, int vacMax)
{
    int contVac = 0;
    /*
        randPos es un array que tiene numeros del 1-144
        que describen una posicion en la tabla, nos servira
        para eliminar aleatoriamente posiciones
    */
    array<int, N*N> randPos;
    genRandPos(randPos);

    for(int i = 0; i < vacMax; i++)
    {
        int x = randPos[i] / 12;
        int y = randPos[i] % 12;
        int aux = this->tabla[x][y];
        this->tabla[x][y] = VACIO;

        int nSol = 0;
        contarSoluciones(this->tabla, nSol);
        if(nSol != 1)
            this->tabla[x][y] = aux;
        else
            contVac++;
    }

    if(contVac < vacMin)
        return false;
    else
        return true;
}


bool Sudoku::resolverSudoku(array<array< char, N>, N> tabla)
{
    int fil, col;

    /* Si no hay espacios vacios, está resuelto
    Si los hay, fil y col son modificados */
    if(!HallarVacio(tabla, fil, col)){
        copy(begin(tabla), end(tabla), begin(this->tablaSol));
        return true;
    }

    // Revisar cada caracter disponible
    for(char car : caracts)
    {
        // Revisar si es seguro asignarlo al espacio
        if(esSeguro(tabla, fil, col, car))
        {

            // Proceder si es seguro
            tabla[fil][col] = car;

            // Seguir resolviendo hasta finalizar
            if(resolverSudoku(tabla))
                return true;

            // Falló el numero, retroceder y volver a intentarlo
            tabla[fil][col] = VACIO;
        }
    }

    // No existe solucion en este estado de la tabla
    return false;
}


/*
    llenarDiagionales() llena los cuadrados 3x4 que no generarán conflicto
    entre ellos mismos ya que no comparten filas ni columnas
*/


// Crea una tabla ya solucionada y la almacena en tablaSol
void Sudoku::crearTablaSol()
{
    resetearTabla();
    llenarDiagonales(this->tablaSol);
    resolverSudoku(this->tablaSol);
}


//      --FUNCIONES LIBRERIA--

bool letraValida(char letra)
{
    for(char c : caracts)
        if(letra == c)
            return true;
    return false;
}


#endif // SUDOKU_H_INCLUDED
