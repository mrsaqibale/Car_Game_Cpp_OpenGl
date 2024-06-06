#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

float carPosX = 0.0f;   // Red car's X position
float carPosY = -0.8f;  // Red car's Y position
int lane = 1;           // Red car's lane (0: left, 1: middle, 2: right)
int score = 0;
bool gameOver = false;

struct OtherCar {
    float posX;
    float posY;
    int lane;
};

std::vector<OtherCar> otherCars;

void drawCar(float x, float y, bool isRed) {
    glColor3f(isRed ? 1.0f : 0.0f, 0.0f, isRed ? 0.0f : 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y + 0.1f);
    glVertex2f(x - 0.1f, y + 0.1f);
    glEnd();
}

void drawRoad() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = -1; i <= 1; i++) {
        glBegin(GL_LINES);
        glVertex2f(i * 0.8f, -1.0f);
        glVertex2f(i * 0.8f, 1.0f);
        glEnd();
    }
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
        
        // Draw the red car
        drawCar(carPosX, carPosY, true);

        // Draw other cars
        for (auto& car : otherCars) {
            drawCar(car.posX, car.posY, false);
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
        for (auto& car : otherCars) {
            car.posY -= 0.02f;
            if (car.posY < -1.0f) {
                score++;
                car.posY = 1.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.0f)));
                car.lane = rand() % 3;
                car.posX = -0.6f + car.lane * 0.6f;
            }

            if (car.lane == lane && car.posY < carPosY + 0.1f && car.posY > carPosY - 0.1f) {
                gameOver = true;
            }
        }
        glutPostRedisplay();
        glutTimerFunc(50, update, 0);
    }
}

void specialInput(int key, int x, int y) {
    if (!gameOver) {
        if (key == GLUT_KEY_LEFT && lane > 0) {
            lane--;
            carPosX -= 0.6f;
        } else if (key == GLUT_KEY_RIGHT && lane < 2) {
            lane++;
            carPosX += 0.6f;
        } else if (key == GLUT_KEY_UP && carPosY < 0.9f) {
            carPosY += 0.1f;
        } else if (key == GLUT_KEY_DOWN && carPosY > -0.9f) {
            carPosY -= 0.1f;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (gameOver) {
        if (key == 13) { // ASCII value for Enter key
            gameOver = false;
            score = 0;
            carPosX = 0.0f;
            carPosY = -0.8f;
            otherCars.clear();
            otherCars.push_back({ -0.6f, 1.0f, 0 });
            otherCars.push_back({ 0.0f, 1.5f, 1 });
            otherCars.push_back({ 0.6f, 2.0f, 2 });
            glutPostRedisplay();
            glutTimerFunc(50, update, 0);
        } else if (key == 27) { // ASCII value for Escape key
            exit(0);
        }
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    otherCars.push_back({ -0.6f, 1.0f, 0 });
    otherCars.push_back({ 0.0f, 1.5f, 1 });
    otherCars.push_back({ 0.6f, 2.0f, 2 });

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
