#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;


struct subCadena { 
    int cantApariciones;
    std::vector < std::string > prefijo;
    vector< pair <int,int> > posicionDeRepeticion;
};

string damePalabra(string secuencia, int desde, int hasta);
string palabraValidaSinCaracterIndistinguible(string secuencia, int desde, int hasta);
pair <int, vector< pair <int,int> >> cantRepeticiones(string secuencia, string subSecuencia);
void  maximo(struct subCadena *subSecuencia, int count);
int tamPalabra(string secuencia);
bool sinRepetidos(struct subCadena *subSecuencia, string cadenaUnitaria, int count);
bool igualdad(string cadenaYaIngresada, string cadenaPorIngresar);
void mostrarHastaPesos(string palabra);
void buscoMaximal(struct subCadena *subSecuenciaSinRep, string secuencia, int count);
