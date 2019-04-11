#define N 10000000

#include <stdio.h>
#include <omp.h>


int A[N],B[N];
int Cs[N],Cp[N];

int main(){
  int i,flag=0;
  double st,et;

  /* Initialization step */
  printf("Number of processors: %d\n",omp_get_num_procs());
  printf("Max threads: %d\n",omp_get_max_threads());

  for(i=0;i<N;i++){
    A[i]=-i;
    B[i]=i;
  }


  st = omp_get_wtime();
  // Compute sequentially（逐次）
  for(i=0;i<N;i++){
    Cs[i] = A[i]+B[i];
  }
  et = omp_get_wtime();

  printf("sequentially: %5.3f sec.\n",et-st);


  st = omp_get_wtime();
  // Compute in parallel（並列）
#pragma omp parallel for
  for(i=0;i<N;i++){
    Cp[i] = A[i]+B[i];
  }
  et = omp_get_wtime();

  printf("at parallel: %5.3f sec.\n",et-st);





  for(i=0;i<N;i++){
    if(Cp[i]-Cs[i]!=0){
      printf("Error at %d, (%d)\n",i,Cp[i]-Cs[i]);
      flag=1;
    }
  }
  if(flag==0) printf("Parallelized code worked correctly!!\n");

  return 0;
}

