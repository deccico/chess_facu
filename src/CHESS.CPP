//Programa Ajedrez
//Archivo: ajedrez.cpp   (archivo principal)
/**********************************************************************
Materia: Algoritmos y Programaci¢n III   7507  curso 003
Profesor: Carlos Fontela
Ayudante: Sergio Pap

Trabajo Pr ctico:
	Implementaci¢n de Ajedrez: Jaque al Rey

Archivo: chess.cpp

Grupo:14   Fontdevila Diego 74169  dfontde@fi.uba.ar
   	Deccico Adrián   75223  deccico@geocities.com

Descripci¢n:
	El trabajo tiene por finalidad la implementación de una
	aplicaci¢n que permita a dos jugadores jugar interactivamente al
	ajedrez contra la computadora. La computadora realizar  la
	supervisi¢n de la partida, convalidar  las jugadas de cada jugador
	y permitir  administrar las partidas.

Entorno: Builder C++ 3.0

Segunda Entrega - (Implemetación de Jaque, Mate, Coronación y enroque)
*******************************************************************/
#pragma hdrstop
#include <condefs.h>


//---------------------------------------------------------------------------
USEUNIT("tablero.cpp");
USEUNIT("ejercito.cpp");
USEUNIT("partida.cpp");
USEUNIT("pieza.cpp");
USEUNIT("str.cpp");
USEUNIT("chess.cpp");
//---------------------------------------------------------------------------
#pragma argsused



#include <fstream>  //incluye a iostream
#include <conio.h>    //la funcion gotoxy
#include <ctype.h>
#include <string>

#include "partida.h"
#include "str.h"
#include "tablero.h"
#include "ejercito.h"
#include "pieza.h"

using std::string;
using namespace std;



//---------------------------------------------------------------------------
void ImprimirOpciones()
{
  cout <<" Ingrese su movida   o elija  1 Nuevo Juego  2 Abrir  3 Guardar  0 para salir\n";
  cout <<" ej: 'a1-a2'\n";
  gotoxy(1,23);
  cout <<"\nIngrese su opcion: ";
}


//imprime el tablero
//y avisa si la movida es inválida, hay jaque o mate
void Imprimir (cPartida &oPartida, int nEstado=0)
{
  clrscr();
  gotoxy(20,1);
  cout <<"                           Algortimos y Programaci¢n III \n";
  gotoxy(20,2);
  cout <<"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ          Ing.Fontela\n";
  gotoxy(20,3);
  cout <<"ÛcJUEGO de oAJEDREZÛÛÛ        TP AJEDREZ versi¢n 2.0\n";
  gotoxy(20,4);
  cout <<"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ        g.14 Deccico-Fontdevila\n";
  gotoxy(20,5);
  cout <<"  ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ        ayudante: Javier Macchi\n";
  gotoxy(5,7);

  oPartida.mImprimir(); //dibuja el tablero
  cout << endl;
  gotoxy(10,18);

  switch (nEstado)
  {
     case 4:  //pieza clavada
              cout <<" Movida inv lida. Las ";
              cout << (oPartida.mMueven() == 'b' ? "blancas" : "negras");
              cout << " quedar¡an en Jaque\n";
              gotoxy(1,19);
              cout <<"    Juegan las ";
              cout <<(oPartida.mMueven() == 'b' ? "blancas" : "negras")<<"\n\n";
              ImprimirOpciones();
              break;
     case 3:  //jaque mate
              cout <<" Las ";
              cout << (oPartida.mMueven() == 'b' ? "negras" : "blancas");
              cout << " han dado Jaque Mate";
              break;
     case 2:  //jaque
              cout <<" Las ";
              cout << (oPartida.mMueven() == 'b' ? "blancas" : "negras");
              cout << " se encuentran en Jaque\n ";
              gotoxy(1,19);
              cout <<"    Juegan las ";
              cout <<(oPartida.mMueven() == 'b' ? "blancas" : "negras")<<"\n\n";
              ImprimirOpciones();
              break;
     case 1:  //movida invalida
              cout << " Movida inv lida ";
              gotoxy(1,19);
              cout <<"    Juegan las ";
              cout <<(oPartida.mMueven() == 'b' ? "blancas" : "negras")<<"\n\n";
              ImprimirOpciones();
              break;
     case 0:  //movida normal
              gotoxy(1,19);
              cout <<"    Juegan las ";
              cout <<(oPartida.mMueven() == 'b' ? "blancas" : "negras")<<"\n\n";
              ImprimirOpciones();
              break;
   }

} //fin Imprimir


//Ingreso de la movida por parte del usuario
//realizando la validación de la misma
string Input(cPartida &oPartida, int nEstado)
{
   bool lvale;
   string sOpcion=" ";
 
   do            //validaci¢n del ingreso del usuario
    {
     Imprimir(oPartida,nEstado);
     lvale=false;

     cin >> sOpcion;
     sOpcion= Minuscula(sOpcion);

 /*
     // para debuggear en bc++5.0, no acepta cin de strings
     string s1="b1-c3",s2="d7-d5",
            s3="e2-e4",s4="e7-e5",
            s5="f1-c4",s6="b8-c6",
            s7="e1,g1";
     static int i=1;
     if (i == 1)
     sOpcion=s1;
     else
     if (i == 2)
     sOpcion=s2;
     else
     if (i == 3)
     sOpcion=s3;
     else
     if (i == 4)
     sOpcion=s4;
     else
     if (i == 5)
     sOpcion=s5;
     else
     if (i == 6)
     sOpcion=s6;
     else
     if (i == 7)
     sOpcion=s7;
     i++;
 */

            //*********VALIDACION DEL INPUT
     //if que chequea que el caracter ingresado sea 1, 2, o 3
     //en caso de que sea un ingreso de longitud 1
     if ( sOpcion.length()==1 && sOpcion >= "0" && sOpcion <= "3")
        lvale=true;

     //if que chequea que el caracter 1º y 4º sean letras y el 2do y 5to números
     //en caso de que sea un ingreso de longitud mayor a 4
     if (sOpcion.length() >4 && ( sOpcion[0] <= 'h' && sOpcion[0] >= 'a'
         && sOpcion[3] <= 'h' && sOpcion[3] >= 'a'  && sOpcion[1] <= '8'
         && sOpcion[1] >= '1' && sOpcion[4] <= '8'  && sOpcion[4] >= '1') )
       lvale=true;
            //*********FIN VALIDACION DEL INPUT
     }while (!lvale);
    //fin do..while
    return sOpcion;
}//fin Input


//Maneja la interface con el usuario
//pre inicialicar un objeto partida
//post devuelve 0 si se eligió salir, 2 en caso de mate  1 por default
int menu(cPartida &oPartida )
{
 int nEstado,nOpcion; //indica el estado de la partida. Jaque, Mate o jugada corriente
 string sOpcion=" ",sNombre=" ",sC1=" ",sC2=" ",sName=" ";

      //chequeo de jaque y mate
 if (oPartida.mHayJaque())
   {  if (oPartida.mHayMate())
        {Imprimir(oPartida,3);     //imprimir mate
         return 0;   //salir
         }
      else
         nEstado=2;      //jaque
    }
 else nEstado=0;    //Imprimir una movida normal

 bool vale=false;

 do  //Input de la jugada, vertifica que sea valida, y la pieza no este clavada
 {
   sOpcion=Input(oPartida,nEstado);    //Input de las pieza a mover
   nOpcion=Entero(sOpcion);
   if (sOpcion=="0") 
      nOpcion=10;
   switch (nOpcion)
   {
     case 10 :  //salir
                  return 0;    
     case 1  :  //Nueva Partida
                  oPartida.mVaciar();
                  oPartida.mCargar();
                  return 1; 
     case 2  :  //Abrir partida
                  gotoxy(1,23);
                  cout <<"\nIngrese el nombre del archivo: ";
                  cin >> sName;
                  oPartida.mVaciar();
                  if (!oPartida.mCargar(sName))
                  { gotoxy(1,1);
                    cout <<"  ERROR, no se ha hallado "<<sName;
                    oPartida.mCargar();
                   }
                  return 1;
     case 3  :  //Guardar partida
                  gotoxy(1,23);
                  cout <<"\nIngrese el nombre del archivo: ";
                  cin >> sName;
                  oPartida.mGuardar(sName);
                  return 1;
     case 0  :  //realizar la movida correspondiente
                  sC1=sOpcion.substr(0,2); //casilla origen
                  sC2=sOpcion.substr(3,2); //casilla destino
                  if (oPartida.mEsMovidaValida(sC1,sC2) )
                    {if (oPartida.mEstaClavado(sC1,sC2))
                        nEstado=4; //pieza clavada
                     else
                        vale=true;
                    }
                  else
                     nEstado=1; //movida no valida
   }//fin switch

 }while (!vale);

 oPartida.mMover ( sC1,sC2 );
 oPartida.mSiguienteMovida();
 return 1;  //sale pero indica al main que se repita el ciclo

}//fin menu


//Funcion principal del programa
int main(int argc, char **argv)
{
  bool conpiezas= argc == 1;
  cPartida oPartida(conpiezas);
  if ( !conpiezas )
      oPartida.mCargar();
  int lOpcion;

  do
   {
    lOpcion=menu(oPartida);
   }
  while (lOpcion==1);
  
  cout << "              GAME OVER        ";
}//fin main()
