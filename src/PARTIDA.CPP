/*
Proyecto Ajedrez
archivo: partida.cpp

contiene la implementación de la clase cPartida
*/

#include "partida.h"



cPartida::cPartida( bool conpiezas )
:mBlancas('b'),mNegras('n')
{
    mEnroqueNegroIzq=false;
    mEnroqueNegroDer=false;
    mEnroqueBlancoIzq=false;
    mEnroqueBlancoDer=false;
    msJuega= 'b';
    mpBackupPieza= NULL;
    if ( conpiezas )
    {
        mArmarBando('b');
        mArmarBando('n');
    }
}//fin Constructor por default de Partida.


void cPartida::mVaciar()
{
    mBlancas.mDesbandar();
    mNegras.mDesbandar();
    mTablero.mVaciar();
}


void cPartida::mGuardar(string filename)
{
     ofstream out(filename.c_str());
     if (!out)
     {
        cout << "No se pudo guardar la partida en el archivo: " << filename << endl;
        return;
     }
     out << msJuega << endl;
     mBlancas.mSerialize(out);
     mNegras.mSerialize(out);
     out.close();
}


/**
Agrega las piezas al atributo ejercito correspondiente y
agrega esas piezas al tablero.
**/
void cPartida::mArmarBando(char color){
    //agrego las todas piezas al ejercito.
    mObtenerEjercito(color).mArmar();
    int posInicial= 0;
    cPieza* p= mNegras.mPrimera();;
    if (color == 'b')
    {
        posInicial= 48;     //Casilla a2
        //recorre el ejercito hasta el primer peon.
        for ( p= mBlancas.mPrimera();
              p && !dynamic_cast<cPeon*>(p);
              p= mBlancas.mSiguiente() );
    }
    for (int i=0;i<8;i++)
    {
        mTablero.mPonerPieza(p,i+posInicial);
        p= mObtenerEjercito(color).mSiguiente();
    }
    posInicial+= 8;
    if (color == 'b')
        p= mBlancas.mPrimera();

    for (int i=0;i < 8; i++,p= mObtenerEjercito(color).mSiguiente() )
    {
        mTablero.mPonerPieza( p, posInicial+i );
    }
}

void cPartida::mImprimir()
{
    mTablero.mImprimir();
}

//La primera linea informa a quien le toca jugar.
// El formato de las siguientes lineas es, por ej.
// 'a1=Tb' - En la casilla a1 se encuentra la una torre blanca.
bool cPartida::mCargar( string filename )
{
	const int max_length= 6;
    ifstream in(filename.c_str());
    if (!in)
    {
        return false;
    }
	char line[max_length];
    in.getline(line,max_length);
    //Selecciona a que bando le toca mover
    msJuega= line[0];
	while ( in.getline(line,max_length)){
            cPieza* p= cEjercito::mCrearPieza(line[3],line[4],
                    cTablero::mCalcularCasilla(line[0],line[1]) );
            if ( !mObtenerEjercito(line[4]).mAgregarPieza( p ) )
            {
                cout << "oops: Error en la linea " << line << endl;
                throw;
            }
 	        mTablero.mPonerPieza(p, line[0],line[1]);
	}
  //establece las variables de control del enroque, asumiendo 
  //que no se han movido ni las torres ni los reyes. 
  //Aunque el enroque solo se podrá realizar si estas se encuentran en el lugar correcto
   mEnroqueNegroIzq=false;   
   mEnroqueNegroDer=false;
   mEnroqueBlancoIzq=false;
   mEnroqueBlancoDer=false;

   return true;
}//fin cargar partida


//Mueve a las piezas
//pre: La movida debe ser valida.
//post devuelve 1 si es jaque y 2 si es mate. 0 en otro caso
void cPartida::mMover (const string &c1, const string &c2)
{
   mnPosVieja= cTablero::mCalcularCasilla(c1);
   mnPosNueva= cTablero::mCalcularCasilla(c2);
//   int nC1=mnPosVieja;
//   int nC2=mnPosNueva;
    cPieza *p= mTablero.mSacarPieza(c1);
    //Si hayPieza(), son de distinto color, porque la mov. es valida.
    if ( mTablero.mHayPieza(c2) ) {
        cPieza *pComida= mTablero.mSacarPieza(c2);
        mObtenerEjercito( pComida->mObtenerColor() ).mSacarPieza(pComida);
        //Ahora guardo un referencia de respaldo a la pieza para
        //poder Deshacer.
        if ( mpBackupPieza )
            delete mpBackupPieza;
        mpBackupPieza= pComida;
    }
    mTablero.mPonerPieza(p,c2);
    mCoronarPeon(c2);  //Si se corono un peon, no pudo haber enroque
    mSetEnroque(c2);//establece variables de control para evitar enroque
}//fin mMover


/*
Cada llamada solo puede hacerse después de una llamada a mMover().
*/
void cPartida::mDeshacerMovida()
{
    mTablero.mPonerPieza( mTablero.mSacarPieza(mnPosNueva) ,mnPosVieja);
    mTablero.mPonerPieza(mpBackupPieza,mnPosNueva);
    //Si se comío una pieza.
    if (mpBackupPieza){
        char color= mpBackupPieza->mObtenerColor();
        mObtenerEjercito(color).mAgregarPieza(mpBackupPieza);
    }
    mpBackupPieza= NULL;
}


//Realiza los chequeos necesarios que determinan si se puede mover una pieza
//pre: c1 y c2 son casillas validas 
//post: true o false segun la movida sea valida
bool cPartida::mEsMovidaValida(const string &sC1, const string &sC2)
{
   //calcula el codigo numerico de las casillas
   int nC1= cTablero::mCalcularCasilla(sC1);
   int nC2= cTablero::mCalcularCasilla(sC2);

   if (mEsMovidaValida(nC1,nC2))  //procedimiento con enteros
   	return true;
   else
      return false;
}//fin mEsMovidaValida


//Realiza los chequeos necesarios que determinan si se puede mover una pieza
//pre: c1 y c2 son casillas validas (igualmente la clase piezas realiza una
//     validacion con mValidar
//post: true o false segun la movida sea valida
bool cPartida::mEsMovidaValida(int c1, int c2)
{
   //Si la casilla a mover no esta vacia chequea que tenga una pieza
   //de distinto color del que se va a mover.
  	if ( !mTablero.mHayPieza(c1) ||
          mTablero.mObtenerPieza(c1)->mObtenerColor() != mMueven() )
       	return false;

   bool bEsAtaque= false;  //almacena si se trata de un ataque

   //determina si es un ataque y chequea que el peon no coma para adelante
	if (mTablero.mHayPieza(c2))
	{
		char color1= mTablero.mObtenerPieza(c1)->mObtenerColor();
		char color2= mTablero.mObtenerPieza(c2)->mObtenerColor();
  		if ( color1 == color2)
	   	    return false;
        bEsAtaque= true;
        //Para que el peon no coma para adelante
        if (mTablero.mObtenerPieza(c1)->mObtenerSimbolo()=='P')
      	    if(c1==c2+8 || c2==c1+8)
	            return false;
	}

   //Chequea que el rey no capture al rey rival
   if (mTablero.mObtenerPieza(c1)->mObtenerSimbolo()=='R')
      if (mTablero.mHayPieza(c2) &&
            mTablero.mObtenerPieza(c2)->mObtenerSimbolo()=='R')
         return false;

   //determina si el camino esta bloqueado
   bool bEstaBloqueada= mHayBloqueo(c1,c2);

  //si se trata de un rey que se quiere mover dos posiciones se chequea enroque
  if( mTablero.mObtenerPieza(c1)->mObtenerSimbolo()=='R' && abs(c2-c1)==2 )
      if(!mEnroque(c2))
         return false;
      else
         return true;

   //pregunta a la pieza si la movida es valida
   if ( mTablero.mObtenerPieza(c1)->
       mEsMovidaValida(c1,c2,bEstaBloqueada,bEsAtaque) )
         return true;



  return false; //caso por defecto
}
//fin mEsMovidaValida


bool cPartida::mChequear(int n1,int n2, int nIncremento)
//realiza un chequeo desde mnPosicion hasta nPosicion. Y nIncremento indicará
//si buscará en la misma columna(hor o ver) o diagonal(izq o der)
{

   //chequeo para columnas y diagonales
 for(int i=1;i<8;i++)
 { if (n1<n2)
    {if (n1+(nIncremento*i) < n2)
       if (mTablero.mObtenerPieza(n1+(nIncremento*i)) != NULL)
          return true;
     }
   if (n2<n1)
    {if (n2+(nIncremento*i) < n1)
       if (mTablero.mObtenerPieza(n2+(nIncremento*i)) != NULL)
          return true;
    }
  }
    return false;  //caso por defecto
}  //fin cPartida::mChequear


//pre casillas validas (de 0 a 63)
//post devuelve true si hay una pieza entre el camino de otras dos.
bool cPartida::mHayBloqueo(int nC1, int nC2)
{
    //se suma 1 dada las diferente implementacion del vector de casillas (1a64)
    //que hacen la pieza y el tablero

  if (!cPieza::mValidar(nC1,nC2) )
		return false;
  //busca si las posiciones corresponden a la misma diagonal o columna
  if (cPieza::mEsMismaLinea(nC1, nC2,1) == true) //col. hor.
	 if (mChequear(nC1,nC2,1)==true)
           return true;

  if (cPieza::mEsMismaLinea(nC1, nC2,7) == true) //diag izq
	 if (mChequear(nC1,nC2,7)==true)
           return true;

  if (cPieza::mEsMismaLinea(nC1, nC2,8) == true) //col vert
	 if (mChequear(nC1,nC2,8)==true)
      return true;
  if (cPieza::mEsMismaLinea(nC1, nC2,9) == true) //diag der
	 if (mChequear(nC1,nC2,9)==true)
             return true;

  return false; //caso por defecto
}//fin mHayBloqueo


/*
Se debe llarmar si HayJaque().
Evalúa y devuelve si ninguna movida válida saca al ejercito de Jaque.
*/
bool cPartida::mHayMate()
{
    cEjercito e= mObtenerEjercitoActivo();
    for ( cPieza* p= e.mPrimera(); p ; p= e.mSiguiente() )
    {
        int nLong;
        int* posiciones;
        p->mCalcularMovidasValidas(posiciones,nLong);
        for (int i= 0; i < nLong ; i++)
        {
            string c1= cTablero::mCalcularCasilla(p->mObtenerPosicion());
            string c2= cTablero::mCalcularCasilla(posiciones[i]);
            if ( mEsMovidaValida(p->mObtenerPosicion(),posiciones[i]) &&
                !mEstaClavado(c1,c2) )
                return false;
        }
        delete[] posiciones;
    }
    return true;
}


//al coronar un peón, el usuario elige en que pieza se convertirá
char cPartida::mElegir()
{
  char sOpcion;
  do
  {
   cout <<"                                                                                    ";

   gotoxy(1,23);
   cout <<"\nIngrese la pieza a coronar D (dama), T (torre), C (caballo), A (alfil)): ";
   cin >> sOpcion;
   sOpcion=Mayuscula(sOpcion);
  }while (sOpcion!='D' && sOpcion!='T' && sOpcion!='A' && sOpcion!='C');

  return sOpcion;
}//fin mElegir


bool cPartida::mCoronarPeon(const string &cFinal)
{
    int casilla= cTablero::mCalcularCasilla(cFinal);

    if ( mTablero.mObtenerPieza(casilla)->mObtenerSimbolo() == 'P' )
        if ( (msJuega=='b' && casilla >= 0 && casilla <= 7)
        || (msJuega=='n' && casilla >= 56 && casilla <= 63) )
        {
            cPieza* aux= mTablero.mObtenerPieza(casilla);
            char color= aux->mObtenerColor();
            int pos= mObtenerEjercitoActivo().mBuscarPieza(aux);

            char sPieza=mElegir();
            cPieza* p= cEjercito::mCrearPieza(sPieza,color,casilla);
            mObtenerEjercitoActivo().mPonerPieza( p, pos);
            mTablero.mPonerPieza( p, casilla);

         /*
            cDama* d= new cDama( color, casilla );
            mObtenerEjercitoActivo().mPonerPieza( d, pos);
            mTablero.mPonerPieza( d, casilla);
          */
            delete aux;
            return true;
        }
    return false;
}


//Función que verifica que la pieza no este clavada
//o sea que el bando propio no quede en jaque al moverse la pieza especificada
//pre: sC1 y sC2 son movimientos valido dentro del tablero
//post: true o false según si la pieza a mover está clavada
bool cPartida::mEstaClavado (const string &sC1, const string &sC2)
{
    mMover(sC1,sC2);
    if (mHayJaque() )
     {mDeshacerMovida();
      return true;
      }
    mDeshacerMovida();
    return false;
}//fin mEstaClavado


bool cPartida::mHayJaque()
{
    char colorActivo = msJuega;
    cEjercito e= mObtenerEjercito( mContrario(colorActivo) );
    //Activo al contrario para simular un ataque.
    mSiguienteMovida();
    for ( cPieza* p= e.mPrimera(); p ; p= e.mSiguiente() )
    {
        int posReyActivo= mObtenerEjercito(colorActivo).mObtenerRey()->mObtenerPosicion();
        //Si atacan al rey.
        if ( mEsMovidaValida(p->mObtenerPosicion(), posReyActivo)  )
        {
            mSiguienteMovida(colorActivo);
            return true;
        }
    }
    mSiguienteMovida(colorActivo);
    return false;
}


//Establece las variables que controlan el movimiento de torre y rey
//que evitan el enroque
void cPartida::mSetEnroque(string sC1)
{
   int nC1= cTablero::mCalcularCasilla(sC1);
   char cpieza=mTablero.mObtenerPieza(nC1)->mObtenerSimbolo();

    if (cpieza=='R')
      if (msJuega=='b')
       {mEnroqueBlancoIzq=true;
        mEnroqueBlancoDer=true;
        }

    if (cpieza=='R')
      if (msJuega=='n')
       {mEnroqueNegroIzq=true;
        mEnroqueNegroDer=true;
        }

    if (cpieza=='T')
      if (msJuega=='n')
      {
        if (nC1==0)
         mEnroqueNegroIzq=true;
        if (nC1==7)
         mEnroqueNegroDer=true;
       }

    if (cpieza=='T')
      if (msJuega=='b')
      {
        if (nC1==56)
         mEnroqueBlancoIzq=true;
        if (nC1==63)
         mEnroqueBlancoDer=true;
       }

}//fin mSetEnroque()


//chequea a través del color activo y el lado sobre el cual se hace el enroque
//si este es o no valido
bool cPartida::mEnroqueNoValido(char sColor, char sLado)
{

 if (sColor=='b')
  if (sLado=='d')
   if (mEnroqueBlancoDer)
       return true;

 if (sColor=='b')
  if (sLado=='i')
   if (mEnroqueBlancoIzq)
       return true;

 if (sColor=='n')
  if (sLado=='d')
   if (mEnroqueNegroDer)
       return true;

 if (sColor=='n')
  if (sLado=='i')
   if (mEnroqueNegroIzq)
       return true;

 return false;
}//fin mEnroqueNoValido


bool cPartida::mEnroque(int nDestino)
{
  char sColor=msJuega;  //color activo
  int nRey = mObtenerEjercitoActivo().mObtenerRey()->mObtenerPosicion();
  int nPos1; //correcta ubicación del rey. Puede no ser la real
  int nPos2; //correcta ubicación de la torre. Puede no ser la real
  int nCelda1; //celda 1 intermedia del movimento del rey
  int nCelda2; //celda 2 intermedia del movimento del rey

  if ( mHayJaque() )   //no se puede enrocar si se está en jaque
    return false;

  char lado;
  if (nDestino-nRey==2)        //enroque a la derecha
      {lado='d';
       if (sColor=='b')
         {nPos1=60;
          nCelda1=61;
          nCelda2=62;
          nPos2=63;
          }
       if (sColor=='n')
         {nPos1=4;
          nCelda1=5;
          nCelda2=6;
          nPos2=7;
          }
      }
  if (nDestino-nRey==-2)
      {lado='i';
       if (sColor=='b')
         {nPos1=60;
          nCelda1=59;
          nCelda2=58;
          nPos2=56;
          }
       if (sColor=='n')
         {nPos1=4;
          nCelda1=3;
          nCelda2=2;
          nPos2=0;
          }
      }

  string sPos1= cTablero::mCalcularCasilla(nPos1);    //posicion correcta rey
  string sPos2= cTablero::mCalcularCasilla(nPos2);  //posicion correcta torre
  string sCelda1= cTablero::mCalcularCasilla(nCelda1);  //celda intermedia 1 rey
  string sCelda2= cTablero::mCalcularCasilla(nCelda2);  //celda intermedia 2 rey

  //chequear que se cumplan todas las condiciones para el enroque
  if (mTablero.mObtenerPieza(nPos1) != NULL )   //casilla del rey no vacia
   if (mTablero.mObtenerPieza(nPos2) != NULL )  //casilla de la torre no vacia
    if (mTablero.mObtenerPieza(nPos1)->mObtenerColor()==sColor) //color correcto casilla rey
     if (mTablero.mObtenerPieza(nPos2)->mObtenerColor()==sColor)//color correcto casilla torre
      if (mTablero.mObtenerPieza(nPos1)->mObtenerSimbolo()=='R') //rey en la casilla rey
       if (mTablero.mObtenerPieza(nPos2)->mObtenerSimbolo()=='T') //torre en la casilla torre
        if (!mEnroqueNoValido(sColor,lado))   //no se han movido rey y torre correcta
          if (!mEstaClavado(sPos1,sCelda1))  //el rey no queda en jaque al mover a la casilla 1
           if (!mEstaClavado(sPos1,sCelda2)) //el rey no queda en jaque al mover a la casilla 2
            if (!mHayBloqueo(nPos1,nPos2))   //no hay piezas entremedio del rey y torre
             {mMover(sPos2,sCelda1); //mover la torre
              return true;
              }
   return false;  //caso por defecto, si no se cumplen todos los chequeos
}
