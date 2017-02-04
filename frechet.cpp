#include<iostream>
#include<math.h>
#include<string>
#include<vector>
#include<fstream>
#include<deque>
using namespace std;
#define frgm 10.0
#define dist 2
typedef unsigned short int usi;

class pnt{
	public:
		float x,y;
		friend ostream& operator<<(ostream& os,const pnt& pel){
			os<<"\nx="<<pel.x<<" y="<<pel.y<<'\t';
    		return os;
		}
};

class quel{
	public:
		float beg,end,val;
		quel(float ibeg, float iend,float ival): beg(ibeg), end(iend), val(ival) {}
		friend ostream& operator<<(ostream& os,const quel& qel){
			os<<"\nbeg="<<qel.beg<<" end="<<qel.end<<" val="<<qel.val<<'\t';
    		return os;
		}
		bool cutl(float ct){
			if(end<ct) return 1;
			else{
				beg=ct; return 0;
			}
		}
		bool cutr(float ct){
			if(beg>ct) return 1;
			else{
				end=ct; return 0;
			}
		}
};

bool gff(string ifn,vector<pnt>& poly1,vector<pnt>& poly2){
	ifstream fpi;
    fpi.open(ifn.c_str(),ios::binary);
    if(!fpi.is_open()) {cout<<"\nerr: gff no input file"; return 0;}
    else{
    	unsigned char ch='\0'; float fnum; bool isf=1; pnt tmppt;
		while(1){
			while(ch!='(') fpi>>ch; fpi>>fnum; tmppt.x=fnum;//cout<<fnum<<' ';
			fpi>>ch>>fnum; tmppt.y=fnum;
			fpi>>ch>>ch; //cout<<ch<<' '<<'\n'; system("pause");
			if(isf) poly1.push_back(tmppt);
			else  poly2.push_back(tmppt);
			if(ch=='s') {isf=0; continue;}
			if(fpi.eof()) break;
		}
     fpi.close();    
    }
    return 1;
}

void fab(unsigned int i,unsigned int j,vector<pnt>& poly1,vector<pnt>& poly2,float* &tmpa,float* &tmpb){
	float k,b,eps; bool fl=0; unsigned int incr=0,i1=i+1; float *a=new float,*pb=new float;
	*a=0; *pb=0; tmpa=NULL; tmpb=NULL;
	if(i>=poly1.size()) i=i-poly1.size(); //if(i>=m) i-=m;
	if(i1>=poly1.size()) i1=i1-poly1.size();
	if(poly1.at(i).x!=poly1.at(i1).x){
		k=(poly1.at(i).y-poly1.at(i1).y)/(poly1.at(i).x-poly1.at(i1).x); b=poly1.at(i).y-k*poly1.at(i).x;// y=k*x+b;
		eps=(poly1.at(i1).x-poly1.at(i).x)/frgm;
		while(incr<=frgm){
			if(fl==0){
				if(pow(poly2.at(j).y-(k*(poly1.at(i).x+eps*incr)+b),2)+pow(poly2.at(j).x-(poly1.at(i).x+eps*incr),2)<=(dist*dist)){
					*a=i+((i1-i)/(frgm+0.0))*incr;//*a=poly1.at(i).x+eps*incr;
					tmpa=a; fl=1;
				}
			}else{
				if(pow(poly2.at(j).y-(k*(poly1.at(i).x+eps*incr)+b),2)+pow(poly2.at(j).x-(poly1.at(i).x+eps*incr),2)>=(dist*dist)){
					*pb=i+((i1-i)/(frgm+0.0))*(incr-1);//*pb=poly1.at(i).x+eps*(incr-1);
					tmpb=pb;
				}
			}
			incr++;	
		}
	}else{
		eps=(poly1.at(i1).y-poly1.at(i).y)/frgm;
		while(incr<=frgm){
			if(fl==0){
				if(pow(poly2.at(j).y-(poly1.at(i).y+eps*incr),2)+pow(poly2.at(j).x-(poly1.at(i).x),2)<=(dist*dist)){
					*a=i+((i1-i)/(frgm+0.0))*incr;//*a=poly1.at(i).x;
					tmpa=a; fl=1;
				}
			}else{
				if(pow(poly2.at(j).y-(poly1.at(i).y+eps*incr),2)+pow(poly2.at(j).x-(poly1.at(i).x),2)>=(dist*dist)){
					*pb=i+((i1-i)/(frgm+0.0))*(incr-1);//*pb=poly1.at(i).x;
					tmpb=pb;
				}
			}
			incr++;	
		}
	}
	if(tmpa!=NULL&&tmpb==NULL){
		*pb=i1;//*pb=poly1.at(i1).x;
		tmpb=pb;
	}
	/*cout<<"\n1a=";
	if(tmpa==NULL) cout<<"NULL";
	else cout<<*tmpa;
	cout<<"\n1b=";
	if(tmpb==NULL) cout<<"NULL";
	else cout<<*tmpb<<'\n';*/
}

void fl(unsigned int i,unsigned int j,vector<pnt>& poly1,vector<pnt>& poly2,float* &tmpa,float* &tmpb){
	float k,b,eps; bool fl=0; unsigned int incr=0,i1=i+1,j1=j; float *a=new float,*pb=new float;
	*a=0; *pb=0; tmpa=NULL; tmpb=NULL;
	if(j>=poly1.size()) j-=poly1.size();
	if(poly2.at(i).x!=poly2.at(i1).x){
		k=(poly2.at(i).y-poly2.at(i1).y)/(poly2.at(i).x-poly2.at(i1).x); 
		b=poly2.at(i).y-k*poly2.at(i).x;// y=k*x+b;
		eps=(poly2.at(i1).x-poly2.at(i).x)/frgm;
		while(incr<=frgm){
			if(fl==0){
				if(pow(poly1.at(j).y-(k*(poly2.at(i).x+eps*incr)+b),2)+pow(poly1.at(j).x-(poly2.at(i).x+eps*incr),2)<=(dist*dist)){
					*a=i+((i1-i)/(frgm+0.0))*incr;//*a=poly2.at(i).x+eps*incr;
					tmpa=a; fl=1;
				}
			}else{
				if(pow(poly1.at(j).y-(k*(poly2.at(i).x+eps*incr)+b),2)+pow(poly1.at(j).x-(poly2.at(i).x+eps*incr),2)>=(dist*dist)){
					*pb=i+((i1-i)/(frgm+0.0))*(incr-1);//*pb=poly1.at(i).x+eps*(incr-1);
					tmpb=pb;
				}
			}
			incr++;
		}
	}else{
		eps=(poly2.at(i1).y-poly2.at(i).y)/frgm;
		while(incr<=frgm){
			if(fl==0){
				if(pow(poly1.at(j).y-(poly2.at(i).y+eps*incr),2)+pow(poly1.at(j).x-poly2.at(i).x,2)<=(dist*dist)){
					*a=i+((i1-i)/(frgm+0.0))*incr;//*a=poly2.at(i).x;
					tmpa=a; fl=1;
				}
			}else{
				if(pow(poly1.at(j).y-(poly2.at(i).y+eps*incr),2)+pow(poly1.at(j).x-poly2.at(i).x,2)>=(dist*dist)){
					*pb=i+((i1-i)/(frgm+0.0))*(incr-1);//*pb=poly1.at(i).x;
					tmpb=pb;
				}
			}
		incr++;	
		}
	}
	if(tmpa!=NULL&&tmpb==NULL){
		*pb=i1;//*pb=poly1.at(i1).x;
		tmpb=pb;
	}
	/*if(j1<=j){
		cout<<"\ni="<<i<<" j="<<j;
		cout<<"\n1a=";
		if(tmpa==NULL) cout<<"NULL\n";
		else cout<<*tmpa<<'\n';
	}*/
}

int main(){
	string srs="q.txt"; vector<pnt> poly1,poly2;
	gff(srs,poly1,poly2);
	unsigned int m=poly1.size(),n=poly2.size();
	cout<<"\npoly1:\n"; vector<pnt>::iterator pntit=poly1.begin();
    while(pntit!=poly1.end()){
		cout<<*pntit++;
	}
	cout<<"\n\npoly2:\n"; pntit=poly2.begin();
	while(pntit!=poly2.end()){
		cout<<*pntit++;
	} cout<<'\n';
	//forward;
	vector<float> ptrs(n-1,0);//ptr(0, j) equals to 0;
	vector<deque<quel>> qu(2*m-1);
	float tmpptr,rast, *tmpa=NULL,*tmpb=NULL,*tmpc=NULL,*tmpd=NULL,*tmpl=NULL,*tmph=NULL;
	for(unsigned int i=0;i<2*m-1;i++){//from left to right;
		for(unsigned int j=0; j<n-1;j++){//from bottom to top;
			//cout<<"\ni="<<i<<" j="<<j<<'\n';
			fab(i,j,poly1,poly2,tmpa,tmpb);
			fab(i,j+1,poly1,poly2,tmpc,tmpd);
			fl(j,i,poly1,poly2,tmpl,tmph);
			if(tmpl!=NULL) {//g_ intersection Lij is not empty;
				tmpptr=ptrs.at(j);
				if(tmpa!=NULL&&tmpb!=NULL){// g_ intersection Bij is not empty;
					if(j==0){
						if(!qu.at(i).empty()) cout<<"\n\neee\n\n";
						quel tmpquel(*tmpa,*tmpb, *tmpb);
						qu.at(i).push_back(tmpquel);
					}
					if(tmpc!=NULL&&tmpd!=NULL){// g_ intersection Tij is not empty;
						if(*tmpc<*tmpa){
							quel tmpquel(*tmpc,*tmpa, tmpptr);
							qu.at(i).push_front(tmpquel);
						}
						else{//cut Q(i) to the left of c;
						//cout<<"\nhere1";
							for(usi k=0;k<qu.at(i).size();k++){
								if(qu.at(i).at(k).cutl(*tmpc)==1){
									qu.at(i).erase(qu.at(i).begin()+k);
									cout<<"\nhere\n\n";
								}	
							}
						}
						if(qu.at(i).empty()) rast=-1;
						else rast=qu.at(i).at(qu.at(i).size()-1).val;//read a triple beg, end, r* from the right and save the value r*;
						if(*tmpb<*tmpd){
							quel tmpquel(*tmpb,*tmpd, rast);
							qu.at(i).push_back(tmpquel);
						}
						else{//cut Q(i) to right of d;
							for(usi k=0;k<qu.at(i).size();k++){
								if(qu.at(i).at(k).cutr(*tmpd)==1){
									qu.at(i).erase(qu.at(i).begin()+k);
									cout<<"\nhere1\n\n";
								}	
							}
						}
					}//TODO;
				}
				else{
					if(qu.at(i).empty()) rast=-1;
					else rast=qu.at(i).at(qu.at(i).size()-1).val;
				}
				tmpptr=rast;
				ptrs.at(j)=tmpptr;
			}
		}
		cout<<'\n';
	}
	cout<<"\n\n";
	for(usi i=0;i<qu.size();i++){
		for(usi j=0;j<qu.at(i).size();j++)
			cout<<"\ni="<<i<<" j="<<j<<'\t'<<qu.at(i).at(j)<<'\n';
	}
	for(usi j=0;j<n-1;j++) cout<<" ptrs.at("<<j<<")="<<ptrs.at(j)<<'\t';
	//backward;
	vector<float> ptrs1(2*m-1,-1);
	vector<deque<quel>> qu1(n-1);
	tmpptr=0,rast=0; tmpa=NULL; tmpb=NULL; tmpc=NULL; tmpd=NULL; tmpl=NULL; tmph=NULL;
	for(usi i=2*m-2;i<=2*m-2;i--){
		for(usi j=n-2;j<=n-2;j--){
			cout<<"\ni="<<i<<" j="<<j;
			fl(j,i+1,poly1,poly2,tmpa,tmpb);
			fl(j,i,poly1,poly2,tmpc,tmpd);
			fab(i,j+1,poly1,poly2,tmpl,tmph);
			if(tmph!=NULL){//g intersection Tij is not empty;
				if(j==n-2) ptrs1.at(i)=*tmph;
				tmpptr=ptrs1.at(i);//here tmpptr equals some val or -1;
				if(tmpa!=NULL&&tmpb!=NULL){////g intersection Rij is not empty;
					if(i==2*m-2){//at the start of the (2m, j)-th step the deque Q(j)
						if(!qu1.at(j).empty()) cout<<"\n\neee\n\n";// is either empty (if g intersection R(2m)j is empty)
						quel tmpquel(*tmpa,*tmpb, i+1);//or includes a single interval with constant pointer 2m;
						qu.at(i).push_back(tmpquel);
					}
					if(tmpc!=NULL&&tmpd!=NULL){//g intersection Lij is not empty;
						if(*tmpb<*tmpd){
							//TODO;
						}
					}
				}
			}
		}
	}
	
	
	return 0;
}
/*cout<<"\na=";
if(tmpa==NULL) cout<<"NULL";
else cout<<*tmpa;
cout<<"\nb=";
if(tmpb==NULL) cout<<"NULL";
else cout<<*tmpb;
cout<<"\nc=";
if(tmpc==NULL) cout<<"NULL";
else cout<<*tmpc;
cout<<"\nd=";
if(tmpd==NULL) cout<<"NULL\n";
else cout<<*tmpd<<'\n';*/

/*cout<<"\na=";
if(tmpa==NULL) cout<<"NULL";
else cout<<*tmpa;
cout<<" b=";
if(tmpb==NULL) cout<<"NULL";
else cout<<*tmpb;
cout<<" c=";
if(tmpc==NULL) cout<<"NULL";
else cout<<*tmpc;
cout<<" d=";
if(tmpd==NULL) cout<<"NULL";
else cout<<*tmpd;
cout<<" l=";
if(tmpl==NULL) cout<<"NULL";
else cout<<*tmpl;
cout<<" h=";
if(tmph==NULL) cout<<"NULL\n";
else cout<<*tmph<<'\n';*/
