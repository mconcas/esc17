#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5 
#endif
#ifndef FS
#define FS 38
#endif
#define PAD 8

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       temp  =  malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     // omp_set_num_threads(N+1);
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     
	 printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
 
     p = init_list(p);
     head = p;
     int idx;
     // int index=0;
     // struct node* nodearr[N+1];
     start = omp_get_wtime();
     {
        struct node *local_addresses[N+1];
        #pragma omp parallel
        {
        // struct node* local_address;
        idx = omp_get_thread_num();
        // printf(" --- I'm %d\n", idx);
        while (p != NULL) {
        #pragma omp critical
        { 
          local_addresses[idx] = p;
          p = p->next;
        }
          processwork(local_addresses[idx]);
        //           nodearr[index] = p;
        //           index = index + 1;
	//           p = p->next;
        }
        }
        // #pragma omp parallel for
        // for(int i=0; i<N+1; i++){
        //   processwork(nodearr[i]);
        // }
     }
     
     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}

