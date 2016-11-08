#ifndef CLASSES_H
#define CLASSES_H
#include<iostream>
using namespace std;

class engm{
	public:
		int feet;//     \if you try making them private, be ready for rain dance with constructors;
		float inches;// /
		bool operator==(engm eem) const;
		friend ostream& operator<<(ostream& os, const engm& em);
};

class dist{
	private:
		const float MTF;
		float mtrs;
		engm emtrs;
		bool ism;
	public:
		dist(engm emu);
		dist(float meters);
		float em2m() const;
		engm m2em() const;
		friend ostream& operator<<(ostream& os, const dist& dst);
};

class tstdist{
	private:
		const static float mtf;
		void tstem2m() const;
		void tstm2em() const;
	public:
		tstdist();
		friend ostream& operator<<(ostream&os, const tstdist& td);
};
#endif
