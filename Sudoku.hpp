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
    void mostrarTablaSol();
    void cambiarTabla(int fil, int col, char car);
    bool solucionarTabla();
    void generarTabla(int dific);
    void resetearTabla();
    bool estaSolucionado();


private:
    array<array< char, N>, N > tabla;
    array<array< char, N>, N > tablaSol;
    bool solucionado;

    bool generarVacios(int vacMin, int vacMax);
    void crearTablaSol();
    bool resolverSudoku(array<array< char, N>, N> tabla);
};

//      --FUNCIONES PUBLICAS--

Sudoku::Sudoku(string nombre)
{
    resetearTabla();
    this->nombre = nombre;
}

bool Sudoku::estaSolucionado()
{
    return this->solucionado;
}

/*
    Mostrar tabla permite imprimir la tabla con los caracteres previamente guardados
    e interpretar los ceros como espacios vacios en el sudoku.
*/
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

/*
    Mostrar tabla permite imprimir la tabla solucionada
*/
void Sudoku::mostrarTablaSol()
{
    for(int i = 0; i < N; i++)
    {
        for(int j=0; j < N; j++)
            cout<< this->tablaSol[i][j] << "|";
        cout<<endl;
    }
}

/*
    Resetear tabla permite asignar ceros a cada espacio del sudoku
    para así tener una tabla completamente vacia.
*/
void Sudoku::resetearTabla()
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            this->tabla[i][j] = VACIO;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            this->tablaSol[i][j] = VACIO;

    this->solucionado = false;
}

/*
    Cambiar tabla nos permite cambiar un caracter especificando
    su fila y su columna.
*/
void Sudoku::cambiarTabla(int fil, int col, char car)
{
    if(esPosible(this->tabla, fil, col, car))
    {
        this->tabla[fil][col] = car;
        this->solucionado = false;
    }
    else
        cout << "No es posible ya que " << car << " se encuentra ya en la fila " << fil + 1 << " con columna " << col + 1 << endl;
}

/*
    Solucionar tabla resuelve el sudoku almacenado en el atributo de
    tabla.
*/
bool Sudoku::solucionarTabla()
{
    return resolverSudoku(this->tabla);
}

/*
    Generar tabla permite generar un Sudoku jugable con sus espacios
    vacios generados a partir del parametro de dificultad que sea pasado
    al método.
*/
void Sudoku::generarTabla(int dific)
{
    int vacMin, vacMax; // Número de casillas vacias
    switch(dific)
    {
        case 0:
            vacMin = 5;
            vacMax = 100;
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
    }while(!generarVacios(vacMin, vacMax));
}

//      --FUNCIONES PRIVADAS--

/*
    generarVacios es un método que tiene como parametros un minimo y un máximo de espacios
    vacios y que a partir de esto aleatoriamente en la tabla elimina espacios y verifica
    que la tabla siga siendo solucionable y tenga solo una solución para mantener las reglas
    del Sudoku.
*/
bool Sudoku::generarVacios(int vacMin, int vacMax)
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

/*
    resolverSudoku usa una técnica de backtracking para resolver la tabla que sea
    pasada como párametro y al resolverla, la asigne al atributo de tablaSol
*/
bool Sudoku::resolverSudoku(array<array< char, N>, N> tabla)
{
    int fil, col;

    // Si no hay espacios vacios, está resuelto
    if(!HallarVacio(tabla, fil, col)){
        copy(begin(tabla), end(tabla), begin(this->tablaSol));
        this->solucionado = true;
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
