/*
Proyecto Ajedrez
Grupo 14 Deccico-Fontdevila
archivo: partida.h
*/

#ifndef _PARTIDA_H_
#define _PARTIDA_H_

#include <fstream>
#include <string>

#include "conio.h"
#include "ejercito.h"
#include "tablero.h"
#include "str.h"

class cPartida
{
protected:
   //A qué color de pieza le toca jugar.
   char msJuega;
   int mnPosVieja, mnPosNueva;
   bool mEnroqueNegroIzq;     
   bool mEnroqueNegroDer;
   bool mEnroqueBlancoIzq;
   bool mEnroqueBlancoDer;
   void mSetEnroque(string); //actualiza el ctrl de posibilidad de enroque
   bool mEnroqueNoValido(char,char); //controlar la posibilidad de enrocar
   bool mEnroque(int);
   cPieza* mpBackupPieza;
   cTablero mTablero;
   cEjercito mBlancas;
   cEjercito mNegras;
   static cPieza* mCrearPieza(char color,char simbolo);
   void cPartida::mArmarBando(char color);
   bool mHayBloqueo(int, int);
   bool mChequear(int,int,int);
   char mElegir();  //eleccion de pieza cuando se corona
   int mBuscarPieza(int);
   int mBuscarPieza(int,int);

public:
    cPartida();
    cPartida(bool conpiezas= true);
    ~cPartida(){}

    cEjercito& mObtenerEjercito(char color)
    {
        return color == 'b' ? mBlancas : mNegras;
    }

    cEjercito& mObtenerEjercitoActivo()
    {
        return msJuega == 'b' ? mBlancas : mNegras;
    }

    char mContrario(char c){return c == 'b' ? 'n':'b'; }
    void mImprimir();
    bool mCargar(string filename="default.css");
    void mGuardar(string filename);
    bool mEsMovidaValida(const string &c1, const string &c2);
    bool mEsMovidaValida(int, int);
    void mMover(const string &c1, const string &c2);
    bool mEstaClavado(const string &c1, const string &c2);
    void mDeshacerMovida();
    void mVaciar();
    void mSiguienteMovida()
        {msJuega= msJuega == 'b'? 'n': 'b';   }
    void mSiguienteMovida(char c)  {msJuega= c;}
    char mMueven() const {return msJuega;}
    bool mHayJaque();
    bool mHayMate();
    bool mDeshacer(int,int);
    bool mCoronarPeon(const string& cFinal);
};
//End of class Partida

#endif
