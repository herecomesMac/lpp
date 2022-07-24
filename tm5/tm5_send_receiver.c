#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

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
	

		if(rank == 0){

			//Gera o vetor aleatorio
			int vetor[quant_elem], i;
			for(i=0; i<quant_elem; i++){
				vetor[i]=rand()%100;
			}

			//Calcula o tamanho do chunk 
			int chunk_size = quant_elem/size;

			//Tive que colocar porque nos testes o elemento nunca era encontrado
			elem = vetor[quant_elem/2];

			//cria infos para enviar aos outros processos
			int dados[2] = {elem, chunk_size};

			MPI_Bcast(dados, 2, MPI_INT, 0, MPI_COMM_WORLD);     
			
			//Vetor que guarda os elementos que serão enviados para os outros processos
			int vector_chunk[chunk_size];
			int prox_pos = 0;

			//Realiza a distribuição do vetor para os processos
			for(i=0; i<=quant_elem; i++){
				//Calcula o processo de destino
				int processo = (i)/chunk_size;
				printf("%d processo \n", processo);
				if(processo == 0){
					vector_chunk[prox_pos] = vetor[i];
					prox_pos += 1;
				}else{
					MPI_Send(&vetor[i], 1, MPI_INT, processo, 0, MPI_COMM_WORLD);
				}
			}

			//Mestre procura o elemento no seu chunk
			int flag_achou = 0;
			for(int j=0; j < chunk_size; j++){
				if(vector_chunk[j] == quant_elem){
					flag_achou = 1;
				}
			}
			if(flag_achou == 1){
				printf("rank %d achou o elemento %d \n", rank, quant_elem);
			}else{
				printf("rank %d não achou o elemento %d \n", rank, quant_elem);
			}

		}else{
			//Escravos recebem os dados
			int dados[2];
			MPI_Bcast(dados, 2, MPI_INT, 0, MPI_COMM_WORLD);

			//Escrevos recebem os elementos 
			//Vetor para guardar os elementos do tamanho chunk
			int elem_rec[dados[2]], i;
			int elems;
			for(i=0; i < dados[2]; i++){
				MPI_Recv(&elems, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				elem_rec[i] = elems;	
			}


			//Verifica se achou o elemento
			int flag_achou = 0;
			for(int j=0; j < dados[2]; j++){
				if(elem_rec[j] == dados[0]){
					flag_achou = 1;
				}
			}
			if(flag_achou == 1){
				printf("rank %d achou o elemento %d \n", rank, dados[0]);
			}else{
				printf("rank %d não achou o elemento %d \n", rank, dados[0]);
			}

		}
		
		MPI_Finalize();
	}

  return 0;
}