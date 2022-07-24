#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {

    if(argc != 3){
		printf("Necessario 3 argumentos \n");
		printf("[1] Quantidade de processos \n");
		printf("[2] Elemento a ser procurado \n");
		printf("[3] Quantidade de elementos \n");
	}else{


        MPI_Init(&argc, &argv);
        int rank, size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        //Pega os argumentos
		//[1] Elemento a ser procurado
		//[2] Quantidade de elementos do vetor
        int elem = atoi(argv[1]);
        int quant_elem = atoi(argv[2]);	
        

        //Gera o vetor aleatorio
        int vetor[quant_elem], i;
        for(i=0; i<quant_elem; i++){
            vetor[i]=rand()%100;
        }

        //Calcula o tamanho do chunk 
        int chunk_size = quant_elem/size;

        //Tive que colocar porque nos testes o elemento nunca era encontrado
        elem = vetor[quant_elem/2];

        int recv_buf[chunk_size];

        //Divide o vetor de envio em partes iguais
        MPI_Scatter(vetor, chunk_size, MPI_INT, recv_buf, 4, MPI_INT, 0, MPI_COMM_WORLD);

        //Verifica se achou o elemento
        int flag_achou = 0;
        for(int j=0; j<chunk_size; j++){
            if(recv_buf[j] == elem){
            flag_achou = 1;
            }
        }
        if(flag_achou == 1){
            printf("\n rank: %d achou o elemento %d\n", rank, elem);
        }else{
            printf("\n rank: %d nao achou o elemento %d\n", rank, elem);
        }
        
        MPI_Finalize();
    }

    return 0;
}

