#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <string>
#include <cstdlib>
#include "perceptron.h"
#include "random.cpp"
#include "algebra.h"
#include "statistics.h"
#include "theoretic.h"

using namespace std;

ofstream output;

vector<double> partner(const vector<double> & p, double overlap);

double Psi(double rho);

clock_t startTimer();

double stopTimer(clock_t begin);

int main(int argc, char ** argv){

	auto time = startTimer();

	if( argc != 5 ){
		cerr << "USAGE: ./program.x val1 prob1 val2 prob2" << endl;
		return -1;
	}

	// definition of initial parameters
	int dimension = 5;				// dimension of the vectorial space where the points are
	int max_p = dimension * 4;		// maximum number of points considered 
	long N_iterations = 1000;		// number of dicotomies attempted for fixed number of points and dimension
	long max_batches = 10000;		// maximum number of batches allowed (iterations in which perceptron algorithm tries to learn)
	double rate = 0.1;				// learning rate (0.1 nearly always good)

	//	creating the overlap distribution (in form of linear combination of different delta-distribution)
	vector<double> rho(2);
	vector<double> psi(2);
	vector<double> probabilities(2);

	for(int i = 0; i < rho.size(); ++i){
		rho[i] = atof( argv[1+i*2] );
		probabilities[i] = atof( argv[2+i*2] );
	}
	Random< Discrete, vector<double>, vector<double> > overlap(randomEngine(), rho, probabilities);
	for(int i = 0; i < psi.size(); ++i){
		psi[i] = Psi(rho[i]);
	}

	//	opening the output file
	string filename;
	for(int i = 1; i < argc; i = i + 2){
		 filename = filename + argv[i] + ";";	
	}
	filename.pop_back();
	filename = filename + ".dat";
	if( probabilities[0] == probabilities[1] ){
		filename = "SameWeights/" + filename;
	}
	else{
		filename = "DiffWeights/" + filename;
	}
	cout << filename << endl;
	output.open(filename);

	//	creating the theoretical prevision
	Learning theory(dimension, max_p, mean(psi, probabilities));
	theory.compute();

	//	cycling over the number of points
	for(int p = 1; p <= max_p; ++p){

		long learned_dichotomies = 0;

		//	cycling over the number of iterations for fixed p and dimension
		for(long iter_count = 0; iter_count < N_iterations; ++iter_count){

			//	build up the points set

			vector< pair< vector<double>, vector<double> > > points(p);
			for(auto & i : points){
				i.first = buildRandomPoint(dimension);
				i.second = partner(i.first, overlap.generate());
			}

			//	build up the Perceptron and the dichotomy to learn
			Perceptron machine(dimension);

			Random< Discrete, vector<double>, vector<double> > rndlabel(randomEngine(), {1.,-1.}, {0.5,0.5});
			vector<short> labels(p);
			for(auto & i : labels){
				i = rndlabel.generate();
			}

			//	cycling over batches: it stops if the learning is complete (for the condition has_updated==false)
			//		of the learning is impossible / too slow (for the condition batch==max_batches)
			bool has_updated = true;		//	to check whether the Perceptron is still learning or has already learnt everything
			for(int batch = 0; batch < max_batches && has_updated; ++batch){
				has_updated = false;

				auto iterlabel = labels.begin();
				for(auto & i : points){
					if( machine.learning( i.first, *iterlabel, rate ) || machine.learning( i.second, *iterlabel, rate ) ){
						has_updated = true;
					}
					++iterlabel;
				}
			}

			if(!has_updated){
				++learned_dichotomies;
			}

/*			if( iter_count % 100 == 0 ){
				cout << "Elapsed time: " << (int)(stopTimer(time)) << "s\t\tCompletamento: ";
				cout << 100 * ( (p - 1) * N_iterations + iter_count ) / (max_p * N_iterations) << "%\r" << flush;
			}
*/		}

		output << p << "\t" << (double)(learned_dichotomies) / N_iterations << "\t" << theory.getC(dimension,p) / pow(2,p) /*expectedLearnt(dimension, p, mean(rho))*/ << endl;
	}

	output.close();
	cout << endl << "Tempo totale impiegato: " << stopTimer(time) << "s" << endl;

	return 0;
}


//	First of all we find the tangent bundle of the n-sphere at the point p.
//		We have a orthonormal basis of this bundle (vector<vector<double>>).
//	Then we find a random direction on this tangent hyperplane by choosing a random linear combination of the basis vector (we call it "temp")
//	We have now to stretch the new vector "temp" so that it's projection on the n-sphere will have the wanted overlap
//		(simple geometric construction lead to ||temp||^2=(1-rho^2)/rho^2).
//	It's now time to add "temp" and "p" so that we find the "newpoint", projected on the n-sphere by normalizing.
//	The case with overlap<0 is considered by adding "temp" to "-p". The equality cos(x)=-cos(pi-x) implies
//		d(p,newpoint)=rho -> d(-p,newpoint)=-rho
//	The case with overlap=0 is considered returning "temp" after normalization to 1.
vector<double> partner(const vector<double> & p, double overlap){
	auto tan_bun = tangentBundle(p);
	Random< normal_distribution<>, double, double > rnd(randomEngine(), 0., 1.);
	vector<double> temp(p.size(), 0.);
	for(auto & i : tan_bun){
		temp = temp + (i * rnd.generate()) ;
	}
	if( overlap != 0 ){
		normalize( temp, sqrt(1 - overlap * overlap) / abs(overlap) );
		if( sign(overlap) > 0 ){
			vector<double> newpoint = p + temp;
			normalize(newpoint);
			return newpoint;
		}
		else{
			vector<double> newpoint = (p * (-1.)) + temp ;
			normalize(newpoint);
			return newpoint;
		}
	}
	else{
		normalize(temp);
		return temp;
	}
}


//	Calculates the fraction of dichotomies which can assign the same label to both of points of the doublet
double Psi(double rho){
	return 2 / M_PI * atan( sqrt( (1.+rho) / (1.-rho) ) );
}


// Starts the timer
clock_t startTimer(){
	return clock();
}


// Returns the time (in seconds) elapsed from the time passed by argument
double stopTimer(clock_t begin){
	return (double)( clock() - begin ) / CLOCKS_PER_SEC;
}