#include <GL/glut.h>

double rotate_y = 0;
double rotate_x = 0;

void display()
{
    float size = 1.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очистить экран и Z-буфер (буфер глубины)
    glLoadIdentity(); // Сброс матрицы в значение по умолчанию
// Осуществлять поворот когда пользователь изменяет rotate_x и rotate_y

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
// цвет
    glColor3f(0.0, 0.5, 1.0);
// левая грань
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
// правая грань
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
// нижняя грань
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
// верхняя грань
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
// задняя грань
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
// передняя грань
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glEnd();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) // Функция отвечающая за считывание нажатий клавиш
{
    if (key == GLUT_KEY_RIGHT) {
        rotate_y += 5;
    }
    else if (key == GLUT_KEY_LEFT) {
        rotate_y -= 5;
    }
    else if (key == GLUT_KEY_UP) {
        rotate_x += 5;
    }
    else if (key == GLUT_KEY_DOWN) {
        rotate_x -= 5;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Задаем режим работы дисплея
    glutInit(&argc, argv);
// GLUT_DOUBLE — включает двойной экранный буфер
// GLUT_RGB — включает четырехкомпонентный цвет (используетсяx по умолчанию)
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("LR1 - 3D Cube");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display); // Задает функцию рисования изображения
    glutSpecialFunc(specialKeys); // Задает функцию обработки нажатия клавиш клавиатуры
    glutMainLoop(); // Главный цикл
    return 0;
}
