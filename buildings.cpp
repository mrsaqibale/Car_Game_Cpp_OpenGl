#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>

float playerCarX = 0.0f;
float playerCarY = -0.8f;
int lane = 1;  // 0: left, 1: middle, 2: right
bool gameOver = false;
int score = 0;

struct Car {
    float x;
    float y;
};

std::vector<Car> enemyCars;

void drawCar(float x, float y, bool isPlayer) {
    if (isPlayer) {
        glColor3f(1.0f, 0.0f, 0.0f);  // Red for player car
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);  // Blue for enemy cars
    }
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y + 0.1f);
    glVertex2f(x - 0.1f, y + 0.1f);
    glEnd();
}

void drawRoad() {
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, -1.0f);
    glVertex2f(0.6f, -1.0f);
    glVertex2f(0.6f, 1.0f);
    glVertex2f(-0.6f, 1.0f);
    glEnd();

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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRoad();
    drawCar(playerCarX, playerCarY, true);

    for (const auto& car : enemyCars) {
        drawCar(car.x, car.y, false);
    }

    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.1f, 0.0f);
        const char* msg = "Game Over";
        while (*msg) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *msg++);
        }
    } else {
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
        for (auto& car : enemyCars) {
            car.y -= 0.02f;
            if (car.y < -1.0f) {
                score++;
                car.y = 1.0f;
                car.x = (rand() % 3 - 1) * 0.4f;
            }

            if (car.y < playerCarY + 0.1f && car.y > playerCarY - 0.1f && car.x == playerCarX) {
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
            playerCarX -= 0.4f;
        } else if (key == GLUT_KEY_RIGHT && lane < 2) {
            lane++;
            playerCarX += 0.4f;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    } else if (key == 13 && gameOver) { // Enter key to restart
        gameOver = false;
        score = 0;
        playerCarX = 0.0f;
        playerCarY = -0.8f;
        enemyCars.clear();
        enemyCars.push_back({ -0.4f, 1.0f });
        enemyCars.push_back({ 0.0f, 1.5f });
        enemyCars.push_back({ 0.4f, 2.0f });
        glutPostRedisplay();
        glutTimerFunc(50, update, 0);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    enemyCars.push_back({ -0.4f, 1.0f });
    enemyCars.push_back({ 0.0f, 1.5f });
    enemyCars.push_back({ 0.4f, 2.0f });

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Racing Game");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutSpecialFunc(specialInput);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(50, update, 0);

    glutMainLoop();
    return 0;
}
