#include <iostream>
#include <functional>   
#include <numeric>  
#include <map>
#include "markov.h"
#include <fstream>
#include <map>
#include <math.h>
#include <vector>
#include <random>
#include <algorithm>
#include <Eigen\dense>



int main(){
  //SIMULATE DISCRETE TIME MARKOV CHAIN
  std::vector< std::vector<double> > matrix(101,std::vector<double> (101)); //initializes a 3x3 matrix with zeros
  
  std::vector<int> DTMC(Eigen::MatrixXf, int, int);
  //set transition matrix
  /*matrix[0][1] = 1;
  matrix[1][2] = 1;
  matrix[2][0] = 1;*/

 /* int steps = 10;
  int start = 0;
  double T = 8.5;*/
  
  {
	  int size = 10;  //TODO
	  Eigen::MatrixXf TransitionMatrix(101, 101);
	  Eigen::VectorXf v(size);

	  unsigned int ROLLS = 0; //TODO

	  double prob = 0.0;  //TODO




	  void SetTransitionMatrix()
	  {
		  TransitionMatrix.setZero();

		  //TODO


	  }
  //simulate discrete time Markov Chain
  //unsigned int N = 100000;
  //std::map<int, int> hist;
  std::vector<int> discreteMC;
  //for (unsigned int i = 0; i < N; ++i){
	 discreteMC = DTMC(matrix, steps, start);
//	  ++hist[std::round(discreteMC.back())];
//  }
  //Returns an array with the states at each step of the discrete-time Markov Chain
  //The number of transitions is given by steps. The initial state is given by start 
  //(the states are indexed from 0 to n-1 where n is the number of arrays in transMatrix).

  for (auto elem : discreteMC)
	  std::cout << elem << std::endl;

  std::cout  << std::endl;

//  for (auto p : hist)
//	  std::cout << p.first << "\t" << p.second << std::endl;


   std::cout<<std::endl << "End State is: " << discreteMC.back() << std::endl << std::endl;





  return 0;
}
