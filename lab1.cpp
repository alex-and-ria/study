#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include <winbgim.h> 
#define tstlnsz 10
#define slnsz 20
#define llnsz 60
#define scl 50
typedef unsigned short int usi;
using namespace std;

bool gff(string ifn,usi *aq1, usi *aq2){
	ifstream fpi;
    fpi.open(ifn.c_str(),ios::binary);
    if(!fpi.is_open()) {cout<<"\nerr: getaltff no input file"; return 0;}
    else{
    	usi i=0,cnt=0; unsigned char ch;
		while(1){
			fpi>>ch; //cout<<ch<<' ';
			if(fpi.eof()) break;
			if(ch!=' '&&i%2==0) {aq1[cnt]=ch-'0'; i++;}
			else if(ch!=' '&&i%2==1) {aq2[cnt]=ch-'0'; i++; cnt++;}
		}
     fpi.close();    
    }
    return 1;
}

inline void ct1(usi* q1,usi* q2,usi sz){
	for(usi i=0;i<sz;i++) cout<<setw(3)<<left<<i; cout<<'\n';
	for(usi i=0;i<sz;i++) cout<<setw(3)<<left<<q1[i]; cout<<'\n';
	for(usi i=0;i<sz;i++) cout<<setw(3)<<left<<q2[i];
}

bool pptc(usi* q1,usi* q2,usi sz, usi* out,bool p){
	for(usi i=0;i<sz;i++) out[i]=100;
	usi i=0,j=1;
	m2: while(i<sz-1){
		 if(out[i]==100||out[j]==100){
			if((q1[i]>q1[j]&&q2[i]>=q2[j] || q1[i]>=q1[j]&&q2[i]>q2[j]) && p ||
				(q1[i]>q1[j]&&q2[i]>q2[j] || q1[i]>q1[j]&&q2[i]>q2[j]) && !p){
				out[j]=i;
				if(j<sz-1) {j++; goto m2;}
				else if(i<sz-1){i++; j=i+1; goto m2;}
				else break;
			}
			else if((q1[j]>q1[i]&&q2[j]>=q2[i] || q1[j]>=q1[i]&&q2[j]>q2[i]) && p ||
					(q1[j]>q1[i]&&q2[j]>q2[i] || q1[j]>q1[i]&&q2[j]>q2[i])&& !p){
				out[i]=j;
				if(i<sz-1){i++; j=i+1; goto m2;}
				else break;
			}
			else{
				if(j<sz-1) {j++; goto m2;}
				else if(i<sz-1){i++; j=i+1; goto m2;}
				else break;
			}
		}
		else{
			if(out[i]!=100) i++;
			if(out[j]!=100 &&j<sz-1) j++;
		}
	}
	if(p){
	cout<<"\n\n";
		for(usi i=0;i<sz;i++){
			if(i==25||i==50) cout<<'\n';
			cout<<setw(3)<<left<<i;
		} cout<<'\n';
		for(usi i=0;i<sz;i++){
			if(i==25||i==50) cout<<'\n';
			cout<<setw(3)<<left<<q1[i];
		} cout<<'\n';
		for(usi i=0;i<sz;i++){
			if(i==25||i==50) cout<<'\n';
			cout<<setw(3)<<left<<q2[i];
		}
	} cout<<'\n';
	for(usi i=0;i<sz;i++) {
		if(i==25||i==50) cout<<'\n';
		if(out[i]==100/*||out[i]==sz*/) cout<<setw(3)<<left<<'-';
		else cout<<setw(3)<<left<<out[i];
	}
	return 1;
}

bool sh(usi* q1arr,usi* q2arr,usi* out,usi sz){
	initwindow(1356,720);
	usi cnt=0,cx,cy;
	for(usi i=0;i<sz;i++){
		if(out[i]==100) {cx=q1arr[i]; cy=q2arr[i]; break;}
	}
	for(usi i=0;i<sz;i++){
		outtextxy(q1arr[i]*scl,720-q2arr[i]*scl,".");
		if(i!=cnt && out[i]==100){
			line(cx*scl,720-cy*scl,q1arr[i]*scl,720-q2arr[i]*scl);
			cx=q1arr[i]; cy=q2arr[i];
		}
	}
	system("pause");
	cleardevice();
	return 0;
}

bool btw(usi* q1arr,usi* q2arr,usi* out,usi sz,string srs){
	if(gff(srs,q1arr,q2arr)) //cout<<"\nget:\n";
	//ct1(q1arr,q2arr,sz);
	pptc(q1arr,q2arr,sz,out,1);
	sh(q1arr,q2arr,out,sz);
	pptc(q1arr,q2arr,sz,out,0);
	sh(q1arr,q2arr,out,sz);
	return 1;
}

int main(){
	initwindow(1356,720);
	usi* q1arr,*q2arr,*out; 
	q1arr=new usi [tstlnsz]; q2arr=new usi [tstlnsz]; out=new usi [tstlnsz];
	for(usi i=0;i<tstlnsz;i++) q1arr[i]=q1arr[i]=0;
	string srs1="q1.txt",srs2="q2.txt",srs3="q3.txt",srsl="ql.txt", srstst="qtst.txt";
	btw(q1arr,q2arr,out,tstlnsz,srstst);
	delete q1arr,q2arr,out;
	
	cout<<"\n\nsrs1:";
	q1arr=new usi [slnsz]; q2arr=new usi [slnsz]; out=new usi [slnsz];
	for(usi i=0;i<slnsz;i++) q1arr[i]=q1arr[i]=0; btw(q1arr,q2arr,out,slnsz,srs1);
	cout<<"\n\nsrs2:";
	for(usi i=0;i<slnsz;i++) q1arr[i]=q1arr[i]=0; btw(q1arr,q2arr,out,slnsz,srs2);
	cout<<"\n\nsrs3:";
	for(usi i=0;i<slnsz;i++) q1arr[i]=q1arr[i]=0; btw(q1arr,q2arr,out,slnsz,srs3);
	delete q1arr,q2arr,out;
	
	cout<<"\n\nsrsl:";
	q1arr=new usi [llnsz]; q2arr=new usi [llnsz]; out=new usi [llnsz];
	for(usi i=0;i<llnsz;i++) q1arr[i]=q1arr[i]=0; btw(q1arr,q2arr,out,llnsz,srsl);
	
	delete q1arr,q2arr,out;
	closegraph();
	return 0;	
}
