/*
Proyecto Ajedrez
archivo: ejercito.h
Grupo 14 -Deccico/Fontdevila  ayudante JAvier MAcchi
contiene la implementación de la clase cEjercito
*/


//---------------------------------------------------------------------------
#ifndef _EJERCITO_H
#define _EJERCITO_H


#include <fstream>
#include "tablero.h"

class cEjercito
{
protected:
	char mColor;

    int actual;

    cPieza* piezas[16];

	cPieza *mSeleccionar();

    bool mAgregarRey(cPieza*);
    bool mAgregarDama(cPieza*);
    bool mAgregarAlfil(cPieza*);
    bool mAgregarCaballo(cPieza*);
    bool mAgregarTorre(cPieza*);
    bool mAgregarPeon(cPieza*);

public:

	cEjercito(char color);

    //Construye y agrega todas las piezas de un ejercito completo
    void mArmar();

    /*
    Elimina todas sus referencias a pieza. No destruye las piezas.
    Equivale a sacar todas las piezas.
    Ver mSacarPieza().
    */
    void mDesbandar();

    bool mAgregarPieza(cPieza*);

    //Busca la pieza y pone esa pos. en NULL.
    void mSacarPieza(cPieza*);

	static cPieza* mCrearPieza(char simbolo,char color, int pos);

	cRey* mObtenerRey()
	{
		return dynamic_cast<cRey*>(piezas[4]);
	}

	cPieza* mPrimera();

    cPieza* mSiguiente();

    cPieza* mPonerPieza( cPieza* p, int i ) { piezas[i]= p;}

    //Devuelve la pos. de la pieza, -1 si no la encuentra.
    int mBuscarPieza( cPieza* p );

    //Envía al fstream o una línea por cada pieza, con el sig. formato:
    // a1=Tb donde a1 es la pos. de una Torre blanca.
    void cEjercito::mSerialize(ofstream& o);
};
#endif
