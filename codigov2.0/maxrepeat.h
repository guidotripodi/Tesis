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
    long cantApariciones;
    std::vector < std::string > prefijo;
    vector< pair <long,long> > posicionDeRepeticion;
    bool valido;
};

string damePalabra(string secuencia, long desde, long hasta);
pair <long, vector< pair <long,long> >> cantRepeticiones(string secuencia, string subSecuencia);
long tamPalabra(string secuencia);
void mostrarHastaPesos(string palabra);
void printNE(string secuencia, long cantidadCadenas, vector<string> cadenasSMR);
void buscoMaximal(struct subCadena *subSecuencias, string secuencia, long count, long cantidadCadenas, vector<string> cadenasSMR);
bool esValida(string palabra,vector<string> cadenasSMR, long count);