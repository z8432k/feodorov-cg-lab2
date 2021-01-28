#include <cube.h>

#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>

static void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double cameraPos[] = {0, 0, 10};
    double focusPos[] = {0, 0, 0};
    double up[] = {0,1,0};

    gluLookAt( cameraPos[0], cameraPos[1], cameraPos[2],
               focusPos[0], focusPos[1], focusPos[2],
               up[0], up[1], up[2]);

    glBegin(GL_TRIANGLES);

    glEnd();
    glutSwapBuffers();
}

static void reshape(int width, int height) {

}

void cube(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0,0);

    int windowID = glutCreateWindow("Computer graphic. Lab 1.");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glutMainLoop();
}
