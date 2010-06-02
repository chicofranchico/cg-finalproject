// End.hpp
// by JuanPi Carbajal carbajal@ifi.uzh.ch

#ifndef END_HPP
#define END_HPP

#include "Particle/pAPI.h"
using namespace PAPI;

#include "GL/glut.h"

//function Prototypes
void ComputeParticles();
void BoxBase();
void BoxBack();
void BoxFront();
void BoxLeft();
void BoxRight();
void DrawGroupAsPoints();
void Draw();
void Reshape(int w, int h);

#endif //END_HPP
