int size = 10;  //TODO  changed to 10 from class notes to check matrix as it is built
Eigen::MatrixXf TransitionMatrix(size, size);
Eigen::VectorXf v(size);

unsigned int ROLLS = 0; //TODO

double prob = 1.0 / 6.0;  //TODO  use 5 to check as build should be 1.0/6.0

std::cout << TransitionMatrix << std::endl;




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
	for (int i = 0; i < size; i++)
	{
		TransitionMatrix(i, i) = 1
	}

	myvector.transpose() * Matrix  //from Piazza

	for (int i = 0; i < TransitionMatrix.rows - 6; i++) //from class on 3/21  -6 omits last 6 rows
	{
		TransitionMatrix(i, i + 1) = prob;
		TransitionMatrix(i, i + 2) = prob;
		TransitionMatrix(i, i + 3) = prob;
		TransitionMatrix(i, i + 4) = prob;
		TransitionMatrix(i, i + 5) = prob;
		TransitionMatrix(i, i + 6) = prob;
// A markov chain defines the probability from state i to state j by a transition matrix, T
		
		myvector.transpose() * Matrix

		for (int j = 0 ; j < TransitionMatrix.rows (); j++)//all probabilities for last row is 0
		TransitionMatrix(j, j + 1) = 0;
		TransitionMatrix(j, j + 2) = 0;
		TransitionMatrix(j, j + 3) = 0;
		TransitionMatrix(j, j + 4) = 0;
		TransitionMatrix(j, j + 5) = 0;
		TransitionMatrix(j, j + 6) = 0;
}
	std::cout << TransitionMatrix << std::endl;
	exit(1); //class notes 3/21