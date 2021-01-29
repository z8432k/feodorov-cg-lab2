#include <orig.h>

#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

int windowID;
int windowWidth, windowHeight;
double angle = 0.0;
double cameraHeight = 1.0;

void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
    GLfloat ambient_light0[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuse_light0[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specular_light0[] = {0.0f, 0.7f, 0.7f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);

    GLfloat light0_pos[] = {50.0f, 0.0f, 15.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

    glEnable(GL_LIGHT0);
}

void doIdle()
{
    angle += 0.01;
    cameraHeight = 1.0;
    // Перерисовка
    glutPostRedisplay();
}

void reshape(int newWindowWidth, int newWindowHeight)
{
    glViewport(0,0,newWindowWidth,newWindowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    windowWidth = newWindowWidth;
    windowHeight = newWindowHeight;
    double minZPlane = 0.01;
    double maxZPlane = 10.0;
    gluPerspective(45.0f, 1.0 * windowWidth / windowHeight, minZPlane, maxZPlane);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void KeyboardFunc (unsigned char key, int x, int y)
{
    switch (key)
    {
        //glutDestroyWindow(windowID);
        //exit(0);
        //break;

        default:
            break;

    }

}


void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double cameraPosition[3] = {cos(angle) * 2, cos(angle / 3.3), sin(angle) * 2};
    double focusPosition[3] = {0, 0, 0};
    double up[3] = {0,1,0};
    gluLookAt( cameraPosition[0], cameraPosition[1], cameraPosition[2],
               focusPosition[0], focusPosition[1], focusPosition[2],
               up[0], up[1], up[2]);
    int verticalParts = 48;
    float verticalMultiplier = 2 * M_PI / verticalParts;
    int horisontalParts = 128;
    float horisontalMultiplier = 2 * M_PI / horisontalParts;


    float radius = .5;
    float partRadius = .125;
    glBegin(GL_QUADS);
    for (int k = -1; k <= 1; k += 2) {
        if (k > 0) {
            GLfloat left_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_SPECULAR, left_specular);
            glMateriali(GL_FRONT, GL_SHININESS, 10);
        } else {
            GLfloat right_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

            glMaterialfv(GL_FRONT, GL_SPECULAR, right_specular);
            glMateriali(GL_FRONT, GL_SHININESS, 30);
            glColor3f(0.0f, 0.0f, 1.0f);

        }
        for (int i = 0; i < horisontalParts; i++) {
            float a1 = i * horisontalMultiplier;
            float a2 = (i + 1) * horisontalMultiplier;

            float cosa1 = cosf(a1 + angle * 2);
            float cosa2 = cosf(a2 + angle * 2);
            float sina1 = sinf(a1 + angle * 2);
            float sina2 = sinf(a2 + angle * 2);

            for (int j = 0; j < verticalParts; j++) {
                if (k < 0)
                    if (j % 2 == 0)
                        if (i % 2 == 0)
                            glColor3f(0.8, 0, 0);
                        else
                            glColor3f(0, 0, 1);
                    else
                    if (i % 2 == 0)
                        glColor3f(1, 0.8, 0);
                    else
                        glColor3f(0, 0.8, 1);
                else
                    glColor3f(1, 1, 1);
                float b1 = j * verticalMultiplier;
                float b2 = (j + 1) * verticalMultiplier;

                float cosb1 = cosf(b1 + angle * 4);
                float cosb2 = cosf(b2 + angle * 4);
                float sinb1 = sinf(b1 + angle * 4);
                float sinb2 = sinf(b2 + angle * 4);

                float x1 = (cosa2 * cosb1 * partRadius - cosa2 * radius) - (cosa1 * cosb1 * partRadius - cosa1 * radius);
                float y1 = (sina2 * cosb1 * partRadius - sina2 * radius) - (sina1 * cosb1 * partRadius - sina1 * radius);
                float z1 = (sinb1 * partRadius + k * radius) - (sinb1 * partRadius + k * radius);

                float x2 = (cosa1 * cosb2 * partRadius - cosa1 * radius) - (cosa1 * cosb1 * partRadius - cosa1 * radius);
                float y2 = (sina1 * cosb2 * partRadius - sina1 * radius) - (sina1 * cosb1 * partRadius - sina1 * radius);
                float z2 = (sinb2 * partRadius + k * radius) - (sinb1 * partRadius + k * radius);

                glNormal3f(
                                -(y1 * z2 - z1 * y2),
                        -(z1 * x2 - x1 * z2),
                        -(x1 * y2 - x2 * y1)

                );

                glVertex3f(
                cosa1 * cosb1 * partRadius - cosa1 * radius,
                        sina1 * cosb1 * partRadius - sina1 * radius,
                        sinb1 * partRadius + k * radius
                );
                glVertex3f(

                cosa2 * cosb1 * partRadius - cosa2 * radius,
                        sina2 * cosb1 * partRadius - sina2 * radius,
                        sinb1 * partRadius + k * radius
                );
                glVertex3f(
                cosa2 * cosb2 * partRadius - cosa2 * radius,
                        sina2 * cosb2 * partRadius - sina2 * radius,
                        sinb2 * partRadius + k * radius
                );

                glVertex3f(
                cosa1 * cosb2 * partRadius - cosa1 * radius,
                        sina1 * cosb2 * partRadius - sina1 * radius,
                        sinb2 * partRadius + k * radius
                );
            }
        }
    }

    glEnd();
    glutSwapBuffers();

}

void orig(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    windowWidth = 400;
    windowHeight = 400;
    glutInitWindowSize (windowWidth,windowHeight);
    glutInitWindowPosition (0,0);
    char s[] = "Hello world";
    windowID = glutCreateWindow(s);
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutIdleFunc(doIdle);
    glutKeyboardFunc(KeyboardFunc);

    init();
    glutMainLoop();
}
