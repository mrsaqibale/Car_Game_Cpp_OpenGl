#include <GL/glut.h>
#include <cmath>

// Function to draw a filled circle
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // Get the current angle
        float x = r * cosf(theta); // Calculate the x component
        float y = r * sinf(theta); // Calculate the y component
        glVertex2f(x + cx, y + cy); // Output vertex
    }
    glEnd();
}

// Function to draw the apple tree
void drawAppleTree() {
    // Draw the trunk
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, -0.5f);
    glVertex2f(0.05f, -0.5f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(-0.05f, 0.0f);
    glEnd();

    // Draw the leaves
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    drawCircle(0.0f, 0.1f, 0.2f, 100); // Center top
    drawCircle(-0.15f, 0.0f, 0.15f, 100); // Left
    drawCircle(0.15f, 0.0f, 0.15f, 100); // Right

    // Draw apples
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawCircle(-0.1f, 0.05f, 0.03f, 100); // Left apple
    drawCircle(0.1f, 0.05f, 0.03f, 100); // Right apple
    drawCircle(0.0f, 0.15f, 0.03f, 100); // Top apple
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAppleTree();
    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Apple Tree");

    // Set up the display callback function
    glutDisplayFunc(display);

    // Set the clear color to sky blue
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
