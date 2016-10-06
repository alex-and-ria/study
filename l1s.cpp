#include<iostream>
#include<cstdlib>//exit();
#include<stdio.h>//sps();
#include <sys/types.h>
#include <sys/socket.h>
#include<unistd.h>//close(sock);
#include<netinet/in.h>
using namespace std;
#define n 2
#define m 5
#define prt 2558
typedef unsigned short int usi;

inline void sps(void){
    cout<<"\npak..."; getc(stdin);
    printf("\033[1A");
}

int main(){
	int sock,lsnr; struct sockaddr_in addr; srand(time(NULL));
	lsnr=socket(AF_INET, SOCK_STREAM, 0);
	if(lsnr<0){cout<<"socket"; exit(1);}
	addr.sin_family=AF_INET; addr.sin_port=htons(prt);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(lsnr, (struct sockaddr *)&addr,sizeof(addr))<0){
		cout<<"\nbind"; exit(1);
	}
	listen(lsnr,1);
	while(1){
		sock=accept(lsnr,NULL,NULL);
		if(sock<0){cout<<"\naccept"; exit(1);}
		while(1){
			for(usi i=0;i<n;i++){
				float sndvr=(float)rand();
				cout<<"\nsndvr="<<sndvr;
				if(send(sock,(void *)&sndvr, sizeof(float),0)<0){
					cout<<"\nresend"; i--;
				}
			}
			for(usi i=0;i<m;i++){
				double sndvr=(double)rand();
				cout<<"\nsndvr1="<<sndvr;
				if(send(sock,(void *)&sndvr, sizeof(double),0)<0){
					cout<<"\nresend"; i--;
				}
			}
			sps();
		}
		close(sock);
	}
	return 0;
}
