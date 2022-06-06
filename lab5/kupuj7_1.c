#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#define N_GOODS  40
#define N_CUSTOMERS 20
#define N_ROUNDS  100000
#define RATING 10
#define SERVER_SOCKET "/tmp/adres_253191_1"
#define MAX_SIZE 64

int main()
{
    FILE *fp;
    int x,y,n;
    int recived=0;
    int sum=0;
    int sock;
    socklen_t serv_len;
    struct sockaddr_un serv_addrstr;
    char message[BUFSIZ];
    double RATINGS[40];
    int N_RATINGS[40];
    sock = socket(PF_UNIX, SOCK_DGRAM, 0);
    serv_addrstr.sun_family = AF_UNIX;
    strcpy(serv_addrstr.sun_path, SERVER_SOCKET);
    unlink(SERVER_SOCKET);
    serv_len = sizeof(serv_addrstr);
    if (bind(sock,(struct sockaddr *)&serv_addrstr, serv_len) == -1)
    {
        perror ("BIND ERROR");
        exit(-1);
    }

    struct timespec timeout = {0, 100};

    for (int i=0;i<N_GOODS;i++){
        RATINGS[i]=0;
        N_RATINGS[i]=0;
    }
    int child[N_CUSTOMERS];
    for (int k=0;k<N_CUSTOMERS;k++)
    {
        if((child[k]=fork())==0)
        {
            for (int i = 0; i < N_ROUNDS; i++)
            {
                int x,y;
                srand(time(NULL)+i+k);
                x = rand()%(N_GOODS);
                y = rand()%(RATING + 1 -0) + 0;
                memcpy((void *)message, (void *)&x, sizeof(int));
                memcpy((void *)(message+sizeof(int)), (void *)&y, sizeof(int));
                sendto(sock, message, 2*sizeof(int), 0,
                (struct sockaddr *) &serv_addrstr, serv_len);
            }
        exit(1);
        }
    }
    while(1)
    {
        n=recvfrom(sock, &message, sizeof(message),0, (struct sockaddr*)0,0);
        if (n==-1)
        {
            perror("read_err recvfrom \n");
        }
        else if (n!=2*sizeof(int))
        {
            printf("read_err recvfrom \n");
        }
        else
        {
            memcpy((void *)&x, (void *)message, sizeof(int));
            memcpy((void *)&y, (void *)(message+sizeof(int)), sizeof(int));
            N_RATINGS[x] += 1;
	    RATINGS[x] =((N_RATINGS[x]-1) * RATINGS[x] + y)/N_RATINGS[x];
            recived++;
        }
        if (recived == N_CUSTOMERS*N_ROUNDS)
        {
            break;
        }
    }

    printf("TOWAR \t ZAKUPIONO \t OCENA\n");

    for (int i=0; i < N_GOODS; ++i)
    {
        printf("%d \t %d \t \t %f\n",i,N_RATINGS[i],RATINGS[i]);
        sum = sum + N_RATINGS[i];
    }
    printf("Suma towarow: %d\n", sum);
}
