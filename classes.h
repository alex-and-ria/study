//! \file \brief file with definitions
#ifndef CLASSES_H
#define CLASSES_H
#include<iostream>
using namespace std;

//! represents measurement system in feet and inches;
class engm{
	public:
		int feet;//     \if you try making them private, be ready for rain dance with constructors;
		float inches;// /
		bool operator==(engm eem) const;//!< to compare two objects;
		friend ostream& operator<<(ostream& os, const engm& em);//!< for enable using cout<<[engm_object];
};

//! distance class which supports converting feet and inches into meters and vice versa;
class dist{
	private:
		const float MTF;
		float mtrs;
		engm emtrs;
		bool ism;
	public:
		dist(engm emu);//!< constructor to set distance in feet and inches;
		dist(float meters);//!< constructor to set distance in meters;
		float em2m() const;//!<convertation feet and inches into meters;
		engm m2em() const;//!<convertation merers into feet and inches;
		friend ostream& operator<<(ostream& os, const dist& dst);//!< for enable using cout<<[dist_object];
};

//! class to test methods in dist class
class tstdist{
	private:
		const static float mtf;
		void tstem2m() const;
		void tstm2em() const;
	public:
		tstdist();//!< contains void tstem2m() const; and void tstm2em() const;
		friend ostream& operator<<(ostream&os, const tstdist& td);//!< for enable using cout<<[tstdist_object];
};
#endif
