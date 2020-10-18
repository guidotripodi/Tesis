#include <iostream>
#include <vector>
#include <algorithm> 
#include <string.h>

using namespace std;

long printMaximaRepeticiones(vector<long>arrayMaxRepeat, long n, string cadenaOriginal);
void printVector(vector<long>arrayMaxRepeat, long n);
void maxRepeat(string cadenaInicio);
void printNN(vector<long>arrayMaxRepeat, long n, string cadenaOriginal, long supermaximal);
void NE(vector<long>arrayMaxRepeat, long n, string cadenaOriginal, long supermaximal);

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
void printNE(string secuencia);
