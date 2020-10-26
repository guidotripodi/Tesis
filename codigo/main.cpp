#include <fstream>
#include <iostream>
#include <string.h>
#include "lcp.h"
#include "maxrepeat.cpp"


int main(){
	string cadenaInicio;
	fstream ficheroEntrada;
	char letra;
	ofstream cout("output1.txt"); 
	ficheroEntrada.open ("prueba1.fa", ios::in);
	 if (ficheroEntrada.is_open()) {
		 while (! ficheroEntrada.eof() ) {
			 ficheroEntrada >> letra;
			 if (!(letra == '.')){
			 	cadenaInicio = cadenaInicio + letra;
			 }else{
			 	break;
			 }
		 }
		ficheroEntrada.close();
	}	
		//cout << cadenaInicio << endl;
	    maxRepeat(cadenaInicio);
	    return 0;
}