#include<iostream>
#include<math.h>
#include<time.h>
#include<cassert>
using namespace std;
#define ntst 10
#define eps 10e-5

class engm{
	public:
		int feet;
		float inches;
		bool operator==(engm eem){
			if(eem.feet==feet&&fabs(eem.inches-inches)<eps) return true;
			cout<<"\neem.feet="<<eem.feet<<" feet="<<feet<<" eem.inches="<<eem.inches<<" inches="<<inches;
			return false;
		}
};

class dist{
	private:
		const float MTF;
		float mtrs;
		engm emtrs;
	public:
		dist(engm emu): emtrs(emu), MTF(3.280833F) {}
		dist(float meters): mtrs(meters), MTF(3.280833F) {} 
		float em2m(){
			float fracfeet=emtrs.inches/12.;     //convert the inches
			fracfeet += static_cast<float>(emtrs.feet); //add the feet
			return fracfeet/MTF;
		}
		engm m2em(){
			engm emtmp;
			float fltfeet=MTF * mtrs;  //convert to float feet
			emtmp.feet=int(fltfeet);           //feet is integer part
			emtmp.inches=12*(fltfeet-emtmp.feet); 
			return emtmp;
		}
};

class tstdist{//1 feet is 3.280833F meter;
	private:
		static float mtf;
		void tstem2m(){
			for(uint8_t i=0;i<ntst;i++){
				engm emtmp; emtmp.feet=rand()%200; emtmp.inches=rand()%12;//%200 to prevent overflow;
				dist dst(emtmp);
				float resm=(emtmp.feet+emtmp.inches/12.)/mtf;
				assert(fabs(dst.em2m()-resm)<eps);
			}
		}
		void tstm2em(){
			for(uint8_t i=0;i<ntst;i++){
				float mtmp=rand()%200;//%200 to prevent overflow;
				dist dst(mtmp);
				engm resengm; resengm.feet=(int)(mtf*mtmp); resengm.inches=12.*(mtf*mtmp-resengm.feet);
				assert(dst.m2em()==resengm);
				//cout<<(dst.m2em()==resengm)<<' ';
			}
		}
	public:
		tstdist(){
			srand(time(NULL));
			tstem2m();
			tstm2em();
		}
		
};
float tstdist::mtf=3.280833F;

int main(){
	tstdist tst;
	
	return 0;
}
