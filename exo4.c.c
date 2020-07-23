//Threads in C

#include<stdio.h>
#include <stdlib.h> 
#include<pthread.h>
#include <time.h>
#include <stdlib.h>


#define N 20
long tableau[N];
long tableau_val[N];
long max_val;


void thread(void  *n) {
   fprintf(stdout,"numero de thread : %ld\n", (long)n) ;

   tableau[(long)n]=(rand() % (1000 - 1 + 1)) + 1;
   long max=0;
   for(long i=0;i<N;i++){
    if(tableau[i]>max)
        max=tableau[i];
    }
      
   pthread_exit((void *)max);

}

int main() {
     void *messageRenvoyer ;
       srand(time(NULL)); 
      
    
pthread_t num_thread[N];

    for(long i=0; i<N;i++){
        if (pthread_create(&num_thread[i], NULL, (void *(*)())thread,(void *)i) == -1)
                perror ("pb pthread_create\n");
    }
    
    for(long i=0;i<N;i++){
        pthread_join(num_thread[i],&messageRenvoyer);
        fprintf(stdout,"message renvoye %ld\n",(long) messageRenvoyer) ;
        tableau_val[i]=(long) messageRenvoyer;
    }
    
    for(long i=0;i<N;i++){
       if(tableau_val[i]>max_val)
           max_val=tableau_val[i];
    }
    printf("la valeur maximal est : %ld\n",max_val);
    
    return 0;
}