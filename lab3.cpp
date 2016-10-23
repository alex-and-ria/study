#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
#define C 100
using namespace std;
uint32_t cmp1=0;

bool gff(string ifn,vector<uint16_t>& vect){
	ifstream fpi;
    fpi.open(ifn.c_str(),ios::binary);
    if(!fpi.is_open()) {cout<<"\nerr: gff no input file"; return 0;}
    else{
    	uint16_t nff;
		while(1){
			fpi>>nff; vect.push_back(nff);
			if(fpi.eof()) break;
		}
     fpi.close();    
    }
    return 1;
}

uint16_t nfa(map<uint16_t,vector<uint16_t>>& mp,vector<uint16_t>& wgs){
	uint16_t cnt=0,cmp=0; uint16_t inc=0; vector<uint16_t> tmpv;
	for(vector<uint16_t>::iterator inv=wgs.begin(); inv!=wgs.end(); ++inv){
		if(inc+(*inv)<=C){
			tmpv.push_back(*inv);
			inc+=(*inv);
		}
		else{
			mp[cnt]=tmpv;
			inc=0; cnt++; inv--;
			//cout<<"\ncnt="<<cnt<<"=>"; for(vector<uint16_t>::iterator it=tmpv.begin(); it!=tmpv.end(); ++it){cout<<*it<<' ';}
			if(inv!=wgs.end()-1) tmpv.clear();
		}cmp++;
	}
	mp[cnt]=tmpv;
	return cmp;
}

uint16_t ffa(map<uint16_t,vector<uint16_t>>& mp,vector<uint16_t>& wgs){
	uint16_t cnt=0,cmp=0,inc=0; bool fnd=false; vector<uint16_t> tmpv;
	for(vector<uint16_t>::iterator inv=wgs.begin(); inv!=wgs.end(); ++inv){
		fnd=false;
		if(inc+(*inv)<=C){
			tmpv.push_back(*inv);
			inc+=(*inv);
		}
		else{
			if(cnt==0){
				mp[cnt]=tmpv;
				inc=0; cnt++; inv--;
				//cout<<"\ncnt="<<cnt<<"=>"; for(vector<uint16_t>::iterator it=tmpv.begin(); it!=tmpv.end(); ++it){cout<<*it<<' ';}
				if(inv!=wgs.end()-1) tmpv.clear();
			}
			else{//(1);
				for(uint16_t tmpcnt=0;tmpcnt<cnt;tmpcnt++){
					uint16_t tmpinc=0;
					for(vector<uint16_t>::iterator tmpit=(mp[tmpcnt]).begin(); tmpit!=(mp[tmpcnt]).end(); ++tmpit){tmpinc+=(*tmpit);}
					if(tmpinc+(*inv)<=C){
						(mp[tmpcnt]).push_back(*inv);
						fnd=true;
						break;
					}cmp++;
				}
				if(fnd==false){
					mp[cnt]=tmpv;
					inc=0; cnt++; inv--;
					//cout<<"\ncnt="<<cnt<<"=>"; for(vector<uint16_t>::iterator it=tmpv.begin(); it!=tmpv.end(); ++it){cout<<*it<<' ';}
					if(inv!=wgs.end()-1) tmpv.clear();
				}
			}	
		}cmp++;
	}
	mp[cnt]=tmpv;
	return cmp;
}

uint16_t wfa(map<uint16_t,vector<uint16_t>>& mp,vector<uint16_t>& wgs){
	uint16_t cnt=0,cmp=0,inc=0; vector<uint16_t> tmpv;
	for(vector<uint16_t>::iterator inv=wgs.begin(); inv!=wgs.end(); ++inv){
		if(inc+(*inv)<=C){
			tmpv.push_back(*inv);
			inc+=(*inv);
		}
		else{
			if(cnt==0){
				mp[cnt]=tmpv;
				inc=0; cnt++; inv--;
				if(inv!=wgs.end()-1) tmpv.clear();
			}
			else{
				uint16_t minw=C,minwcnt=0;
				for(uint16_t tmpcnt=0;tmpcnt<cnt;tmpcnt++){
					uint16_t tmpinc=0;
					for(vector<uint16_t>::iterator tmpit=(mp[tmpcnt]).begin(); tmpit!=(mp[tmpcnt]).end(); ++tmpit){tmpinc+=(*tmpit);}
					if(tmpinc<minw){
						minw=tmpinc;
						minwcnt=tmpcnt;
					}cmp++;
				}
				if(minw+(*inv)<=C){
					(mp[minwcnt]).push_back(*inv);
				}
				else{
					mp[cnt]=tmpv;
					inc=0; cnt++; inv--;
					if(inv!=wgs.end()-1) tmpv.clear();
				}cmp++;
			}
		}cmp++;
	}
	mp[cnt]=tmpv;
	return cmp;
}

uint16_t bfa(map<uint16_t,vector<uint16_t>>& mp,vector<uint16_t>& wgs){
	uint16_t cnt=0,cmp=0,inc=0; vector<uint16_t> tmpv,tminv;
	for(vector<uint16_t>::iterator inv=wgs.begin(); inv!=wgs.end(); ++inv){
		if(inc+(*inv)<=C){
			tmpv.push_back(*inv);
			inc+=(*inv);
		}
		else{
			uint16_t maxw=0,maxwcnt=0; bool fnd=false;
			for(uint16_t tmpcnt=0;tmpcnt<cnt;tmpcnt++){
				uint16_t tmpinc=0;
				for(vector<uint16_t>::iterator tmpit=(mp[tmpcnt]).begin(); tmpit!=(mp[tmpcnt]).end(); ++tmpit){tmpinc+=(*tmpit);}
				if(tmpinc+(*inv)<=C&&tmpinc>maxw){
					maxw=tmpinc;
					maxwcnt=tmpcnt;
					fnd=true;
				}cmp+=2;
			}
			if(fnd){
				(mp[maxwcnt]).push_back(*inv);
			}
			else{
				mp[cnt]=tmpv;
				inc=0; cnt++; inv--;
				if(inv!=wgs.end()-1) tmpv.clear();
			}
		}cmp++;
	}
	mp[cnt]=tmpv;
	return cmp;
}

bool msrt(uint16_t i,uint16_t j){cmp1++; return (i>j);}

int main(){
	vector<uint16_t> wgs;
	map<uint16_t,vector<uint16_t>> cntnrs;
	gff("qtst.txt",wgs);
	sort(wgs.begin(),wgs.end(),msrt); cout<<"cmp1="<<cmp1<<'\n';
	for(vector<uint16_t>::iterator it=wgs.begin(); it!=wgs.end(); ++it){cout<<*it<<' ';} cout<<'\n';
	wfa(cntnrs,wgs);
	for (map<uint16_t,vector<uint16_t>>::iterator it=cntnrs.begin(); it!=cntnrs.end(); ++it){
		cout<<it->first<<" => ";
		for(vector<uint16_t>::iterator itv=(it->second).begin(); itv!=(it->second).end(); ++itv){cout<<*itv<<' ';}
		cout<<'\n';
	}
	
	return 0;
}

/*(1);
for(uint16_t tmpcnt=cnt-1; ;tmpcnt--){
	if(tmpcnt==0&&fnd==false) fnd=true;
	uint16_t tmpinc=0;
	for(vector<uint16_t>::iterator tmpit=(mp[tmpcnt]).begin(); tmpit!=(mp[tmpcnt]).end(); ++tmpit){tmpinc+=(*tmpit);}
	if(tmpinc+(*inv)<=C){
		(mp[tmpcnt]).push_back(*inv);
		fnd=true;
		break;
	}cmp++;
	if(tmpcnt==0&&fnd==true){fnd=false; break;}
}
*/
