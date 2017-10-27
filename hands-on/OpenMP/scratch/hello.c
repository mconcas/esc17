#include <stdio.h>
#include <omp.h>

int main ()  
{
omp_set_num_threads(666);
#pragma omp parallel
{
  printf("Hello World ");
  printf("Mom\n");
}
}
