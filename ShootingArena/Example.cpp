// Example.cpp - An example of the Particle System API in OpenGL.
//
// Copyright 1999-2006 by David K. McAllister

#include "../End/Particle/pAPI.h"
using namespace PAPI;

#include "GL/glut.h"

ParticleContext_t P;

// A fountain spraying up in the middle of the screen
void ComputeParticles()
{
    //P.TimeStep(1/2.0);P.StartingAge();ResetSourceState()

    // Set up the state.
    P.Velocity(PDCylinder(pVec(0.0f , 0.0f, 0.05f), pVec(0.0f , 0.0f, 0.08f), 0.02f, 0.02f));
    //P.Velocity(PDLine(pVec(0.0f, 0.0f, 0.0f), pVec(0.0f, 0.0f, 2.0f)));
    P.Color(PDLine(pVec(0.0f, 1.0f, 0.0f), pVec(0.0f, 1.0f, 1.0f)), PDPoint(pVec(0.5f)));
     P.Size(10.0);
	
	
    // Generate particles along a very small line in the nozzle.
    P.Source(100, PDLine(pVec(0.0, 0, 0.0f), pVec(0.0, 0, 4.4f)));
	
	//P.TimeStep(1/2.0);
	P.Source(100, PDLine(pVec(2.0, 0, 0.0f), pVec(2.0, 0, 4.4f)));
	P.Source(100, PDLine(pVec(-2.0, 0, 0.0f), pVec(-2.0, 0, 4.4f)));

    // Kill particles below Z=-3.
    //P.Sink(true, PDPlane(pVec(0,0,3), pVec(0,0,10)));

    

    P.Velocity(PDSphere(pVec(0.0f , 0.0f, 0.0f), 0.01f, 0.01f));
    P.Color(PDLine(pVec(0.0f, 0.0f, 0.0f), pVec(0.0f, 0.0f, 1.0f)), PDPoint(pVec(0.5f)));
    P.Source(100, PDSphere(pVec(2.0f,6.0f, 1.0f), 0.005f, 0.005f));
    P.Sink(true, PDSphere(pVec(2.0f,6.0f, 1.0f),2.0,1.5));

    P.Velocity(PDSphere(pVec(0.0f , 0.0f, 0.0f), 0.01f, 0.01f));
    P.Color(PDLine(pVec(1.0f, 0.0f, 0.0f), pVec(1.0f, 1.0f, 0.0f)), PDPoint(pVec(0.5f)));
    P.Source(100, PDSphere(pVec(-2.0f,6.0f, 1.0f), 0.005f, 0.005f));
    P.Sink(true, PDSphere(pVec(-2.0f,6.0f, 1.0f),2.0,1.5));

    P.Velocity(PDSphere(pVec(0.0f , 0.0f, 0.0f), 0.01f, 0.01f));
    P.Color(PDLine(pVec(1.0f, 0.0f, 0.0f), pVec(0.0f, 1.0f, 0.0f)), PDPoint(pVec(0.5f)));
    P.Source(100, PDSphere(pVec(5.0f,10.0f, 2.0f), 0.005f, 0.005f));
    P.Sink(true, PDSphere(pVec(5.0f,10.0f, 2.0f),2.0,1.5));

    P.Velocity(PDSphere(pVec(0.0f , 0.0f, 0.0f), 0.01f, 0.01f));
    P.Color(PDLine(pVec(1.0f, 0.0f, 0.0f), pVec(1.0f, 0.0f, 0.0f)), PDPoint(pVec(0.5f)));
    P.Source(100, PDSphere(pVec(-5.0f,10.0f, 2.0f), 0.005f, 0.005f));
    P.Sink(true, PDSphere(pVec(-5.0f,10.0f, 2.0f),2.0,1.5));
// Move particles to their new positions.
    P.Move(true, false);    
    
}
void BoxBase()
{
        glBegin(GL_QUADS);
        glColor3ub(0, 5, 140);
        glVertex3f(-0.5,-1.0,0);
        glColor3ub(0, 5, 140);
        glVertex3f(-0.5,1.0,0);
        glColor3ub(0, 5, 140);
        glVertex3f(0.5,1.0,0);
        glColor3ub(0, 5, 140);
        glVertex3f(0.5,-1.0,0);
        glEnd(); 
}
void BoxBack()
{
	glBegin(GL_QUADS);
        glColor3ub(0, 5, 140);
        glVertex3f(-0.5,1.0,0);
        glColor3ub(0, 115, 0);
        glVertex3f(-0.5,1.0,1.0);
        glColor3ub(0, 115, 0);
        glVertex3f(0.5,1.0,1.0);
        glColor3ub(0, 5, 140);
        glVertex3f(0.5,1.0,0);
        glEnd();
}
void BoxFront()
{
	glBegin(GL_QUADS);
        glColor3ub(0, 5, 140);
        glVertex3f(-0.5,-1.0,0);
        glColor3ub(0, 115, 0);
        glVertex3f(-0.5,-1.0,1.0);
        glColor3ub(0, 115, 0);
        glVertex3f(0.5,-1.0,1.0);
        glColor3ub(0, 5, 140);
        glVertex3f(0.5,-1.0,0);
        glEnd();
}
void BoxLeft()
{
        glBegin(GL_QUADS);
        glColor3ub(0, 5, 140);
        glVertex3f(-0.5,-1.0,0);
        glColor3ub(0, 115, 0);
        glVertex3f(-0.5,-1.0,1.0);
        glColor3ub(0, 115, 0);
        glVertex3f(-0.5,1.0,1.0);
        glColor3ub(0, 5, 140);
        glVertex3f(-0.5,1.0,0);
        glEnd();
}
void BoxRight()
{
	glBegin(GL_QUADS);
        glColor3ub(0, 5, 140);
        glVertex3f(0.5,-1.0,0);
        glColor3ub(0, 115, 0);
        glVertex3f(0.5,-1.0,1.0);
        glColor3ub(0, 115, 0);
        glVertex3f(0.5,1.0,1.0);
        glColor3ub(0, 5, 140);
        glVertex3f(0.5,1.0,0);
        glEnd();
}

// Draw as points using vertex arrays
// To draw as textured point sprites just call
// glEnable(GL_POINT_SPRITE_ARB) before calling this function.
void DrawGroupAsPoints()
{
    size_t cnt = P.GetGroupCount();
    if(cnt < 1) return;

    float *ptr;
    size_t flstride, pos3Ofs, posB3Ofs, size3Ofs, vel3Ofs, velB3Ofs, color3Ofs, alpha1Ofs, age1Ofs, up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs;

    cnt = P.GetParticlePointer(ptr, flstride, pos3Ofs, posB3Ofs,
        size3Ofs, vel3Ofs, velB3Ofs, color3Ofs, alpha1Ofs, age1Ofs,
        up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs);
    if(cnt < 1) return;

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, int(flstride) * sizeof(float), ptr + color3Ofs);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, int(flstride) * sizeof(float), ptr + pos3Ofs);

    glDrawArrays(GL_POINTS, 0, (GLsizei)cnt);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the view.
    glLoadIdentity();
    gluLookAt(0, -8, 3, 0, 0, 0, 0, 0, 1);

    glEnable(GL_LIGHTING);

	float noAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        float blueDiffuse[] = {0.0f, 0.0f, 1.0f, 1.0f};
	float blueSpecular[] = {0.0f, 0.0f, 1.0f, 1.0f};

	float position_d[] = {0.0f, -4.0f, -4.0f, 0.0f};
	
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, position_d);
	glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, blueDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, blueSpecular);

	glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);    
        glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);    
        glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0 );

	float yellowAmbientDiffuse[] = {1.0f, 1.0f, 0.0f, 1.0f};
     
        float position_pos[] = {0.0f, 4.0f, 0.0f, 1.0f};
        
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, position_pos);
        glLightfv(GL_LIGHT1, GL_AMBIENT, yellowAmbientDiffuse);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowAmbientDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, yellowAmbientDiffuse);
        
	glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
        glEnable ( GL_COLOR_MATERIAL ) ;

	glShadeModel(GL_SMOOTH);
        
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
        
 	BoxBase();
        BoxBack();
	BoxFront();
        BoxLeft();
	BoxRight();

	glTranslatef(-2.0,0.0,0.0);
        BoxBase();
        BoxBack();
	BoxFront();
        BoxLeft();
	BoxRight();

	glTranslatef(4.0,0.0,0.0);
        BoxBase();
        BoxBack();
	BoxFront();
        BoxLeft();
	BoxRight();
	glPopMatrix();

	char *string = "GAME OVER!!!";
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	char *c;
	glRasterPos3f(-0.9, -1.0, -0.5);
	for (c=string; *c != '\0'; c++)
	{
	glutBitmapCharacter(font, *c);
	}
	string = "Please reopen the application to play again!!!";
	glRasterPos3f(-2.5, -1.0, -1.0);
	for (c=string; *c != '\0'; c++)
	{
	glutBitmapCharacter(font, *c);
	}

        glEnable(GL_FOG);
	float FogCol[3]={0.8f,0.8f,0.8f}; // Define a nice light grey
 	glFogfv(GL_FOG_COLOR,FogCol);
	glFogi(GL_FOG_MODE, GL_LINEAR); 
	glFogf (GL_FOG_DENSITY, 0.35);
        glHint (GL_FOG_HINT, GL_DONT_CARE);
  	glFogf(GL_FOG_START, 4.0f);
  	glFogf(GL_FOG_END, 20.f);
      
        glClearColor(0.6, 0.6, 0.6, 1.0);
	glDisable(GL_LIGHTING);


    // Do what the particles do.
    ComputeParticles();

    // Draw the particles.
    DrawGroupAsPoints();

    glutSwapBuffers();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, w / double(h), 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main1(int argc, char **argv)
{
    // Initialize GLUT.
    glutInit(&argc, argv);

    // Make a normal 3D window.
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Particle Example");

    glutDisplayFunc(Draw);
    glutIdleFunc(Draw);
    glutReshapeFunc(Reshape);

    // We want depth buffering, etc.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Make a particle group
    int particle_handle = P.GenParticleGroups(1, 10000);

    P.CurrentGroup(particle_handle);

    try {
        glutMainLoop();
    }
    catch (PError_t &Er) {
        std::cerr << "Particle API exception: " << Er.ErrMsg << std::endl;
        throw Er;
    }

    return 0;
}
