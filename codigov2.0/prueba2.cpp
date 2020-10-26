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
    vector<string> todasLasCadenas;
    for (long i = 0; i < n; ++i){
        if(arrayMaxRepeat[i] != n){
            for (long j = arrayMaxRepeat[i]; j <= i; ++j){
                cadenaSMR = cadenaSMR + cadenaOriginal[j];
                longPalabra++;
            }
            if (longPalabra == supermaximal){
                todasLasCadenas.push_back(cadenaSMR);
                cantidadCadenas++;
            }
            longPalabra = 0;
            cadenaSMR = "";
        }
    }
    subCadena* subSecuencia = new subCadena[cantidadCadenas];
    for (long i = 0; i < cantidadCadenas; ++i){
        subSecuencia[i].prefijo.push_back(todasLasCadenas[i]);
    }


    vector<pair <long int, string> > cadenasSMRValidas;
    for (long i = 0; i < cantidadCadenas; ++i){
        cadenasSMRValidas.push_back(printNE(todasLasCadenas[i], subSecuencia, cantidadCadenas));
    }
    long tamSecuenciaValida = 0;
    string cadenaNEValida;
    for (long i = 0; i < cantidadCadenas; ++i){
        if (cadenasSMRValidas[i].first > tamSecuenciaValida){
            cadenaNEValida = cadenasSMRValidas[i].second;
        }
    }
    mostrarHastaPesos(cadenaNEValida);

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


pair <long int, string> printNE(string secuencia, struct subCadena *cadenaSMR, long cantidadCadenas)
{
   long tamSecuencia =0;
   long c=0;
   tamSecuencia = secuencia.length();

   //cuento la cantidad de array necesarios como maximo para separar la cadena
   long count = 0;
   for (long i = 1; i <= tamSecuencia; ++i){
        count = i + count;
   }

    subCadena* subSecuencia = new subCadena[count];
  
   //hago partes
   c = 0;
    for (long h = 0; h < tamSecuencia; ++h){
        for (long j = 0; j < tamSecuencia; ++j){
            if (j + h >= tamSecuencia){
                break;
            }
            subSecuencia[c].prefijo.push_back(damePalabra(secuencia, h, h+j)); 
            c++;
        }
    }

    bool valido = true;
    for (long i = 0; i < count; ++i){
        valido = true;
        for (long x = 0; x < cantidadCadenas; ++x){
            if ((cantRepeticiones(cadenaSMR[x].prefijo[0], subSecuencia[i].prefijo[0]).first)>1){
                subSecuencia[i].cantApariciones = cantRepeticiones(cadenaSMR[x].prefijo[0], subSecuencia[i].prefijo[0]).first;
                subSecuencia[i].posicionDeRepeticion = cantRepeticiones(cadenaSMR[x].prefijo[0], subSecuencia[i].prefijo[0]).second;
                if (/* condition */)
                {
                    /* code */
                }
            
            }else{
                valido = false;
            }
        }
        if (valido){
            subSecuencia[i].valido = true;
        }
    }
    
     pair <long, string> cadenaValida;
     cadenaValida.first = 0;
    for (long i = 0; i < count; ++i){
        if (subSecuencia[i].valido){
            if (cadenaValida.first < tamPalabra(subSecuencia[i].prefijo[0])){
                cadenaValida.second = subSecuencia[i].prefijo[0];
                cadenaValida.first = tamPalabra(subSecuencia[i].prefijo[0]);
            }
        }
    }
    return cadenaValida;
    delete[] subSecuencia;
    
}


string damePalabra(string secuencia, long desde, long hasta){
    long longitud =  hasta-desde+1;
    long count = secuencia.length();
    char *palabra = new char[count];
    long i = 0;
    for (i = 0; i < longitud; ++i){
        //cout << "damePalabra" << "\n";
        if (secuencia[desde+i] == '#'){
            break;
        }
        palabra[i] =  secuencia[desde+i];
    }
    palabra[i] = '$';
    for (long i = longitud+1; i < count; ++i){
        palabra[i] = ' ';
    }
    return palabra;
    delete[] palabra;
}


void buscoMaximal(struct subCadena *subSecuenciaSinRep, string secuencia, long count){
    std::pair <string,long> palabraMaximal;
    long tamSecuencia = secuencia.length(); 
    long cantidadDeMaximales = 0;
    vector< pair <string,long> > palabrasMaximales;
    bool esMaximal = false;
    bool valido = false;
    long indiceInicial = 0;
    long indiceFinal = 0;
    long j = 0;
    for (long i = 0; i < count; ++i){
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
                if (esMaximal && valido){
                    palabraMaximal.first = subSecuenciaSinRep[i].prefijo[0];
                    palabraMaximal.second =  subSecuenciaSinRep[i].cantApariciones;
                    palabrasMaximales.push_back(palabraMaximal);
                    cantidadDeMaximales++;
                }
            }
        }
    }
    cout << cantidadDeMaximales;
    for (long i = 0; i < cantidadDeMaximales; ++i){
        cout << "Maximal " ;
        mostrarHastaPesos(palabrasMaximales[i].first);
        cout << "\n";
    }

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


 pair <long int, vector< pair <long int ,long int > >> cantRepeticiones(string secuencia, string subSecuencia){

  long encontrados = 0;
  bool valido = false;
  bool salir = false;
  long c = 0;
  long j = 0;
  long count = secuencia.length();
  vector< pair <long,long> > posicionDeRepeticionTotal;
  pair <long,long> posicionDeRepeticion;
  pair <long, vector< pair <long,long> >> cantidadDeAparicionesConPosicion;
  for (long i = 0; i < count; ++i){
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
  cout << subSecuencia << " cantidad de apariciones: " << encontrados << endl;
    cantidadDeAparicionesConPosicion.first = encontrados;
    cantidadDeAparicionesConPosicion.second = posicionDeRepeticionTotal;
    return cantidadDeAparicionesConPosicion;
}

void  maximo(struct subCadena *subSecuencia, long count){
    long max = subSecuencia[0].cantApariciones;
    string palabra = subSecuencia[0].prefijo[0];
    for (long i = 0; i < count; ++i) {
        if (max <= subSecuencia[i].cantApariciones){
            max = subSecuencia[i].cantApariciones;
            palabra = subSecuencia[i].prefijo[0];
        }
    }

    //me quedo con el maximo tanto en repeticiones como en tamaño
    for (long i = 0; i < count; ++i){
        if (max == subSecuencia[i].cantApariciones) {
            if (tamPalabra(palabra) < tamPalabra(subSecuencia[i].prefijo[0])){
                palabra = subSecuencia[i].prefijo[0];
            }
        }
    }
    std::pair <string,long> palabraMax;
    //cout << "Maxima ";
    palabraMax.first = palabra;
    palabraMax.second = max; 
  //  cout << " Cantidad de apariciones: " << max << "\n";
    for (long i = 0; i < max; ++i){
        mostrarHastaPesos(palabra);
    }

}

long tamPalabra(string secuencia){
    bool salir = false;
    long i = 0;
    while(!salir){
        if (secuencia[i] == '$'){
            salir = true;
        }
        i++;
    }
    return i;
}

bool sinRepetidos(struct subCadena *subSecuencia, string cadenaUnitaria, long count){
    for (long i = 0; i < count; ++i){
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
        for (long i = 0; i < tamPalabra(cadenaYaIngresada); ++i){
            if (!(cadenaYaIngresada[i] == cadenaPorIngresar[i])){
                return false;
            }
        }
        return true;
    }
} 

void mostrarHastaPesos(string palabra){
//  cout << "Palabra: ";
    long count = palabra.length();
    for (long i = 0; i < count; ++i){
        if (palabra[i] == '$'){
            break;
        }else{
          cout << palabra[i];
        }
    }
    cout << endl;
}