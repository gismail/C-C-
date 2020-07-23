//Threads in C

#include<stdio.h>
#include <stdlib.h> 
#include<pthread.h>
#include <unistd.h>
#include <time.h>

long x, y;

void mytime(int MIN, int MAX){
double s;
s=(rand() % (MAX-MIN+1) + MIN);
printf("J'attend %4.2f ms\n",s/1000);
usleep(s);
}
void thread1(void  *n) {
   fprintf(stdout,"thread number : %ld was created \n", (long)n) ;
    x++;
    fprintf(stdout,"X+ =  %ld \n", x) ;
    mytime(4000, 8000); // attendre entre 4 et 8
    y++;
    fprintf(stdout,"Y+ =  %ld \n", y) ;
   pthread_exit(NULL);

}
void thread2(void  *n) {
   fprintf(stdout,"thread number : %ld was created \n", (long)n) ;
    x=x*2;
    fprintf(stdout,"X* =  %ld \n", y) ;
    mytime(4000, 8000); // attendre entre 4 et 8ms.
    y=y*2;
    fprintf(stdout,"Y* =  %ld \n", y) ;
   pthread_exit(NULL);

}

int main() {

      srand(time(NULL)); //pour generer les valeurs random
      x=y=1;

pthread_t num_thread1,num_thread2;

 
        if (pthread_create(&num_thread1, NULL, (void *(*)())thread1,(void *)1) == -1)
                perror ("pb pthread_create\n");
        if (pthread_create(&num_thread2, NULL, (void *(*)())thread2,(void *)2) == -1)
                perror ("pb pthread_create\n");
    
    

        pthread_join(num_thread1,NULL);
        pthread_join(num_thread2,NULL);
    
    

    
    return 0;
}

/*

le resultats obtenus :
deux cas : 
soit thread1 en premier : dans ce cas là , il affiche X+ puis il attend entre 4 et 8 ms , lors cette durée , thread2 prend le processeurs et affiche X*.
			le Y+ et Y* reste toujours imprédictibles.
soit thread2 en premier : dans ce cas là , il affiche X* puis il attend entre 4 et 8 ms , lors cette durée , thread1 prend le processeurs et affiche X+.
			le Y+ et Y* reste toujours imprédictibles.
la remarque générale : la fonction sleep va suspendre le thread et le processeur devient libre pour d'autres threads (l'ordonnancement des threads ).mais la concurrences entre eux (les threads ) reste toujours imprédictible.

*/