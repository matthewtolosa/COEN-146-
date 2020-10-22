/*Matthew Tolosa 
Date: 10/2/20 
Description: Writing a program so that the multiplication of two matrices is performed at a minimum time
*/

#include <stdlib.h> 
#include <stdio.h>
#include <pthread.h> 

#define N  2 /*defining the size of row and columns */
#define M  2
#define L  2

double matrixA[N][M], matrixB[M][L], matrixC[N][L]; /*resulting matrices */

struct r {
    int row;   /* row of the matrix */
};


pthread_t matrix_thread[N];
void *thread(void *param);
void printMatrix(int nr, int nc, double matrix[nr][nc]);

int main() {
    srand(time(NULL)); /*produces random number */
    int i, j, count = 0;
    
    for(i = 0; i < N; i++){             /*iterates to fill in random numbers in the rows and columns */
        for(j = 0; j < M; j++){
            matrixA[i][j] = rand();
        }
    }

    for(i = 0; i < M; i++) {     
        for(j = 0; j < L; j++){
            matrixB[i][j] = rand();
        }
    }

    for(i = 0; i < N; i++) {
        struct r *data = (struct r *) malloc(sizeof(struct r));  /*allocates block of memory for struct pointer data */
        data->row = i; /*struct pointer points to the rows of each struct pointer created */

        pthread_t threadID;
        pthread_attr_t attribute;
        pthread_attr_init(&attribute);
        pthread_create(&matrix_thread[count],&attribute,thread,data); /*creates the thread */

        count++; /*increase count of the threads made */
    }

    printf("The count of threads =  %d\n", count);
    printf("\n\n Matrix A:\n");
    printMatrix(N, M, matrixA);
    printf("\n\n Matrix B:\n");
    printMatrix(M, L, matrixB);
    printf("\n\n Matrix C:\n");
    printMatrix(N, L, matrixC);
    
    for(i=0; i < count; i++) {        /*suspends execution of calling thread until the target thread terminates */
        pthread_join(matrix_thread[i], NULL);
    }
    
    return 0;

}


void *thread(void *param) {     /* Working function of thread */
    struct r *data = param;
    int j, k;  
    for(j = 0; j < L; j++){
        double temp = 0;
        for(k = 0; k < M; k++){
            temp+= matrixA[data->row][k] * matrixB[k][j];
        }    
        matrixC[data->row][j] = temp;
    }
    pthread_exit(0);
}


void printMatrix(int nr, int nc, double matrix[nr][nc]) {
    int i, j;
    for (i = 0; i < nr; i++) {
        for(j = 0; j < nc; j++){
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}










