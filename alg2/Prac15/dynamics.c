#define NSTEPS 2000
#define G 9.8

#include <stdio.h>
#include <math.h>
#include <omp.h>

typedef struct{
  double x,y;
  double v_x, v_y;
  double dv_x,dv_y;
  double m;
}Object;

int main(){
  int step,flag=0;
  double st,et;

  Object ball,ball2;
  double v0=100.0 , dt=0.01; 

  /* Initialization step */
  printf("Number of processors: %d\n",omp_get_num_procs());
  printf("Max threads: %d\n",omp_get_max_threads());

  ball.x = 0.0;
  ball.y = 495.0;
  ball.v_x = v0*cos(M_PI/6.0);
  ball.v_y = v0*sin(M_PI/6.0);
  ball.m = 1.0;


  st = omp_get_wtime();
  // Compute sequentially（逐次）
  for(step = 0; step < NSTEPS; step++){
    ball.x += ball.v_x * dt;   // dx += dv*dt
    ball.y += ball.v_y * dt;

    ball.dv_x = 0;              //m*dv/dt = F (Newton's 2nd law of motion)
    ball.dv_y = (-ball.m*G)/ball.m*dt;   // ---> dv = F/m*dt

    ball.v_x += ball.dv_x;    // v += dv
    ball.v_y += ball.dv_y;

    printf("%6.3f,%6.3f     (%d)\n",ball.x,ball.y,omp_get_thread_num());
  }
  et = omp_get_wtime();

  printf("sequentially: %5.3f sec.\n",et-st);

  printf("\n\n");


  ball2 = ball;

  ball.x = 0.0;
  ball.y = 495.0;
  ball.v_x = v0*cos(M_PI/3.0);
  ball.v_y = v0*sin(M_PI/3.0);
  ball.m = 1.0;


  st = omp_get_wtime();
  // Compute in parallel（並列）
#pragma omp parallel for
  for(step = 0; step < NSTEPS; step++){
    ball.x += ball.v_x * dt;   // dx += dv*dt
    ball.y += ball.v_y * dt;

    ball.dv_x = 0;              //m*dv/dt = F (Newton's 2nd law of motion)
    ball.dv_y = (-ball.m*G)/ball.m*dt;   // ---> dv = F/m*dt

    ball.v_x += ball.dv_x;    // v += dv
    ball.v_y += ball.dv_y;


    printf("%6.3f,%6.3f     (%d)\n",ball.x,ball.y,omp_get_thread_num());
  }
  et = omp_get_wtime();

  printf("at parallel: %5.3f sec.\n",et-st);


  printf("Position Error:\n");
  printf("x:%f y:%f\n",ball2.x-ball.x,ball2.y-ball.y);

  return 0;
}
