#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct Car {
    float x, y;
    int lane;
    bool isStopped;
    float stopTime;
    bool hasStopped; // new flag to track if car has stopped before
};

vector<Car> cars;

void drawCar(float x, float y) {
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y + 0.1f);
    glVertex2f(x - 0.1f, y + 0.1f);
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

    // Draw road lines
    glLineWidth(10);
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glBegin(GL_LINES);
    for (float i = -1.0f; i <= 1.0f; i += 0.2f) {
        glVertex2f(-0.2f, i);
        glVertex2f(-0.2f, i + 0.1f);
        glVertex2f(0.2f, i);
        glVertex2f(0.2f, i + 0.1f);
    }
    glEnd();

    // Draw zebra crossing
    glColor3f(0.0f, 1.0f, 0.0f); // White
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(0.6f, 0.2f);
    glVertex2f(0.55f, 0.4f);
    glVertex2f(-0.55f, 0.4f);
    glEnd();
    // glColor3f(0.0f, 0.0f, 0.0f); // White
    // glBegin(GL_QUADS);
    // glVertex2f(-0.6f, 0.2f);
    // glVertex2f(0.6f, 0.2f);
    // glVertex2f(0.6f, 0.4f);
    // glVertex2f(-0.6f, 0.4f);
    // glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(0.5f, 0.25f);
    glVertex2f(0.5f, 0.35f);
    glVertex2f(-0.5f, 0.35f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRoad();

    for (auto& car : cars) {
        drawCar(car.x, car.y);
    }

    glutSwapBuffers();
}

void update(int value) {
    for (auto& car : cars) {
        if (!car.isStopped) {
            car.y -= 0.02f;
            if (car.y < -1.0f) {
                car.y = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f)));
                car.lane = rand() % 3;
                car.x = -0.4f + car.lane * 0.4f;
                car.hasStopped = false; // reset flag
            }

            if (car.y < 0.4f && car.y > 0.2f && car.x > -0.6f && car.x < 0.6f &&!car.hasStopped) {
                car.isStopped = true;
                car.stopTime = glutGet(GLUT_ELAPSED_TIME);
                car.hasStopped = true; // set flag
            }
        } else {
            int currentTime = glutGet(GLUT_ELAPSED_TIME);
            if (currentTime - car.stopTime > 1000) {
                car.isStopped = false;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

int main(int argc, char** argv) {
    srand(time(NULL));

    for (int i = 0; i < 10; ++i) {
        cars.push_back({ -0.4f + (rand() % 3) * 0.4f, 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f))), rand() % 3, false, 0, false });
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Car Game");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutTimerFunc(50, update, 0);

    glutMainLoop();
    return 0;
}