#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm> 
using namespace std;

// Structure to store information of a suffix
struct suffix
{
    long index;  // me guardo el index original en la cadena
    long rank[2]; //  cantidad de ranks y proximo pair rank
};
 
int cmp(struct suffix a, struct suffix b);

vector<long> buildSuffixArray(string txt, long n);

vector<long> kasai(string txt, vector<long> suffixArr);

void printArray(vector<int>array, int n);

void printSuffixArray(vector<long>array, long n, string cadenaOriginal);


