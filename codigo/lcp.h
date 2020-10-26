// C++ program for building LCP array for given text
#include <string.h>
#include <algorithm> 
#include <iostream>
#include <vector>
using namespace std;

// Structure to store information of a suffix
struct suffix
{
    long index;  // To store original index
    long rank[2]; // To store ranks and next rank pair
};
 
int cmp(struct suffix a, struct suffix b);

vector<long> buildSuffixArray(string txt, long n);

vector<long> kasai(string txt, vector<long> suffixArr);

void printArr(vector<int>arr, int n);

void printSuffixArr(vector<long>arr, long n, string str);


