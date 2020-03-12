#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>

using namespace std;

ifstream input;
ofstream output;

template <typename Container>
double discrepancy(const Container & observed, const Container & expected, int nConstraints = 0);

int main(int argc, char ** argv){

	//	Opening the output file
	output.open("errors.txt");

	//	Reading each file passed by argument when running the program
	int i = 1;
	while( i < argc ){
		string inputfile = argv[i];
		vector<string> rho;
		int delimiter = inputfile.find(";");
		while( delimiter >= 0 && delimiter < inputfile.size() ){
			rho.push_back( string(inputfile, 0, delimiter) );
			inputfile.erase(0, delimiter+1);
			delimiter = inputfile.find(";");
		}
		delimiter = inputfile.find(".dat");
		rho.push_back( string(inputfile, 0, delimiter) );
		inputfile = argv[i];
		//	at this point you have the name of the input file in inputfile and the values of rho in the vector named rho

		input.open(inputfile);

		//	Start calculating the chi-squared for each file
		vector<double> measured;
		vector<double> theory;
		vector<double> statistical;
		string provv;
		double provvM, provvT, provvS;
		while(!input.eof()){
			input >> provv >> provvM >> provv >> provvS >> provvT >> provv;
			measured.push_back(provvM);
			theory.push_back(provvT);
			statistical.push_back(provvS);
		}
		measured.pop_back();
		theory.pop_back();
		statistical.pop_back();

		input.close();

		for(auto & j : rho){
			output << j << "\t";
		}
		double discr = discrepancy(measured, theory);
		double stat = inner_product(statistical.begin(), statistical.end(), statistical.begin(), 0.);
		output << discr << "\t" << stat << "\t" << 100 * discr / stat << endl;

		++i;
	}

	output.close();

	return 0;
}


// Normalized chi-squared of a set of data respect to a theoretical distribution
//	nConstraints represents the number of constraints imposed while producing the values in expected Container
template<typename Container>
double discrepancy(const Container & observed, const Container & expected, int nConstraints){
	if( observed.size() != expected.size() || observed.size() == 1 ){
		return -1.;
	}
	int degreeOfFreedom = observed.size() - 1 - nConstraints;
	double chi = 0.;
	auto it = expected.begin();
	for(auto & i : observed){
		if( *it != 0 ){
			chi += pow( i - *it, 2 );
		}
		else{
			chi += i;
		}
		++it;
	}
	return chi / degreeOfFreedom;
}