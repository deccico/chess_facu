/*
Proyecto Ajedrez
archivo: ejercito.cpp
Grupo 14 -Deccico/Fontdevila  ayudante JAvier MAcchi
contiene la implementación de la clase cEjercito
*/


#include "ejercito.h"

cEjercito::cEjercito(char color)
{
	mColor= color;
    for (int i=0; i<16 ;i++) piezas[i]= NULL;
}

void cEjercito::mArmar()
{
      piezas[0]= new cTorre(mColor);
      piezas[1]= new cCaballo(mColor);
      piezas[2]= new cAlfil(mColor);
    	piezas[3]= new cDama(mColor);
    	piezas[4]= new cRey(mColor);
    	piezas[5]= new cAlfil(mColor);
    	piezas[6]= new cCaballo(mColor);
    	piezas[7]= new cTorre(mColor);
        for(int i=8;i<16;i++)
        {
            piezas[i]= new cPeon(mColor);
        }
}

void cEjercito::mDesbandar()
{
    for (int i=0 ;i<16; i++) piezas[i]= NULL;
}

cPieza* cEjercito::mPrimera()
{
        actual= -1;
        return mSiguiente();
}


cPieza* cEjercito::mSiguiente()
{
    if ( actual == 15)
        return NULL;
    while( actual < 15 && piezas[++actual] == NULL );
    return piezas[actual];
}

/*
La pieza p existe en el array piezas.
La posición del array piezas de valor igual a p queda en NULL.
*/
void cEjercito::mSacarPieza(cPieza* p)
{
    int i= mBuscarPieza(p);
    if ( i != -1 )
        piezas[i]= NULL;
}

cPieza* cEjercito::mCrearPieza(char simbolo,char color,int pos)
{
	if ('P' == simbolo)
		return ( new cPeon(color,pos) ) ;
	if ('A' == simbolo)
		return ( new cAlfil(color,pos) );
	if ('C' == simbolo)
		return ( new cCaballo(color,pos) );
	if ('T' == simbolo)
		return ( new cTorre(color,pos) );
	if ('D' == simbolo)
		return ( new cDama(color,pos) );
	if ('R' == simbolo)
		return ( new cRey(color,pos) );
	return NULL;
}//fin mCrearPieza


/*
La pieza es del mismo color y está creada.
La pieza queda agregada a la lista de piezas del ejercito y
será devuelta por next() eventualmente.
*/
bool cEjercito::mAgregarPieza(cPieza* p)
{
    if ( mAgregarRey(p) )
        return true;
    if ( mAgregarDama(p) )
        return true;
    if ( mAgregarAlfil(p) )
        return true;
    if ( mAgregarCaballo(p) )
        return true;
    if ( mAgregarTorre(p) )
        return true;
    if ( mAgregarPeon(p) )
        return true;
    return false;
}

/*
Si es un rey, y no hay todavía uno,
agrega la pieza y devuelve true, si no false.
*/
bool cEjercito::mAgregarRey( cPieza* p )
{
    cRey* pRey= dynamic_cast<cRey*>( p );
    if ( pRey )
    {
        if ( !piezas[4] )
        {
            piezas [4]= pRey;
            return true;
        }
        else
            return false;   //p es un rey y ya hay uno
    }
    else
        return false;
}

/*
Si es una dama, y no hay todavía una,
agrega la pieza y devuelve true, si no false.
*/
bool cEjercito::mAgregarDama(cPieza* p)
{
    cDama* pDama= dynamic_cast<cDama*>( p );
    if ( pDama )
    {
        if ( !piezas[3] )
        {
            piezas [3]= pDama;
            return true;
        }
        else
            return false;   //p es una dama y ya hay una
    }
    else
        return false;
}

/*
Si es una torre, y no hay todavía dos,
agrega la pieza y devuelve true, si no false.
*/
bool cEjercito::mAgregarTorre(cPieza* p)
{
    cTorre* pTorre= dynamic_cast<cTorre*>( p );
    if ( pTorre )
    {
        if ( !piezas[0] )
        {
            piezas [0]= pTorre;
            return true;
        }
        else
            if ( !piezas[7] )
            {
                piezas [7]= pTorre;
                return true;
            }
            return false;   //p es una torre y ya hay dos
    }
    else
        return false;
}

/*
Si es un alfil, y no hay todavía dos,
agrega la pieza y devuelve true, si no false.
*/
bool cEjercito::mAgregarAlfil(cPieza* p)
{
    cAlfil* pAlfil= dynamic_cast<cAlfil*>( p );
    if ( pAlfil )
    {
        if ( !piezas[2] )
        {
            piezas [2]= pAlfil;
            return true;
        }
        else
            if ( !piezas[5] )
            {
                piezas [5]= pAlfil;
                return true;
            }
            return false;   //p es un alfil y ya hay dos
    }
    else
        return false;
}

/*
Si es un caballo, y no hay todavía dos,
agrega la pieza y devuelve true, si no false.
*/
bool cEjercito::mAgregarCaballo(cPieza* p)
{
    cCaballo* pCaballo= dynamic_cast<cCaballo*>( p );
    if ( pCaballo )
    {
        if ( !piezas[1] )
        {
            piezas [1]= pCaballo;
            return true;
        }
        else
            if ( !piezas[6] )
            {
                piezas [6]= pCaballo;
                return true;
            }
            return false;   //p es un caballo y ya hay dos
    }
    else
        return false;
}

/*
Si es un peón, y no hay todavía ocho,
agrega la pieza y devuelve true, si no false.
*/
bool cEjercito::mAgregarPeon(cPieza* p)
{
    cPeon* pPeon= dynamic_cast<cPeon*>( p );
    if ( pPeon )
    {
        int cuenta= 7;
        while( cuenta < 15 && piezas[++cuenta] != NULL );
        if ( piezas[cuenta] != NULL )  //Si ya estaban todos los peones insertados
            return false;
        piezas[cuenta]= p;
        return true;
    }
    else
        return false;
}

cEjercito::mBuscarPieza( cPieza* p)
{
    int i;
    for ( i=0 ; i < 16 && piezas[i] != p; i++ );
    if ( piezas[i] == p )
        return i;
    return -1;
}

void cEjercito::mSerialize(ofstream& o)
{
    for ( cPieza* p= mPrimera(); p ; p= mSiguiente() )
    {
        o.write(cTablero::mCalcularCasilla( p->mObtenerPosicion() ).c_str(),2);
        string line= "=";
        line+= p->mObtenerSimbolo();
        line+= p->mObtenerColor();
        o.write(line.c_str() ,3 );
        o << endl;
    }
}
