#include <iostream>

#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>

#define PI 3.141592653


using namespace std;


static float alpha = 0.f;
static float beta = 0.f;

static int xOrigin = -1;
static int yOrigin = 0;

static const float R = 30.f;

static GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
static GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };


static void mouse_button(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            xOrigin = -1;
        }
        else  {
            xOrigin = x;
            yOrigin = y;
        }
    }
}

static void mouse_move(int x, int y) {
    if (xOrigin >= 0) {
        alpha = (xOrigin - x) * 0.01;
        beta = (yOrigin + y) * 0.01;
        cout << alpha * 180.f / 3.14 << "-" << beta * 180.f / 3.14 << endl;
    }
}

static void idle_cb() {
    glutPostRedisplay();
}


static void gl_init() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    GLfloat ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_NORMALIZE);

    // Light
    GLfloat light3_diffuse[] = {0.4, 0.8, 0.4};
    GLfloat light3_position[] = {0, 0, 0, 1.0};
    GLfloat light3_spot_direction[] = {0.0, 0.0, -1.0};
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 8);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);


    GLfloat light4_diffuse[] = {0.4, 0.4, 0.8};
    GLfloat light4_position[] = {0, 5, -10, 1.0};
    GLfloat light4_spot_direction[] = {0.0, 0.0, -1.0};
    glEnable(GL_LIGHT4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
    glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 8);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light4_spot_direction);


    GLfloat light5_diffuse[] = {0.8, 0.4, 0.4};
    GLfloat light5_position[] = {-10, 5, -10, 1.0};
    GLfloat light5_spot_direction[] = {0.0, 0.0, -1.0};
    glEnable(GL_LIGHT5);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
    glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 9);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light5_spot_direction);
}

static void render_cube(const float start_x, const float start_y, const float start_z, const float size) {
    glBegin(GL_QUADS);

    // Front
    // glColor3f(1, 0, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    glMaterialfv(GL_BACK, GL_EMISSION, black);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, red);

    glNormal3f(0, 0, 1);
    float k = 0.05;
    float z = start_z + size;
    for (float x = start_x; x < start_x + size; x += k)
    {
        for (float y = start_y; y < start_y + size; y += k)
        {
            glVertex3f(x, y, z);
            glVertex3f(x + k, y, z);
            glVertex3f(x + k, y + k, z);
            glVertex3f(x, y + k, z);
        }
    }


    // Back
    //glColor3f(0, 0, -1);
    glNormal3f(0, 0, 1);
    z = start_z;
    for (float x = start_x; x < start_x + size; x += k)
    {
        for (float y = start_y; y < start_y + size; y += k)
        {
            glVertex3f(x, y, z);
            glVertex3f(x, y + k, z);
            glVertex3f(x + k, y + k, z);
            glVertex3f(x + k, y, z);
        }
    }


    // Left
    //glColor3f(0, 0, 1);

    glMaterialfv(GL_FRONT, GL_EMISSION, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glMaterialfv(GL_BACK, GL_EMISSION, black);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, yellow);

    glNormal3f(-1, 0, 0);
    float x = start_x;
    for (float z = start_z; z < start_z + size; z += k)
    {
        for (float y = start_y; y < start_y + size; y += k)
        {
            glVertex3f(x, y, z);
            glVertex3f(x, y, z + k);
            glVertex3f(x, y + k, z + k);
            glVertex3f(x, y + k, z);
        }
    }

    // Right
    //glColor3f(0, 1, 1);

    glMaterialfv(GL_FRONT, GL_EMISSION, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_BACK, GL_EMISSION, black);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    glNormal3f(1, 0, 0);
    x = start_x + size;
    for (float z = start_z; z < start_z + size; z += k)
    {
        for (float y = start_y; y < start_y + size; y += k)
        {
            glVertex3f(x, y, z);
            glVertex3f(x, y + k, z);
            glVertex3f(x, y + k, z + k);
            glVertex3f(x, y, z + k);
        }
    }

    // Bottom
    //glColor3f(1, 0, 1);

    glNormal3f(0, -1, 0);
    float y = start_y;
    for (float z = start_z; z < start_z + size; z += k)
    {
        for (float x = start_x; x < start_x + size; x += k)
        {
            glVertex3f(x, y, z);
            glVertex3f(x + k, y, z);
            glVertex3f(x + k, y, z + k);
            glVertex3f(x, y, z + k);
        }
    }

    // Top
    //glColor3f(1, 1, 1);
    glNormal3f(0, 1, 0);
    y = start_y + size;
    for (float z = start_z; z < start_z + size; z += k)
    {
        for (float x = start_x; x < start_x + size; x += k)
        {
            glVertex3f(x, y, z);
            glVertex3f(x, y, z + k);
            glVertex3f(x + k, y, z + k);
            glVertex3f(x + k, y, z);
        }
    }

    glEnd();
}

static void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(	R * sin(alpha) * cos(beta), R * sin(alpha) * sin(beta), R * cos(alpha),
                  0, 0,  0,
                  0.0f, 1.0f,  0.0f);

    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(15.0);
    glVertex3f(0, 0, 6);
    glEnd();

    glBegin(GL_LINES);

    glColor3f (1.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);

    glColor3f (1.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);

    glColor3f (1.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();

    glTranslatef(-10, 0, 0);
    render_cube(-5., -5., -5, 10);

    glTranslatef(20, 0, 0);
    render_cube(-5., -5., -5, 10);

    glTranslatef(-10, 0, -15);
    render_cube(-5., -5., -5, 10);
    glutSwapBuffers();
}

static void reshape(int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double minZPlane = 0.01;
    double maxZPlane = 100.0;
    gluPerspective(45.0f, 1.0 * newWidth / newHeight, minZPlane, maxZPlane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char* argv[] ) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0,0);
    int windowID = glutCreateWindow("Computer graphic. Lab 1.");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle_cb);

    glutMouseFunc(mouse_button);
    glutMotionFunc(mouse_move);

    gl_init();

    glutMainLoop();
}
