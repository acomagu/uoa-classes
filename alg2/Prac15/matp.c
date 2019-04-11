#define N 1024

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int main(){
  int i,j,k ,err;
  int **A, **B, **C, **C2;
  double st,et;

  /* Initialization step */
  printf("Number of processors: %d\n",omp_get_num_procs());
  printf("Max threads: %d\n",omp_get_max_threads());

  A = (int **)malloc(N * sizeof(int *));
  B = (int **)malloc(N * sizeof(int *));
  C =  (int **)malloc(N * sizeof(int *));
  C2 = (int **)malloc(N * sizeof(int *));
  for (i = 0; i < N; i++) {
    A[i] = (int *)malloc(N * sizeof(int));
    B[i] = (int *)malloc(N * sizeof(int));
    C[i] =  (int *)malloc(N * sizeof(int));
    C2[i] =  (int *)malloc(N * sizeof(int));
  }

  srand(time(NULL));
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = rand()%10-5;
      B[i][j] = rand()%10-5;
      C[i][j] = 0;
      C2[i][j] = 0;
    }
  }



  st = omp_get_wtime();
  // Compute sequentially（逐次）
  for(i=0; i<N; i++) {
    for(j=0; j<N; j++) {
      for(k=0; k<N; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  et = omp_get_wtime();

  printf("sequetially: %5.3f sec.\n",et-st);



  st = omp_get_wtime();
  // Compute in parallel（並列）
#pragma omp parallel for private(j,k)
  for(i=0; i<N; i++) {
    for(j=0; j<N; j++) {
      for(k=0; k<N; k++) {
        C2[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  et = omp_get_wtime();

  printf("at parallel: %5.3f sec.\n",et-st);



  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      err = C[i][j]-C2[i][j];
      if(err!=0) printf("Error at C2[%d,%d] : %d\n",i,j,err);
    }
  }


  for (i = 0; i < N; i++) {
    free(A[i]);
    free(B[i]);
    free(C[i]);
    free(C2[i]);
  }
  free(A);
  free(B);
  free(C);
  free(C2);

  return 0;
}
