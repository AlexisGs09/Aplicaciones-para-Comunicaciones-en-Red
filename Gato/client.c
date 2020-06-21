#include<ctype.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE sizeof(struct sockaddr_in) 

int play();
int menu(void);
void tablero(char tabJugada[][3]);
void jugadorGana(int signum);
int te=0;

int main(void){
    printf("\nJuego del gato");
	while(1){
		switch(menu()){
			case 1:{
				printf("\nJugar\n\n");
				play();
				break;
			}
			case 2:{
				printf("\nSalir\n\n");
				exit(0);
				break;
			}
			default:{
				printf("\nOpcion invalida\n\n");
				break;
			}
		}
	}
}

int play(void){
	void result(char [],char []);
	static struct sigaction act; 
	act.sa_handler = SIG_IGN; 
	sigfillset(&(act.sa_mask)); 
	sigaction(SIGTSTP, &act, 0);
	signal(SIGUSR1,jugadorGana);
	signal(SIGUSR2,jugadorGana);
	struct sockaddr_in server = {AF_INET, 8001}; 
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	int sockfd,i; 
	int fil,col,choice;
	int iclientRead; 		
	char input; 
	char a[2][40];
	char pid[4];
	char clientRead[3][3];
	char clientWrite[1];
	char tabNumeros [3][3] = {							
	 		         		{'1','2','3'},
		        			{'4','5','6'},
		       				{'7','8','9'}
	       		        	}; 

        char tabJugada [3][3] = {							
			         		{' ',' ',' '},
							{' ',' ',' '},
		       				{' ',' ',' '}
	                        };


	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Conexion fallida");
		exit(1);
	}

	if ( connect (sockfd, (struct sockaddr *)&server, SIZE) == -1) { 
		perror("Conexion fallida"); 
		exit(1); 
	} 
	
	read(sockfd,a,sizeof(a));
	printf("%s\n",a[0]);

	if(strcmp(a[1],"0")==0){
		int num1 = getpid();
		sprintf(pid,"%d",num1);
		write(sockfd, pid, sizeof(pid));	
		read(sockfd,a,sizeof(a));
		printf("%s\n",a[0]);
	}

	if(strcmp(a[1],"2")==0){
		int num2 = getpid();
		sprintf(pid,"%d",num2);
		write(sockfd, pid, sizeof(pid));	
	}
	
	if (strcmp(a[1],"1")!=0){
		tablero(tabNumeros);	
	
		for(;;){
			printf("\nElije el numero de la casilla para jugar '%c': \n",(strcmp(a[1], "1")==0)?1:2,(strcmp(a[1], "1")==0)?'X':'O');
			scanf("%s",clientWrite);

			choice = atoi(clientWrite);
			fil = --choice/3;
			col = choice%3;
		
			if(choice<0 || choice>9 || tabJugada [fil][col]>'9'|| tabJugada [fil][col]=='X' || tabJugada [fil][col]=='O'){
				printf("Casilla ocupada, intente de nuevo.\n\n");
			}
			else{
				tabJugada[fil][col] = (strcmp(a[1], "1")==0)?'X':'O';					
				break;
			}
		}	

		write(sockfd, clientWrite, sizeof(clientWrite));	
		tablero(tabJugada);
	}

	for(input = 'x';;){ 	
		if (input == '\n'){	
			if (te==0){
				//tablero(numberBoard);	
			}					
			for(;;){	
				if (te==0){
					printf("\nElige el numero de la casilla para jugar '%c': \n",(strcmp(a[1], "1")==0)?1:2,(strcmp(a[1], "1")==0)?'X':'O');
					scanf("%s",clientWrite);
			
					choice = atoi(clientWrite);
					fil = --choice/3;
					col = choice%3;
			
					if(choice<0 || choice>9 || tabJugada [fil][col]>'9'|| tabJugada [fil][col]=='X' || tabJugada[fil][col]=='O'){
						printf("Casilla ocupada, intente de nuevo\n\n");
					}
					else{
						tabJugada[fil][col] = (strcmp(a[1], "1")==0)?'X':'O';
						break;
					}
				}
			}	
			
			write(sockfd, clientWrite, sizeof(clientWrite));
			system("clear");
			tablero(tabJugada);
			if (te==1){
				printf("\nGANO EL JUGADOR 1!!\n");
				exit(0);
			}
   			if (te==2){
				printf("\nGANO EL JUGADOR 2!!\n");
				exit(0);
   			}
		}

		if (read(sockfd, clientRead, sizeof(clientRead)) >0) {
			system("clear");
			memcpy(tabJugada, clientRead, sizeof(tabJugada));
			tablero(tabJugada);
			input = '\n';
			if (te==1){
				printf("GANO EL JUGADOR 1!!\n");
				exit(0);
			}
   			if (te==2){
				printf("GANO EL JUGADOR 2!!\n");
				exit(0);
   			}
		}	
		else {
			close(sockfd);
			exit(1); 
		} 
	}
}

void tablero(char tabJugada[][3]){
        printf(" _________________\n");
        printf("|     |     |     | \n");
        printf("|  %c  |  %c  |  %c  |\n",tabJugada[0][0],tabJugada[0][1],tabJugada[0][2]);
        printf("|_____|_____|_____|\n");
        printf("|     |     |     |\n");
        printf("|  %c  |  %c  |  %c  |\n",tabJugada[1][0],tabJugada[1][1],tabJugada[1][2]);
        printf("|_____|_____|_____|\n");
        printf("|     |     |     |\n");
        printf("|  %c  |  %c  |  %c  |\n",tabJugada[2][0],tabJugada[2][1],tabJugada[2][2]);
        printf("|_____|_____|_____|\n");
	}

int menu(void){
	int o;
	printf("\n1.Jugar.\n\n");
	printf("\n2.Salir.\n\n");
	scanf("%d", &o);
	return o;
}

void jugadorGana(int signum){
    if (signum == SIGUSR1){
        te=1;
    }
    if (signum == SIGUSR2){
	te=2;
    }
}
