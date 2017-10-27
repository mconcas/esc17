#include <omp.h>
#include <stdio.h>

int main() {
  omp_set_num_threads(2);
  printf("I think");
  #pragma omp parallel
  {
    #pragma omp single
    {
      #pragma omp task
      printf(" race");
      #pragma omp task
      printf(" car");
    }
  }
    printf("s");
    printf(" are fun\n");
}
