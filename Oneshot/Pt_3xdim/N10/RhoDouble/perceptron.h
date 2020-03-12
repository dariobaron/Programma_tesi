#ifndef perceptron_h
#define perceptron_h

#include <vector>
using namespace std;

class Perceptron{
public:
	Perceptron(int dim);
	short operator()(const vector<double> & v);
	bool learning(const vector<double> & point, short wanted_label, double rate);
protected:
	int dim;
	vector<double> weights;
};

#endif