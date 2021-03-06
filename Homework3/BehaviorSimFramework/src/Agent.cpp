// Agent.cpp: implementation of the SIMAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Behavior.h"
#include "Agent.h"
#include <random>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//Construct static variables
//Their real values are set in static function SIMAgent::InitValues()
vector<SIMAgent*> SIMAgent::agents;
bool SIMAgent::debug = false;
float SIMAgent::radius = 20.0;
float SIMAgent::Mass = 1.0;
float SIMAgent::Inertia = 1.0;
float SIMAgent::MaxVelocity = 20.0;
float SIMAgent::MaxForce = 10.0;
float SIMAgent::MaxTorque = 40.0;
float SIMAgent::MaxAngVel = 10.0;
float SIMAgent::Kv0 = 1.0;
float SIMAgent::Kp1 = 1.0;
float SIMAgent::Kv1 = 1.0;
float SIMAgent::KArrival = 1.0;
float SIMAgent::KDeparture = 1.0;
float SIMAgent::KNoise = 1.0;
float SIMAgent::KWander = 1.0;
float SIMAgent::KAvoid = 1.0;
float SIMAgent::TAvoid = 1.0;
float SIMAgent::RNeighborhood = 1.0;
float SIMAgent::KSeparate = 1.0;
float SIMAgent::KAlign = 1.0;
float SIMAgent::KCohesion = 1.0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////////////// 
vec2 SIMAgent::WorldToLocal(vec2 &w)
{
	vec2 l;
	float s = sin(state[1]);
	float c = cos(state[1]);
	l[0] = c * w[0] + s * w[1];
	l[1] = -s * w[0] + c * w[1];
	return l;
}

vec2 SIMAgent::LocalToWorld(vec2 &l)
{
	vec2 w;
	float s = sin(state[1]);
	float c = cos(state[1]);
	w[0] = c * l[0] - s * l[1];
	w[1] = s * l[0] + c * l[1];
	return w;
}

void SIMAgent::SetVTheta(vec2 &V)
{
	vd = V.Length();
	if (vd < 0.0001) {
		thetad = 0.0;
	}
	else {
		if (abs(V[0]) < 0.0001) {
			if (V[1] > 0)
				thetad = M_PI / 2.0;
			else
				thetad = M_PI / -2.0;
		}
		else
			thetad = atan2(V[1], V[0]);
	}

	ClampAngle(thetad);
}

SIMAgent::SIMAgent()
{
}

SIMAgent::~SIMAgent()
{
}

void SIMAgent::Display()
{
	glPushMatrix();
	glTranslatef(GPos[0], rootHeight[frameNum], GPos[1]);
	if (showLeader && this == SIMAgent::agents[0]) {
		float red[] = { 1.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
		glPushMatrix();
		glTranslatef(0.0, 100.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidCone(10.0, 20.0, 24, 24);
		glPopMatrix();
	}

	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	if (SIMAgent::debug) {
		glutSolidSphere(10.0, 24, 24);
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glRotatef(-state[1] / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + state[2], 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glRotatef(-thetad / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + vd, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glLineWidth(1.0);
		glEnable(GL_LIGHTING);
	}
	else {
		glRotatef(90.0f - state[1] * Rad2Deg, 0.0, 1.0, 0.0);
		//glutSolidSphere(6.0f, 12, 12);
		glCallList(AgentDisplay::listNames + frameNum);
	}
	glPopMatrix();
}

void SIMAgent::ClearAgents() {
	for (unsigned int i = 0; i < agents.size(); i++)
		delete SIMAgent::agents[i];
	SIMAgent::agents.clear();
}

SIMAgent::SIMAgent(float* color, CEnvironment* env) {
	memcpy(this->color, color, sizeof(float) * 3);
	dimState = 4;
	dimInput = 2;
	frameNum = rand() % totalFrames;
	this->env = env;
	float angle = float(rand() % 360) / 180.0 * M_PI;
	vWander[0] = cos(angle) * SIMAgent::KWander;
	vWander[1] = sin(angle) * SIMAgent::KWander;
	angle = float(rand() % 360) / 180.0 * M_PI;
	v0[0] = cos(angle) * SIMAgent::MaxVelocity / 2.0;
	v0[1] = sin(angle) * SIMAgent::MaxVelocity / 2.0;
	SIMAgent::agents.push_back(this);
}

void SIMAgent::SetInitState(float pos[], float angle)
{
	int i;
	GPos[0] = pos[0];
	GPos[1] = pos[1];
	for (i = 0; i < dimState; i++) {
		state[i] = 0.0;
	}
	for (i = 0; i < dimInput; i++)
		input[i] = 0.0;
	state[1] = angle;
}

void SIMAgent::Sense(int type)
{
	showLeader = (type == LEADER);
	goal = env->goal;
	switch (type) {
	case SEEK: Seek(); break;
	case FLEE: Flee(); break;
	case ARRIVAL: Arrival(); break;
	case DEPARTURE: Departure(); break;
	case WANDER: Wander(); break;
	case AVOID: Avoid(); break;
	case SEPARATION: Separation(); break;
	case ALIGNMENT: Alignment(); break;
	case COHESION: Cohesion(); break;
	case FLOCKING: Flocking(); break;
	case LEADER: Leader(); break;
	}
}

void SIMAgent::Act(float deltaT)
{
	int dframe;
	this->deltaT = deltaT;
	FindDeriv();
	UpdateState();
	if (abs(state[2]) < 0.001)
		dframe = 0;
	else {
		dframe = int(state[2] / SIMAgent::MaxVelocity * 2 + 1);
	}
	frameNum += dframe;
	if (frameNum >= totalFrames) {
		frameNum = frameNum - totalFrames;
	}
}

void SIMAgent::SetV0()
{
	v0 = env->goal - GPos;
	v0 = v0.Normalize() * SIMAgent::MaxVelocity / 2;
}

/*
Sets the intial Values
*/
void SIMAgent::InitValues()
{
	/*********************************************
	// TODO: Add code here
	Set initial value for control and behavior settings
	You need to find out appropriate values for:
	SIMAgent::Kv0, SIMAgent::Kp1, SIMAgent::Kv1, SIMAgent::KArrival, SIMAgent::KDeparture,
	SIMAgent::KNoise, SIMAgent::KWander, SIMAgent::KAvoid, SIMAgent::TAvoid, SIMAgent::RNeighborhood,
	SIMAgent::KSeparate, SIMAgent::KAlign, SIMAgent::KCohesion.
	*********************************************/
	Kv0 = 10.0;   //used Utube video for these parameters
	Kp1 = -200.0;
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
}

/*
*	You should apply the control rules given desired velocity vd and desired orientation thetad.
*/
void SIMAgent::Control()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	/* This is from Dr. Kider Piazza post 
	* You should apply the control rules given desired velocity vd and desired orientation thetad.
	* Velocity control: input[0] = f = m * Kv0 * (vd - v)
	* Heading control: input[1] = tau = I * ( -Kv1 * thetaDot - Kp1 * theta + Kp1 * thetad)
	* This function sets input[0] and input[1] appropriately after being called.
	*/

		Truncate(vd, -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);
		input[0] = SIMAgent::Mass * SIMAgent::Kv0 * (vd - state[2]);
		Truncate(input[0], -SIMAgent::MaxForce, SIMAgent::MaxForce);

		double dangle = AngleDiff(state[1], thetad);
		input[1] = SIMAgent::Inertia * (Kp1 * dangle - Kv1 * state[3]);
		Truncate(input[1], -SIMAgent::MaxTorque, SIMAgent::MaxTorque);
	}


		

/*
*	Compute derivative vector given input and state vectors
*  This function sets derive vector to appropriate values after being called
*/

void SIMAgent::FindDeriv()
{
	/*********************************************
	// TODO: Add code here   help from Julie in Class
	*********************************************/
	deriv[0] = state[2];  
	deriv[1] = state[3];  //1st dervivative is velocity
	deriv[2] = input[0] / Mass;
	/*deriv[3] = input[1] / Inertia;*/
	/*deriv[0] = 0;*/
	deriv[3] = input[1] / Inertia - state[3];
	/*deriv[0] = input[0] / Mass;  //this makes the agent twitch
	deriv[1] = input[1] / Inertia;
	deriv[2] = state[2];  //deriv[2] is velocity per notes but this group does not work
	deriv[3] = state[3];*/
}

/*
*	Update the state vector given derivative vector
*  Compute global position and store it in GPos
*  Perform validation check to make sure all values are within MAX values
*/
//void SIMAgent::UpdateState()
//{
	/*********************************************
	// TODO: Add code here  given on Piazza
	*********************************************/

void SIMAgent::UpdateState()
{
	for (int i = 0; i < dimState; i++) {
		state[i] += deriv[i] * deltaT;
	}
	state[0] = 0.0;

	ClampAngle(state[1]);
	Truncate(state[2], -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);

	vec2 GVelocity;
	GVelocity[0] = state[2] * cos(state[1]);
	GVelocity[1] = state[2] * sin(state[1]);
	GPos += GVelocity;

	Truncate(GPos[0], -1.0 * env->groundSize, env->groundSize);
	Truncate(GPos[1], -1.0 * env->groundSize, env->groundSize);

	Truncate(state[3], -SIMAgent::MaxAngVel, SIMAgent::MaxAngVel);

}
//}

/*
*	Seek behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Seek()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	/*goal = env->goal
		v0 = env->goal - GPos;
	v0 = v0.Normalize() * SIMAgent::MaxVelocity / 2;*/
	
	vec2 tmp;
	tmp = goal - GPos;
	tmp.Normalize();
	/*thetad = atan2(tmp[0], tmp[1]);*/
	thetad = atan2(tmp[1], tmp[0]);
	//thetad = thetad + M_PI; 
	/*ClampAngle(thetad);*/
	vd = SIMAgent::MaxVelocity;
	tmp = vec2((cos(thetad)*vd), (sin(thetad)*vd));
	return tmp;
}

/*
*	Flee behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Flee()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;
	//tmp = goal - GPos;
	tmp = GPos - goal; //fleeing is the difference between the particle position and the target
	tmp.Normalize();
	thetad = atan2(tmp[0], tmp[1]);
	//thetad = atan2(tmp[1], tmp[0]);
	thetad = thetad + M_PI;
	/*ClampAngle(thetad);*/
	float vn = SIMAgent::MaxVelocity;
	tmp = vec2((cos(thetad)*vn), (sin(thetad)*vn));
	return tmp;
}

/*
*	Arrival behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  Arrival setting is in SIMAgent::KArrival
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Arrival()
{
	/*********************************************
	// TODO: Add code here   this is a combo of webcourse information and my class notes
	*********************************************/
	vec2 tmp;
	vec2 Xd= goal - GPos; //desired position
	double Y = Xd.Length(); //desired position 
	vd = Xd.Length() * KArrival;  //desired velocity is desired position multiply by the speed of the object
	thetad = atan2(Xd[1], Xd[0]); //thetad is my angle
	//thetad += M_PI;
	if (Y > 0.0) // if my desired position is greater than zero then 
	{
		return vec2((cos(thetad)*vd), (sin(thetad)*vd));
	}
	float M = SIMAgent::KArrival;   //KArrival is my speed 
	float vn = (M * vd / radius);  //speed x desired velocity/ radius
	return vec2((cos(thetad)*vn), (sin(thetad)*vn));
	return tmp;
}

/*
*	Departure behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  Departure setting is in KDeparture
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Departure()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;
	vec2 Xd = goal - GPos;
	double Y = Xd.Length();
	vd = Xd.Length() * KDeparture;
	thetad = atan2(Xd[1], Xd[0]);
	thetad += M_PI;
	if (Y > 0.0)
	{
		return vec2((cos(thetad)*vd), (sin(thetad)*vd));
	}
	float M = SIMAgent::KDeparture;
	float vn = (M * vd / radius);
	return vec2((cos(thetad)*vn), (sin(thetad)*vn));
	return tmp;
}

/*
*	Wander behavior
*  VWander is in vWander
*  V0(nominal velocity) is in v0
*  Wander setting is in KWander
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Wander()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	//wander add a random number using rand command  http://tigerprints.clemson.edu/cgi/viewcontent.cgi?article=1956&context=all_theses
	
	vec2 tmp;
	//std::random_device rd;  //discrete 2 hw
	//std::mt19937_64 engine(rd()); //discrete 2 hw for random variables
	//std::uniform_real_distribution<double> dist(0, M_PI);  // example of a uniform distribution
	//thetad = atan2(Xv[1], Xv[0]);  
	float angle = float(rand() % 360) / 180.0 * M_PI; //from the code at the top
	angle = float(rand() % 360) / 180.0 * M_PI; //from the code at the top
	vd= SIMAgent::MaxVelocity;
	thetad = angle;
	tmp = vec2(vd*cos(thetad)*KNoise, vd*sin(thetad)*KNoise)*KWander; //webcourse multiply vectors by KNoise and KWander
	return tmp;
}

/*
*	Avoid behavior
*  Obstacles are in env->obstacles
*  Number of obstacles is env->obstaclesNum
*  env->obstacles[i][0] and env->obstacles[i][1] are the global position of the ith obstacle
*  env->obstacles[i][2] is the radius of the ith obstacle
*  Agent bounding sphere radius is in SIMAgent::radius
*  Avoidance settings are in SIMAgent::TAvoid and SIMAgent::KAvoid
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Avoid()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	//avoid needs the dot product of a vector and it normal vector at point of intersection
	//float Vector3f::Dot(const Vector3f &b) { dot product from earlier lecture
	//+return X * b.X + Y * b.Y + Z * b.Z;
	vec2 tmp;
	//vec2 Xd = goal - GPos; //desired position
	//double Y = Xd.Length(); //desired position 
	//vd = Xd.Length() * KArrival;  //desired velocity is desired position multiply by the speed of the object
	//thetad = atan2(Xd[1], Xd[0]); //thetad is my angle
	//thetad += M_PI /2;
	//for (int i = 0; i< env->obstaclesNum; i++) //obstaclesNum is the number of obstacles given above
	//{
		
	
	return tmp;
}

/*
*  Separation behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Separation settings are in SIMAgent::RNeighborhood and SIMAgent::KSeperate
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Separation()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;
	//tmp = goal - GPos;
	//float i; 
	//SIMAgent::agents[i];
	//SIMAgent::agents.size();   //will tell you how many agents are currently in the system. Webcourse
	//SIMAgent * tmp = SIMAgent::agents[i];   //calls an agent that is a local agent. Webcourse
	vec2 S = vec2(0.0, 0.0); //start position vector
	for (int i = 0; i< agents.size(); i++)
	{
		vec2 dist = GPos - agents[i]->GPos; //compute a vector for each neighbor by subtracting position from current position
		int distx = dist[0];
		int disty = dist[1];
		if (distx == 0 && disty == 0)
		{
			continue;
		}
		double neighbors = sqrt(distx*distx + disty*disty); //calculate length of the neighbors vector
		vec2 Distance = vec2(distx, disty);
		if (neighbors < RNeighborhood);
		{
			S[0] = S[0] + (distx/(neighbors*neighbors)); //finding the closest neighbor on the x plane
			S[1] = S[1] + (disty/(neighbors*neighbors)); //finding the closest neighbor on the  y plan
			
		}
	}
	vec2 newbie = KSeparate * S;  //newbie is the desired velocity vector
	newbie.Normalize();
	vd = sqrt((newbie[0] * newbie[0] + (newbie[1] * newbie[1])));//length of the newbie vector
	thetad = atan2(newbie[1], newbie[0]);
	thetad = thetad + M_PI;
	tmp = vec2(cos(thetad)*vd, sin(thetad)*vd);
	return tmp;
}
	

/*
*	Alignment behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Alignment settings are in SIMAgent::RNeighborhood and SIMAgent::KAlign
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Alignment()
{
	/*********************************************
	// TODO: Add code here  do alignment first, then cohesion and separation is a simple change in code https://gamedevelopment.tutsplus.com/tutorials/3-simple-rules-of-flocking-behaviors-alignment-cohesion-and-separation--gamedev-3444
	*********************************************/
	//alignment causes the agent to line up with the closest agent nearby
	vec2 tmp;
	//SIMAgent::agents[i];
	//vec2 A = Arrival();
	vec2 A = vec2(0.0, 0.0);
	int agents_number = 0;
	for (int i = 0; i< agents.size(); i++)
	{
		//vec2 dist = GPos - agents[i]->GPos;  //dist is the goal position minus the position of the agent
		vec2 dist = agents[i]->GPos - GPos;
		int distx = dist[0];
		int disty = dist[1];
		//double neighbors = dist.Length();
		//if (distx == 0 && disty == 0)
			if (dist.Length() < RNeighborhood);
			{
				A[0] = A[0] + cos(agents[i]->state[1] * agents[i]->state[2]);
				A[1] = A[1] + cos(agents[i]->state[1] * agents[i]->state[2]);
				agents_number++;
			}
		{
		}
		//double neighbors = sqrt(distx*distx + disty*disty); //calculate length of the vector
		//if (neighbors < KAlign);
		{
			/*A[0] = A[0] + cos(agents[i]->state[1] * agents[i]->state[2]);
			A[1] = A[1] + cos(agents[i]->state[1] * agents[i]->state[2]);
			agents_number++;*/
		}
	}
	//vec2 newbie = KAlign / agents_number*A;
	vec2 newbie = A /agents_number;
	newbie.Normalize();
	//vd = sqrt((newbie[0] * newbie[0] + (newbie[1] * newbie[1]))); //length of vector
	vd = newbie.Length() * KArrival;
	Truncate(vd, 0, MaxVelocity);
	thetad = atan2(newbie[1], newbie[0]);
	tmp = vec2(cos(thetad)*vd, sin(thetad)*vd);
	//tmp = newbie;
	return tmp;
}

/*
*	Cohesion behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Cohesion settings are in SIMAgent::RNeighborhood and SIMAgent::KCohesion
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Cohesion()
{
	/*********************************************
	// TODO: Add code here  Cohesion goes towards the Center of Mass of the immediate neighbor and change in velocity to position
	*********************************************/
	vec2 tmp;
	////SIMAgent::agents[i];
	vec2 S = vec2(0.0, 0.0); //steering force
	//vec2 C = vec2(0.0, 0.0); //center of mass
	float agents_number = 0;  //number of agents
	//for (int i = 0; i < agents.size; i++);
	//{
	//	vec2 dist = GPos - (SIMAgent::agents[i]->GPos); //all the neighbors of the current particle
	//	int distx = dist[0];
	//	int disty = dist[1];
	//	float neighbors = sqrt(distx*distx + disty*disty); //calculate length of the vector
	//	if (neighbors < RNeighborhood);
	//	{
	//		S[0] = S[0] + agents[i]->GPos[0];   //sum all the positions of the neighbors on the x
	//		S[1] = S[1] + agents[i]->GPos[0]; //sum all the positions of the neighbors on the y
	//		agents_number = agents_number + 1;   //sum all the neighbors add 1 to repeat
	//	}
	//}
	vec2 Xm = S / agents_number;
	//Xm.Normalize();
	tmp = goal - GPos;  //Webcourse states Cohesion similar to Goal seeking.  
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	thetad = thetad + M_PI;
	vd = SIMAgent::KCohesion;
	vec2 VCoh = KCohesion *(Xm - GPos);
	vd = sqrt((VCoh[0] * VCoh[0] + (VCoh[1] * VCoh[1])));
	//thetad = atan2(VCoh[1], VCoh[0]);
	tmp = vec2(cos(thetad)*vd, sin(thetad)*vd);
	
	return tmp;
}

/*
*	Flocking behavior
*  Utilize the Separation, Cohesion and Alignment behaviors to determine the desired velocity vector
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Flocking()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;
	vec2 separation = Separation();
	vec2 cohesion = Cohesion();
	vec2 align = Alignment();

	vec2 flocking = (separation * KSeparate) + (cohesion * KCohesion) + (align * KAlign); //webcourse
	//vec2 flocking = SIMAgent::KSeparate + SIMAgent::KCohesion + SIMAgent::KAlign;
	
	return tmp;
}

/*
*  Flocking behavior
*  Utilize the Separation, Arrival behaviors to determine the desired velocity vector
*  You need to find the leader, who is always the first agent in SIMAgent::agents
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Leader()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;
	vec2 separation = Separation();
	vec2 arrival = Arrival();
	vec2 leader = (separation * KSeparate) + (arrival * KArrival); //webcourse
	return tmp;
}