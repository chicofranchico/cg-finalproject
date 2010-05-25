/**
 * scene.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "scene.hpp"

// Includes
#include "window.hpp"
#include "positionalLight.hpp"
#include "directionalLight.hpp"
#include "spotLight.hpp"
#include "camera2D.hpp"
#include "utils.hpp"
#include "text.hpp"
#include "screenTexture.hpp"
#include "monitor.hpp"
#include "stage.hpp"

//#include "soundClass2.hpp"

/*
#include <sstream>
#include <iostream>
#include <cstdlib>
*/

#include <iostream>

GRAPHICSLAB_NAMESPACE_BEGIN


Scene::Scene( Window &window ) : 
    KeyboardEventHandler(),
    MouseEventHandler(),
    _window( window ),
	_cameraMode( SCENE_VIEW ),
    _camera3D( NULL ),
    _camera2D( NULL ),
	_stage( NULL ),
    _tracking( false ),
	_zooming( false ),
	_moving( false ),
	_theta(0.0),
	sinusY(0.0),
	growth(5.0),
	temp(0.0),
	selector(0.0)/*,
	_sounder(NULL)*/
{
}

Scene::~Scene()
{
	delete _stage;
    delete _camera2D;
    delete _camera3D;

    //delete _sounder;
}

void Scene::updateLookAtData()
{
	Point position;
	_cameraPosition.getCartesianPoint( position );

	Camera::LookAtData lookAtData( 
		Point( _cameraCenter.x + position.x, _cameraCenter.y + position.y, _cameraCenter.z + position.z ), 
		Point( _cameraCenter ), 
        vec3f( 0.0, 1.0, 0.0 ) );

	_camera3D->setLookAtData( lookAtData );
}

void Scene::initialize()
{
    

    _viewport = Camera::Viewport( _window.getApplicationParameters().getWidth(), _window.getApplicationParameters().getHeight() );
    
    _camera3D = new Camera3D( *this );
    _camera3D->setViewport( _viewport );    
    _frustum = Camera3D::Frustum( 100, _viewport.width*1.0/_viewport.height, 1.0, 100.0 );
	//_frustum = Camera3D::Frustum( 60.0f, 1.0, 1.0, 400.0 );
	
    _camera3D->setFrustum( _frustum );

    _cameraPosition = SphericalCoordinates( 30, 0.0, -76.9476 );
	//_cameraPosition = SphericalCoordinates( 4.0, 0.0, 0.0 );
	//_cameraPosition = SphericalCoordinates( 15.0, 0.0, 0.0 );

    //_cameraCenter = Point( -31.5, 5.0, 1.0 );
	//_cameraCenter = Point( 0.0, 0.0, -150.0 );
	//_cameraCenter = Point( 10.0f, 15.0f, 20.0f );
    _cameraCenter = Point( 0.0, 5.0, 1.0 );

	updateLookAtData();

	// Initialize data
	_stage = new Stage( *this );
	
    // Initialize OpenGL
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glClearDepth( 1.0 );

    t3dInit();

    sphereY = 2.0;

    musicOn = false;

    //_sounder = new SceneSoundClass();

    //sounder = new SceneSoundClass();

    //_sound = new SceneSoundClass();

    //_sounder->playSound(BOOM);


}


void Scene::resize( int width, int height )
{
    _viewport = Camera::Viewport( width, height );
    
	
    _camera3D->setViewport( _viewport );
    _frustum.aspect = width*1.0/height;
    _camera3D->setFrustum( _frustum );

	_stage->resize( width, height );
}

void Scene::draw()
{
     
    // Clear the screen
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    // Set up scene camera
	_camera3D->applyViewport();
	_camera3D->applyProjection();
	_camera3D->applyModelview();

	//menu selector: a simple sphere
	if ( sphereY == 2.0 && selector == 0 )
	{
		glPushMatrix();
			glColor3f(1.0f, 0.0, 0.0);
			glTranslatef(-16, sphereY, -4.0);
			glutSolidSphere(0.7, 30, 30);
		glPopMatrix();

	}
	else if ( sphereY == -1.0 && selector == 0 )
	{

		glPushMatrix();
			glColor3f(1.0f, 0.0, 0.0);
			glTranslatef(-16, sphereY, -4.0);
			glutSolidSphere(0.7, 30, 30);
		glPopMatrix();

	}
	else if ( sphereY == -4.0 && selector == 0 )
	{

		glPushMatrix();
			glColor3f(1.0f, 0.0, 0.0);
			glTranslatef(-16, sphereY, -4.0);
			glutSolidSphere(0.7, 30, 30);
		glPopMatrix();

	}

	////////////////////////////
	////// WELCOME SCREEN //////
	////////////////////////////
	if ( selector == 0 )
	{

		_cameraPosition = SphericalCoordinates( 10, 0.0, 0.0 );
		_cameraCenter = Point( 0.0, 0.0, 0.0 );

		updateLookAtData();

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

	    glDisable(GL_TEXTURE_GEN_S);
	    glDisable(GL_TEXTURE_GEN_T);
	    glDisable(GL_TEXTURE_GEN_R);

	    glDisable(GL_TEXTURE_CUBE_MAP_EXT);

	    glEnable(GL_DEPTH_TEST);

		//renormalize stuff
		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);

		//sweet 3d text
		DrawTitle();

		//menu text
		DrawMenuText();

		if (!musicOn)
		{
			musicOn = true;
			_stage->sounder->playSound(BOOM);
		}

	}
	//////////////////////////////////
	////// CINEMATIC PLAY SETUP //////
	//////////////////////////////////
	else if ( selector == 1 )
	{
		_cameraPosition = SphericalCoordinates( 30, 0.0, -76.9476 );
		_cameraCenter = Point( -1.0, 5.0, 1.0 );

		updateLookAtData();

		_stage->setupCubeWorld( );

		//_stage->setupSound(false);
		_stage->startSceneSound();
		_stage->sounder->stopSound(BOOM);

		_stage->draw( _renderParameters );

		selector = 2;

	}
	////////////////////////////
	////// CINEMATIC PLAY //////
	////////////////////////////
	else if ( selector == 2 )
	{
		//draw scene
		_stage->draw( _renderParameters );

		growth += 0.17;

		//sinus function simulating step
		sinusY = 4.5 + (sin(growth))/6;

		if(_theta < 4.5)
		{
			Camera::LookAtData lookAtData(
					Point( -31.5 + _theta*_theta, sinusY, _cameraCenter.z + _theta ),
					Point( _cameraCenter ),
					vec3f( 0.0, 1.0, 0.0 ) );

			_camera3D->setLookAtData( lookAtData );
			_theta+= 0.04;

			if (_theta > 4.5)
				temp = -31.5 + _theta*_theta;

		}
		//approach end
		else if ( _theta < 5.0 )
		{

			Camera::LookAtData lookAtData(
							Point( temp, _cameraCenter.y, _cameraCenter.z + _theta/_theta ),
							Point( _cameraCenter ),
							vec3f( 0.0, 1.0, 0.0 ) );

			_camera3D->setLookAtData( lookAtData );
			_theta+= 0.04;

			if (_theta > 4.9 )
				_stage->sounder->stopSound(WALK);

		}
		//move head to the left to see the arena
		else
		{
			Point position ( temp, _cameraCenter.y, _cameraCenter.z + _theta/_theta );

			Point center ( _cameraCenter.x, _cameraCenter.y, _cameraCenter.z );

			SphericalCoordinates s;

			//s.getCartesianPoint(p);
			s.set(position, center);

			//std::cout << s.radius << " " << s.elevation << " " << s.azimuth << std::endl;

			_cameraCenter = Point( temp, 5.0, 1.0 );
			_cameraPosition = SphericalCoordinates(s.radius, 0, -76.9476 + (_theta - 5.0) );

			_theta += 0.01;

			updateLookAtData();

		}
	}
	else if ( selector == 3 )
	{

		_stage->sounder->stopSound(BOOM);
		_stage->stopAllSound();

		system("/home/chico/cg-finalproject/ShootingArena/AppShootingDemo");

		_stage->setupSound();
		_stage->sounder->playSound(BOOM);

		selector = 0;

	}
	else if ( selector == 4 )
	{
		_stage->sounder->stopSound(BOOM);
		_stage->stopAllSound();

		system("/home/chico/cg-finalproject/Particle221Src/Particle2/Example/example");

		_stage->setupSound();
		_stage->sounder->playSound(BOOM);

		selector = 0;

	}
 
	// Switch to the newly drawn screen buffer
    glutSwapBuffers();

}

void Scene::DrawMenuText( )
{

	glColor3f(1.0,1.0,1.0);

	const char* SCENE_PLAY[14] = { "S", "C", "E", "N", "E", " ", "A", "N", "D", " ", "P", "L", "A", "Y"};
	const char* PLAY[4] = { "P", "L", "A", "Y"};
	const char* GAME_OVER[9] = { "G", "A", "M", "E", " ", "O", "V", "E", "R"};

	float space = 0.0;

	for ( int i = 0; i < 14; i++ )
	{

		glPushMatrix();
			//glRotatef(90 * i, 0, 1, 0);
			glTranslatef(-12 + space, 2.0, -4.0);
			t3dDraw3D(SCENE_PLAY[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 1.125;

	}

	space = 0.0;

	for ( int i = 0; i < 4; i++ )
	{

		glPushMatrix();
			//glRotatef(90 * i, 0, 1, 0);
			glTranslatef(-12 + space, -1.0, -4.0);
			t3dDraw3D(PLAY[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 1.125;

	}

	space = 0.0;

	for ( int i = 0; i < 9; i++ )
	{

		glPushMatrix();
			//glRotatef(90 * i, 0, 1, 0);
			glTranslatef(-12 + space, -4.0, -4.0);
			t3dDraw3D(GAME_OVER[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 1.125;

	}



}

void Scene::DrawTitle( )
{
	const char* ARENA[5] = { "A", "R", "E", "N", "A" };
	const char* BOOM_BOOM[11] = { "B", "O", "O", "M", "!", " ", "B", "O", "O", "M", "!" };
	const char* BOOM2[9] = { "B", "O", "O", "O", "O", "M", "M", "M", "!" };

	float space = 0.0;


	for ( int i = 0; i < 11; i++ )
	{

		glColor3f( 1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX) );

		glPushMatrix();
			glTranslatef(-17 + space, 9.0, -4.0);
			glScalef(1.5,1.5,1.5);
			t3dDraw3D(BOOM_BOOM[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 2.0;

	}

	space = 0.0;

	for ( int i = 0; i < 9; i++ )
	{
		glColor3f( 1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX) );
		glPushMatrix();
			glTranslatef(-17 + space, 7.0, -4.0);
			glScalef(1.5,1.5,1.5);
			t3dDraw3D(BOOM2[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 2;

	}

	space = 0.0;
	glColor3f(1.0,0.0,0.0);

	for ( int i = 0; i < 5; i++ )
	{

		glPushMatrix();

			glTranslatef(7.0 + space , 9.5 - space, -4.0);
			glRotatef(-45, 0, 0, 1);
			glScalef(1.5,1.5,1.5);
			t3dDraw3D(ARENA[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 0.8;

	}

}

void Scene::reset()
{
    //// EXERCISE 06 : Reset data to initial values
    // Write code here to reset data like renderParameters, etc to initial values.
    // Reset all data that can be changed over time with key press or mouse click.

	//reset parameters
	_renderParameters.drawMode = RenderParameters::POLYGON;
	_renderParameters.smoothShading = true;

	//reset camera
	_cameraMode 	= SCENE_VIEW;
	_cameraCenter 	= Point ( 0, 0, 0 );
	_cameraPosition = SphericalCoordinates ( 10, 0, 0 );
	updateLookAtData();



	//reset stage
	_stage->reset();

}

// Event Handlers
void Scene::onEvent( const KeyDownEvent &event )
{
    if ( event.modifiers & KeyEvent::MODIFIER_CTRL )
    {
        int keyVal = event.key + 96;

        if ( keyVal == 'f' || keyVal == 'F' )
            _window.setFullscreen( !_window.getFullscreen() );
        else if ( keyVal == 'c' || keyVal == 'C' )
            _window.quit(); // cleanup first
    }
    else if ( event.modifiers & KeyEvent::MODIFIER_ALT )
    {
    }
    else
    {
        // if ( event.key == 127 ) // BACKSPACE
        // if ( event.key == 'x' ) // 'x' character without CTRL or ALT modifiers
		switch ( event.key )
		{
		// Enter
		case 13 :

			if ( sphereY == 2.0 && selector == 0 )
			{
				selector = 1;
			}
			else if ( sphereY == -1.0 && selector == 0 )
			{
				selector = 3;
			}
			else if ( sphereY == -4.0 && selector == 0 )
			{
				selector = 4;
			}

			break;
		case 'x':
			{
				std::cout << _cameraPosition.radius << " " << _cameraPosition.elevation << " " << _cameraPosition.azimuth << std::endl;
				std::cout << _cameraCenter.x << " " << _cameraCenter.y << " " << _cameraCenter.z << std::endl;
				break;
			}
		case 'r':
		case 'R':
			{
				reset();
				break;
			}
		case 'c':
		case 'C':
			{

			}
		case 'm':
		case 'M':
			{
				break;
			}
		case 's':
		case 'S':
			{
				_renderParameters.smoothShading = ! _renderParameters.smoothShading;
				break;
			}
        case '1':
            {
                selector = 0;
                _stage->sounder->stopSound(START);
                _stage->sounder->stopSound(WALK);
                musicOn = false;
                break;
            }
        case '2':
            {
                //_stage->_directionalLight->turnOn( !_stage->_directionalLight->isOn() );
                break;
            }
        case '3':
            {
                //_stage->_spotLight->turnOn( !_stage->_spotLight->isOn() );
                break;
            }
                
		default:
			break;
		}        
    }
    
    _window.repaint();
}

void Scene::onEvent( const SpecialKeyDownEvent &event )
{
    switch ( event.key )
    {
        case GLUT_KEY_UP:
        {
        	if (sphereY == 2.0)
				sphereY = -4.0;
        	else if (sphereY == -4.0)
				sphereY = -1.0;
			else if (sphereY == -1.0)
				sphereY = 2.0;

            break;
        }
        case GLUT_KEY_DOWN:
        {
        	if (sphereY == 2.0)
        		sphereY = -1.0;
        	else if (sphereY == -1.0)
        		sphereY = -4.0;
        	else if (sphereY == -4.0)
        		sphereY = 2.0;

            break;
        }
        case GLUT_KEY_LEFT:
        {
            break;
        }
        case GLUT_KEY_RIGHT:
        {
            break;
        }
        default:
            break;
    }   
    _window.repaint();
}

/*
Enable only tracking
Translate camera to stage, perform the modifications only for left button so that the camera changes the position

*/
void Scene::onEvent( const MousePressEvent &event )
{

    //// EXERCISE 06 : Make the necessary updates to code here to be able to manipulate stage or scene camera.
    // Update code here so that mouse mouvement changes the correct camera according to _cameraMode.
	if ( event.pressed && _cameraMode == SCENE_VIEW )
	{
		_mouseX = event.x;
		_mouseY = event.y;

		if ( event.button == MousePressEvent::BUTTON_LEFT )
		{
			_tracking = true;
			_zooming = false;
			_moving = false;
	    }
		else if ( event.button == MousePressEvent::BUTTON_RIGHT )
		{
			_zooming = true;
			_tracking = false;
			_moving = false;
		}    
		else if ( event.button == MousePressEvent::BUTTON_MIDDLE )
		{
			_moving = true;
	        _zooming = false;
			_tracking = false;
		}
	}
	else if ( event.pressed && ( /*_cameraMode == GLMONITOR_VIEW || 
							  	 _cameraMode == MANUALMONITOR_VIEW || 
							  	 _cameraMode == DIFFMONITOR_VIEW ||*/
							  	 _cameraMode == STAGE_VIEW ) )
	{
		_tracking = true;
		_zooming = false;
		_moving = false;
	}
	else
	{
        _tracking = false;
		_zooming = false;
		_moving = false;
	}
}

void Scene::onEvent( const MouseEnterEvent &event )
{  
}

void Scene::onEvent( const MouseLeaveEvent &event )
{  
}

void Scene::onEvent( const MouseMoveEvent &event )
{
    //// EXERCISE 06 : Make the necessary updates to code here to be able to manipulate stage or scene camera.
    // Update code here so that mouse mouvement changes the correct camera according to _cameraMode.

	//std::cout << _cameraPosition.radius << " " << _cameraPosition.elevation << " " << _cameraPosition.azimuth << std::endl;
    
    if ( event.passive == false && _cameraMode == SCENE_VIEW )
    {
		if ( _tracking )
		{
			_cameraPosition.elevation += ( event.y - _mouseY )*2*Utils::PI/_window.getApplicationParameters().getHeight();
			_cameraPosition.azimuth -= ( event.x - _mouseX )*2*Utils::PI/_window.getApplicationParameters().getWidth();
		}
		else if ( _zooming )
		{
			_cameraPosition.radius += ( event.y - _mouseY )*3.0/_window.getApplicationParameters().getHeight();
		}
		else if ( _moving )
		{
			_cameraCenter.x -= ( event.x - _mouseX )*3.0/_window.getApplicationParameters().getWidth();
			_cameraCenter.y += ( event.y - _mouseY )*3.0/_window.getApplicationParameters().getHeight();
		}

		_mouseX = event.x;
		_mouseY = event.y;

		updateLookAtData();        
        _window.repaint();
    }
    
}

GRAPHICSLAB_NAMESPACE_END

