
IF (USE_GLUT)

SET(SharedDemoSubdirs
	OpenGL )


if (CMAKE_SIZEOF_VOID_P MATCHES "8")
	SUBDIRS( 	${SharedDemoSubdirs}
	)
else (CMAKE_SIZEOF_VOID_P MATCHES "8")
	SUBDIRS( 		${SharedDemoSubdirs}
		MultiThreadedDemo
		MiniCL_VectorAdd
	)
endif (CMAKE_SIZEOF_VOID_P MATCHES "8")

ELSE (USE_GLUT)

SUBDIRS( 
	OpenGL 
	BasicDemo 
	Benchmarks 
	Box2dDemo 
	CollisionInterfaceDemo 
	ConcaveDemo 
	ConstraintDemo 
	ConvexDecompositionDemo 
	InternalEdgeDemo
	GimpactTestDemo 
	GenericJointDemo 
	SerializeDemo 
	SoftDemo
	MiniCL_VectorAdd
)

ENDIF (USE_GLUT)
