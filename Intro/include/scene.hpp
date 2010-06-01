/**
 * scene.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_SCENE_HPP
#define GRAPHICSLAB_SCENE_HPP

// Base class includes
#include "keyboardEventHandler.hpp"
#include "mouseEventHandler.hpp"

// Includes
#include "types.hpp"
#include "camera3D.hpp"

#include <vector>

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class Window;
class Light;
class Camera2D;
class Stage;
//class SceneSoundClass;

/** Class that contains contents of the screen to display */
class Scene : public KeyboardEventHandler, public MouseEventHandler
{
public:
    /** 
     * Constructor.
     *
     * @param[in]   window      Associated window to display
     */
    Scene( Window &window );
    
    /** Destructor */
    virtual ~Scene();
    
    /** Initialize the scene data */
    virtual void initialize();
    
    virtual void resize( int width, int height );
    virtual void draw();
    
	const Window &getWindow() const { return _window; }
	const Camera::Viewport &getViewport() const { return _viewport; }
    
    // Keyboard event handlers
    virtual void onEvent( const KeyDownEvent &event );
    virtual void onEvent( const SpecialKeyDownEvent &event );
    
    // Mouse event handlers
    virtual void onEvent( const MousePressEvent &event );
    virtual void onEvent( const MouseEnterEvent &event );
    virtual void onEvent( const MouseLeaveEvent &event );
    virtual void onEvent( const MouseMoveEvent &event );

	Camera3D *_camera3D;

	//SceneSoundClass *sounder;

	bool musicOn;

	virtual void updateLookAtData();
    
protected:
    /** Associated window to display */
    Window &_window;
    
	/** Camera mode */
	enum CameraMode
	{
		SCENE_VIEW,
		GLMONITOR_VIEW,
		MANUALMONITOR_VIEW,
		DIFFMONITOR_VIEW,
		STAGE_VIEW
	} _cameraMode;

    /** 3D Camera to view the screen */
    
    
    /** 2D Camera to overlay 2D data to the screen */
    Camera2D *_camera2D;
    
     
    /** Screen render parameters */
    RenderParameters _renderParameters;

	/** Virtual stage */
	Stage *_stage;

	// Camera related data
    bool _tracking;	// Whether altering the position
	bool _zooming;	// Whether altering the radius
	bool _moving;	// Whether altering the center
    int _mouseX, _mouseY;	// Last mouse event coordinates
	SphericalCoordinates _cameraPosition;	// Spherical camera coordinates
	Point _cameraCenter;	// Center of the camera to look at
    Camera3D::Frustum _frustum;   // Projection for the camera
    
    Camera::Viewport _viewport; // Window viewport

	float _theta;
	float sinusY;
	float growth;

	int selector;

	float temp;

	//2.0 -1.0 -4.0
	float sphereY;

    
protected:
    
    virtual void reset();

	virtual void DrawTitle(void);

	virtual void DrawMenuText(void);

    
}; // class Scene

GRAPHICSLAB_NAMESPACE_END

#endif  //  GRAPHICSLAB_SCENE_HPP


