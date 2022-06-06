#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <sys/socket.h>

#define SERVER_SOCET "/tmp/adres_253191"

int main(){
	int sock;
	socklen_t serv_len, cli_len;
	struct sockaddr_un serv_addrstr, cli_addrstr;
	char buf[BUFSIZ];
	int N_RATING[40];
	double RATINGS[40];
	int N_GOODS = 40;
	int N_CUSTOMERS = 20;
	int N_ROUNDS = 100;
	int RATING = 10;
	int c, i, shmid;
	int suma = 0;

	printf("DEKLARACJA_ZMIENNYCH");

	sock = socket(PF_UNIX, SOCK_DGRAM, 0);
	serv_addrstr.sun_family = AF_UNIX;
	strcpy(serv_addrstr.sun_path, SERVER_SOCET);

	unlink(SERVER_SOCET);
	serv_len = sizeof(serv_addrstr);
	if (-1==bind(sock, (struct sockaddr *)&serv_addrstr, serv_len)) {
		exit(-1);
	}


	for(i=0; i<N_GOODS; ++i){
		RATINGS[i] = 0;
		N_RATING[i] = 0;
	}
	for(i=0;c < N_CUSTOMERS; i++){
		if(fork()==0){
			srand(getpid());

			int towar, ocena;
			for(i=0; i<N_ROUNDS; ++i){
				towar = rand()%N_GOODS;
				ocena = rand()%(RATING+1);
				memcpy((void *)buf, (void *)&towar, sizeof(int));
				memcpy((void *)(buf+sizeof(int)), (void *)&ocena, sizeof(int));
				sendto(sock, buf, 2*sizeof(int), 0, (struct sockaddr *) &serv_addrstr, serv_len);
			}
			exit(1);
		}

	printf("PETLA");

	}

	int n,towar,ocena;
	for(i=0; i<N_CUSTOMERS*N_ROUNDS; i++){

		n = recvfrom(sock, buf, 2*sizeof(buf), 0,(struct sockaddr *)&cli_addrstr, &cli_len);

		if(n==-1){
			printf("read err\n");
		}else if (n!=2*sizeof(int)){
			printf("read err\n");
		}else{
			memcpy((void *)&towar, (void *)buf, sizeof(int));
			memcpy((void *)&ocena, (void *)(buf+sizeof(int)), sizeof(int));
		}

		N_RATING[towar]++;
		RATINGS[towar] += ocena;

	}
	for(i=0; i<N_GOODS; ++i){
		RATINGS[i]=RATINGS[i]/N_RATING[i];
		suma += N_RATING[i];
	}

	printf("TOWAR \t ZAKUPIONO \t OCENA\n");
	for(i=0; i<N_GOODS; ++i){
		printf("%d \t %d \t \t %f\n",i+1,N_RATING[i],RATINGS[i]);
	}
	printf("\nSuma: %d\n",suma);
}


