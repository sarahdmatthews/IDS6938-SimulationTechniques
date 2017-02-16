#Homework 1 : The Jello Cube (Continuous Simulation Assignment
## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

Sarah Matthews

This is the framework for homework #1. Please first read the [homework writeup](HomeWork%231.pdf).

The assignment is due: Monday, February 27 at 11:59PM (EST)

| undeformed jello  | deformed jello |
| ------------- | ------------- |
| ![](images/undeformed3.png?raw=true)  | ![](images/deformed3.png?raw=true) |


Part 1:
A & B:
y'(x)= (y- ((1/2)*e^(x/2)) * sin(5x))+ (5e^(x/2) * cos5x), y(0)=0 (equation placed in Wolfram Alpha)
Returned approximate form: y(x) = e^(x/2) sin(5 x)
Exact form: y(x)˜2.71828^(0.5 x) sin(5 x)

C: graph named part 1 c graph 
|![](images/Part 1 c graph.pgn?/raw=true)  | ![](images/Part 1 c graph.pgn?/raw=true) |

D: graph named part 1 d graph
|![](images/Part 1 d graph.pgn?/raw=true)  | ![](images/Part 1 d graph.pgn?/raw=true) |

E: graph named part 1 e graph RK4 Results and part 1 e graph RK4 Percent Error
|![](images/Part 1 e graph RK4 Results.pgn?/raw=true)  | ![](images/Part 1 e graph RK4 Results.pgn?/raw=true) |
|![](images/Part 1 e graph RK4 Percent Error.pgn?/raw=true)  | ![](images/Part 1 e graph RK4 Percent Error.pgn?/raw=true) |

F: In theory varying the integration methods towards higher order introduces more accuracy and less error. 
This is a trend that is illustrated in the differential equation given in this exercise as shown in the graphs for part c and d of the assignment.  
As the order is increased from RK1 (Euler) to RK2 (Midpoint) to RK4 the graphical representation shows the function moving more toward the shape of the exact and the percent error is reduced.  
In other words, Euler method is the least accurate for integrating the equation.  
(2) As the value of x is increased the accuracy in lowered, this is illustrated in graph d for this exercise.  
(3) As the value of h (step size) is increased the accuracy is lowered which is illustrated in the graph in part e of this exercise.  
(4)The method that is most accurate is RK4 with the lower step size of h=0.3, the percent error is lesser than the other steps size in RK4.  

