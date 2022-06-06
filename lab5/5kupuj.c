
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <pthread.h>
#define N_GOODS  40
struct shared_memory {
	int NRatings[N_GOODS];
	double Ratings[N_GOODS];
	pthread_mutex_t mut;
}memory;

struct shared_memory *mem;

#define N_CUSTOMERS 20
#define N_ROUNDS 1000000
#define RATING 10

int main()
{

int child[N_CUSTOMERS];
//srand(time(NULL));
//int N_GOODS = 40;
//int N_CUSTOMERS =1;
//int N_ROUNDS = 1000000;
//int RATING = 10;
//struct shared_memory {
//	int NRatings[N_GOODS];
//	double Ratings[N_GOODS];
//};
//struct shared_memory memory;
//memory *mem;
	int      key;       /* key to be passed to shmget() */
	int      shmflg;    /* shmflg to be passed to shmget() */
 	int      shmid;     /* return value from shmget() */
	int size = sizeof ( struct shared_memory);
	shmflg = IPC_CREAT;

	if ((shmid = shmget (key, size, 0660 | shmflg )) == -1) {
 		perror("shmget: shmget failed");
 		exit(1);
 	} else {
 		(void) fprintf(stderr,
 					"shmget: shmget returned %d\n", shmid);
// 		exit(0);
 	}
int status;
int suma =0;

mem = (struct shared_memory*) shmat(shmid, NULL, 0);

pthread_mutexattr_t attr;
pthread_mutexattr_init(&attr);
pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
//pthread_mutex_init(&mem->mut, &attr);
pthread_mutex_init(&mem->mut, &attr);

//zerowanie
for (int i=0; i<N_GOODS;i++){//memory.NRatings[i]=0; memory.Ratings[i]=0; 
mem->Ratings[i]=0; mem->NRatings[i]=0;};

for (int k=0;k<N_CUSTOMERS;k++)
{ if((child[k]=fork())==0)
{
mem = (struct shared_memory*) shmat(shmid, NULL, 0);
if(mem == NULL) { perror("shmat"); exit(-1); }
//dodac sprawdzanie bledu mem == NULL
int x =0;
double y=1;
//int suma =0;

//Czysczcenie zawrtosci tablic
//for (int i=0; i<N_GOODS;i++){//memory.NRatings[i]=0; memory.Ratings[i]=0; 
//mem->Ratings[i]=0; mem->NRatings[i]=0;};
//printf("czyszczenie\n");
for (int i = 0; i < N_ROUNDS; i++)
{	srand(NULL+k+i);
	 x = rand()%(N_GOODS);
	 y = rand()%(RATING + 1 -0) + 0;

	//Blokowanie
	pthread_mutex_lock(&mem->mut);
/*Dostęp do pamięci wspóldzielonej */
	mem->NRatings[x]++;
	mem->Ratings[x] = ((((mem->NRatings[x])-1) * mem->Ratings[x] + y) /mem->NRatings[x]);		
//Odblokowywanie
	pthread_mutex_unlock(&mem->mut);

}
exit(1);
}else {};
}
for (int i=0;i<N_CUSTOMERS;i++) {wait(&status);};
for (int i=0; i < N_GOODS; i++)
{
 printf("Indeks: %-2d | Ilość sztuk: %-3d | Sr ocena %-3f |\n", i,  mem->NRatings[i], mem->Ratings[i]);
 suma = suma + ((*mem).NRatings[i]);
}
printf("\n\tSuma zakupionych produktów: %d \n",suma);
return 0;
}
