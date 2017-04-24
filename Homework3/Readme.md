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
This was also a trial and error using the mathematics.  Dr. Kider's post on 4/24/17 in Piazza confirmed our trial and error methods.  

To implement the initial values, trial and error method was first utilized but the numbers did not work.  I used a Utube video to help with understanding the parameters these
values should have and what the behaviors should look like. Bradley Crusco https://www.youtube.com/watch?v=tEGR6NN-cQc  

	deriv[0] = state[2];  
	deriv[1] = state[3];  //1st dervivative is velocity
	deriv[2] = input[0] / Mass;
	deriv[3] = input[1] / Inertia - state[3];
	

Initially used trial and error method to figure out these parameters but then used a Utube video to help with understanding the parameters these values should have and what 
the behaviors should look like. Bradley Crusco https://www.youtube.com/watch?v=tEGR6NN-cQc  These parameters are adjusted when doing the group behaviors.

	Kv0 = 10.0;  
	Kp1 = 200.0;
	Kv1 = 32.0;
	KArrival = 0.05;
	KDeparture = 15.0;  //velocity of departure
	KNoise = 10.0;
	KWander = 8.0;  //velocity to wander
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
By trial and error, implemented arrival and then the seek and flee worked, but it was backwards.  My seek fleed and my flee seeked. Therefore, I exchanged the code in the place.
Then implemented departure. Mac, Roberto and I worked on this part for over 6 hours. Alex assisted later on this and we changed the KP1 in the initial values and then the original code
for seek and flee worked correctly.  

We realized that you have to put the code for arrival into the system before Seek or Flee would work. Implemented Arrival, Departure, Seek and Flee.  
The motion of the object is still not smooth.  Once it was gliding along the surface and then it would twitch, the best I could get it to do is to walk with a twist.    

**These are some of the references we used.
**(1)**: https://gamedevelopment.tutsplus.com/tutorials/3-simple-rules-of-flocking-behaviors-alignment-cohesion-and-separation--gamedev-3444 
**(2)**: http://tigerprints.clemson.edu/cgi/viewcontent.cgi?article=1956&context=all_theses
**(3)**: http://www.kfish.org/boids/pseudocode.html

Arrival is the object heading to a desired position at a desired velocity and slows down when it gets close to the target position.  
Departure is the object heading away from a desired position to another position with a desired velocity.  
Seek is the object going toward a target and flee is the object going away from the target.

| Behaviors:Seek, Flee, Arrival, Departure | 
| ------------- | 
| ![](images/Behaviors.png?raw=true)  | 


Wander is the object moving randomly about.
To implement wander, we read that in one of our references above that wander add a random number using rand command.  Thus, we reused the code from our discrete 2, homework 2 assignment and implemented
the random number generator code from that homework to make the object wander. However, after discussion with Alex, was advised to use code in the beginning of the file that contained Wander elements
Using webcourse information to multiple returned vectors by KNoise and KWander for final vectors.

Obstacle Avoidance 

| Behaviors: Arrival, Departure, Wander, Separation with 10 | 
| ------------- | 
| ![](images/Group1.png?raw=true)  | 



**(c)**: Implement the following group behaviors
* Separation
* Cohension
* Alignment
* Flocking
* Leader Following

In group behaviors, BOIDS adhere to a set of rules.  Separation is when the BOIDS try to avoid each other, repulsion.  Alignment is where they steer toward a single average heading of neighbors.
Cohesion is when they go towards the Center of Mass of the immediate neighbor and change in velocity to position, they are attracted to each other. 

In one of the references it recommended to do alignment first, then cohension and separation is a simple change in code where.  I was not successful in this and received some help from
Roberto on the Separation code initially. The objects arrive at the target and the separation rule is applied.  The BOIDS twist themselves to separate, following the rules very slowly.
When the alignment rules are applied, the objects again twist slowly to align with their immediate neighbor.  The cohesion rule makes them all disappear.  Since Flocking and Leader Following
involves all three group behaviors (Separation, cohesion and Alignment), I was not fully able to implement this based on my limited coding.  I would have summed the rules together and add them to the
desired velocity.  For leader following, the group needs to follow a leader.  I would again use a summation of forces (arrival, separation and avoidance) and then add it to the current position.  

| Behaviors: Separation, Alignment, Cohesion | 
| ------------- | 
| ![](images/Group2.png?raw=true)  | 


As an aside, my numerous hours completing work for this class took away hours from my family.  In this assignment, I decided to include my 8 year old daughter.  Here she is playing with
the agent based models.  This was fun and memorable to her.  


| My 8 year old daughter and the Agent Based Simulations| 
| ------------- |
| ![](images/VidyaHW3.jpg?raw=true)  | | ![](images/VidyaHW3pic.jpg?raw=true)  | 



# Part 2: Simulating a simple pedestrian flow

**(a)** Subway Entrance Example


| Subway Tutorial| 
| ------------- | 
| ![](images/Subwaytutor.png?raw=true)  |


**(b)** Create a Maze

The maze is a simple maze that initally when ran, all the objects found the correct route to the exit.  

| Simple Maze| 
| ------------- | 
| ![](images/Slide1.PNG?raw=true)  |


To make the maze more realistic, I used the Assemble feature with attractors (at min 10) and decisions of 50% probability when the person had to chose which direction to go.  The assemble function simulates a person that is loss and
confused and they wait until another attractor come in to give them directions so they can leave and go to the next decision point.  I put the pedisterain density map into the simulation to show the paths that would be first utilize (show in red-greater density)
than those that would not (yellow to blue-less dense).  In the start of the simulation this tool is useful but after the run, the usefulness is limited.  In the picture, there is a flow route, I thought this would be able to give me some useful statistics as to how many
actually ran the correct route without taking a wrong turn, but I could not make it work, so it was removed.  


| Simple Maze when Running Model| 
| ------------- | 
| ![](images/Mazerun.png?raw=true)  |


I used the time and intensity statistics time plots to understand where the most hold up might be in the system.  Here is it at the entrance, midpoint and exit, but I could have put in points 
at each of the decision points to see if one took more time than the other.  The traffic function is calcuated by count the number of people that cross each of the lines in the model time (rate 1000/hour)
The flow direction is set by the object parameters which is the path of the maze.   The intensity is calculated by the traffic number dividd by the line length in meter so it is in the unit pedestrians/(hour*meter).



| Simple Maze in 3D and with Time and Intensity Statistics| 
| ------------- | 
| ![](images/Maze2.png?raw=true)  |

**(c)** UCF Building

According to the UCF Libriarian, Frank Allen, the 4th floor has five stairwells, each of which have emergency exits at the bottom level. 
Depending upon where a person is on the floor, they would use one of those stairwells.  
So there is no one “evacuation plan” because it differs depending upon where you are on the floor at any given time.  
Overhead “EXIT” signs with arrows on each floor point out a path to a stairwell and emergency exit from the major aisles. 
So the patron is given a suggested evacuation route from any location by following the overhead lighted exit signs. The maximum occupancy for the library overall is 2,000, this is not delinated by floor. 
I started doing the 4th floor and then switched to the 5th floor because I was finding the bookshelves tough to draw.  So the 5th floor had no bookshelves. The library staff was not well informed on their
evacuation plans and sent me to the UCF Office of Environmental Health and Safety.  Additional consultation with Librarian Frank Allen, identified that they will on occasion do occupancy studies.  The latest was October 2014, midsemester 
was chosen because it was busy.  Of the days sample, they peaked at 2:30p.m. on October 6th with 1,374 people per hour.  At 11:00a.m., the count was 883 and at 8:30p.m. count was 847, following a predictable bell curve.
The count is done manually with students standing at the door with clickers counting patrons coming in
and out.  They will be installing a system in the next few months that will automate this count. 


If a fire alarm goes off, the police instructions are for everyone including staff to exit to the nearest stairwell or front entrance.  There is no safe area identified and instructions are to stay a distance away from the building.
There are no posters in the public areas showing which path to take for closest exit but the illuminated fire exits signs have arrows that suggest which way to go and find a stairwell.  There are emergency exits at the bottom of each
stairwell.  During a fire alarm the doors into the stairwells close so that you can not come back into the building once you exit.   


Here is my scenerio that is based on the information that Frank Allen provided and my own experience as an undergraduate, now I think students don't go to the library as frequently to study because everything is online. 
It is finals week and the Libray Quite areas are filled to capacity.  The 5th floor is a quite area that students can go to study, since the entire building can only hold 2,000 people, I estimated at maximum
capacity the 5th floor will hold 300 people.  I have them arriving 10 per minute.  Each student finds a place on the 5th floor and starts studying.  To maintain the appropriate number of people that are allowed on 
each floor, only the front stairs are in use for arrival.  The elevators are being serviced at the moment and the side stairs can only be used for exits as the open from the inside out not from the outside in. It 
takes 30 minutes for the floor to meet max capacity.  Then the students start to study (Ped Wait), after 20 minutes, the fire alarm is set off (Event) and the students must leave by one of the three exits available
to go to the safety zone outside the library.  Note: Safety zone is for simulation as the real evacuation plans do not contain this element. This takes over 10 minutes to complete and the Anylogic software times out.  
The statistics I put into the model is traffic and intensity.  I did this because I wanted to see which exit would be utilized more frequently.  AnyLogic build that the people will take the shortest point and we see 
this with the objects utilizing the front stairs and the south stairs (right) and noone going to the west stairs (back left).  This logic fits nicely with the library evacuation plans described above.
It would have been interesting to put a longer duration for the students to meet the safety point to simulate the time it would take for them to go down 5 floors.  Also to simulate that when the bottleneck
is at the two doors, that some students would choose the west stairs to get out.    

| UCF 5th Floor Hitt Library Model| 
| ------------- | 
| ![](images/UCFSlide1.PNG?raw=true)  |


I also implemented the traffic and intensity ped statistics in this model as well. The picture shows the traffic statistics.  


| UCF 5th Floor Hitt Library Model Run| 
| ------------- | 
| ![](images/UCFSlide2.PNG?raw=true)  |


This picture shows both the traffic and intensity ped statistics for the model.  

| UCF 5th Floor Hitt Library Model with Intesity and Traffic Stats| 
| ------------- | 
| ![](images/PedStats.png?raw=true)  |


As a follow up, I sent the model to Librarian Frank Allen with some additional questions. Here is the feedback I received "Hi Sarah, Impressive work you are doing."

  