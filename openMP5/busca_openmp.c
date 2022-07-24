#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

void main (int argc, char**argv){
    int X = atoi(argv[1]); // X value being searched in the vector

    int Svector = atoi(argv[2]); // vector size
    int nthreads = atoi(argv[3]); // number of threads as input
    int npt = Svector/nthreads; // the number of elements per threads

    // generating randomically a vector
    srand (time(NULL));
    // this could be also read from a file.
    int* S = malloc (Svector * sizeof(int));
    for (int i=0; i < Svector; ++i) {
        S[i] = rand() % Svector;
    }

    //Tive que colocar porque nos testes o elemento nunca era encontrado
    X = S[rand()%Svector];
    int flag_achou = 0;

    //Diretiva for para o número de threads
    #pragma omp parallel for num_threads(nthreads)
    for(int i = 0; i < Svector; i++){
        int id = omp_get_thread_num();
        if(S[i] == X){
            flag_achou = 1;
        }
    }

    if(flag_achou == 1){
        printf("o numero %d foi achado \n", X);
    }else{
        printf("o numero %d não foi achado :( \n", X);
    }

    free(S);

} 
