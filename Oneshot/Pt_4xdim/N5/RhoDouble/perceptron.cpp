#include "perceptron.h"
#include "random.cpp"
#include "algebra.h"

Perceptron::Perceptron(int n) : dim(n), weights(n){
	Random< uniform_real_distribution<>, double, double > rnd(randomEngine(), 0., 1.);
	for(auto & i : weights){
		i = rnd.generate();
	}
	normalize(weights);
}


short Perceptron::operator()(const vector<double> & v){
	return sign( weights * v );
}


bool Perceptron::learning(const vector<double> & point, short wanted_label, double rate){
    if ( operator()(point) * wanted_label == -1 ){
    	for (int i = 0; i < point.size(); ++i){
    		weights[i] += rate * wanted_label * point[i];
    	}
      return true;
    }
    return false;
}