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
    string cadenaTotal = "#";
    long cantidadCadenas = 0;
    vector<string> cadenasSMR;
    for (long i = 0; i < n; ++i){
        if(arrayMaxRepeat[i] != n){
            for (long j = arrayMaxRepeat[i]; j <= i; ++j){
                cadenaSMR = cadenaSMR + cadenaOriginal[j];
                longPalabra++;
            }
            if (longPalabra == supermaximal){
                cantidadCadenas++;
                cadenaTotal = cadenaTotal + "#" + cadenaSMR;
                cadenasSMR.push_back(cadenaSMR);
            }
            longPalabra = 0;
            cadenaSMR = "";
        }
    }
    /*
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
*/
   // cout << cadenaTotal << endl;
   // cout << cantidadCadenas << endl;
    printNE(cadenasSMR[0], cantidadCadenas, cadenasSMR);
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


void printNE(string secuencia, long cantidadCadenas, vector<string> cadenasSMR)
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
           // cout << damePalabra(secuencia, h, h+j) << endl;
            subSecuencia[c].prefijo.push_back(damePalabra(secuencia, h, h+j)); 
            c++;
        }
    }

    //busco cantidad de repeticiones de cada particion
    for (long i = 0; i < count; ++i){
        subSecuencia[i].cantApariciones = cantRepeticiones(secuencia, subSecuencia[i].prefijo[0]).first;
        subSecuencia[i].posicionDeRepeticion = cantRepeticiones(secuencia, subSecuencia[i].prefijo[0]).second;
    }
        //maximo(subSecuencia, count); 
    for (long i = 0; i < count; ++i){
        subSecuencia[i].valido = true;
        for (long j = 0; j < cantidadCadenas; ++j){
            if (cantRepeticiones(cadenasSMR[j], subSecuencia[i].prefijo[0]).first < 1){
                subSecuencia[i].valido = false;
            }
        }
    }
    buscoMaximal(subSecuencia, secuencia, count, cantidadCadenas, cadenasSMR);
    delete[] subSecuencia;
}


string damePalabra(string secuencia, long desde, long hasta){
    long longitud =  hasta-desde+1;
    string cadena;
    long i = 0;
    for (i = 0; i < longitud; ++i){
        //cout << "damePalabra" << "\n";
        if (secuencia[desde+i] == '#'){
            break;
        }
        cadena = cadena + secuencia[desde+i];
    }
    cadena = cadena + '$';
    return cadena;
}


void buscoMaximal(struct subCadena *subSecuencias, string secuencia, long count, long cantidadCadenas, vector<string> cadenasSMR){
    std::pair <string,long> palabraMaximal;
    long tamSecuencia = secuencia.length(); 
    long cantidadDeMaximales = 0;
    vector< pair <string,long> > palabrasMaximales;
    bool esMaximal = false;
    bool valido = false;
    long indiceInicial = 0;
    long indiceFinal = 0;
    long j = 0;
//    long tamPalabraMaximal = 0;
    //cout << "PALABRA MAXIMAL" << endl;
  //  cout << cantidadCadenas << endl;
    for (long i = 0; i < count; ++i){
        if (subSecuencias[i].valido){
                //es potencial maximal
                esMaximal = true;
                j = 0;
                valido = false;
                while(esMaximal && !valido){
                    if (subSecuencias[i].posicionDeRepeticion[j].first-1 >=0){
                        indiceInicial = subSecuencias[i].posicionDeRepeticion[j].first-1;
                        indiceFinal = subSecuencias[i].posicionDeRepeticion[j].second;
                        string palabra = damePalabra(secuencia, indiceInicial,indiceFinal);
                        if (esValida(palabra, cadenasSMR, cantidadCadenas)){
                            esMaximal = false;
                                 break;
                        }
                    }
                    if (subSecuencias[i].posicionDeRepeticion[j].second + 1 < tamSecuencia){
                        indiceFinal = subSecuencias[i].posicionDeRepeticion[j].second + 1;
                        string palabra = damePalabra(secuencia, subSecuencias[i].posicionDeRepeticion[j].first, indiceFinal);
                        if (esValida(palabra, cadenasSMR, cantidadCadenas)){
                            esMaximal = false;
                            break;

                        }
                    }
                    j++;
                    if (j == subSecuencias[i].cantApariciones){
                        valido = true;
                    }
                }
                if (esMaximal && valido){
                    palabraMaximal.first = subSecuencias[i].prefijo[0];
                    palabraMaximal.second =  subSecuencias[i].cantApariciones;
                    palabrasMaximales.push_back(palabraMaximal);
                    cantidadDeMaximales++;
          /*          if (tamPalabraMaximal < tamPalabra(palabraMaximal.first)){
                        tamPalabraMaximal = tamPalabra(palabraMaximal.first);
                    }*/
                }
        }
    }
   // cout << cantidadDeMaximales;
    for (long i = 0; i < cantidadDeMaximales; ++i){
  //      cout << "Maximal " ;
       // if (tamPalabraMaximal == tamPalabra(palabrasMaximales[i].first)){
            mostrarHastaPesos(palabrasMaximales[i].first);
        //}
     //   cout << "\n";
    }

}



bool esValida(string palabra,vector<string> cadenasSMR, long count){
    for (long i = 0; i < count; ++i){
        if (cantRepeticiones(cadenasSMR[i], palabra).first <1){
            return false;
        }
    }
    return true;
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
 // cout << subSecuencia << " cantidad de apariciones: " << encontrados << endl;
    cantidadDeAparicionesConPosicion.first = encontrados;
    cantidadDeAparicionesConPosicion.second = posicionDeRepeticionTotal;
    return cantidadDeAparicionesConPosicion;
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