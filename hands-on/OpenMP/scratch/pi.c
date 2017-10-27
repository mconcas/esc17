/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step, pi;
double integral(double left_b, double right_b, int steps);

int main ()
{
	  float start_time = omp_get_wtime();
#pragma omp parallel
{
#pragma omp single
{
          pi = integral(0., 1., num_steps);
}
}
	  float run_time = omp_get_wtime() - start_time;
	  printf("\npi with %ld steps is %lf in %lf seconds\n",num_steps,pi,run_time);
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
