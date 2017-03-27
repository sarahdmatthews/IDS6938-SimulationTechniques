int size = 101;  //TODO  changed to 10 from class notes to check matrix as it is built
Eigen::MatrixXf TransitionMatrix(size, size);
Eigen::VectorXf v(size);

unsigned int ROLLS = 50; //TODO

double prob = 1.0 / 6.0;  //TODO  use 5 to check as build should be 1.0/6.0

void SetTransitionMatrix()
{
	TransitionMatrix.setZero();

	//TODO
	//this would be it by hand
	/*TransitionMatrix(0, 0) = prob;
	TransitionMatrix(1, 0) = prob;
	TransitionMatrix(0, 1) = prob;
	TransitionMatrix(2, 0) = prob;*/

	// Make and idenity matrix : https://en.wikipedia.org/wiki/Identity_matrix from Piazza
	
	for (int i = 0; i < TransitionMatrix.rows() - 6; i++) //from class on 3/21  -6 omits last 6 rows
		{
			TransitionMatrix(i, i + 1) = prob;
			TransitionMatrix(i, i + 2) = prob;
			TransitionMatrix(i, i + 3) = prob;
			TransitionMatrix(i, i + 4) = prob;
			TransitionMatrix(i, i + 5) = prob;
			TransitionMatrix(i, i + 6) = prob;
		}
// A markov chain defines the probability from state i to state j by a transition matrix, T
		
		//
		//for (int j = 95 ; j < TransitionMatrix.rows(); j++)//all probabilities for last row is 0
		//TransitionMatrix(j, j + 1) = prob;
		//TransitionMatrix(j, j + 2) = prob;
		//TransitionMatrix(j, j + 3) = prob;
		//TransitionMatrix(j, j + 4) = prob;
		//TransitionMatrix(j, j + 5) = prob;
		//TransitionMatrix(j, j + 6) = prob;
	//This is for the Null State
		for (int j = 95; j < TransitionMatrix.size(); j++)//all probabilities for last row is 0
		for (int k=95; k < TransitionMatrix.size() -1; k++)
			TransitionMatrix(j, k+1) = prob;

		// row 95 probability
		TransitionMatrix(95, 96) = prob;
		TransitionMatrix(95, 97) = prob;
		TransitionMatrix(95, 98) = prob;
		TransitionMatrix(95, 99) = prob;
		TransitionMatrix(95, 100) = prob*2;

		// row 96 probability
		TransitionMatrix(96, 97) = prob;
		TransitionMatrix(96, 98) = prob;
		TransitionMatrix(96, 99) = prob;
		TransitionMatrix(96, 100) = prob*3;

		// row 97 probability
		TransitionMatrix(97, 98) = prob;
		TransitionMatrix(97, 99) = prob;
		TransitionMatrix(97, 100) = prob*4;

		// row 98 probability
		TransitionMatrix(98, 99) = prob;
		TransitionMatrix(98, 100) = prob*5;

		// row 99 probability
		TransitionMatrix(99, 100) = 1;

		// row 100 probability
		TransitionMatrix(100, 100) = 1;

		std::cout << TransitionMatrix << std::endl;
		exit(1); //class notes 3/21

}