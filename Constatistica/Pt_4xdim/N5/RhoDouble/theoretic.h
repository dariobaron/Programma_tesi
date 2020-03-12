#ifndef theoretic_h
#define theoretic_h

#include <vector>
using namespace std;


class Learning{
public:
	Learning(int n, int p, double psi);
	void compute();
	double getC(int n, int p);
	void printAll();
protected:
	vector< vector<double> > recursion;
	double Psi;
};

#endif