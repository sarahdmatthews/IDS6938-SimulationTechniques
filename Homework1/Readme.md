#Homework 1 : The Jello Cube (Continuous Simulation Assignment
## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

Sarah Matthews

This is the framework for homework #1. Please first read the [homework writeup](HomeWork%231.pdf).

The assignment is due: Monday, February 27 at 11:59PM (EST)

| undeformed jello  | deformed jello |
| ------------- | ------------- |
| ![](images/undeformed3.png?raw=true)  | ![](images/deformed3.png?raw=true) |


Please look at Excel spreadsheet [Part_1_HW_1](Part_1_HW_1.xlsx).

##Part 1:
####A & B:
(equation placed in Wolfram Alpha)
~~~
y'(x)= (y- ((1/2)*e^(x/2)) * sin(5x))+ (5e^(x/2) * cos5x), y(0)=0 
~~~
Returned approximate form: 
~~~
y(x) = e^(x/2) sin(5 x)
~~~
Exact form: y(x)=2.71828^(0.5 x) sin(5 x)

***

####C: graph named part 1 c graph 

**************look between here**********

|![](images/Part1cgraph.png?/raw=true)  |

******

####D: graph named part 1 d graph
******
|![](images/Part1dgraph.png?/raw=true)  | 
*****
####E: graph named part 1 e graph RK4 Results and part 1 e graph RK4 Percent Error

*****

|![](images/Part1egraphRK4Results.png?/raw=true)  | 

******

|![](images/Part1egraphRK4PercentError.png?/raw=true)  |

*****

####F: In theory varying the integration methods towards higher order introduces more accuracy and less error. 

This is a trend that is illustrated in the differential equation given in this exercise as shown in the graphs for part c and d of the assignment.  

As the order is increased from RK1 (Euler) to RK2 (Midpoint) to RK4 the graphical representation shows the function moving more toward the shape of the exact and the percent error is reduced.  

In other words, Euler method is the least accurate for integrating the equation.  

(2) As the value of x is increased the accuracy in lowered, this is illustrated in graph d for this exercise.  

(3) As the value of h (step size) is increased the accuracy is lowered which is illustrated in the graph in part e of this exercise.  

(4)The method that is most accurate is RK4 with the lower step size of h=0.3, the percent error is lesser than the other steps size in RK4.  

*****

###Part2:
Part 2 of this assignment, I received assistance from students in our class.  
Outside help included Dr. P. Weigand at UCF 
H.Carr-computer engineer
###
Resources Used
msdn.com to understand C++ commands
http://beginnerscpp.com/ for online tutorials


*********


##Part 3:
#### 1. As Ks gets bigger the bouncer or less ridgid the cube becomes. Kd, the damping force will always oppose the motion.  
Thus if you increase Ks and Kd the cube will not bounce at the same time.  Lower Kd and increase Ks for lower stiffness. 
If no value to Kd the cube will continue to bounce.
*****

####2. The benefit of the collision system is it is simple to teach novice persons about the system, but the barrier is that the 
applicability for other systems seems limited. 
*****
####3. Systems that could model mass-spring simulations include hair simulations, grass simulations, fur, deformed shapes, 
which can be applied to animation, video games, fashion (modeling cloth).
*****
####4. My jello does not behave realistically but I believe it could if given the better paramaters as seen in some of the simulations online.  
Realistically, if a jello cube hit a cylinder it would have 
cut through the cube (I am thinking jello jigglers, this is what is used in the jello molds to give stiffer jello).
*****
The integration method utilized in my homework was RK4.
*****
####5. Simulating water would be complex, taking formless matter (liquid) and putting it into a form in order to simulate it.  
Fluids can be static or dynamic and would involve the physics of fluid dynamics.
Fluid dynamics would include things like flow rate, bernoulli's equation, viscosity, surface tension and adhesion and venturi effects.  
But would also include gravity and the use of Pascal's Principles. 
Also, it may include bouyancy and thus Archimedes Principles would need to be applied.  
Because fluids take the shape of the container it is in, the number of particles that would be used would be significantly
greater than that used in the cube (bound matter).

~~~
###Part 4:
Results of Cube:
Spring Constants:  For Ks values ranged from 1000-5000.  Kd values were less than 10.  
The Ks had to be set high to see any change in the cube.  Too high and the cube bounced off or blew up.

g_structuralKs = 3000.0
g_structuralKd = 5.0
g_attachmentKs = 1000.0
g_attachmentKd = 5.0
g_shearKs = 3000.0;
g_shearKd = 6.0;
g_bendKs = 5000.0;
g_bendKd = 5.0;
g_penaltyKs = 1000.0;
g_penaltyKd =200.0;

I used Rk4 integration because the cube looked cleaner.  When I used midpoint, the cube was suspended and did not bounce.  Euler integration bounced and then the
cube disappeared into the ground and then pulsated and came back up.  It was messy.  


