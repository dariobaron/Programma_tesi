#include <vector>
#include <numeric>
#include <cmath>
using namespace std;


// weighted mean of a Container
template<typename Container>
double mean(const Container & v, const Container & weights){
	return inner_product(v.begin(), v.end(), weights.begin(), 0.) / accumulate(weights.begin(), weights.end(), 0.);
}


// mean of a Container
template<typename Container>
double mean(const Container & v){
	return accumulate(v.begin(), v.end(), 0.) / v.size();
}


// weighted dev std of a Container
template<typename Container>
double devstd(const Container & v, const Container & weights){
	double temp_mean = mean(v, weights);
	double a = 0.;
	for(int i = 0; i < v.size(); ++i){
		a += weights[i] * (v[i] - temp_mean) * (v[i] - temp_mean);
	}
	return sqrt( a / accumulate(weights.begin(), weights.end(), 0.) );
}


// dev std of a Container
template<typename Container>
double devstd(const Container & v){
		double temp_mean = mean(v);
		double a = 0.;
		for(auto & i : v){
			a += (i - temp_mean) * (i - temp_mean);
		}
		return sqrt( a / (v.size() - 1) );
}


// dev std of the mean of a Container
template<typename Container>
double devstdofmean(const Container & v){
	return devstd(v) / sqrt(v.size());
}


// Normalized chi-squared of a set of data respect to a theoretical distribution
//	nConstraints represents the number of constraints imposed while producing the values in expected Container
template<typename Container>
double chiSquared(const Container & observed, const Container & expected, int nConstraints = 0){
	if( observed.size() != expected.size() || observed.size() == 1 ){
		return -1.;
	}
	int degreeOfFreedom = observed.size() - 1 - nConstraints;
	double chi = 0.;
	auto it = expected.begin();
	for(auto & i : observed){
		if( *it != 0 ){
			chi += pow( i - *it, 2 ) / *it;
		}
		else{
			chi += i;
		}
		++it;
	}
	return chi / degreeOfFreedom;
}