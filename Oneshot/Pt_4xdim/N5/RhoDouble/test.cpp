#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <iomanip>

using namespace std;

double Psi(double rho){
	return 2. / M_PI * atan( sqrt( (1.+rho) / (1.-rho) ) );
}


double expectedLearnt(int n, int p, double rho){
	if( n <= 0 ){
		return 0.;
	}
	else if( n == 1 && p == 1 ){
		return 2. * Psi(rho);
	}
	if( p == 1 ){
		return 2.;
	}
	return Psi(rho) * expectedLearnt(n, p-1, rho) +
				expectedLearnt(n-1, p-1, +rho) +
				(1 - Psi(rho)) * expectedLearnt(n-2, p-1, rho);
}


class Factorial{
public:
	int operator()(int n){
		if( n < 0 ){
			return 0;
		}
		else if( n <= 1 ){
			return 1;
		}
		while( v.size() <= n ){
			v.push_back( v.back() * ( v.end() - v.begin() ) );
		}
		cout<<"OK"<<endl;
		return v[n];
	};
protected:
	vector<long> v;
};


double multinominal(int n, int m1, int m2){
	if ( n - m1 - m2 < 0 ){
		return 0.;
	}
	Factorial factorial;
	return factorial(n) / factorial(m1) / factorial(m2) / factorial(n-m1-m2);
}


double Kappa(int i, int p, double rho){
	double sum = 0.;
	for(int m = 0; m <= p - 1; ++m){
		cout<<"ok "<<i<<" "<<p<<" "<<m<<endl;
		sum += multinominal(p-1, m, i-2*m) * pow(Psi(rho), p-1-i+m) * pow(1-Psi(rho), m);
	}
	return sum;
}


double closedFormula(int n, int p, double rho){
	double sum = 0.;
	for(int i = 0; i <= n - 2; ++i){
		sum += Kappa(i, p, rho);
	}
	return 2 * sum + 2 * Psi(rho) * Kappa(n-1, p, rho);
}


// ATTENZIONE CHE L'INDICE SU N RAPPRESENTA LE DIMENSIONI, MENTRE L'INDICE SU P RAPPRESENTA P-1 PUNTI
class Learning{
public:
	Learning(int n, int p, double overlap) : recursion(n+1, vector<double>(p+1)), rho(overlap){
		for(auto & i : recursion[0]){
			i = 0.;
		}
		recursion[1][0] = 2. * Psi(rho);
		for(int i = 2; i < recursion.size(); ++i){
			recursion[i][0] = 2.;
		}
	};
	void compute(){
		for(int j = 1; j < recursion[1].size(); ++j){
			recursion[1][j] = Psi(rho) * recursion[1][j-1] + recursion[0][j-1];
		}
		for(int i = 2; i < recursion.size(); ++i){
			for(int j = 1; j < recursion[i].size(); ++j){
				recursion[i][j] = Psi(rho) * recursion[i][j-1] + recursion[i-1][j-1] + ( 1 - Psi(rho) ) * recursion[i-2][j-1];
			}
		}
	};
	double getC(int n, int p){ return recursion[n][p-1]; };
	void print(){
		for(auto & i : recursion){
			for(auto & j : i){
				cout << fixed << setprecision(1) << j << " ";
			}
			cout << endl;
		}
	};
protected:
	vector< vector<double> > recursion;
	double rho;
};


template<typename Container>
double mean(const Container & v){
	return accumulate(v.begin(), v.end(), 0.) / v.size();
}


int main(){

	vector<double> rho = {-0.5, 0.2};

	int n = 5;

	Learning machine(n, 20, mean(rho));

	machine.compute();

	for(int p = 16; p <= 20; ++p){
		cout << p << "\t" << expectedLearnt(n, p, mean(rho)) / pow(2, p) << "\t" << machine.getC(n,p) / pow(2, p) << "\t" << closedFormula(n, p, mean(rho)) / pow(2, p) << endl;
	}

	return 0;
}