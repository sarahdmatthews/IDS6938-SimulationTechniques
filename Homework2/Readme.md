#Homework 2 :  Discrete-Event Simulation Assignment

## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

[University of Central Florida](http://www.ist.ucf.edu/grad/)
This is the framework for homework #2. 

The assignment is due: **Tuesday, March 28 at 11:59PM (EST)**

Sarah Matthews.  I would like to use an extra day and turn my final responses in on Wednesday, March 29. (This statement was uploaded at 11:40p.m. on 3/28/17.
Final submission for grading submitted March 29 at 11:20AM


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

*** Graphing the RNG and reviewing the test statistics illustrates that the RNG are not normally distributed. The RNG showed very similar patterns.  

| ScatterPlots| 
| ------------- | 
| ![](images/Part1AScatter.png?raw=true)  |


* **B 
***The RNG samples "N" are varied.  
With N varied among the random generators the trend remains the same, the magnitude is increases as N is increased. Mean and Stdev remain consistent but the test
statistics increased as N increased.   

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
Looking at the unit squares and unit circles, it would seem that the greater the N the less randomness with the denser plots.  I know that the class said my sobol looked like 
the pattern but I think this was just manipulation of the data and not truely what should be expected.  The RNGs used are Mersene Twister, Knuth B, Minimal Std Rand, Ranlux and Quasi

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
*** The distributions for the Mersene Twister are below.  Not sure how to interpret the unit square and circle plots. I used the Exponential and Weibull distributions in this analysis as 
opposed to the previous distributions as the program would not run on some of the distributions I previously selected.  The distributions used are Uniform, Normal, Poission, Weibull, and Exponential.

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
* **Response A  See Code for Null State Game Transition Matrix.  Received help in study group for creating code.  Code that I wrote was commented out as it did not work.
* **Response B  Code simulated.  Help from Julie in class to create code.  Was not sure what to do here with the analysis.    
* **Response C  Results from simulation attached in Excel spreadsheet, unsure of what other analysis to do here.  Took the extra day to focus on this but it is just too confusing for me to tackle today.  

| Snakes and Ladders Output without analysis| 
| ------------- | 
| ![](images/SnakesOutputDTMC.png?raw=true)  |
| ------------- |
| ![](images/SnakesOutputMarkov.png?raw=true)  |

Run the same simulation and analyze your results similar to part (b) for the proper game of *Snakes and Ladders* for both methods. How often are the snakes and ladders used, how do the probability of finishing change, etc? What is the maximum and expected amount of moves for the game? Use charts and graphs to illustrate these points.
* **(d) Think - 0pts:** If these games are built entirely on chance, do they require any strategy? Is it really a *game*, would you rather play games of chance or games of strategy?


##Part 3 - Discrete Event Simulation - Queue Simulation (30 pts)

We will make the following assumptions: (1) there is only one airline - Southwest; (2) passengers' interarrival times are independent and identically distributed (IID) with an exponential distribution with mean 1 / lambda. The service times are also assumed to be IID and exponentially distributed random variables with mean 1 / mu.
<BR>![](images/queue.png?raw=true)<BR>
When a passanger arrives they have to wait in a queue to present their ID and ticket to the gate agent with all the other passengers. Once approved by the agent they will have to pass through a security check. Since this is Orlando, there are only 3 open metal/screening devices open and again passangers have to wait in a queue. After passing through security you again have to wait in a queue to board your plane.


* **Response a  see code in in *main.cpp*. Checkin will have a *mu* of 53 and accept new arrivals, the security gates will have a *mu* of 20, and will not accept new arrivials, boarding will have a *mu* of 80. You will have to set up  the appropriate *MM1_Queue* objects to capture the functionality above.
* **Response b  see code for process error range will be 0.002
* **Response c in *mm1_queue.cpp* add code to caculate the expected results for:
   *   expected_server_utilization_ = lambda_ /mu_;
   *   expected_idle_prob_ = 1- (lambda_ / mu_); ///1-rho   rho=lambda/mu
   *   expected_queue_length_ = ((lambda_ / mu_)*(lambda_ / mu_)) / (1- (lambda_ / mu_));//(lamda/mu)^2 / (1-(lambda/mu))
   *   expected_number_customers_ = (lambda_ / mu_) / (1- (lambda_ / mu_));  //  rho/(1-rho)
   *   expected_waiting_time_ = (lambda_ / mu_) / (mu_ - lambda_); // rho/ (mu-lamda)
   *   expected_response_time_ = 1/ (mu_ - lambda_); //1/(mu-lamda)

*  ** Response d output data in Excel spreadsheet.  I took the information made a chart and graphed the mean verses expected.  Not sure if this is accurate and what if any meaningful information is here. 

| Queue Data| 
| ------------- | 
| ![](images/QueueStats.png?raw=true)  |

* **Response e See attached file in Anylogic

| Any Logic Screenshots| 
| ------------- | 
| ![](images/AnyLogicQueue.png?raw=true)  |
| ![](images/AnyLogicRunning.png?raw=true)  |
| ![](images/AnyLogic3D.png?raw=true)  |

##Part 4 - Implementing Extra Features (10 pts)
Implementing 2 features on the extra features list. Pick any feature on the "*extra features*" list below to customize your assignment to fit your interests. Please document this in your writeup. (*Note: These should total 10pts. You could successfully implement a feature worth 10pts or greater. This also fulfills this requirement. The features are assigned points based on difficulty. The 5pt features are more straightforward.*)

* **(10 Points)** - Add a 2D visualization to AnyLogic for Part 3.  See Anylogic file. 

* **(10 Points)** - Add a 3D visualization to AnyLogic for Part 3.  I tried to do this but it looks like my people are making a tornado before the queue.  

