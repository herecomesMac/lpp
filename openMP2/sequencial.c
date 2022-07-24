#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
   double sum;
   int num_arr = atoi(argv[1]);
   double a[num_arr], b[num_arr];
   int n = num_arr, i;
   for (i=0; i<n; i++){
        a[i] = i * 0.5;
        b[i] = i * 2.0;
   }
   sum = 0;

   for (i=1; i<n; i++){
       sum = sum + a[i]*b[i];
   }
   printf ("sum = %f\n", sum);
}