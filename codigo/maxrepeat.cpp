#include "lcp.h"
#include <fstream>


void printMaxRepeats(vector<long>arr, long n, string str){
    for (long i = 0; i < n; ++i){
        cout << arr[i];
        cout << endl;
    }
    cout << endl;
    for (long i = 0; i < n; ++i){
        if(arr[i] != n){
            for (long j = arr[i]; j <= i; ++j){
                cout << str[j];
            }
            cout << endl;
        }
    }
}

void printVector(vector<long>arr, long n){
    for (long i = 0; i < n; ++i){
        cout << arr[i];
    }
    cout << endl;
}

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
    long length = cadenaInicio.length();
    vector<long> suffixArray = buildSuffixArray(cadenaInicio, length);
    long n = suffixArray.size();
    printVector(suffixArray, n);
    //cout << "LCP" << endl;
    //LCP
    vector<long>lcp = kasai(cadenaInicio, suffixArray);
    lcp.push_back(0);
  //  printVector(lcp, n);
    //cout << "MAXREP" << endl;
    //Inicializar maxRep
    vector<long> maxRepeat(n, n);

    long lcp_i, right_index, left_index;
    for (long i = 0; i < n; ++i){
        if (cadenaInicio[i+1] != '#' &&  cadenaInicio[i] != '#'){
            lcp_i = max(lcp[i], lcp[i+1]);        

            if(lcp_i > 0){
                right_index = suffixArray[i] + lcp_i - 1;
                left_index = min(maxRepeat[right_index], suffixArray[i]);
                maxRepeat[right_index] = left_index; 
            }
        }

    }
    printMaxRepeats(maxRepeat, n, cadenaInicio);
}
