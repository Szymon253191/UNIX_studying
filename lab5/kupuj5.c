
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include <stdio.h>
#include <string.h>

/*
//pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t recmutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

//int pthread_mutex_trylock(pthread_mutex_t *mutex;
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);


int pthread_mutex_lock(pthread_mutex_t *mutex);
*/

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

double RATINGS[40];
int NRATINGS[40];
int suma;
double cpuUsedTime;

int main(){
    int N_ROUNDS = 1000000;
    int N_GOODS = 40;
    int a ,b;
    int CUSTOMERS = 20;
    int ChildPid[CUSTOMERS];
    int wpid;
    int status = 0;
    for ( int k = 0; k <N_GOODS;k++){NRATINGS[k] =0; RATINGS[k] =0;};
   int shmid = shmget(2211,(sizeof(RATINGS) + sizeof(NRATINGS)), IPC_CREAT|0666);

//clock_t startZerowanie = clock();
   double *buf;
   buf = (double *)shmat(shmid,0,0);
   for (int g = 0; g<=N_GOODS*2;g++)
   {
      buf[g] = 0;
   }

unsigned long howMany = 1;

//clock_t stopZerowanie = clock();
//float czasZerowanie = (float)(stopZerowanie - startZerowanie) / CLOCKS_PER_SEC;
//printf("Czas zerowania: %f\n", czasZerowanie);
//clock_t startKupowanie

    for ( int h = 0; h < CUSTOMERS;h++){
	counter += 1;
        if(fork() == 0)
        {
//	clock_t startKupowanie = clock();
            for (int j = 0; j < N_ROUNDS; j++) {
	pthread_mutex_t  = PTHREAD_MUTEX_INITILIZER;
	pthread_mutex_lock(&mut);
            srand(time(NULL)+j);
		    b = rand() % N_GOODS;
            NRATINGS[b] += 1;
		    a = rand() % 11;
		    RATINGS[b] = (((NRATINGS[b]-1)* RATINGS[b] + a)/NRATINGS[b]);
            buf[b] += 1;
            buf[b+N_GOODS] = RATINGS[b];
            }
	exit(1);
	pthread_mutex_unlock(&mut);
        }
    }
    for (int i=0;i<=CUSTOMERS;i++)
    {
     wait(NULL);
    }
//clock_t stopKupowanie = clock();
//float czasKupowanie = (stopKupowanie - startKupowanie) / CLOCKS_PER_SEC;
//printf("Czas kupowania: %f\n", czasKupowanie);

//clock_t startOcenianie = clock();
    for (int k = 0; k < N_GOODS; k++) {
    printf("RATING %d [%lf] NRATINGS %d [%lf]\n",k, buf[k+N_GOODS],k ,buf[k]);
    suma += buf[k];
    }
//clock_t stopOcenianie = clock();
//float czasOcenianie = (stopOcenianie - startOcenianie) / CLOCKS_PER_SEC;
//printf("Czas oceniania: %f\n", czasOcenianie);

    printf("suma %d\n",suma);
return 0;
}
