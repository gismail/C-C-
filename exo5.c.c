//Threads in C

#include<stdio.h>
#include <stdlib.h> 
#include<pthread.h>
#include <time.h>
#include <stdlib.h>


#define N 10

long max_val;


void thread(void  *n) {
   fprintf(stdout,"numero de thread : %ld\n", (long)n) ;

   long val=(rand() % (1000 - 1 + 1)) + 1;
    fprintf(stdout,"la valeur genere : %ld\n", val) ;
    if(val>max_val)
        max_val=val;
   pthread_exit(NULL);

}

int main() {

       srand(time(NULL)); //pour generer les valeurs random
      max_val=0;
    
pthread_t num_thread[N];

    for(long i=0; i<N;i++){
        if (pthread_create(&num_thread[i], NULL, (void *(*)())thread,(void *)i) == -1)
                perror ("pb pthread_create\n");
    }
    
    for(long i=0;i<N;i++){
        pthread_join(num_thread[i],NULL);
    }
    
    printf("la valeur maximal est : %ld\n",max_val);
    
    return 0;
}