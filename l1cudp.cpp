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

int main(){
	int sock; struct sockaddr_in addr;
	sock=socket(AF_INET,SOCK_DGRAM, 0);
	if(sock<0){cout<<"socket"; exit(1);}
	addr.sin_family=AF_INET; addr.sin_port=htons(prt);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    while(1){
    	uint8_t bt;
    	if(sendto(sock,&bt,sizeof(uint8_t),0,(struct sockaddr *)&addr,sizeof(addr))<0){
    		cout<<"\ntrying establish connection"; continue;
    	}
    	else{
			for(usi i=0;i<n;i++){
				float recvvr;
				if(recvfrom(sock,(void *)&recvvr, sizeof(float),0,NULL,NULL)<0){
					cout<<"\nrecv err"; i--;
				}
				else cout<<"\nrecvvr="<<recvvr;
			}
			for(usi i=0;i<m;i++){
				double recvvr;
				if(recvfrom(sock,(void *)&recvvr, sizeof(double),0,NULL,NULL)<0){
					cout<<"\nrecv err"; i--;
				}
				else cout<<"\nrecvvr1="<<recvvr;
			}
			cout<<'\n';
		}
    }
    close(sock);
    return 0;
}
