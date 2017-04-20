# Homework 3 : Agent based Simulation Assignment 

## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

[University of Central Florida](http://www.ist.ucf.edu/grad/)
This is the framework for homework #3. 

The assignment is due: **Monday, April  24 at 11:59PM (EST)**

# Part 1: Behaviors
**(a)**: Compute the derivative vectors
Initially started with the derviative 0 as the original position and wrote the equations of the 1st derivative as velocity and second as acceleration. 
But this process did not work with the information given in the instructions.  With help from Julie was able to rework what derivatives and states equated to
motion of the object.   Initially derivative 3 was computed using F=ma and solving for a, with input[1] being torque force and inertia being the m as inertial mass.  
Mass determines momentum in a given velocity p=mv and m is equal to intertial mass.  State 3, angular velocity is removed from the inertia so that accleration is computed.
This was also a trial and error using mathematics.  

To implement the initial values, trial and error method was first utilized but the numbers did not work.  I think used a Utube video to help with understanding the parameters these
values should have and what the behaviors should look like. Bradley Crusco https://www.youtube.com/watch?v=tEGR6NN-cQc  

	deriv[0] = state[2];  
	deriv[1] = state[3];  //1st dervivative is velocity
	deriv[2] = input[0] / Mass;
	deriv[3] = input[1] / Inertia - state[3];
	
These parameters are adjusted when doing the group behaviors.
	Kv0 = 10.0;   //used Utube video for these parameters
	Kp1 = 200.0;
	Kv1 = 32.0;
	KArrival = 0.05;
	KDeparture = 15.0;
	KNoise = 10.0;
	KWander = 8.0;
	KAvoid = 1.0;
	TAvoid = 20.0;
	RNeighborhood = 800.0;
	KSeparate = 1000.0;
	KAlign = 20.0;
	KCohesion = 0.05;

**(b)**: Implement the following behaviors
* Seek
* Flee
* Arrival
* Departure
* Wander
* Obstacle Avoidance

Using notes from class and the webcourse notes, implement equations for Seek and Flee.  When the model was run, it did not work. 
By trial and error, implemented arrival and then the seek and flee worked.  Then implemented departure. Mac, Roberto and I worked on this part for
over 6 hours.  

These are some of the references we used.
https://gamedevelopment.tutsplus.com/tutorials/3-simple-rules-of-flocking-behaviors-alignment-cohesion-and-separation--gamedev-3444 
http://tigerprints.clemson.edu/cgi/viewcontent.cgi?article=1956&context=all_theses
http://www.kfish.org/boids/pseudocode.html

| Behaviors:Seek, Flee, Arrival, Departure | 
| ------------- | 
| ![](images/Behaviors.png?raw=true)  | 

To implement wander, we read that in one of our references above that wander add a random number using rand command.  Thus, we reused the code from our discrete 2, homework 2 assignment and implemented
the random number generator code from that homework to make the object wander.



**(c)**: Implement the following group behaviors
* Separation
* Cohension
* Alignment
* Flocking
* Leader Following

In one of the references it recommended to do alignment first, then cohension and separation is a simple change in code where.  



# Part 2: Simulating a simple pedestrian flow
**(a)** Subway Entrance Example
| Subway Tutorial| 
| ------------- | 
| ![](images/Subwaytutor.png?raw=true)  |


**(b)** Create a Maze

| Simple Maze| 
| ------------- | 
| ![](images/Slide1.PNG?raw=true)  |


| Simple Maze when Running Model| 
| ------------- | 
| ![](images/Mazerun.png?raw=true)  |

*I used the time and intensity statistics time plots to understand where the most hold up might be in the system.  Here is it at the entrance, midpoint and exit, but I could have put in points 
at each of the decision points to see if one took more time than the other.  It is interesting because each decision point had a 50% probabililty of choice.  

| Simple Maze in 3D and with Time and Intensity Statistics| 
| ------------- | 
| ![](images/Maze2.png?raw=true)  |

**(c)** UCF Building
According to the Libriarian, the 4th floor has five stairwells, each of which have emergency exits at the bottom level. 
Depending upon where a person is on the floor, they would use one of those stairwells.  
So there is no one “evacuation plan” because it differs depending upon where you are on the floor at any given time.  
Overhead “EXIT” signs with arrows on each floor point out a path to a stairwell and emergency exit from the major aisles. 
So the patron is given a suggested evacuation route from any location by following the overhead lighted exit signs. The maximum occupancy for the library overall is 2,000, this is not delinated by floor. 
I started doing the 4th floor and then switched to the 5th floor because I was finding the bookshelves tough to draw.  

  