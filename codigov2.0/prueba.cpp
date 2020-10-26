#include <iostream>
#include <iostream>
char maxRepeating(char str[], int n){
   int count = 0;
   char repchar = str[0];
   int maxC = 1;
   for (int i=0; i<n; i++){
      if (str[i] == str[i+1] && i < n-1 )
         maxC++;
      else{
         if (maxC > count){
            count = maxC;
            repchar = str[i];
         }
         maxC = 1;
      }
   }
   return repchar;
}
int main(){
   char string1[] = "aaabbaacccddef";
   int N=14;
   printf("Maximum Consecutive repeating character in string: %c",maxRepeating(string1,N));
   return 0;
}