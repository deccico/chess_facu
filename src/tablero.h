/*
Proyecto Ajedrez
Grupo 14 Deccico-Fontdevila
archivo: tablero.h
*/


#ifndef _TABLERO_H_
#define _TABLERO_H_

#include <fstream>
#include <string>


#include "math.h"
#include "pieza.h"

class cTablero
{
protected:
   cPieza* tablero[64];

public:
   static const int mCantCasillas= 64;
   cTablero();
   ~cTablero();

   //Destruye todas las piezas.
   void mVaciar();             

   static int mCalcularCasilla(int col, int fila)
   {
        return fila*8 + col;
   }

   /*
   Devuelve la pos. a partir de la notación tradicional.
   Columnas de a hasta h, filas de 1 hasta 8.
   */
   static int mCalcularCasilla(char col, char fila){
        return abs( (int)(fila-'0') - 8 )*8 + (int)(col-'a') ;
    }
   /*
   Devuelve la pos. a partir de la notación tradicional.
   Columnas de a hasta h, filas de 1 hasta 8.
   */
   static int mCalcularCasilla(const string &sCasilla)
   {
        return mCalcularCasilla( (char)sCasilla[0], (char)sCasilla[1] );
   }

   static string mCalcularCasilla(int cas)
   {
        string fila,col;
        fila= '0'+abs(cas/8 - 8);
        col= 'a'+(char)cas % 8;
        return (col+fila);
//        return string(col+fila);
   }

   void mPonerPieza(cPieza *p, int casilla)
   {
        tablero[casilla]= p;
        if (p) p->mPonerPosicion(casilla);
   }

   void mPonerPieza(cPieza * p,char col,char fila)
   {
        tablero[mCalcularCasilla(col,fila)]= p;
        if (p) p->mPonerPosicion(mCalcularCasilla(col,fila));
   }

   void mPonerPieza(cPieza * p, const string& sCasilla)
   {
        tablero[mCalcularCasilla(sCasilla)]= p;
        if (p) p->mPonerPosicion(mCalcularCasilla(sCasilla));
   }

   cPieza* mObtenerPieza(int casilla)
   {
        return tablero[casilla];
   }

   cPieza* mObtenerPieza(char col, char fila)
   {
        return tablero[mCalcularCasilla(col,fila)];
   }


   cPieza* mObtenerPieza( const string& sCasilla )
   {
        return tablero[mCalcularCasilla(sCasilla)];
   }

   //Devuelve la pieza en casilla y deja la casilla en NULL
   cPieza* mSacarPieza(int casilla)
   {
        cPieza* aux= tablero[casilla];
        tablero[casilla]= NULL;
        return aux;
   }

   cPieza* mSacarPieza(char col,char fila){
        return mSacarPieza( mCalcularCasilla(col,fila) );
   }

   cPieza* mSacarPieza( const string& sCasilla){
        return mSacarPieza( mCalcularCasilla(sCasilla) );
   }

   bool mHayPieza(int casilla){
        return tablero[casilla] != NULL;
   }

   bool mHayPieza( const string& sCasilla){
        return tablero[mCalcularCasilla( sCasilla)] != NULL;
   }

   void mImprimir(int indent=10);
};
//End of class cTablero

#endif
