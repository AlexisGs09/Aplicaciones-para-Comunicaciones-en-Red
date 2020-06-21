#include<ctype.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<signal.h> 
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define SIZE sizeof(struct sockaddr_in) 

void check (char tabJugada[][3]); 
int newsockfd[2]; 
int pid[2];

int main(void){ 
	int sockfd[2]; 
	char serverRead[1];
	char ans[1];
	int usr=0;
	int ctr=1;
	int row = 0;
	int column = 0;
	int choice=0;
	char x[4];
	char a[2][40];
    char tabJugada [3][3] = {							
			         		{' ',' ',' '},
							{' ',' ',' '},
		       				{' ',' ',' '}
	                        };
	
	struct sockaddr_in server = {AF_INET, 8001, INADDR_ANY}; 
	strcpy(ans,"");
	static struct sigaction act,act2;  
	sigfillset(&(act.sa_mask)); 
	sigaction(SIGPIPE, &act, 0); 
	sigaction(SIGTSTP, &act, 0);
	sigaction(SIGINT, &act, 0);

	if ((sockfd[0] = socket(AF_INET, SOCK_STREAM, 0)) == -1){ 
		perror("Conexion fallida"); 
		exit(1); 
		} 

	if (bind(sockfd[0], (struct sockaddr *)&server, SIZE) == -1){ 
		perror("Conexion fallida"); 
		exit(1); 
		}

	printf("\nJuego del gato");
	printf("\nEsperando jugadores.. \n");

	strcpy(a[0],"Esperando otro jugador\n");

	while(usr<2){
		if ( listen(sockfd[0], 5) == -1 ){ 
			perror("Conexion fallida\n"); 
			exit(1) ; 
		}
		
		newsockfd[usr] = accept(sockfd[0], 0, 0);
		usr++;

		if (usr==1){	
			strcpy(a[1],"0");
			write(newsockfd[0],a,sizeof(a));
			read(newsockfd[0],x,sizeof(x));
			pid[0]=atoi(x);
									
		}

		printf("Numero de jugadores: %d\n",usr);
	
		if (usr==2){
			strcpy(a[0],"Iniciando el juego");
			strcpy(a[1],"1");
			write(newsockfd[0],a,sizeof(a));
			strcpy(a[1],"2");
			write(newsockfd[1],a,sizeof(a));
			read(newsockfd[1],x,sizeof(x));
			pid[1]=atoi(x);
		} 	
	}	
	
		if ( fork() == 0){
			int count=0; 		
			
			while (count==0){ 	
			
				read(newsockfd[ctr], serverRead, sizeof(serverRead));			
				choice = atoi(serverRead);
				printf("Numero elegido por el cliente: %d\n",choice);
				row = --choice/3;
	       			column = choice%3;
				tabJugada[row][column] = (ctr==0)?'X':'O';
							
				if(ctr == 1)
					ctr = 0;
				else
					ctr = 1;
				
				write(newsockfd[ctr],tabJugada,sizeof(tabJugada)); 
				check(tabJugada);				
				
			}
			
			close(newsockfd[0]);
			exit (0);
		} 	
			wait();
			close(newsockfd[1]);
		}

void check (char tabJugada[][3]){
	  int i;
	  char key = ' ';

	  
	  for (i=0; i<3;i++)
	  if (tabJugada [i][0] == tabJugada [i][1] && tabJugada [i][0] == tabJugada [i][2] && tabJugada [i][0] != ' ') key = tabJugada [i][0];	
	  
	  for (i=0; i<3;i++)
	  if (tabJugada [0][i] == tabJugada [1][i] && tabJugada [0][i] == tabJugada [2][i] && tabJugada [0][i] != ' ') key = tabJugada [0][i];
	  if (tabJugada [0][0] == tabJugada [1][1] && tabJugada [1][1] == tabJugada [2][2] && tabJugada [1][1] != ' ') key = tabJugada [1][1];
	  if (tabJugada [0][2] == tabJugada [1][1] && tabJugada [1][1] == tabJugada [2][0] && tabJugada [1][1] != ' ') key = tabJugada [1][1];

	  if (key == 'X'){

		   printf("GANO EL JUGADOR 1!!\n\n");
	           kill(pid[0], SIGUSR1);
		   kill(pid[1], SIGUSR1);
		   exit (0); 
	  }

	  if (key == 'O'){
		   printf("GANO EL JUGADOR 2!!\n\n");
		   kill(pid[0], SIGUSR2);
		   kill(pid[1], SIGUSR2);
		   exit (0);
	    }	
}
