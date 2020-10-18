#include "lcp.h"

//comparo ranks entre 2 sufijos
int cmp(struct suffix a, struct suffix b){
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
           (a.rank[0] < b.rank[0] ?1: 0);
}
 
//A partir de la cadena original construyo todos los sufijos
vector<long> buildSuffixArray(string txt, long n){
    
    suffix* sufijos = new suffix[n];
    
//Almaceno los sufijos con el index original 
    for (long i = 0; i < n; i++){
        sufijos[i].index = i;
        sufijos[i].rank[0] = txt[i] - 'a';
        sufijos[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }
 
//ordeno los sufijos usando sort (pierdo complejidad)
    sort(sufijos, sufijos+n, cmp);
    long* ind = new long[n]; // uso long, sino exploit!
    
    for (long k = 4; k < 2*n; k = k*2){
       // en base al orden voy asignando los valores de cada rank
        long rank = 0;
        long prev_rank = sufijos[0].rank[0];
        sufijos[0].rank[0] = rank;
        ind[sufijos[0].index] = 0;
 
        for (long i = 1; i < n; i++){
            // Si el primer rank y los siguientes son los mismos que el del anterior se lo asigno
            if (sufijos[i].rank[0] == prev_rank &&
                    sufijos[i].rank[1] == sufijos[i-1].rank[1]){
                prev_rank = sufijos[i].rank[0];
                sufijos[i].rank[0] = rank;
            }
            else {
                // Sino se incrementa y seguimos..

                prev_rank = sufijos[i].rank[0];
                sufijos[i].rank[0] = ++rank;
            }
            ind[sufijos[i].index] = i;
        }
 
        // Asigno nuevo rank
        for (long i = 0; i < n; i++){
            long nextindex = sufijos[i].index + k/2;
            sufijos[i].rank[1] = (nextindex < n)?
                                  sufijos[ind[nextindex]].rank[0]: -1;
        }
 
        // ordeno de nuevo, no se me ocurrio otra forma para reducir la complejidad
        sort(sufijos, sufijos+n, cmp);
    }
    
    delete[] ind;
    
    // guardo en el vector de mis sufijos todos los indices
    vector<long>suffixArray;
    for (long i = 0; i < n; i++)
        suffixArray.push_back(sufijos[i].index);
 
    delete[] sufijos;
    return  suffixArray;
}
 
vector<long> kasai(string txt, vector<long> suffixArr)
// LCP!
{
    long n = suffixArr.size();
 
    vector<long> lcp(n, 0);
    vector<long> invSuff(n, 0);
 
    // Veo todos los sufijos
    for (long i=0; i < n; i++)
        invSuff[suffixArr[i]] = i;
 
    long k = 0;
 

    for (long i=0; i<n; i++){

        if (invSuff[i] == n-1){
         /* Si tenemos el sufijo en n-1 no hay siguiente cadena, no tengo lcp definido */
            k = 0;
            continue;
        }
        /* guardo la siguiente subcadena para comparar */

        long j = suffixArr[invSuff[i]+1];
        while (i+k<n && j+k<n && txt[i+k]==txt[j+k] && txt[i+k] != '+')
            k++;
 
        lcp[invSuff[i]+1] = k; 
        // elimino el caracter inicial de la cadena y sigo
        if (k>0)
            k--;
    }
 
    return lcp;
}
 
void printArray(vector<long>array, long n){
    for (long i = 0; i < n; i++)
        cout << array[i] << " ";
    cout << endl;
}
 
void printSuffixArray(vector<long>array, long n, string cadenaOriginal){
    for (long i = 0; i < n; i++){
        cout << array[i];

        if(array[i]<10){
            cout << "  ";
        }else{
            cout << " ";
        }

        for (long j = array[i]; j < n; ++j){
            cout << cadenaOriginal[j];
        }
        cout << endl;
    }
    cout << endl;
}
 
