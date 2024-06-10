#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int score = 0;
bool gameOver = false;

struct Car {
    float posX;
    float posY;
    float speed;
};

std::vector<Car> cars;

void drawCar(float x, float y) {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y + 0.1f);
    glVertex2f(x - 0.1f, y + 0.1f);
    glEnd();
}

void drawZebraCrossing() {
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, -0.1f);
    glVertex2f(0.6f, -0.1f);
    glVertex2f(0.6f, 0.1f);
    glVertex2f(-0.6f, 0.1f);
    glEnd();
}

void drawRoad() {
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

    // Draw zebra crossing
    drawZebraCrossing();
}

void display() {
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
        std::string scoreText = "Final Score: " + std::to_string(score);
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

        // Draw cars
        for (auto& car : cars) {
            drawCar(car.posX, car.posY);
        }

        // Display score
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(0.7f, 0.9f);
        std::string scoreText = "Score: " + std::to_string(score);
        for (char c : scoreText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glutSwapBuffers();
}

void update(int value) {
    if (!gameOver) {
        // Spawn new cars
        if (rand() % 100 < 5) { // Adjust spawn rate here
            cars.push_back({ (rand() % 12 - 6) / 10.0f, 1.0f, (rand() % 11 + 5) / 100.0f });
        }

        // Update cars' positions
        for (auto& car : cars) {
            car.posY -= car.speed;
            if (car.posY < -1.0f) {
                car = cars.back();
                cars.pop_back();
                score++;
            }
        }

        glutPostRedisplay();
        glutTimerFunc(50, update, 0);
    }
}

void specialInput(int key, int x, int y) {
    if (!gameOver) {
        // No user input required in this version
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (gameOver) {
        if (key == 13) { // ASCII value for Enter key
            gameOver = false;
            score = 0;
            cars.clear();

            glutPostRedisplay();
            glutTimerFunc(50, update, 0);
        } else if (key == 27) { // ASCII value for Escape key
            exit(0);
        }
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Car Game");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutTimerFunc(50, update, 0);
    glutSpecialFunc(specialInput);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
