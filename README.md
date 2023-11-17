# Jack Purkiss Position Based Dynamics Cloth Simulator Project

## Overview

For my assignment I will create a program that demonstrates a cloth simulator built with Position Based Dynamics.

It will be using a Position-based Dynamics system, where the behaviour of the cloth mesh is determined by a set of particles that have various constraints connecting them. 
[This video](https://www.youtube.com/watch?v=z5oWopN39OU&ab_channel=TenMinutePhysics) looks at zero compliance distance constraints, which takes in a bending resitance parameter handling a constraint between two neighbouring triangles. 
He discusses two approaches to this, being an additional distance constraint between opposing particles, or the angle between triangles. 
These two approaches will be explored in this project.

For the data, a mesh will be created to represent the cloth, which will be made up of vertices stored as Particle objects. These vertices connect to form a triangulated mesh. 
A particle is constructed with a position vector and is assigned a mass, which is set to the [sum of one third of the mass of each adjacent triangle](https://www.cs.toronto.edu/~jacobson/seminar/mueller-et-al-2007.pdf). 
A stretching constraint is solved with a constrain function and a stiffness. A bending constraint is also calculated between each pair of adjacent triangles. 
Other constraints to be factored are pin constraints, which control which vertices are pinned in space and collision constraints which factor collision geometry with rigid objects. 
Also, external forces such as gravity and wind must be factored. This is a real time simulation, so the time step will be taking place in real time.
