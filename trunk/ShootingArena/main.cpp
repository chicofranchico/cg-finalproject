/*
  Main file modified from the Bullet demo set.
*/

#include "ShootingDemo.h"
#include "GlutStuffs.h"
#include "GLDebugDrawer.h"
#include "btBulletDynamicsCommon.h"


GLDebugDrawer	gDebugDrawer;

int main(int argc,char** argv)
{
				    	
	ShootingDemo* ccdDemo = new ShootingDemo();

	ccdDemo->initPhysics();
	ccdDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);

	glutmain(argc, argv,640,480,"Shooting Arena Demo",ccdDemo);

	delete ccdDemo;
	return 0;
}
