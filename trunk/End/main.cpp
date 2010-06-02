#include "End.hpp"

extern ParticleContext_t P;

int main(int argc, char **argv)
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
