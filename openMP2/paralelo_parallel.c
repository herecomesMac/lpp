#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    if(argc != 2){
		printf("Necessario 2 argumentos \n");
		printf("[1] Quantidade de elementos \n");
		printf("[2] Número de Threads \n");		
	}else{
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
            int id, i, Nthrds, istart, iend;
            id = omp_get_thread_num();
            Nthrds = omp_get_num_threads();
            istart = id * num_arr / Nthrds;
            iend = (id+1) * num_arr / Nthrds;

            if (id == Nthrds-1) iend = num_arr;

            for(i = istart; i<iend; i++){
                #pragma omp atomic 
                sum = sum + a[i]*b[i];
            }
            }
        printf ("sum = %f\n", sum);
    }
}