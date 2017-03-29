#Homework 2 :  Discrete-Event Simulation Assignment

## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

[University of Central Florida](http://www.ist.ucf.edu/grad/)
This is the framework for homework #2. 

The assignment is due: **Tuesday, March 28 at 11:59PM (EST)**

Sarah Matthews.  I would like to use an extra day and turn my final responses in on Wednesday, March 29. (This statement was uploaded at 11:40p.m. on 3/28/17.


# Assignment
##Part 0 - Getting Started
Read the assignment. Sync your fork with the [main IDS6938 repository](https://github.com/hepcatjk/IDS6938-SimulationTechniques). Use CMake to create project files for the Homework 2 assignment (*Hint: and Discrete Lecture folders*). Set your *startup project* to the correct project. Test building and executing the homework 2 project. Look over and understand the framework and find the functions you need to edit for the assignment.


##Part 1: Empirical Tests of Randomness (20 pts).

##Part 1 Responses:
* **A 
***Outputs for 5 different RNG-Mersene Twister, Knuth B, Minimal Std Rand, Ranlux and Quasi.  
Using uniform distribution for values between 0-100.  Statistics that were generated include Mean,
Standard Deviation Stdev, Standard error of the mean SE, Chi Squared test statistic.  The alpha 
used as the critical value equaled 123.255.  N was 100000, expected generated of 1000, the df was 99.

| Parameters and Statistics | 
| ------------- | 
| ![](images/Part1A1.png?raw=true)  | 

*** The tests that were included in the analysis included the Kolmogorov-Smirnov test, Skewness and Kurtosis.  
The K-S test is used to look at goodness of fit test.  The null hypothesis is that the data generated will be
normally distributed.  If the test statistic D is greater than the critical value then the null is rejected. 
In all the 5 RNG's the D is greater than the critical value.  A normal distribution has skewness and excess kurtosis of 0, 
if the distribution is close to this values then it is probably close to normal.
  
| Kolmogorov-Smirnov test, Skewness and Kurtosis| 
| ------------- | 
| ![](images/Part1A2.png?raw=true)  |

*** Graphing the RNG and reviewing the test statistics illustrates that the RNG are not normally distributed.  

| ScatterPlots| 
| ------------- | 
| ![](images/Part1AScatter.png?raw=true)  |


* **B 
***The RNG samples "N" are varied.  
With N varied among the random generators the trend remains the same, the magnitude is increases as N is increased. 

| 5 Engines with Vary N Plot| 
| ------------- | 
| ![](images/Part1B1.png?raw=true)  |

*** As N is varied the test statistics are increased as N is increased.  

| 5 Engines with Vary N Statistics| 
| ------------- | 
| ![](images/MinimalStdVaryN.png?raw=true)  |
| ------------- | 
| ![](images/MTStatsVaryN.png?raw=true)  |
| ------------- | 
| ![](images/KnuthVaryN.png?raw=true)  |
| ------------- | 
| ![](images/QuasiVaryN.png?raw=true)  |
| ------------- | 
| ![](images/RanluxVaryN.png?raw=true)  |

* **C
*** The distributions used are used with the RNG-Mersene Twister. N is 100000
Distributions are Normal, Binomial, Uniform Discrete, Poission and Chi Squared.

| 5 Distributions in Mersene Twister| 
| ------------- | 
| ![](images/Distributiongraphs.png?raw=true)  |
| ![](images/Distributiongraphs2.png?raw=true)  |


Cumulative distribution function-If normally distributed these values should be zero
Kolmogorov-Smirnov test-Dn is larger than  Dnα  Not a good fit of normal distribution. If the data is normally distributed then the critical value Dn,α will be larger than Dn.
Skewness should be equal to zero if normal distribution
Kurtosis should be equal to zero if normal distribution

* **D, F

| Random Numbers in Unit Square Quasi-Random Sobol| 
| ------------- | 
| ![](images/QuasiRadomUnitSquareCircle.png?raw=true)  |


| Random Numbers in Unit Square and Unit Circle for Different RNG| 
| ------------- | 
| ![](images/UnitSquareUnitCircleRNGSlide1.PNG?raw=true)  |
| ------------- |
| ![](images/UnitSquareUnitCircleRNGSlide2.PNG?raw=true)  |
| ------------- |
| ![](images/UnitSquareUnitCircleRNGSlide3.PNG?raw=true)  |
| ------------- |
| ![](images/UnitSquareUnitCircleRNGSlide4.PNG?raw=true)  |
| ------------- |
| ![](images/UnitSquareUnitCircleRNGSlide5.PNG?raw=true)  |

* **E, F
***
| Random Numbers in Unit Square and Unit Circle for Different Distributions| 
| ------------- | 
| ![](images/Slide1.PNG?raw=true)  |
| ------------- |
| ![](images/Slide2.PNG?raw=true)  |
| ------------- |
| ![](images/Slide3.PNG?raw=true)  |
| ------------- |
| ![](images/Slide4.PNG?raw=true)  |
| ------------- |
| ![](images/Slide5.PNG?raw=true)  |

##Part 2 - Snakes and Ladders (Discrete Event Markov Chains and Monte Carlo Simulations) (30 pts)


##### Background
* **(a) Create this transition matrix. The end is trickier, we will consider any roll past 100 a win case. (Opposed to rolling exactly onto square 100.) Confirm you have a well formed stochastic matrix (Write checks for confirming each row of T sums to one and all elements are non-negative). The Transition Matrix methods can be found in the TransitionMatrix.h file.

***Response A  See Code for Null State Game Transition Matrix
***Response B  Code simulated.  The modal number of moves required by a single player to finish the game is

* **(b) Simulate and analyze the results of Null State Game - 10pts:** What is the modal number of moves required by a single player to finish the game? We will be simulating the game two different ways. **(1) Markov Chain**: The game can be analyzed with a row vector, *v* with 101 components, representing the probabilities that the player is on each of the positions. V(0) is (1,0,0,...,0) since we know we start at square 0. v evolves by: <BR>![](images/prob.png?raw=true)<BR>
For this part (1) use the *Markov project* in the Snake and Ladders starter code.<BR>
**(2) Monte Carlo**: he will will use a monte carlo process to solve our Discrete Time Markov Chains. Here (2) use the DTMC project, and utilize the DTMC method similar to what we did in class. <BR><BR>Produce graphs to analyze the results and show how the game evolves over time for both methods. Plot useful statistics of the results such as percentage chance of finishing the game in n-moves, cumulative probability of finishing the game in n-moves, and other ways to convey useful information of the results.

* **(c) Simulate and analyze the results of Snakes and Ladders -10pts:**  Construct a new transition matrix based on the table:


Ladders From  | Ladders To | |  Snakes From  | Snakes To 
-------- | -------- | ------------- | -------- | -------- 
3|19| |11|7
15|37| |18|13
22|42| |28|12
25|64| |36|34
41|73| |77|16
53|74| |47|26
63|86| |83|39
76|91| |92|75
84|98| |99|70



Run the same simulation and analyze your results similar to part (b) for the proper game of *Snakes and Ladders* for both methods. How often are the snakes and ladders used, how do the probability of finishing change, etc? What is the maximum and expected amount of moves for the game? Use charts and graphs to illustrate these points.
* **(d) Think - 0pts:** If these games are built entirely on chance, do they require any strategy? Is it really a *game*, would you rather play games of chance or games of strategy?


##Part 3 - Discrete Event Simulation - Queue Simulation (30 pts)

We will make the following assumptions: (1) there is only one airline - Southwest; (2) passengers' interarrival times are independent and identically distributed (IID) with an exponential distribution with mean 1 / lambda. The service times are also assumed to be IID and exponentially distributed random variables with mean 1 / mu.
<BR>![](images/queue.png?raw=true)<BR>
When a passanger arrives they have to wait in a queue to present their ID and ticket to the gate agent with all the other passengers. Once approved by the agent they will have to pass through a security check. Since this is Orlando, there are only 3 open metal/screening devices open and again passangers have to wait in a queue. After passing through security you again have to wait in a queue to board your plane.


**Response a  see code in in *main.cpp*. Checkin will have a *mu* of 53 and accept new arrivals, the security gates will have a *mu* of 20, and will not accept new arrivials, boarding will have a *mu* of 80. You will have to set up  the appropriate *MM1_Queue* objects to capture the functionality above.
**Response b  see code for process error range will be 0.002
**Response c in *mm1_queue.cpp* : add code to caculate the expected results for:
   *   expected_server_utilization_ = lambda_ /mu_;
   *   expected_idle_prob_ = 1- (lambda_ / mu_); ///1-rho   rho=lambda/mu
   *   expected_queue_length_ = ((lambda_ / mu_)*(lambda_ / mu_)) / (1- (lambda_ / mu_));//(lamda/mu)^2 / (1-(lambda/mu))
   *   expected_number_customers_ = (lambda_ / mu_) / (1- (lambda_ / mu_));  //  rho/(1-rho)
   *   expected_waiting_time_ = (lambda_ / mu_) / (mu_ - lambda_); // rho/ (mu-lamda)
   *   expected_response_time_ = 1/ (mu_ - lambda_); //1/(mu-lamda)

*  **(d) - 4pts:** Write code to call the functions to output and generate data from the airport senario. Plot and analyze the useful statistics/results in the program of your choice.  (Hint -  basically call  *.output();* on the MM1_Queue objects you create. Hint2 - two other use functions are *get_current_time()* and  *plot_results_output()* call intially on your intial MM1_Queue object.)  

| Queue Data| 
| ------------- | 
| ![](images/QueueStats.png?raw=true)  |

* **(e) - 15pts:** Download the personal edition of **[Anylogic](http://www.anylogic.com/)**, read through the [documentation](http://www.anylogic.com/learn-simulation) as needed, and set up the same type of simulation discussed above.

***Response e See attached file in Anylogic

| Any Logic Screenshots| 
| ------------- | 
| ![](images/AnyLogicQueue.png?raw=true)  |
| ![](images/AnyLogicRunning.png?raw=true)  |
| ![](images/AnyLogic3D.png?raw=true)  |

##Part 4 - Implementing Extra Features (10 pts)
Implementing 2 features on the extra features list. Pick any feature on the "*extra features*" list below to customize your assignment to fit your interests. Please document this in your writeup. (*Note: These should total 10pts. You could successfully implement a feature worth 10pts or greater. This also fulfills this requirement. The features are assigned points based on difficulty. The 5pt features are more straightforward.*)

* **(10 Points)** - Add a 2D visualization to AnyLogic for Part 3.  See Anylogic file. 

* **(10 Points)** - Add a 3D visualization to AnyLogic for Part 3.  I did this but it looks like my people are making a tornado before the queue.  



##Part 5 - Final Report (10 pts)
Write up the results to the previous sections in the main *readme.md* in your forked repository. Turn in the URL for your fork in webcourses. Be visual. The report should contain the graphs and analysis requested. I have high expectations for the documentation here and you should allot the proper time to compose the writeup.


##Extra Features (Extra Credit - 25pts)
You have to implement two features from this list for Part 4. You may choose any two features you wish from this list. (Please explicitly note them in your *Readme.md*)

If you feel like going beyond the scope of the assignment, you should consider implementing more of the following extra features. *Get the assignment working without them first.* You can get a maximum of 25 points in extra credit. Simply implementing these things doesn't guarantee you a 25; you really need to go above and beyond to get the full amount. (*The instructor reserves the right to hand out extra credit as his he sees fit.*)

* **(5 Points)** - Implement and compare Halton, Hammersley, (Or another quasi method) Quasi sequences and add them to your analysis for appropriate subparts of Part 1.
* **(5 Points)** - Implement different distributions inside the Quasi random sequences and add them to your analysis for appropriate subparts of Part 1.
* **(5 Points)** - Implement and compare another (advanced) psedo random sequences and add them to your analysis for all subparts of Part 1 (Examples include: [PCG](http://www.pcg-random.org/), or [Random123](https://github.com/DEShawResearch/Random123-Boost)).
* **(20 Points)** - Complete Part 2 with a different board game. Construct the game's transition matrix, simulate the game, and analyze the results (Run the game past the instructor).
* **(20 Points)** - Complete Part 2 with a 3D version of Snakes and Ladders. Construct the game's transition matrix, simulate the game, and analyze the results.
* **(10 Points)** - Provide code in (Python, R, Matlab...) that demonstrates an animation of the board itself evolving overtime for Snakes in Ladder for part 2. 
* **(10 Points)** - Add a 2D visualization to AnyLogic for Part 3.
* **(10 Points)** - Add a 3D visualization to AnyLogic for Part 3.
* **(5 Points)** - Pick a research problem (from your dissertation, Energy Microgrids, Missle Defence...). Compare and contrast different software packages (AnyLogic, Simio, Simulu8, Arena etc). Convince me as your "manager/advisor" what advantages, weaknesses, and costs each program has. Come to a conclusion. Roughly sketch out how you would formulate the problem in the framework.
* **(10 Points)** - Create an Anylogic simulation for Part 2 - Snakes and Ladders.
* **(10 Points)** - Setup another resource allocation / queueing problem related to your research in Anylogic with a basic visualization
* **(10 Points)** - Setup up SmartGrid or a Microgrid System that creates resources of power from wind, solar, and electric grid. Set up various devices in your house to draw power. [Reference 1](http://www.sciencedirect.com/science/article/pii/S1877050916301740),   [Reference 2](http://www.tandfonline.com/doi/full/10.1080/19401493.2013.866695?src=recsys&).
* **(25 Points)** - Set up a discrete simulation of your choice that uses an approved real-time data source and visualizes the results. (See instructor for approval).
* **(N Points)** - You are welcome to make suggestions for a feature of your own choosing, but they must be approved by instructor before implementing.