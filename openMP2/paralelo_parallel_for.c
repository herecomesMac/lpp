#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

int main(int argc, char* argv[])
{
   double sum;
   int num_arr = atoi(argv[1]);
   int num_threads = atoi(argv[2]);
   double a[num_arr], b[num_arr];
   int n = num_arr, i;
   for (i=0; i<n; i++){
        a[i] = i * 0.5;
        b[i] = i * 2.0;
   }
   sum = 0;

   omp_set_num_threads(num_threads);
   #pragma omp parallel
   {
    #pragma omp for 
    for(i = 0; i<num_arr; i++){
        #pragma omp atomic 
        sum = sum + a[i]*b[i];
    }
    }
   printf ("sum = %f\n", sum);
}