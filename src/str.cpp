//archivo str.cpp
//algunas funciones utiles para manejar strings

#include <iostream>
#include <string>
using std::string;
#include "str.h"



string Ingresar(char* psChar)
//realiza un input en un puntero a char
//y lo pasa a un string
{
 string sString=" ";
 cin >> psChar;
 sString=psChar;

 return sString;
}

//pre: largo del string > 0
//post: string en minusculas Ej: PeRro123 = perro123
//descripción: funcion que transforma un char a mayusculas
//solo afecta a los caracteres entre A..Z. Incluyendo a la Ñ
char Mayuscula(char sChar)
{
 char sMayus=sChar;   //se le asigna sString para solo reemplazar de A..Z

   if (sChar >= 'a' && sChar <= 'z')
     switch(sChar)
      {case 'a': sMayus='A';break;     case 'ñ': sMayus='Ñ';break;
       case 'b': sMayus='B';break;     case 'o': sMayus='O';break;
       case 'c': sMayus='C';break;     case 'p': sMayus='P';break;
       case 'd': sMayus='D';break;     case 'q': sMayus='Q';break;
       case 'e': sMayus='E';break;     case 'r': sMayus='R';break;
       case 'f': sMayus='F';break;     case 's': sMayus='S';break;
       case 'g': sMayus='G';break;     case 't': sMayus='T';break;
       case 'h': sMayus='H';break;     case 'u': sMayus='U';break;
       case 'i': sMayus='I';break;     case 'v': sMayus='V';break;
       case 'j': sMayus='J';break;     case 'w': sMayus='W';break;
       case 'k': sMayus='K';break;     case 'x': sMayus='X';break;
       case 'l': sMayus='L';break;     case 'y': sMayus='Y';break;
       case 'm': sMayus='M';break;     case 'z': sMayus='Z';break;
       case 'n': sMayus='N';break;
      }
 return sMayus;
}


//pre: largo del string > 0
//post: string en minusculas Ej: PeRro123 = perro123

//descripción: funcion que transforma un string a minusculas
//solo afecta a los caracteres entre A..Z. Incluyendo a la Ñ
string Minuscula(string sString)
{
 string sMinus=sString;   //se le asigna sString para solo reemplazar de A..Z
 if (sString.length()==0)
   return sString;
 for(int i=0; i<=(int)sString.length(); i++)
 {
   if (sString[i] >= 'A' && sString[i] <= 'Z')
     switch(sString[i])
      {case 'A': sMinus[i]='a';break;     case 'N': sMinus[i]='n';break;
       case 'B': sMinus[i]='b';break;     case 'Ñ': sMinus[i]='ñ';break;
       case 'C': sMinus[i]='c';break;     case 'O': sMinus[i]='o';break;
       case 'D': sMinus[i]='d';break;     case 'P': sMinus[i]='p';break;
       case 'E': sMinus[i]='e';break;     case 'Q': sMinus[i]='q';break;
       case 'F': sMinus[i]='f';break;     case 'R': sMinus[i]='r';break;
       case 'G': sMinus[i]='g';break;     case 'S': sMinus[i]='s';break;
       case 'H': sMinus[i]='h';break;     case 'T': sMinus[i]='t';break;
       case 'I': sMinus[i]='i';break;     case 'U': sMinus[i]='u';break;
       case 'J': sMinus[i]='j';break;     case 'V': sMinus[i]='v';break;
       case 'K': sMinus[i]='k';break;     case 'W': sMinus[i]='w';break;
       case 'L': sMinus[i]='l';break;     case 'X': sMinus[i]='x';break;
       case 'M': sMinus[i]='m';break;     case 'Y': sMinus[i]='y';break;
       case 'Z': sMinus[i]='z';break;
      }
 }
 return sMinus;
}


//pre: largo del string > 0
//post: string en minusculas Ej: PeRro123 = perro123

//descripción: funcion que transforma un string a minusculas
//solo afecta a los caracteres entre A..Z. Incluyendo a la Ñ
char Minuscula(char sCaracter)
{
    //en caso de no encontrar coinciden se devuelve el mismo
   char sMinus=sCaracter;

   if (sCaracter >= 'A' && sCaracter <= 'Z')
     switch(sCaracter)
      {case 'A': sMinus='a';break;     case 'N': sMinus='n';break;
       case 'B': sMinus='b';break;     case 'Ñ': sMinus='ñ';break;
       case 'C': sMinus='c';break;     case 'O': sMinus='o';break;
       case 'D': sMinus='d';break;     case 'P': sMinus='p';break;
       case 'E': sMinus='e';break;     case 'Q': sMinus='q';break;
       case 'F': sMinus='f';break;     case 'R': sMinus='r';break;
       case 'G': sMinus='g';break;     case 'S': sMinus='s';break;
       case 'H': sMinus='h';break;     case 'T': sMinus='t';break;
       case 'I': sMinus='i';break;     case 'U': sMinus='u';break;
       case 'J': sMinus='j';break;     case 'V': sMinus='v';break;
       case 'K': sMinus='k';break;     case 'W': sMinus='w';break;
       case 'L': sMinus='l';break;     case 'X': sMinus='x';break;
       case 'M': sMinus='m';break;     case 'Y': sMinus='y';break;
       case 'Z': sMinus='z';break;
      }

   return sMinus;
}


int Entero(string sString, int ni)
//transforma, si pued la posicion especificada del string entero
//en caso de no poder devuelve 0. Por defecto toma la posicion 0.
{
 if (sString[ni]=='1') return 1;
 if (sString[ni]=='2') return 2;
 if (sString[ni]=='3') return 3;
 if (sString[ni]=='4') return 4;
 if (sString[ni]=='5') return 5;
 if (sString[ni]=='6') return 6;
 if (sString[ni]=='7') return 7;
 if (sString[ni]=='8') return 8;
 if (sString[ni]=='9') return 9;
 return 0;  //devuelve 0 si no encontr¢ una coincidencia
}

bool EsEntero(string sString,int i)
//devuelve true o false segun el valor este entre 0..9
//si no es de longitud 1 devolver  falso
{
 if (sString[i]>='0' && sString[i] <= '9')
  return true;
 else
  return false;   //caso por defecto
}


/*
//   //ejemplos de usos compilados y probados
void main()
{
	string sPrueba=" ";
   char* psPrueba=" ";

   cout << "A ver, ingresate algo: \n";
   sPrueba=Ingresar(psPrueba);
   cout <<"\n"<<sPrueba;

}
*/
