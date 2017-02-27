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
~~~
msdn.com to understand C++ commands
http://beginnerscpp.com/ for online tutorials

****
Unable to push my stuff to git hub wrote lines that I changed
~~~

Line 5-15

double JelloMesh::g_structuralKs = 5000.0; 
double JelloMesh::g_structuralKd = 5.0; 
double JelloMesh::g_attachmentKs = 1000.0;
double JelloMesh::g_attachmentKd = 5.0;
double JelloMesh::g_shearKs = 3000.0;
double JelloMesh::g_shearKd = 6.0;
double JelloMesh::g_bendKs = 3000.0;
double JelloMesh::g_bendKd = 5.0;
double JelloMesh::g_penaltyKs = 1000.0;
double JelloMesh::g_penaltyKd =200.0;

****
Line 201-209
//Extra Springs area-Bend Springs entered by HTC  add 1 to each of the values for the Springs
				if (j < m_cols - 1) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 2, k));
				if (i < m_rows - 1) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 2, j, k));
				if (k < m_stacks - 1) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 2));

				//Extra Springs area-Shear Springs
				if (j < m_cols - 2) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 3, k));
				if (i < m_rows - 2) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 3, j, k));
				if (k < m_stacks - 2) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 3));

****

428-459
  Spring& spring = m_vsprings[i];//lookup the i^th spring
        Particle& a = GetParticle(grid, spring.m_p1);//lookup the particle at one end of spring
        Particle& b = GetParticle(grid, spring.m_p2);//lookup the particle at the other end
		vec3 diff = a.position - b.position;
		double dist = diff.Length();
		 // TODO  Hooks Law and Damping  Sum of the force 
		
		//vec3 force_new = -spring.m_Ks* (a.position - b.position) - spring.m_restLen)* ((b.position - a.position / sqrt((a.position - b.position)*(a.position - b.position)); //elastic force of the spring
		vec3 force_new = -(spring.m_Ks * (dist - spring.m_restLen) + spring.m_Kd * (((b.velocity-a.velocity)* diff) /dist)) * (diff/dist);
		a.force = a.force+  force_new;   // a.force += force_new;
		b.force += -force_new;
		  } //Sum of Forces Ftotal=Felastic + Fdamping
****
461-492
void JelloMesh::ResolveContacts(ParticleGrid& grid)
{
    for (unsigned int i = 0; i < m_vcontacts.size(); i++)
    {
       const Intersection& contact = m_vcontacts[i];
       Particle& p = GetParticle(grid, contact.m_p);
       vec3 normal = contact.m_normal;
	   float dist = contact.m_distance;
	   double r = 0.5;	
	   p.velocity *= -1;
	   vec3 V = p.velocity;

		   // TODO v'=v-2(v dot N) (Nr)  //F=ma  a=distance veclocity/time
		    p.position = p.position + (dist*normal);
			p.force = dist*normal;  
			p.velocity =  (p.velocity) - (2*V*normal*(r * normal));	
    }
}
void JelloMesh::ResolveCollisions(ParticleGrid& grid)
{
    for(unsigned int i = 0; i < m_vcollisions.size(); i++)
    {
        Intersection result = m_vcollisions[i];
        Particle& pt = GetParticle(grid, result.m_p);
        vec3 normal = result.m_normal;
        float dist = result.m_distance;
		float r = 10;

  //      // TODO v'=v-2(v dot N) (Nr)
		pt.velocity = pt.velocity + (-2 * ((pt.velocity*(normal))*(normal*r)));
		pt.position = pt.position + (dist * normal);
	}
****
495-523
bool JelloMesh::FloorIntersection(Particle& p, Intersection& intersection)
{

	//p.position[1] is the contact with floor at y axis p.velocity is the velocity of the particle
	vec3 P1= vec3(0.0, 0.0, 0.0); //floor position
	vec3 normal = vec3(0.0, 1.0, 0.0); //normal to the floor
	vec3 V = p.velocity;
	double dot = (V*normal);//according to Piazza guidance
	{
	
		if (p.position[1] > 0.0 || (p.position[1] < 0.0 && dot >= 0.0)) { //logical OR operator (||) returns the boolean value true if either or both operands is true and returns false otherwise
			return false;
		}
	
	if (0 <= p.position[1] && p.position[1]<=0.0) {  //&&) returns the boolean value true if both operands are true and returns false otherwise.
		intersection.m_p = p.index;
		intersection.m_normal = vec3(0.0, 1.0, 0.0);
		intersection.m_distance = (0.0-p.position[1]);
		intersection.m_type = IntersectionType(COLLISION);
		return true;
	
	}

	
	if (p.position[1] < 0.0)
	{
		intersection.m_p = p.index;
		intersection.m_normal = vec3(0.0, 1.0, 0.0);
		intersection.m_distance =  (0.0-p.position[1]);
		intersection.m_type = IntersectionType(CONTACT);
		return true;

    return false;
}
*****
544-669
void JelloMesh::EulerIntegrate(double dt) //y=yi + h(fx)  
{
     TODO

    double halfdt = 0.5 * dt;
    ParticleGrid target = m_vparticles;  // target is a copy!
    ParticleGrid& source = m_vparticles;  // source is a ptr!
	
    // Step 1
    ParticleGrid accum1 = m_vparticles;
    for (int i = 0; i < m_rows+1; i++)
    {
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& s = GetParticle(source, i, j, k);
				Particle& p = GetParticle(m_vparticles, i, j, k);
		
				Particle& k1 = GetParticle(accum1, i, j, k);
				k1.force = halfdt * s.force * 1 / s.mass;
				k1.velocity = halfdt * s.velocity;

				Particle& t = GetParticle(target, i, j, k);
				t.velocity = s.velocity + k1.force;
				t.position = s.position + k1.velocity;
			}
			
			// Put it all together
			double asixth = 1 / 6.0;
			double athird = 1 / 3.0;
		}
    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
                Particle& p = GetParticle(m_vparticles, i,j,k);
                Particle& k1 = GetParticle(accum1, i,j,k);              
                               
				p.velocity = p.velocity + asixth * k1.force;                     

				p.position = p.position + asixth * k1.velocity;
                    
            }
        }
    }
}

void JelloMesh::MidPointIntegrate(double dt)
{
     TODO	
	{
		double halfdt = 0.5 * dt;
		ParticleGrid target = m_vparticles;  // target is a copy!
		ParticleGrid& source = m_vparticles;  // source is a ptr!

	  // Step 1
		ParticleGrid accum1 = m_vparticles;
		for (int i = 0; i < m_rows + 1; i++)
		{
			for (int j = 0; j < m_cols + 1; j++)
			{
				for (int k = 0; k < m_stacks + 1; k++)
				{
					Particle& s = GetParticle(source, i, j, k);
					
					Particle& k1 = GetParticle(accum1, i, j, k);
					k1.force = halfdt * s.force * 1 / s.mass;
					k1.velocity = halfdt * s.velocity;

					Particle& t = GetParticle(target, i, j, k);
					t.velocity = s.velocity + k1.force;
					t.position = s.position + k1.velocity;
				}
			}
		}

		ComputeForces(target);

		// Step 2
		ParticleGrid accum2 = m_vparticles;
		for (int i = 0; i < m_rows + 1; i++)
		{
			for (int j = 0; j < m_cols + 1; j++)
			{
				for (int k = 0; k < m_stacks + 1; k++)
				{
					Particle& t = GetParticle(target, i, j, k);
					Particle& k2 = GetParticle(accum2, i, j, k);

					k2.force = halfdt * t.force * 1 / t.mass;
					k2.velocity = halfdt * t.velocity;

					Particle& s = GetParticle(source, i, j, k);
					t.velocity = s.velocity + k2.force;
					t.position = s.position + k2.velocity;
				}
			}
		}

		// Put it all together
		double asixth = 1 / 6.0;
		double athird = 1 / 3.0;
		for (int i = 0; i < m_rows + 1; i++)
		{
			for (int j = 0; j < m_cols + 1; j++)
			{
				for (int k = 0; k < m_stacks + 1; k++)
				{
					Particle& p = GetParticle(m_vparticles, i, j, k);
					Particle& k1 = GetParticle(accum1, i, j, k);
					Particle& k2 = GetParticle(accum2, i, j, k);
					

					p.velocity = p.velocity + asixth * k1.force +
						athird * k2.force;

					p.position = p.position + asixth * k1.velocity +
						athird * k2.velocity;
				}
			}
		}
	}
}
*********


##Part 3:
#### 1. As Ks gets bigger the bouncer or less ridgid the cube becomes. Kd, the damping force will always oppose the motion.  
Thus if you increase Ks and Kd the cube will not bounce.  Lower Kd and increase Ks for lower stiffness. 

####2. 

####3. Systems that could model mass-spring simulations include animation, video games, fashion (modeling cloth).

####4. My jello does not behave realistically but it could if given the correct code as seen in some of the simulations online.  

The integration method utilized in my homework was RK4.

####5. Simulating water. 


