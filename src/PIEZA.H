/*
Proyecto Ajedrez
Grupo 14 Deccico-Fontdevila
archivo: pieza.h
*/
	

#ifndef _PIEZA_H_
#define _PIEZA_H_

#include <fstream>
#include <string>

class cPieza {

protected:
   char msColor;
   char msSimbolo;
   int mnPos;
   void mGenerarLineaMovidas(int* &, int, int, int &);

public:
//chequea que se trate de misma linea hor, ver o diagonal según el tercer int
   static bool mEsMismaLinea(int,int,int);
 //validaciones comunes antes de validar una movida
   static bool mValidar(int,int) ;

   cPieza (char sColor)
   {  msColor= sColor;
      mnPos= 0;
   }

   cPieza(char sColor, int npos)
   {
        msColor= sColor;
        mnPos= npos;
   }

   virtual ~cPieza(){}

   char mObtenerColor() const {return msColor;}
   char mObtenerSimbolo() const {return msSimbolo;}
   int mObtenerPosicion() const {return mnPos;}
   void mPonerPosicion(int pos){ mnPos= pos; }
   void mImprimir() const
       {cout << mObtenerSimbolo();cout << mObtenerColor();}
   bool mEsMovidaValidaRCP(int mnPosicion, int nPos, char sPieza) const;
   void mCalcularMovidasRCP(int * & nVec, int, int &, char sPieza='*');
   virtual bool mEsMovidaValida(int,int,bool=false,bool=false) const=0;
   virtual void mCalcularMovidasValidas(int * &, int &, char sCPeon='*')=0;

};//fin cPieza




//pieza Rey
class cRey: public cPieza
{
public:
   //constructor
   cRey::cRey(char sColor):cPieza(sColor) {msSimbolo='R';}
   cRey::cRey(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='R';}
   virtual ~cRey(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
};

//pieza Dama
class cDama: public cPieza
{
public:
   //constructor
   cDama::cDama(char sColor):cPieza(sColor) {msSimbolo='D';}
   cDama::cDama(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='D';}
   virtual ~cDama(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
};

//pieza Alfil
class cAlfil: public cPieza
{
public:
   //constructor
   cAlfil::cAlfil(char sColor):cPieza(sColor) {msSimbolo='A';}
   cAlfil::cAlfil(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='A';}
   virtual ~cAlfil(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
};

//pieza Caballo
class cCaballo: public cPieza
{
public:
   //constructor
   cCaballo::cCaballo(char sColor):cPieza(sColor) {msSimbolo='C';}
   cCaballo::cCaballo(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='C';}
   virtual ~cCaballo(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
};

//pieza Caballo
class cTorre: public cPieza
{
public:
   //constructor
   cTorre::cTorre(char sColor):cPieza(sColor) {msSimbolo='T';}
   cTorre::cTorre(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='T';}
   virtual ~cTorre(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
};

//pieza Peon
class cPeon: public cPieza
{
public:
   //bool mEsMovidaValida(int,int) const;
   //constructor
   cPeon::cPeon(char sColor):cPieza(sColor) {msSimbolo='P';}
   cPeon::cPeon(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='P';}
   virtual ~cPeon(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   bool mEsMovidaValidaColor(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
};

#endif
