# Jack Purkiss Inextensible Cloth Simulator Project

## Overview

For my assignment I will create a program that demonstrates an inextensible cloth simulator 

I am currently writing up some notes on the area to gain an understanding for where to start in the area. 

It will be using a Position-based Dynamics system, where the behaviour of the cloth mesh is determined by a set of particles that have various constraints connecting them. [This video](https://www.youtube.com/watch?v=z5oWopN39OU&ab_channel=TenMinutePhysics) looks at zero compliance distance constraints, which takes in a bending resitance parameter handling a constraint between two neighbouring triangles. He discusses two approaches to this, being an additional distance constraint between opposing particles, or the angle between triangles. These two approaches will be explored in this project.
