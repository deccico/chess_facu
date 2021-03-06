//Proyecto Ajedrez
//Grupo 14 Deccico-Fontdevila
//archivo: pieza.cpp

//#include "str.h"
//#include "pieza.h"


unit cPieza;

interface
//protected:
 var
   msColor: char;
   msSimbolo: char;
   mnPos: int;
   void mGenerarLineaMovidas(int* &, int, int, int &);

public:
//chequea que se trate de misma linea hor, ver o diagonal seg?n el tercer int
   static bool mEsMismaLinea(int,int,int);
 //validaciones comunes antes de validar una movida
   static bool mValidar(int,int) ;

   cPieza (char sColor)
   begin
      msColor= sColor;
      mnPos= 0;
   end

   cPieza(char sColor, int npos)
     begin
        msColor= sColor;
        mnPos= npos;
     end

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
begin
public:
   //constructor
   cRey::cRey(char sColor):cPieza(sColor) {msSimbolo='R';}
   cRey::cRey(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='R';}
   virtual ~cRey(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
end;

//pieza Dama
class cDama: public cPieza
begin
public:
   //constructor
   cDama::cDama(char sColor):cPieza(sColor) {msSimbolo='D';}
   cDama::cDama(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='D';}
   virtual ~cDama(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
end;

//pieza Alfil
class cAlfil: public cPieza
begin
public:
   //constructor
   cAlfil::cAlfil(char sColor):cPieza(sColor) {msSimbolo='A';}
   cAlfil::cAlfil(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='A';}
   virtual ~cAlfil(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
end;

//pieza Caballo
class cCaballo: public cPieza
begin
public:
   //constructor
   cCaballo::cCaballo(char sColor):cPieza(sColor) {msSimbolo='C';}
   cCaballo::cCaballo(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='C';}
   virtual ~cCaballo(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
end;

//pieza Caballo
class cTorre: public cPieza
begin
public:
   //constructor
   cTorre::cTorre(char sColor):cPieza(sColor) {msSimbolo='T';}
   cTorre::cTorre(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='T';}
   virtual ~cTorre(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
end;

//pieza Peon
class cPeon: public cPieza
begin
public:
   //bool mEsMovidaValida(int,int) const;
   //constructor
   cPeon::cPeon(char sColor):cPieza(sColor) {msSimbolo='P';}
   cPeon::cPeon(char sColor,int pos):cPieza(sColor,pos) {msSimbolo='P';}
   virtual ~cPeon(){}
   bool mEsMovidaValida(int,int,bool,bool) const;
   bool mEsMovidaValidaColor(int,int,bool,bool) const;
   void mCalcularMovidasValidas(int * &, int &, char);
end;


implementation
//definicion de los m?todos declarados en pieza.h


bool cPieza::mValidar(int mnPosicion,int nPosicion)
//Realiza varios chequeos antes de intentar cualquier moviento
begin
  if ((nPosicion < 0) || (nPosicion > 63) || (nPosicion < 0) || (nPosicion > 63)
  || (mnPosicion < 0)||(mnPosicion > 63)||(mnPosicion < 0)||(mnPosicion > 63)) then
	return false;

  //verifica que no sea la misma posicion
  if (mnPosicion == nPosicion) then
	return false;

  return true; //opci?n por defecto

end//fin cPieza::MValidar


//chequea que se trate de misma linea horizontal, vertical
//o diagonal izquierda o derecha seg?n el tercer integer pasado
//Pre: nPos1 y nPos 2 son n?meros del 0 al 63
//Pos: true or false seg?n corresponda
bool cPieza::mEsMismaLinea(int nPos1,int nPos2,int nIncremento)
begin
  //si el incremento es de 1, verifica que ambas posiciones
  //esten en la misma columna
  if (nIncremento==1 && abs(nPos2-nPos1)<8) then
  begin
    int n1=nPos1,n2=nPos2;
    if (n1 >=0 && n1 <= 7 && n2 >=0 && n2 <= 7) then
      return true;
    if (n1 >=8 && n1 <= 15 && n2 >=8 && n2 <= 15) then
      return true;
    if (n1 >=16 && n1 <= 23 && n2 >=16 && n2 <= 23) then
      return true;
    if (n1 >=24 && n1 <= 31 && n2 >=24 && n2 <= 31) then
      return true;
    if (n1 >=32 && n1 <= 39 && n2 >=32 && n2 <= 39) then
      return true;
    if (n1 >=40 && n1 <= 47 && n2 >=40 && n2 <= 47) then
      return true;
    if (n1 >=48 && n1 <= 55 && n2 >=48 && n2 <= 55) then
      return true;
    if (n1 >=56 && n1 <= 63 && n2 >=56 && n2 <= 63) then
      return true;
    return false;  // si ambas posiciones no estaban en la misma fila
    end

  int nSearch,nSearch1,nSearch2; //casillas sobre la cuales se realizar? la busqueda

  //chequeo para columna vertical y diagonales
  case nIncremento of
    8: //columna vertical
            for (int i=0; i<8; i++)
             begin
               nSearch1=nPos1+nIncremento*i;
               nSearch2=nPos2+nIncremento*i;
               if ( nSearch1==nPos2 || nSearch2==nPos1 )
                 return true;
             end
            break;

    else //diagonales (nincremento 7 o 9)
             if (! ( (mEsMismaLinea(nPos1,0,8) && nIncremento==7)
             || (mEsMismaLinea(nPos1,7,8) && nIncremento==9) ) ) then
                 for (int i=0; i<8; i++)
                 {  nSearch=nPos1+nIncremento*i;
                    if ( nSearch==nPos2 )
                      return true;
                    if ( ( mEsMismaLinea(nSearch,0,8) && nIncremento==7)
                    || ( mEsMismaLinea(nSearch,7,8) && nIncremento==9) )
                         break;
                 }

            if (! ( (mEsMismaLinea(nPos2,0,8) && nIncremento==7)
            || (mEsMismaLinea(nPos2,7,8) && nIncremento==9) ) ) then
                for (int i=0; i<8; i++)
                begin
                   nSearch=nPos2+nIncremento*i;
                   if ( nSearch==nPos1 )
                     return true;
                   if ( ( mEsMismaLinea(nSearch,0,8) && nIncremento==7)
                   || ( mEsMismaLinea(nSearch,7,8) && nIncremento==9) ) then
                        break;
                end
            break;
  end //fin case

  return false;  //caso por defecto, en caso de no encontrar true

end //fin cPieza::EsMismaLinea


void cPieza::mGenerarLineaMovidas(int* &rnVec, int nPos, int nIncremento, int &nLong)
//devuelve movidas para la linea especificada;
begin
  //si el incremento es de 1, recorre la horizontal indicada
  if (nIncremento==1) then
  begin
    int n1=nPos,ndesde,nhasta;
    if (n1 >=0 && n1 <= 7) then
    {ndesde=0;nhasta=7;}
    else if (n1 >=8 && n1 <= 15) then
    {ndesde=8;nhasta=15;}
    else if (n1 >=16 && n1 <= 23) then
    {ndesde=16;nhasta=23;}
    else if (n1 >=24 && n1 <= 31) then
    {ndesde=24;nhasta=31;}
    else if (n1 >=32 && n1 <= 39) then
    {ndesde=32;nhasta=39;}
    else if (n1 >=40 && n1 <= 47) then
    {ndesde=40;nhasta=47;}
    else if (n1 >=48 && n1 <= 55) then
    {ndesde=48;nhasta=55;}
    else if (n1 >=56 && n1 <= 63) then
    {ndesde=56;nhasta=63;}

    for (int i=ndesde,j=0; i <= nhasta; i++)
       if (i != n1) then
         begin
          rnVec[j]= i;
           j++;
         end

    nLong=7;
    return;
  end   //fin nIncremento = 1


  var:
  i=nLong, n :int ;

  if (! ( (mEsMismaLinea(nPos,0,8) && nIncremento==7)
       || (mEsMismaLinea(nPos,7,8) && nIncremento==9) ) ) then
  begin
    for (n=1; n < 8; n++)
    begin
       int nSearch=nPos+nIncremento*n;  //casilla a analizar. Posiblemente jugada valida.
       if (nSearch >63 || nSearch < 0) then
           break;
       rnVec[i]= nPos+nIncremento*n;
       i++;

       if ( (mEsMismaLinea(nSearch,0,8) && nIncremento==7)
       || (mEsMismaLinea(nSearch,7,8) && nIncremento==9) ) then
         break;
    end
    nLong=i;
  end

  i=nLong;

  if (! ( (mEsMismaLinea(nPos,0,8) && nIncremento==9)
       || (mEsMismaLinea(nPos,7,8) && nIncremento==7) ) ) then
  begin
    for (n=1; n < 8; n++)
    begin
       int nSearch=nPos-nIncremento*n;  //casilla a analizar. Posiblemente jugada valida.
       if (nSearch >63 || nSearch <0) then
           break;
       rnVec[i]= nSearch;
       i++;

       if ( (mEsMismaLinea(nSearch,0,8) && nIncremento==9)
       || (mEsMismaLinea(nSearch,7,8) && nIncremento==7) ) then
         break;
    end
    nLong=i;
  end

end //fin GenerarLineaMovidas


void cPieza::mCalcularMovidasRCP(int* &rnMovidas,int nPos,int &rnLong,char sPieza)
//devuelve un array con todos las movidas posibles para un Rey-Caballo-Peon
//pre nDesde y nHasta son casillas validas y nDesde < nHasta
//post referencia al array deseado
var
  i,j,nDesde,nHasta:int;
begin
  int nMovidas[20];

   //movidas del caballo
  nMovidas[0]=nPos-10;
  nMovidas[1]=nPos+6;
  nMovidas[2]=nPos-17;
  nMovidas[3]=nPos+15;
  nMovidas[4]=nPos-15;
  nMovidas[5]=nPos+17;
  nMovidas[6]=nPos-6;
  nMovidas[7]=nPos+10;

   //movidas de rey
  nMovidas[8]=nPos-9;
  nMovidas[9]=nPos-1;
  nMovidas[10]=nPos+7;
  nMovidas[11]=nPos-8;
  nMovidas[12]=nPos+8;
  nMovidas[13]=nPos-7;
  nMovidas[14]=nPos+1;
  nMovidas[15]=nPos+9;

   //movidas de pe?n negro
  nMovidas[16]=nPos+7;
  nMovidas[17]=nPos+9;

   //movidas de pe?n blanco
  nMovidas[18]=nPos-9;
  nMovidas[19]=nPos-7;


  case sPieza of//analiza a cada pieza, chequea que las movidas sean consecutivas
      'C'://caballo.
                nDesde=0;
                nHasta=7;     //chequeo de borde izquierdo
               if (mEsMismaLinea(nPos,0,8))
                nDesde=4;
               if (mEsMismaLinea(nPos,1,8))
                nDesde=2;
               if (mEsMismaLinea(nPos,7,8))
                nHasta=3;
               if (mEsMismaLinea(nPos,6,8))
                nHasta=5;
               break;
      'R'://rey
               nDesde=8;
               nHasta=15;
               if (mEsMismaLinea(nPos,0,8))   //chequeo de borde izquierdo
                 nDesde=11;
               if (mEsMismaLinea(nPos,7,8))   //chequeo de borde derecho
                 nHasta=12;
               break;
      'n':nDesde=16;
               nHasta=17;
               if (mEsMismaLinea(nPos,0,8))   //chequeo de borde izquierdo
                 nDesde=17;
               if (mEsMismaLinea(nPos,7,8))   //chequeo de borde derecho
                 nHasta=16;
               break;
      'b':nDesde=18;
               nHasta=19;
               if (mEsMismaLinea(nPos,0,8))   //chequeo de borde izquierdo
                 nDesde=19;
               if (mEsMismaLinea(nPos,7,8))   //chequeo de borde derecho
                 nHasta=18;
               break;
      else  //caso por defecto
               nDesde=0;
               nHasta=15;
               break;
   end



  //recorre el vector de movidas posibles, para controlar la
  //cantidad de valores validos y determinar la longitud de rnMovidas
  for (i=nDesde,j=0; i<=nHasta; i++)
      if (nMovidas[i] <64 && nMovidas[i] >=0) then
          j++;


  rnLong=j;  //longitud del vector de movidas validas
  rnMovidas = new int[rnLong];

  //recorre el vector de movidas posibles, para controlar la
  //cantidad de valores validos y determinar la longitud de rnMovidas
  for (i=nDesde,j=0; i<=nHasta; i++)
      if (nMovidas[i] <64 && nMovidas[i] >=0) then
          begin
           rnMovidas[j]=nMovidas[i];
           j++;
          end

end //fin CalcularMovidasValidasRCP


//devuelve true o false si la movida es valida para la pieza especificada
//pre: nPos es la posicion de la pieza y sPieza es su simbolo
//post: true o false seg?n sea movida v?lida o no
bool cPieza::mEsMovidaValidaRCP(int mnPosicion, int nPos, char sPieza) const
 var
  i,j,nDesde,nHasta:int;
  int nMovidas[20];

begin
   //movidas del caballo
  nMovidas[0]=mnPosicion-10;
  nMovidas[1]=mnPosicion+6;
  nMovidas[2]=mnPosicion-17;
  nMovidas[3]=mnPosicion+15;
  nMovidas[4]=mnPosicion-15;
  nMovidas[5]=mnPosicion+17;
  nMovidas[6]=mnPosicion-6;
  nMovidas[7]=mnPosicion+10;

   //movidas de rey
  nMovidas[8]=mnPosicion-9;
  nMovidas[9]=mnPosicion-1;
  nMovidas[10]=mnPosicion+7;
  nMovidas[11]=mnPosicion-8;
  nMovidas[12]=mnPosicion+8;
  nMovidas[13]=mnPosicion-7;
  nMovidas[14]=mnPosicion+1;
  nMovidas[15]=mnPosicion+9;
                         //segmento de peones en desuso,
   //movidas de pe?n negro
  nMovidas[16]=mnPosicion+7;
  nMovidas[17]=mnPosicion+9;

   //movidas de pe?n blanco
  nMovidas[18]=mnPosicion-9;
  nMovidas[19]=mnPosicion-7;

  case sPieza of //analiza a cada pieza, chequea que las movidas sean consecutivas
      'C'://caballo.
                nDesde=0;
                nHasta=7;     //chequeo de borde izquierdo
               if (mEsMismaLinea(mnPosicion,0,8))
                nDesde=4;
               if (mEsMismaLinea(mnPosicion,1,8))
                nDesde=2;
               if (mEsMismaLinea(mnPosicion,7,8))
                nHasta=3;
               if (mEsMismaLinea(mnPosicion,6,8))
                nHasta=5;
               break;
      'R'://rey
               nDesde=8;
               nHasta=15;
               if (mEsMismaLinea(mnPosicion,0,8))   //chequeo de borde izquierdo
                 nDesde=11;
               if (mEsMismaLinea(mnPosicion,7,8))   //chequeo de borde derecho
                 nHasta=12;
               break;
      'n':nDesde=16;
               nHasta=17;
               if (mEsMismaLinea(mnPosicion,0,8))   //chequeo de borde izquierdo
                 nDesde=17;
               if (mEsMismaLinea(mnPosicion,7,8))   //chequeo de borde derecho
                 nHasta=16;
               break;
      'b':nDesde=18;
               nHasta=19;
               if (mEsMismaLinea(mnPosicion,0,8))   //chequeo de borde izquierdo
                 nDesde=19;
               if (mEsMismaLinea(mnPosicion,7,8))   //chequeo de borde derecho
                 nHasta=18;
               break;
      else  //por defecto
               nDesde=0;
               nHasta=15;
               break;
   end


  //recorre el vector de movidas posibles, para controlar la
  //cantidad de valores validos y determinar la longitud de rnMovidas
  for (i=nDesde,j=0; i<=nHasta; i++)
      if (nMovidas[i] <64 && nMovidas[i] >=0) then
         if (nPos==nMovidas[i]) then
            return true;

  return false; //caso por defecto
end//fin CalcularMovidasValidasRCP



bool cRey::mEsMovidaValida(int mnPosicion, int nPosicion, bool ocupado, bool ataca) const
//Pre:Posicion=Coordenada valida del tablero
//Post:Devuelve true o false segun la movida sea o no valida
begin
  if (mValidar(mnPosicion,nPosicion)==false) then  //validaci?n inicial
    return false;

  if (mEsMovidaValidaRCP(mnPosicion,nPosicion, msSimbolo) )then
     return true;
  else
     return false;

end //fin cRey::EsMovidaValida


void cRey::mCalcularMovidasValidas(int* &nMovidas, int &nLong, char sCPeon)
//devuelve una referencia con una lista de movidas validas de la pieza
//y la longitud
begin
  mCalcularMovidasRCP(nMovidas, mnPos, nLong, 'R');
end


bool cDama::mEsMovidaValida(int mnPosicion,int nPosicion,
                            bool ocupado, bool ataca) const
//Pre:Posicion=Coordenada valida del tablero
//Post:Devuelve true o false segun la movida sea o no valida
begin
  if (ocupado) then return false;
  if (!mValidar(mnPosicion,nPosicion)) then  //validaci?n inicial
	return false;

  //busca si las posiciones corresponden a la misma diagonal o columna
  if (mEsMismaLinea(mnPosicion, nPosicion,1)) then //columna horizontal
	return true;
  if (mEsMismaLinea(mnPosicion, nPosicion,7)) then //diagonal izquierda
	return true;
  if (mEsMismaLinea(mnPosicion, nPosicion,8)) then //columna vertical
	return true;
  if (mEsMismaLinea(mnPosicion, nPosicion,9)) then //diagonal derecha
	return true;

  return false;  //si no encuentra la casilla en ninguna columna o diagonal
end //fin cDama::mEsMovidaValida(int nPosicion)


void cDama::mCalcularMovidasValidas(int* &nMovidas, int &nLong, char sCPeon)
//devuelve una referencia con una lista de movidas validas de la pieza
//y la longitud
begin
  nMovidas = new int[28];
  mGenerarLineaMovidas(nMovidas, mnPos, 1, nLong);
  mGenerarLineaMovidas(nMovidas, mnPos, 7, nLong);
  mGenerarLineaMovidas(nMovidas, mnPos, 8, nLong);
  mGenerarLineaMovidas(nMovidas, mnPos, 9, nLong);
end



bool cTorre::mEsMovidaValida(int mnPosicion,int nPosicion,
                             bool ocupado, bool ataca) const
//Pre:Posicion=Coordenada valida del tablero
//Post:Devuelve true o false segun la movida sea o no valida
begin
  if (ocupado==true) then return false;
  if ( !mValidar(mnPosicion,nPosicion) ) then  //validaci?n inicial
	return false;

  //busca si las posiciones corresponden a la misma columna hor. o vert.
  if ( mEsMismaLinea(mnPosicion, nPosicion,1) ) then//columna horizontal
	return true;
  if ( mEsMismaLinea(mnPosicion, nPosicion,8) ) then//columna vertical
	return true;

  return false;  //si no encuentra la casilla en ninguna columna o diagonal
end //fin cTorre::mEsMovidaValida(int nPosicion)


void cTorre::mCalcularMovidasValidas(int* &nMovidas, int &nLong,char sCPeon)
//devuelve una referencia con una lista de movidas validas de la pieza
//y la longitud
begin
  nMovidas = new int[16];
  mGenerarLineaMovidas(nMovidas, mnPos, 1, nLong);
  mGenerarLineaMovidas(nMovidas, mnPos, 8, nLong);
end


bool cAlfil::mEsMovidaValida(int mnPosicion,int nPosicion,
                             bool ocupado, bool ataca) const
//Pre:Posicion=Coordenada valida del tablero
//Post:Devuelve true o false segun la movida sea o no valida
begin
  if (ocupado) then return false;
  if (!mValidar(mnPosicion,nPosicion)) then  //validaci?n inicial
	return false;

  //busca si las posiciones corresponden a la misma diagonal derecha o izquierda
  if (mEsMismaLinea(mnPosicion, nPosicion,7)) then //diagonal  izquierda
	return true;
  if (mEsMismaLinea(mnPosicion, nPosicion,9)) then //diagonal derecha
	return true;

  return false;  //si no encuentra la casilla en ninguna columna o diagonal
end //fin cAlfil::mEsMovidaValida


void cAlfil::mCalcularMovidasValidas(int* &nMovidas, int &nLong,char sCPeon)
//devuelve una referencia con una lista de movidas validas de la pieza
//y la longitud
begin
  nMovidas = new int[16];
  nLong=0;
  mGenerarLineaMovidas(nMovidas, mnPos, 7, nLong);
  mGenerarLineaMovidas(nMovidas, mnPos, 9, nLong);
end



bool cCaballo::mEsMovidaValida(int mnPosicion,int nPosicion,
                               bool ocupado, bool ataca) const
//Pre:Posicion=Coordenada valida del tablero
//Post:Devuelve true o false segun la movida sea o no valida
begin
  if ( !mValidar(mnPosicion,nPosicion) ) then  //validaci?n inicial
	return false;

  if (mEsMovidaValidaRCP(mnPosicion,nPosicion, msSimbolo) ) then
     return true;
  else
     return false;

end//fin cCaballo:mEsMovidaValida


void cCaballo::mCalcularMovidasValidas(int* &nMovidas,int &nLong,char sCPeon)
//devuelve una referencia con una lista de movidas validas de la pieza
//y la longitud
begin
   mCalcularMovidasRCP(nMovidas, mnPos, nLong, 'C');
end


bool cPeon::mEsMovidaValida(int mnPosicion,int nPosicion,
                            bool ocupado, bool ataca) const
begin
    if ( msColor == 'n' ) then
        return mEsMovidaValidaColor(mnPosicion,nPosicion,ocupado,ataca);
    else
        //Invierto mnPosicion y nPosicion para cambiar la dir.
        return mEsMovidaValidaColor(nPosicion,mnPosicion,ocupado,ataca);
end


bool cPeon::mEsMovidaValidaColor(int mnPosicion,int nPosicion,
                            bool ocupado, bool ataca) const
//Pre:Posicion=Coordenada valida del tablero
//Post:Devuelve true o false segun la movida sea o no valida
begin
  if ( !mValidar(mnPosicion,nPosicion) ) then  //validaci?n inicial
	return false;

  //chequea que la posicion dada coincida con una de las casillas
  //a la que puede moverse, dada su condici?n de pe?n.

  if ( nPosicion == mnPosicion + 8 ) then//chequea que sea la casilla de delante
        return true;

  //caso de movida inicial, dos pasos
  if ( (7 < mnPosicion && mnPosicion < 16 ||
         47 < nPosicion && nPosicion < 56) &&
         nPosicion == mnPosicion + 16 ) then
       return true;

  //cheque del borde del tablero
  if ( mEsMismaLinea(mnPosicion,0,8) && nPosicion==mnPosicion+7
  || mEsMismaLinea(mnPosicion,7,8) && nPosicion==mnPosicion+9 ) then
         return false;

  if (ataca) then    //chequea que el pe?n ataque a una pieza contraria
   if ( nPosicion==(mnPosicion+7) || nPosicion==(mnPosicion+9) ) then
    return true;

  return false;      //si no se cumple ninguna de las anteriores

end //fin cPe?n::mEsMovidaValidaColor


void cPeon::mCalcularMovidasValidas(int* &nMovidas, int &nLong,char sCPeon)
//devuelve una referencia con una lista de movidas validas de la pieza
//y la longitud

begin
  //sCPeon es el color del peon. Se trata de un caso especial pues
  //captura a las piezas de modo diferente
   mCalcularMovidasRCP(nMovidas, mnPos, nLong, msColor);
end


(*             //   m?dulos impulsores
void main()
{
 int *Movidas,Longitud,posi;
 cPieza *p = new cDama('b',32);

 do
 {
   p->mCalcularMovidasValidas(Movidas,Longitud);
   cout << "La posicion es: " << p->mObtenerPosicion() << endl;
   cout << "La longitud es: " << Longitud << endl;
   cout << "La pieza es: " <<  p->mObtenerSimbolo()<< endl<<endl;

   for(int i=0,j=0;i<Longitud;i++,j++)
   {cout <<"Movida "<< i <<" "<<Movidas[i] <<endl;
    if (j > 18)
      { j=0;pausa(" ");}
   }
   cout <<"\n Pone una posicion: ";
   cin >> posi;
   p->mPonerPosicion(posi);
 }while (posi<=63 && posi >= 0);

}



main()
{
 int i,j;
 cPieza *p = new cPeon('b',10);

 do{
 cout << "\nLa pieza es: " <<  p->mObtenerSimbolo()<< endl;
 cout << "Ingres? tus horribles valores i,j\n";
 cin >> i;
 cin >> j;
 if (p->mEsMovidaValida(i,j,false,true)==true)
   cout << "trueismo";
 else cout << "faksseimo";
 }while (i!=100);
}

*)




end.
