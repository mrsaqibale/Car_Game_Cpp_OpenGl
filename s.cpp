#include <GL/glut.h>

float carVertices[] = {
    // Front left wheel
    -1.5, -0.5, 0.5,
    -1.5, 0.5, 0.5,
    -1.0, 0.5, 0.5,
    -1.0, -0.5, 0.5,

    // Front right wheel
    1.5, -0.5, 0.5,
    1.5, 0.5, 0.5,
    1.0, 0.5, 0.5,
    1.0, -0.5, 0.5,

    // Back left wheel
    -1.5, -0.5, -0.5,
    -1.5, 0.5, -0.5,
    -1.0, 0.5, -0.5,
    -1.0, -0.5, -0.5,

    // Back right wheel
    1.5, -0.5, -0.5,
    1.5, 0.5, -0.5,
    1.0, 0.5, -0.5,
    1.0, -0.5, -0.5,

    // Car body
    -2.0, -1.0, 0.0,
    2.0, -1.0, 0.0,
    2.0, 1.0, 0.0,
    -2.0, 1.0, 0.0,

    -2.0, -1.0, -1.0,
    2.0, -1.0, -1.0,
    2.0, 1.0, -1.0,
    -2.0, 1.0, -1.0
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -1);
    glRotatef(45, 1, 0, 0);

    // Draw car body
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3fv(&carVertices[24]);
    glVertex3fv(&carVertices[26]);
    glVertex3fv(&carVertices[30]);
    glVertex3fv(&carVertices[28]);
    glEnd();

    // Draw wheels
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex3fv(&carVertices[0]);
    glVertex3fv(&carVertices[1]);
    glVertex3fv(&carVertices[3]);
    glVertex3fv(&carVertices[2]);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3fv(&carVertices[4]);
    glVertex3fv(&carVertices[5]);
    glVertex3fv(&carVertices[7]);
    glVertex3fv(&carVertices[6]);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3fv(&carVertices[8]);
    glVertex3fv(&carVertices[9]);
    glVertex3fv(&carVertices[11]);
    glVertex3fv(&carVertices[10]);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3fv(&carVertices[12]);
    glVertex3fv(&carVertices[13]);
    glVertex3fv(&carVertices[15]);
    glVertex3fv(&carVertices[14]);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Car Model");

    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}