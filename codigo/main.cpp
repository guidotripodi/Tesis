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

int main()
{
    cout << "Ingresar secuencia:" << "\n";


   string secuencia;//En esta variable estará almacenado el nombre ingresado.
   cin >> secuencia; //Se lee el nombre
   int tamSecuencia =0;
   int c=0;
   tamSecuencia = secuencia.length();

   //cuento la cantidad de array necesarios como maximo para separar la cadena
   int count = 0;
   for (int i = 1; i <= tamSecuencia; ++i){
   		count = i + count;
   }
	struct subCadena subSecuencia[count];
  
   //hago partes
   c = 0;
  	for (int h = 0; h < tamSecuencia; ++h){
   		for (int j = 0; j < tamSecuencia; ++j){
   			if (j + h >= tamSecuencia){
   				break;
   			}
   			subSecuencia[c].prefijo.push_back(damePalabra(secuencia, h, h+j)); 
   			c++;
   		}
	}



   	//busco cantidad de repeticiones de cada particion

   	for (int i = 0; i < count; ++i){
   		subSecuencia[i].cantApariciones = cantRepeticiones(secuencia, subSecuencia[i].prefijo[0]).first;
   		subSecuencia[i].posicionDeRepeticion = cantRepeticiones(secuencia, subSecuencia[i].prefijo[0]).second;
   	}
   	struct subCadena subSecuenciaSinRep[count];
   	int cantidadSinRepetidos = 0;
   	for (int i = 0; i < count; ++i){
   		if (sinRepetidos(subSecuenciaSinRep, subSecuencia[i].prefijo[0], count)){
   			subSecuenciaSinRep[i].prefijo.push_back(subSecuencia[i].prefijo[0]);
   			subSecuenciaSinRep[i].cantApariciones = subSecuencia[i].cantApariciones;
   			subSecuenciaSinRep[i].posicionDeRepeticion = cantRepeticiones(secuencia, subSecuencia[i].prefijo[0]).second;
   			mostrarHastaPesos(subSecuenciaSinRep[i].prefijo[0]);
   			cout << " Cantidad de apariciones: " << subSecuenciaSinRep[i].cantApariciones << "\n";
   			cantidadSinRepetidos++;
   		}
   	}

   	maximo(subSecuencia, count); 
   	//buscoMaximal(subSecuenciaSinRep, secuencia, cantidadSinRepetidos);
   	return 0;
}


string damePalabra(string secuencia, int desde, int hasta){
	int longitud =  hasta-desde+1;
	int count = secuencia.length();
	char palabra[count];
	int i = 0;
	for (i = 0; i < longitud; ++i){
		//cout << "damePalabra" << "\n";
			palabra[i] =  secuencia[desde+i];
	}
	palabra[i] = '$';
	for (int i = longitud+1; i < count; ++i){
		palabra[i] = ' ';
	}
	return palabra;
}

string palabraValidaSinCaracterIndistinguible(string secuencia, int desde, int hasta){
	int longitud =  hasta-desde+1;
	int count = secuencia.length();
	char palabra[count];
	int i = 0;
	for (i = 0; i < longitud; ++i){
		//cout << "damePalabra" << "\n";
		if (!(secuencia[desde+i] == '#')){
			palabra[i] =  secuencia[desde+i];
		}
	}
	palabra[i] = '$';
	for (int i = longitud+1; i < count; ++i){
		palabra[i] = ' ';
	}
	return palabra;
}


 pair <int, vector< pair <int,int> >> cantRepeticiones(string secuencia, string subSecuencia){

  int encontrados = 0;
  bool valido = false;
  bool salir = false;
  int c = 0;
  int j = 0;
  int count = secuencia.length();
  vector< pair <int,int> > posicionDeRepeticionTotal;
  pair <int,int> posicionDeRepeticion;
  pair <int, vector< pair <int,int> >> cantidadDeAparicionesConPosicion;
  for (int i = 0; i < count; ++i){
  	if (subSecuencia[0] == secuencia[i]){
  		salir = false;
  		valido = true;
  		posicionDeRepeticion.first = i;
  		if (subSecuencia[1] == '$'){
  			valido = false;
  			salir = true;
  			encontrados++;
  			posicionDeRepeticion.second = i;
  			posicionDeRepeticionTotal.push_back(posicionDeRepeticion);
  		}
  		j = i;
  		while(valido && !salir){
  			c++;
  			j++;
  			if (subSecuencia[c] != '$'){
  				if (subSecuencia[c] != secuencia[j]){
  					valido = false;
  				}
  			}else{
  				encontrados++;
  				salir = true;
  				posicionDeRepeticion.second = j-1;
  				posicionDeRepeticionTotal.push_back(posicionDeRepeticion);
  			}
  		}
  		c = 0;

  	}
  }
  	cantidadDeAparicionesConPosicion.first = encontrados;
  	cantidadDeAparicionesConPosicion.second = posicionDeRepeticionTotal;
  	return cantidadDeAparicionesConPosicion;
}

void  maximo(struct subCadena *subSecuencia, int count){
	int max = subSecuencia[0].cantApariciones;
	string palabra = subSecuencia[0].prefijo[0];
	for (int i = 0; i < count; ++i)	{
		if (max <= subSecuencia[i].cantApariciones){
			max = subSecuencia[i].cantApariciones;
			palabra = subSecuencia[i].prefijo[0];
		}
	}

	//me quedo con el maximo tanto en repeticiones como en tamaño
	for (int i = 0; i < count; ++i){
		if (max == subSecuencia[i].cantApariciones)	{
			if (tamPalabra(palabra) < tamPalabra(subSecuencia[i].prefijo[0])){
				palabra = subSecuencia[i].prefijo[0];
			}
		}
	}
	std::pair <string,int> palabraMax;
	cout << "Maxima ";
	mostrarHastaPesos(palabra);
	palabraMax.first = palabra;
	palabraMax.second = max; 
	cout << " Cantidad de apariciones: " << max << "\n";

}


void buscoMaximal(struct subCadena *subSecuenciaSinRep, string secuencia, int count){
	std::pair <string,int> palabraMaximal;
	int tamSecuencia = secuencia.length(); 
	int cantidadDeMaximales = 0;
	vector< pair <string,int> > palabrasMaximales;
	bool esMaximal = false;
	bool valido = false;
	int indiceInicial = 0;
	int indiceFinal = 0;
	int j = 0;
	for (int i = 0; i < count; ++i){
		if (subSecuenciaSinRep[i].prefijo.size()>0){
			if (subSecuenciaSinRep[i].cantApariciones >= 2){
				//es potencial maximal
				esMaximal = true;
				j = 0;
				valido = false;
				while(esMaximal && !valido){
					if (subSecuenciaSinRep[i].posicionDeRepeticion[j].first-1 >=0){
						indiceInicial = subSecuenciaSinRep[i].posicionDeRepeticion[j].first-1;
						indiceFinal = subSecuenciaSinRep[i].posicionDeRepeticion[j].second;
						string palabra = damePalabra(secuencia, indiceInicial, indiceFinal);
						if (cantRepeticiones(secuencia, palabra).first > 1){
							//si tengo una cadena con mas de una repeticion no soy maximal
							 esMaximal = false;
							 break;
						}
					}
					if (subSecuenciaSinRep[i].posicionDeRepeticion[j].second + 1 < tamSecuencia){
						indiceFinal = subSecuenciaSinRep[i].posicionDeRepeticion[j].second + 1;
						string palabra = damePalabra(secuencia, subSecuenciaSinRep[i].posicionDeRepeticion[j].first, indiceFinal);
						if (cantRepeticiones(secuencia, palabra).first > 1){
							//si tengo una cadena con mas de una repeticion no soy maximal
							 esMaximal = false;
							 break;
						}
					}
					j++;
					if (j == subSecuenciaSinRep[i].cantApariciones){
						valido = true;
					}
				}
				if (esMaximal){
					palabraMaximal.first = subSecuenciaSinRep[i].prefijo[0];
					palabraMaximal.second =  subSecuenciaSinRep[i].cantApariciones;
					palabrasMaximales.push_back(palabraMaximal);
					cantidadDeMaximales++;
				}
			}
		}
	}
	for (int i = 0; i < cantidadDeMaximales; ++i){
		cout << "Maximal " ;
		mostrarHastaPesos(palabrasMaximales[i].first);
		cout << "\n";
	}

}



int tamPalabra(string secuencia){
	bool salir = false;
	int i = 0;
	while(!salir){
		if (secuencia[i] == '$'){
			salir = true;
		}
		i++;
	}
	return i;
}

bool sinRepetidos(struct subCadena *subSecuencia, string cadenaUnitaria, int count){
	for (int i = 0; i < count; ++i){
		if (subSecuencia[i].prefijo.size()>0){
			if (igualdad(subSecuencia[i].prefijo[0],cadenaUnitaria)){
				return false;
			}
		}	

	}
	return true;
}

bool igualdad(string cadenaYaIngresada, string cadenaPorIngresar){
	if (!(tamPalabra(cadenaYaIngresada) == tamPalabra(cadenaPorIngresar))){
		return false;
	}else{
		for (int i = 0; i < tamPalabra(cadenaYaIngresada); ++i){
			if (!(cadenaYaIngresada[i] == cadenaPorIngresar[i])){
				return false;
			}
		}
		return true;
	}
} 

void mostrarHastaPesos(string palabra){
	cout << "Palabra: ";
	int count = palabra.length();
	for (int i = 0; i < count; ++i){
		if (palabra[i] == '$'){
			break;
		}else{
	//		cout << palabra[i];
		}
	}
}

void mostrarHastaPesos2(string palabra){
	cout << "Palabra: ";
	int count = palabra.length();
	for (int i = 0; i < count; ++i){
		if (palabra[i] == '$'){
			break;
		}else{
			cout << palabra[i];
		}
	}
}
