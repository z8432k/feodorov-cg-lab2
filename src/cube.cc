#include <cube.h>
#include <iostream>

#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

static double angle = .0;

static void idle_cb() {
    // BUG:  There is poossible double overflow
    angle += 0.01;

    // cameraHeight = 1.0;
    // Перерисовка

    glutPostRedisplay();
}

static void render_light() {
    // 0
    GLfloat ambient_light0[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuse_light0[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specular_light0[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);

    GLfloat light0_pos[] = {50.0f, 0.0f, 15.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

    glEnable(GL_LIGHT0);

    // 1
    GLfloat ambient_light1[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuse_light1[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specular_light1[] = {0.0f, 1.7f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);

    GLfloat light1_pos[] = {15.0f, 50.0f, 15.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

    glEnable(GL_LIGHT1);

    // 2
    GLfloat ambient_light2[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuse_light2[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specular_light2[] = {0.0f, 0.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_light2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_light2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular_light2);

    GLfloat light2_pos[] = {0.0f, 0.0f, 50.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);

    glEnable(GL_LIGHT2);
}

static void gl_init() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);



    glEnable(GL_LIGHTING);
    GLfloat ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);

    glEnable(GL_NORMALIZE);

    render_light();
}

static void render_shape() {
    glBegin(GL_QUADS);


    // Front
    glColor3f(1, 0, 1);

    glVertex3f(-5, -5, 5);
    glVertex3f(5, -5, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(-5, 5, 5);


    // Back
    glColor3f(0, 0, 1);

    glVertex3f(-5, -5, -5);
    glVertex3f(5, -5, -5);
    glVertex3f(5, 5, -5);
    glVertex3f(-5, 5, -5);


    // Left
    glColor3f(1, 0, 0);

    glVertex3f(-5, -5, 5);
    glVertex3f(-5, 5, 5);
    glVertex3f(-5, 5, -5);
    glVertex3f(-5, -5, -5);

    // Bottom
    glColor3f(1, 1, 0);

    glVertex3f(-5, -5, 5);
    glVertex3f(5, -5, 5);
    glVertex3f(5, -5, -5);
    glVertex3f(-5, -5, -5);

    glEnd();
}

static void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double cameraPos[] = {cos(angle) * 45, 15, sin(angle) * 45};
    double focusPos[] = {0, 0, 0};
    double up[] = {0,1,0};

    gluLookAt( cameraPos[0], cameraPos[1], cameraPos[2],
               focusPos[0], focusPos[1], focusPos[2],
               up[0], up[1], up[2]);

    render_shape();

    glutSwapBuffers();
}

static void reshape(int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // windowWidth = newWidth;
    // windowHeight = newHeight;

    double minZPlane = 0.01;
    double maxZPlane = 100.0;
    gluPerspective(45.0f, 1.0 * newWidth / newHeight, minZPlane, maxZPlane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void cube(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0,0);

    int windowID = glutCreateWindow("Computer graphic. Lab 1.");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle_cb);

    gl_init();

    glutMainLoop();
}
