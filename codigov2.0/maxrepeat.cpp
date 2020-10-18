#include <fstream>
#include "lcp.h"
#include "maxrepeat.h"

long printMaximaRepeticiones(vector<long>arrayMaxRepeat, long n, string cadenaOriginal){
    long longPalabra = 0;
    long superMaximal = 0;
    for (long i = 0; i < n; ++i){
        if(arrayMaxRepeat[i] != n){
            for (long j = arrayMaxRepeat[i]; j <= i; ++j){
                longPalabra++;
            }
            if (longPalabra >= superMaximal){
                superMaximal = longPalabra;
            }
            longPalabra = 0;
        }
    }
    string cadenaMax;
    for (long i = 0; i < n; ++i){
        if(arrayMaxRepeat[i] != n){
            for (long j = arrayMaxRepeat[i]; j <= i; ++j){
                cadenaMax = cadenaMax + cadenaOriginal[j];
                longPalabra++;
            }
            if (longPalabra == superMaximal){
                cout << cadenaMax;
                cout << endl;
            }
            longPalabra = 0;
            cadenaMax = "";
        }
    }
    return superMaximal;
}

void printNN(vector<long>arrayMaxRepeat, long n, string cadenaOriginal, long supermaximal){
    long longPalabra = 0;
    string cadenaNN;
    for (long i = 0; i < n; ++i){
        if(arrayMaxRepeat[i] != n){
            for (long j = arrayMaxRepeat[i]; j <= i; ++j){
                cadenaNN = cadenaNN + cadenaOriginal[j];
                longPalabra++;
            }
            if (longPalabra < supermaximal){
                cout << cadenaNN;
                cout << endl;
            }
            longPalabra = 0;
            cadenaNN = "";
        }
    }
}

void NE(vector<long>arrayMaxRepeat, long n, string cadenaOriginal, long supermaximal){
    long longPalabra = 0;
    string cadenaSMR;
    string cadenaTotal;
    long cantidadCadenas = 0;
    for (long i = 0; i < n; ++i){
        if(arrayMaxRepeat[i] != n){
            for (long j = arrayMaxRepeat[i]; j <= i; ++j){
                cadenaSMR = cadenaSMR + cadenaOriginal[j];
                longPalabra++;
            }
            if (longPalabra == supermaximal){
                if (cantidadCadenas == 0){
                    cadenaTotal = cadenaSMR;
                }else{
                    cadenaTotal = cadenaTotal + "#" + cadenaSMR;
                }
                cantidadCadenas++;
            }
            longPalabra = 0;
            cadenaSMR = "";
        }
    }
    printNE(cadenaTotal);

}


void printVector(vector<long>arrayMaxRepeat, long n){
    for (long i = 0; i < n; ++i){
        cout << arrayMaxRepeat[i];
    }
    cout << endl;
}

void maxRepeat(string cadenaInicio){
    //string cadenaInicio;
   
    long length = cadenaInicio.length();
    vector<long> suffixArray = buildSuffixArray(cadenaInicio, length);
    long n = suffixArray.size();
   // printVector(suffixArray, n);
   // cout << "LCP" << endl;
    //LCP
    vector<long>lcp = kasai(cadenaInicio, suffixArray);
    lcp.push_back(0);
   // printVector(lcp, n);
   // cout << "MAXREP" << endl;
    //Inicializar maxRep
    vector<long> maxRepeat(n, n);

    long lcp_i, right_index, left_index;
    for (long i = 0; i < n; ++i){

        lcp_i = max(lcp[i], lcp[i+1]);        

        if(lcp_i > 0){
            right_index = suffixArray[i] + lcp_i - 1;
            left_index = min(maxRepeat[right_index], suffixArray[i]);
            maxRepeat[right_index] = left_index; 
        }

    }
    cout << "cadenaSMR:" << endl;
    long supermaximal = printMaximaRepeticiones(maxRepeat, n, cadenaInicio);
    cout << "cadenaNN:" << endl;
    printNN(maxRepeat, n, cadenaInicio, supermaximal);
    cout << "cadenaNE:" << endl;
    NE(maxRepeat, n, cadenaInicio, supermaximal);
}


void printNE(string secuencia)
{
   int tamSecuencia =0;
   int c=0;
   tamSecuencia = secuencia.length();

   //cuento la cantidad de array necesarios como maximo para separar la cadena
   int count = 0;
   for (int i = 1; i <= tamSecuencia; ++i){
        count = i + count;
   }

    subCadena* subSecuencia = new subCadena[count];
  
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
    subCadena* subSecuenciaSinRep = new subCadena[count];

    int cantidadSinRepetidos = 0;
    for (int i = 0; i < count; ++i){
        if (sinRepetidos(subSecuenciaSinRep, subSecuencia[i].prefijo[0], count)){
            subSecuenciaSinRep[i].prefijo.push_back(subSecuencia[i].prefijo[0]);
            subSecuenciaSinRep[i].cantApariciones = subSecuencia[i].cantApariciones;
            subSecuenciaSinRep[i].posicionDeRepeticion = cantRepeticiones(secuencia, subSecuencia[i].prefijo[0]).second;
           // mostrarHastaPesos(subSecuenciaSinRep[i].prefijo[0]);
    //      cout << " Cantidad de apariciones: " << subSecuenciaSinRep[i].cantApariciones << "\n";
            cantidadSinRepetidos++;
        }
    }

    maximo(subSecuencia, count); 
    delete[] subSecuencia;
    delete[] subSecuenciaSinRep;

}


string damePalabra(string secuencia, int desde, int hasta){
    int longitud =  hasta-desde+1;
    int count = secuencia.length();
    char *palabra = new char[count];
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
    delete[] palabra;
}

string palabraValidaSinCaracterIndistinguible(string secuencia, int desde, int hasta){
    int longitud =  hasta-desde+1;
    int count = secuencia.length();
    char *palabra = new char[count];
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
    delete[] palabra;
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
    for (int i = 0; i < count; ++i) {
        if (max <= subSecuencia[i].cantApariciones){
            max = subSecuencia[i].cantApariciones;
            palabra = subSecuencia[i].prefijo[0];
        }
    }

    //me quedo con el maximo tanto en repeticiones como en tamaño
    for (int i = 0; i < count; ++i){
        if (max == subSecuencia[i].cantApariciones) {
            if (tamPalabra(palabra) < tamPalabra(subSecuencia[i].prefijo[0])){
                palabra = subSecuencia[i].prefijo[0];
            }
        }
    }
    std::pair <string,int> palabraMax;
    //cout << "Maxima ";
    palabraMax.first = palabra;
    palabraMax.second = max; 
  //  cout << " Cantidad de apariciones: " << max << "\n";
    for (int i = 0; i < max; ++i){
        mostrarHastaPesos(palabra);
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
//  cout << "Palabra: ";
    int count = palabra.length();
    for (int i = 0; i < count; ++i){
        if (palabra[i] == '$'){
            break;
        }else{
          cout << palabra[i];
        }
    }
    cout << endl;
}

