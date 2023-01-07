#include <iostream>
#include "Sudoku.hpp"
#include <vector>

using namespace std;
void crearSudoku(vector<Sudoku> &sudos);
void accederSudoku(Sudoku &sudo);
void cambiarTabla(Sudoku &sudo);
void jugarTabla(Sudoku &sudo);
void solucionarTabla(Sudoku &sudo);
void generarTabla(Sudoku &sudo);
bool correctoTabla(Sudoku &sudo);

int main()
{
    int opt = 0, i = 1;
    vector<Sudoku> prevSudokus;
    do
    {
        cout << endl << "\t---SADOKUN---" << endl;
        for(i = 1; i <= prevSudokus.size(); i++)
            cout << i << ". " << prevSudokus[i-1].nombre << endl;
        cout << i << ". " << "Crear nuevo Sudoku" << endl;
        cout << i + 1<< ". " << "Salir" << endl;
        cin >> opt;

        if(opt >= 1 && opt <= i + 1)
            if(opt == i)
                crearSudoku(prevSudokus);
            else if(opt == i + 1)
                cout << "Hasta la vista!" << endl;
            else
                accederSudoku(prevSudokus[opt-1]);
        else
            cout << "Opción incorrecta" << endl;
    }while(opt != i + 1);
    return 0;
}

void crearSudoku(vector<Sudoku> &sudos)
{
    string nombre;
    cout << endl << "Ingresa un nombre para tu nuevo sudoku: ";
    cin >> nombre;
    sudos.push_back(Sudoku(nombre));
}

void accederSudoku(Sudoku &sudo)
{
    int opt;
    do
    {
        cout << endl << "\t---" << sudo.nombre << "---" << endl;
        cout << endl;
        sudo.mostrarTabla();
        cout << endl;
        cout << "1. Resetear el sudoku" << endl;
        cout << "2. Cambiar alguna casilla" << endl;
        cout << "3. Generar nuevo Sudoku" << endl;
        cout << "4. Jugar contra alguien" << endl;
        cout << "5. Mostrar solucion" << endl;
        cout << "6. Regresar" << endl;
        cin >> opt;

        switch(opt)
        {
            case 1:
                sudo.resetearTabla();
                break;
            case 2:
                cambiarTabla(sudo);
                break;
            case 3:
                generarTabla(sudo);
                break;
            case 4:
                jugarTabla(sudo);
                break;
            case 5:
                solucionarTabla(sudo);
                break;
            case 6:
                break;
            default:
                cout << "Opción incorrecta";
        }
    }while(opt != 6);
}

void cambiarTabla(Sudoku &sudo)
{
    int fil, col;
    char opt, car; 
    do{
        cout << endl << "\t---" << sudo.nombre << "---" << endl;
        cout << endl;
        sudo.mostrarTabla();
        cout << endl;
        do
        {
            cout << "Fila: ";
            cin >> fil;
            fil--;
        }while(!(fil >= 0 && fil <= 11));
        do
        {
            cout << "Columna: ";
            cin >> col;
            col--;
        }while(!(col >= 0 && col <= 11));
        do
        {
            cout << "Caracter: ";
            cin >> car;
        }while(!letraValida(car));
        sudo.cambiarTabla(fil, col, car);
        cout << "Ingrese C si quiere continuar: ";
        cin >> opt;
    }while(opt == 'C');
    
}

void jugarTabla(Sudoku &sudo)
{
    if(!sudo.estaSolucionado())
        if(!sudo.solucionarTabla())
        {
            cout << "No se puede jugar esta tabla ya que no tiene solucion" << endl;
            return ;
        }
    
    bool turnoUno = true;
    int puntajeUno = 0, puntajeDos = 0;
    while(!sudo.tablaTerminada())
    {
        if(turnoUno)
        {
            cout << "\tTurno del Jugador1: " << endl;
            if(correctoTabla(sudo))
                puntajeUno++;
            else
            {
                turnoUno = false;
                cout << "Puntaje Jugador1: " << puntajeUno << endl << endl;
            }
        }
        else
        {
            cout << "\tTurno del Jugador2: " << endl;
            if(correctoTabla(sudo))
                puntajeDos++;
            else {
                turnoUno = true;
                cout << "Puntaje Jugador2: " << puntajeDos << endl << endl;
            }
        }
    }

    if(puntajeUno > puntajeDos)
        cout << "Ganador: Jugador1";
    else if(puntajeDos > puntajeUno)
        cout << "Ganador: Jugador2";
    else
        cout << "Empate";

    cout << endl;
}

void solucionarTabla(Sudoku &sudo)
{
    if(sudo.estaSolucionado())
        sudo.mostrarTablaSol();
    else{
        if(sudo.solucionarTabla())
            sudo.mostrarTablaSol();
        else
            cout << "La tabla no tiene solucion";
    }
    cout << endl;
}

void generarTabla(Sudoku &sudo)
{
    int dif;
    do{
        cout << endl << "\t--DIFICULTADES--" << endl;
        cout << "0. Aleatoria: cualquier sudoku" << endl;
        cout << "1. Fácil: de 110 a 130 pistas" << endl;
        cout << "2. Medio: de 90 a 110 pistas" << endl;
        cout << "3. Dificil: de 70 a 90 pistas" << endl;
        cin >> dif;
    }while(!(dif >= 0 && dif <= 3));
    sudo.generarTabla(dif);
}

bool correctoTabla(Sudoku &sudo)
{
    int fil, col;
    char car; 
    sudo.mostrarTabla();
    cout << endl;
    do{
        do
        {
            cout << "Fila: ";
            cin >> fil;
            fil--;
        }while(!(fil >= 0 && fil <= 11));
        do
        {
            cout << "Columna: ";
            cin >> col;
            col--;
        }while(!(col >= 0 && col <= 11));
        
        if(!sudo.esCasillaVacia(fil, col))
            cout << "La casilla seleccionada no esta vacia." << endl;
    }while(!sudo.esCasillaVacia(fil,col));
    
    do
    {
        cout << "Caracter: ";
        cin >> car;
    }while(!letraValida(car));

    return sudo.caracterCorrecto(fil, col, car);
}