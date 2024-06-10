#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

// Function to draw the car
void drawCar() {
    // Car body
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray color
    glBegin(GL_QUADS);
    glVertex3f(-0.294f, 0.0f, 0.147f);  // Bottom left front
    glVertex3f(0.294f, 0.0f, 0.147f);   // Bottom right front
    glVertex3f(0.294f, 0.0f, -0.147f);  // Bottom right back
    glVertex3f(-0.294f, 0.0f, -0.147f); // Bottom left back
    glEnd();

    // Car windows
    glColor3f(0.2f, 0.5f, 0.8f); // Light blue color
    glBegin(GL_QUADS);
    glVertex3f(-0.245f, 0.0f, 0.1225f);  // Left front
    glVertex3f(-0.245f, 0.102f, 0.1225f);  // Left top
    glVertex3f(0.245f, 0.102f, 0.1225f);   // Right top
    glVertex3f(0.245f, 0.0f, 0.1225f);   // Right front

    glVertex3f(-0.245f, 0.0f, -0.1225f); // Left back
    glVertex3f(-0.245f, 0.102f, -0.1225f); // Left top
    glVertex3f(0.245f, 0.102f, -0.1225f);  // Right top
    glVertex3f(0.245f, 0.0f, -0.1225f);  // Right back
    glEnd();

    // Car roof
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the roof
    glBegin(GL_QUADS);
    glVertex3f(-0.245f, 0.102f, 0.1225f);  // Left front top
    glVertex3f(-0.245f, 0.102f, -0.1225f); // Left back top
    glVertex3f(0.245f, 0.102f, -0.1225f);  // Right back top
    glVertex3f(0.245f, 0.102f, 0.1225f);   // Right front top
    glEnd();

    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f); // Dark gray color
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.2f); // Front left wheel position
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate wheel to be vertical
    glutSolidTorus(0.05, 0.1, 10, 25); // Front left wheel
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.2f); // Front right wheel position
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate wheel to be vertical
    glutSolidTorus(0.05, 0.1, 10, 25); // Front right wheel
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, -0.2f); // Back left wheel position
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate wheel to be vertical
    glutSolidTorus(0.05, 0.1, 10, 25); // Back left wheel
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, -0.2f); // Back right wheel position
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate wheel to be vertical
    glutSolidTorus(0.05, 0.1, 10, 25); // Back right wheel
    glPopMatrix();
}

// Function to display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -0.1f, -3.0f); // Move the car back and down
    glRotatef(30, 1.0f, 0.0f, 0.0f);   // Rotate slightly for better view

    // Draw the car
    drawCar();

    glutSwapBuffers();
}

// Function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mehran Car");

    glewInit();

    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background color

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}