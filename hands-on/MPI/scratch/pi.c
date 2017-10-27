#include <stdio.h>
#include <omp.h>
#include <mpi.h>

static long num_steps = 100000000;
double integral(double left_b, double right_b, int steps);

int main (int argc, char** argv)
{
  double step, pi_part;
  double pi=0.0;
  int size, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int steps_per_node = num_steps/size;
  double l_b = 0.;
  double r_b = 1.;
  double interval = r_b-l_b;
  double part_interval = interval/size; 
  float start_time = omp_get_wtime();

#pragma omp parallel 
{
#pragma omp single firstprivate(rank) 
{
  pi_part = integral(rank*part_interval, (rank+1)*part_interval,steps_per_node);
}
}
  pi+=pi_part;
  MPI_Reduce(&pi_part, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  float run_time = omp_get_wtime() - start_time;
  MPI_Finalize();
  if(rank == 0) printf("PI GRECO E' %f\n\n\n\n", pi);
  return 0;
}	  

double integral(double left_b, double right_b, int steps)
{
  double delta = right_b - left_b;
  if (steps < 2) {
    double x = left_b + delta*0.5;
    return 4.0*delta/(1.0 + x*x);
  } else {
    double x,y;
#pragma omp task shared(x)
    x = integral(left_b, left_b + delta/2, steps/2);
#pragma omp task shared(y)
    y = integral(left_b + delta/2, right_b, steps/2);
#pragma omp taskwait
    return x + y;  
  }
}
