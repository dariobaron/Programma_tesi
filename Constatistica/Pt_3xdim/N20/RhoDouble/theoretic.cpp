#include "theoretic.h"
#include <iostream>
using namespace std;


Learning::Learning(int n, int p, double psi) : recursion(n+1, vector<double>(p+1)), Psi(psi){
	for(auto & i : recursion[0]){
		i = 0.;
	}
	recursion[1][0] = 2. * Psi;
	for(int i = 2; i < recursion.size(); ++i){
		recursion[i][0] = 2.;
	}
}


void Learning::compute(){
	for(int j = 1; j < recursion[1].size(); ++j){
		recursion[1][j] = Psi * recursion[1][j-1] + recursion[0][j-1];
	}
	for(int i = 2; i < recursion.size(); ++i){
		for(int j = 1; j < recursion[i].size(); ++j){
			recursion[i][j] = Psi * recursion[i][j-1] + recursion[i-1][j-1] + ( 1 - Psi ) * recursion[i-2][j-1];
		}
	}
}


double Learning::getC(int n, int p){
	return recursion[n][p-1];
}


void Learning::printAll(){
	for(auto & i : recursion){
		for(auto & j : i){
			cout << j << " ";
		}
		cout << endl;
	}
}