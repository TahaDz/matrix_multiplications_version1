/*  Rahmani Taha  */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define ROW 8
#define COL 3
#define COL2 13
#define NUMTHREADS 3

int mat1 [ROW][COL], mat2 [COL][COL2] , mat [ROW][COL2];



void *  multiplication(int k){
	printf("thread numero %d\n",k);
	int debut,fin;
  	debut=k*(ROW/NUMTHREADS);
   	
   	if(k==NUMTHREADS-1)
     		fin=ROW-1;
	else 
		fin=debut+(ROW/NUMTHREADS)-1;
         

   int s=0;
   for(int i = debut; i <= fin; i++){ 
      
   
	int sum ;
	for(int l = debut; l <= fin; l++){
		for (int i = 0; i < COL2; i++ ){
			sum = 0;
	
			for (int j= 0; j < COL; j++)			
					sum += mat1 [l][j] * mat2 [j][i];

			mat [l][i] = sum;

		}
	}

	}

	pthread_exit(NULL);


	
}


int main(){
	pthread_t threads[ROW]; 
   	int rc; 
      	int th; 
      	double debut,fin;
      	srand(time(NULL));
	

	
	

	printf("------------matrice 1 -----------\n");	
 	for(int i = 0 ; i < ROW ; i++){
		for (int j = 0 ; j < COL ; j++){
			mat1 [i][j] = rand()%10;
			printf("%d ",mat1 [i][j]);
		}
		printf(" \n");
	}

   	printf("------------matrice 2 -----------\n");
	for(int i = 0 ; i < COL ; i++){
	        for (int j = 0 ; j < COL2 ; j++){
                        mat2 [i][j] = rand()%10;
                        printf("%d ",mat2 [i][j]);

                }
                printf(" \n");
	}

	printf("--------------------le calcul du produit matricielle parallele--------------------------\n");
	debut = clock();

	for(th = 0; th < NUMTHREADS ; th++){ 

	      rc = pthread_create(&threads[th], NULL, multiplication, th); 	
	      
	      if (rc){ 
                    	printf("Erreur de creation de thread; code erreur = %d\n", rc); 
	            	exit(-1); 
              } 
	 }
	 
	 
	 for(th = 0; th < NUMTHREADS; th++){ 
	      (void)pthread_join(threads[th],NULL);
         }

         fin =  clock();
         
 
	printf("------------matrice resultat -----------\n");

	for(int i = 0 ; i < ROW ; i++){
		 for (int j = 0 ; j < COL2 ; j++) 
	                printf("%d ",mat [i][j]);
	         printf(" \n");                  
	}

	printf("temps parallele=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC);
	
	/*for(int i = 0 ; i < ROW ; i++){
		 for (int j = 0 ; j < COL2 ; j++) 
	               mat [i][j]=0;
	                           
	}*/

	printf("--------------------le calcul du produit matricielle sequentielle-----------------------\n");
	debut =  clock();
	for(int i=0; i<ROW; i++){
		int sum=0;
		for(int j=0; j<COL2; j++){
	            	sum = 0;
			for(int k=0; k<COL; k++)
	                  	 sum = sum + mat1[i][k] * mat2[k][j];
	                 mat[i][j] = sum;
	        }
	 }
	fin =  clock();
	printf("------------matrice resultat -----------\n");

	        for(int i = 0 ; i < ROW ; i++){
	        	for (int j = 0 ; j < COL2 ; j++) 
	                	printf("%d ",mat [i][j]);
	        	printf(" \n");
	         }
	 printf("temps sequentielle=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC);
	return 0;
} 
