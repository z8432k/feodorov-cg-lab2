#include <cube.h>
#include <iostream>

#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stddef.h>

#define PI 3.141592653


using namespace std;

// static double angle = .0;

static float alpha = 0.f;
static float beta = 0.f;

static float deltaAngle = 0.0f;
static int xOrigin = -1;
static int yOrigin = 0;

static const float R = 30.f; // Радиус удаления тыквы от объекта

//static float cx = R * sin(alpha) * cos(beta);
//static float cy = R * sin(alpha) * sin(beta);
//static float cz = R * cos(alpha);

static GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
static GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };

static void render_plane(float x1, float x2, float y1, float y2, float z1, float z2, const float k) {

    for (float x = x1; x < x2; x += k)

    {

        for (float y = y1; y < y2; y += k)

        {

            for (float z = z1; z < z2; z += k)
            {
                glVertex3f(x, y, z);

                glVertex3f(x, y + k, z);

                glVertex3f(x + k, y + k, z);

                glVertex3f(x + k, y, z);
            }
        }

    }
}

static void mouse_button(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            // angle += deltaAngle;
            xOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
}

static void mouse_move(int x, int y) {
    if (xOrigin >= 0) {

        //                 x     origin      x
        //                10      [15]      20
        //  dx            5                 -5

        alpha = (xOrigin - x) * 0.01;
        beta = (yOrigin + y) * 0.01;

        cout << alpha * 180.f / 3.14 << "-" << beta * 180.f / 3.14 << endl;
    }
}

static void attach_kb(u_char key, int x, int y) {
    cout << x << "-" << y << endl;
}

static void idle_cb() {
    // BUG:  There is poossible double overflow
    // angle += 0.01;

    // cameraHeight = 1.0;
    // Перерисовка

    glutPostRedisplay();
}

void render_point(GLfloat x, GLfloat y, GLfloat z)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(7.0);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

static void render_light() {
    // 0
/*
    GLfloat ambient_light0[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat diffuse_light0[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specular_light0[] = {0.0f, 0.7f, 0.7f, 1.0f};
    GLfloat light0_pos[] = {0.0f, 20.0f, 20.f, 1.f};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);



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
    GLfloat ambient_light2[] = {0.0f, 0.05f, 0.0f, 1.0f};
    GLfloat diffuse_light2[] = {0.0f, 0.10f, 0.0f, 1.0f};
    GLfloat specular_light2[] = {0.0f, 0.99f, 0.0f, 1.0f};
    GLfloat light2_pos[] = {-20.0f, 3.0f, 0.f, 1.f};
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_light2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_light2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular_light2);
    // glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, reinterpret_cast<const GLfloat *>(10));
*/

    render_point(-10, 0, 0);

/*
    GLfloat light5_diffuse[] = {1.0, 1.0, 1.0};

    GLfloat light5_position[] = {0., 6., 0.0, 1.0};

    glEnable(GL_LIGHT5);

    glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);

    glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
*/
    //glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.01);

/*
    // точечный источник света
    // убывание интенсивности с расстоянием
    // задано функцией f(d) = 1.0 / (0.4 * d * d + 0.2 * d)
    GLfloat light2_diffuse[] = {0.4, 0.7, 0.2};

    GLfloat light2_position[] = {0.0, 0.0, 0.0, 1.0};

    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);

    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);

    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);

    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4);
*/

    // прожектор
    // убывание интенсивности с расстоянием
    // отключено (по умолчанию)
    // половина угла при вершине 30 градусов
    // направление на центр плоскости
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

static void gl_init() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);



    glEnable(GL_LIGHTING);

    // Окружающий свет
    //GLfloat ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_NORMALIZE);

    render_light();
}

static void render_cube(const float start_x, const float start_y, const float start_z, const float size) {
    glBegin(GL_QUADS);

    // Front
    //glColor3f(1, 0, 0);

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

static void render_shape() {
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(15.0);
    glVertex3f(0, 0, 6);
    glEnd();

    // Оси
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
    // /Оси

    //glNormal3f(0.0, 10.0, 0.0);

    glTranslatef(-10, 0, 0);
    render_cube(-5., -5., -5, 10);

    glTranslatef(20, 0, 0);
    render_cube(-5., -5., -5, 10);

    glTranslatef(-10, 0, -15);
    render_cube(-5., -5., -5, 10);

    //glTranslatef(-10, -15, -15);

    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    // glMaterialfv(GL_BACK, GL_EMISSION, black);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    // glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    //glutSolidCube(20);
}

static void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // double cameraPos[] = {cos(angle) * 45, 15, sin(angle) * 45};
    double focusPos[] = {0, 0, 0};
    double up[] = {0,1,0};
/*
    gluLookAt( cameraPos[0], cameraPos[1], cameraPos[2],
               focusPos[0], focusPos[1], focusPos[2],
               up[0], up[1], up[2]);
*/
    gluLookAt(	R * sin(alpha) * cos(beta), R * sin(alpha) * sin(beta), R * cos(alpha),
                  0, 0,  0,
                  0.0f, 1.0f,  0.0f);

    //GLfloat right_specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    //glMaterialfv(GL_FRONT, GL_SPECULAR, right_specular);
    //glMateriali(GL_FRONT, GL_SHININESS, 10);


    //GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};

    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

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
    glutKeyboardFunc(attach_kb);

    glutMouseFunc(mouse_button);
    glutMotionFunc(mouse_move);

    gl_init();

    glutMainLoop();
}
