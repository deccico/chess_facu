/*
Proyecto Ajedrez
Grupo 14 Deccico-Fontdevila
archivo: tablero.cpp
*/

#include "tablero.h"

const int cTablero::mCantCasillas;

cTablero::cTablero()
{
	for(int i=0;i<= 63; i++)
         tablero[i]= NULL;
}

cTablero::~cTablero()
{
    mVaciar();
}

void cTablero::mVaciar()
{                         
	for( int i=0;i<= 63; i++ ){
        if ( tablero[i] != NULL )
            delete tablero[i];
            tablero[i]= NULL;
    }
}

void cTablero::mImprimir(int indent)
{
    string tab=" ";
    tab=""; //problemas con strngs en bc5++
    for (int i=0;i<indent;i++) tab+= ' ';
    for (int i=0;i<mCantCasillas;i++)
    {
        if (i%8 == 0) {
            cout << endl << tab << abs(i/8 - 8) << " |";
        }
        if ( mHayPieza(i) )
            mObtenerPieza(i)->mImprimir();
        else
            cout << "  ";
        cout << '|';
    }
    cout << endl << tab << "   a  b  c  d  e  f  g  h " << endl ;
}
