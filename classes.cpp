#include<iostream>
#include<math.h>
#include<time.h>
#include<cassert>
#include"classes.h"
using namespace std;
#define ntst 10
#define eps 10e-5

bool engm::operator==(engm eem) const{
	if(eem.feet==feet&&fabs(eem.inches-inches)<eps) return true;
	cout<<"\neem.feet="<<eem.feet<<" feet="<<feet<<" eem.inches="<<eem.inches<<" inches="<<inches;
	return false;
}
ostream& operator<<(ostream& os, const engm& em){
	os<<"\neem.feet="<<em.feet<<" eem.inches="<<em.inches;
    return os;
}


dist::dist(engm emu): emtrs(emu), ism(0), MTF(3.280833F) {}
dist::dist(float meters): mtrs(meters), ism(1), MTF(3.280833F) {} 
float dist::em2m() const{
	float fracfeet=emtrs.inches/12.;     //convert the inches
	fracfeet += static_cast<float>(emtrs.feet); //add the feet
	return fracfeet/MTF;
}
engm dist::m2em() const{
	engm emtmp;
	float fltfeet=MTF * mtrs;  //convert to float feet
	emtmp.feet=int(fltfeet);           //feet is integer part
	emtmp.inches=12*(fltfeet-emtmp.feet); 
	return emtmp;
}
ostream& operator<<(ostream& os, const dist& dst){
	if(dst.ism) {
		os<<"\nmtrs="<<dst.mtrs; return os;
	}
	os<<"\ndst.emtrs.feet="<<dst.emtrs.feet<<" dst.emtrs.inches="<<dst.emtrs.inches;
	return os;
}

//!1 feet is 3.280833F meter;
void tstdist::tstem2m() const{
	for(uint8_t i=0;i<ntst;i++){
		engm emtmp; emtmp.feet=rand()%200; emtmp.inches=rand()%12;//%200 to prevent overflow;
		dist dst(emtmp);
		float resm=(emtmp.feet+emtmp.inches/12.)/mtf;
		assert(fabs(dst.em2m()-resm)<eps);
	}
}
void tstdist::tstm2em() const{
	for(uint8_t i=0;i<ntst;i++){
		float mtmp=rand()%200;//%200 to prevent overflow;
		dist dst(mtmp);
		engm resengm; resengm.feet=(int)(mtf*mtmp); resengm.inches=12.*(mtf*mtmp-resengm.feet);
		assert(dst.m2em()==resengm);
		//cout<<(dst.m2em()==resengm)<<' ';
	}
}
tstdist::tstdist(){
	srand(time(NULL));
	tstem2m();
	cout<<"testing em2m() complete";
	tstm2em();
	cout<<"\ntesting m2em() complete";
}
ostream& operator<<(ostream&os, const tstdist& td){
	cout<<"\ntesting em2m() complete";
	cout<<"\ntesting m2em() complete";
}

const float tstdist::mtf=3.280833F;
