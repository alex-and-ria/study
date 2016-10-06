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
	int sock; struct sockaddr_in addr,caddr; srand(time(NULL));
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock<0){cout<<"socket"; exit(1);}
	addr.sin_family=AF_INET; addr.sin_port=htons(prt);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock, (struct sockaddr *)&addr,sizeof(addr))<0){
		cout<<"\nbind"; exit(1);
	}
	while(1){
		uint8_t bt; socklen_t slen;
		if(recvfrom(sock,(void *)&bt,sizeof(uint8_t),0,(struct sockaddr *)&caddr,
			&slen)<0){
			cout<<"\nwait for connection"; continue;	
		}
		else{
			for(usi i=0;i<n;i++){
				float sndvr=(float)rand();
				cout<<"\nsndvr="<<sndvr;
				if(sendto(sock,(void *)&sndvr, sizeof(float),0,(struct sockaddr *)&caddr,
					sizeof(caddr))<0){
					cout<<"\nresend"; i--;
				}
			}
			for(usi i=0;i<m;i++){
				double sndvr=(double)rand();
				cout<<"\nsndvr1="<<sndvr;
				if(sendto(sock,(void *)&sndvr, sizeof(double),0,(struct sockaddr *)&caddr,
					sizeof(caddr))<0){
					cout<<"\nresend"; i--;
				}
			}
			sps();
		}
	}
	close(sock);
	return 0;
}
