WARNING:=-Wall -Wno-sign-compare

all: program.x
program.x: perceptron.o random.o algebra.o theoretic.o main.o
	g++ main.o perceptron.o random.o algebra.o theoretic.o ${WARNING} -O3 -o program.x
main.o: main.cpp
	g++ -c main.cpp ${WARNING} -O3 -o main.o
perceptron.o: perceptron.cpp perceptron.h
	g++ -c perceptron.cpp ${WARNING} -O3 -o perceptron.o
random.o: random.cpp
	g++ -c random.cpp ${WARNING} -O3 -o random.o
algebra.o: algebra.cpp algebra.h
	g++ -c algebra.cpp ${WARNING} -O3 -o algebra.o
theoretic.o: theoretic.cpp theoretic.h
	g++ -c theoretic.cpp ${WARNING} -O3 -o theoretic.o
launch: program.x
	./script.sh
clean:
	rm -f *.o *.x
removedata:
	find ./ -name *.dat *.png | xargs rm
compileprofiling: main.cpp perceptron.cpp perceptron.h random.cpp algebra.cpp algebra.h
	g++ main.cpp perceptron.cpp perceptron.h random.cpp algebra.cpp algebra.h -O3 -pg -o profiled.x
profiling: compileprofiling
	./profiled.x 0.5 && gprof profiled.x gmon.out > profile_analysis.txt && rm gmon.out