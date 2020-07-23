//Threads in C

#include<stdio.h>
#include<pthread.h>
#define N 10

void thread(void  *n) {
   fprintf(stdout,"numero de thread : %ld\n", (long)n) ;
   long p= ((long)n)*2;
   pthread_exit((void *)p);

}

int main() {
    void *messageRenvoyer ;
pthread_t num_thread[N];

    for(long i=0; i<N;i++){
        if (pthread_create(&num_thread[i], NULL, (void *(*)())thread,(void *)i) == -1)
                perror ("pb pthread_create\n");
    }
    


    for(int i=0;i<N;i++){
        pthread_join(num_thread[i],&messageRenvoyer);
        fprintf(stdout,"message renvoye %ld\n",(long) messageRenvoyer) ;
    }


    return 0;
}