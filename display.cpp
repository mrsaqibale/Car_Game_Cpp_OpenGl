#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include<display.h>

using namespace std;


void Display::drawCar(float x, float y, bool isRed) {
    glColor3f(isRed ? 1.0f : 0.0f, 0.0f, isRed ? 0.0f : 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y + 0.1f);
    glVertex2f(x - 0.1f, y + 0.1f);
    glEnd();
}

void Display::drawTree(float x, float y) {
    // Draw the trunk
    glColor3f(0.55f, 0.27f, 0.07f); // Dark brown
    glBegin(GL_QUADS);
    glVertex2f(x - 0.02f, y - 0.1f);
    glVertex2f(x + 0.02f, y - 0.1f);
    glVertex2f(x + 0.02f, y);
    glVertex2f(x - 0.02f, y);
    glEnd();

    // Draw the leaves
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.07f, y);
    glVertex2f(x + 0.07f, y);
    glVertex2f(x, y + 0.1f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.05f, y + 0.05f);
    glVertex2f(x + 0.05f, y + 0.05f);
    glVertex2f(x, y + 0.15f);
    glEnd();
}

void Display::drawRoad() {
    // Draw grass
    glColor3f(0.0f, 0.5f, 0.0f); // Dark green
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-0.6f, -1.0f);
    glVertex2f(-0.6f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.6f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.6f, 1.0f);
    glEnd();

    // Draw road
    glColor3f(0.2f, 0.2f, 0.2f); // Dark grey
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, -1.0f);
    glVertex2f(0.6f, -1.0f);
    glVertex2f(0.6f, 1.0f);
    glVertex2f(-0.6f, 1.0f);
    glEnd();

    // Draw road lines
    glLineWidth(10);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (float i = -1.0f; i <= 1.0f; i += 0.2f) {
        glVertex2f(-0.2f, i);
        glVertex2f(-0.2f, i + 0.1f);
        glVertex2f(0.2f, i);
        glVertex2f(0.2f, i + 0.1f);
    }
        glEnd();
}

void Display::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.1f, 0.0f);
        const char* msg = "Game Over";
        while (*msg) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *msg++);
        }

        // Display final score
        glRasterPos2f(-0.1f, -0.1f);
        string scoreText = "Final Score: " + to_string(score);
        for (char c : scoreText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        // Display restart instructions
        glRasterPos2f(-0.3f, -0.3f);
        const char* restartMsg = "Press Enter to Restart or Escape to Exit";
        while (*restartMsg) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *restartMsg++);
        }
    } else {
        drawRoad();
        
        // Draw the red car
        drawCar(carPosX, carPosY, true);

        // Draw other cars
        for (auto& car : otherCars) {
            drawCar(car.posX, car.posY, false);
        }

        // Draw trees on the sides of the road
        for (float y = -0.9f; y <= 1.0f; y += 0.4f) {
            drawTree(-0.8f, y);
            drawTree(0.8f, y);
        }

        // Display score
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(0.7f, 0.9f);
        string scoreText = "Score: " + to_string(score);
        for (char c : scoreText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glutSwapBuffers();
}
