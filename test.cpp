#include <GL/glut.h>

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Car dimensions and position
const float CAR_WIDTH = 0.1f;
const float CAR_HEIGHT = 0.2f;
const float CAR_POS_Y = -0.8f;  // Position of the car on the y-axis
float carPosX = 0.0f;  // Center lane

// Road dimensions
const float ROAD_WIDTH = 0.6f;
const float LANE_WIDTH = ROAD_WIDTH / 3;
float roadOffset = 0.0f;  // Used to animate the moving road

void drawSideOfRoad() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    // Left side
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-ROAD_WIDTH / 2, -1.0f);
    glVertex2f(-ROAD_WIDTH / 2, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    // Right side
    glVertex2f(ROAD_WIDTH / 2, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(ROAD_WIDTH / 2, 1.0f);
    glEnd();
}

void drawCar() {
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex2f(carPosX - CAR_WIDTH / 2, CAR_POS_Y - CAR_HEIGHT / 2);
    glVertex2f(carPosX + CAR_WIDTH / 2, CAR_POS_Y - CAR_HEIGHT / 2);
    glVertex2f(carPosX + CAR_WIDTH / 2, CAR_POS_Y + CAR_HEIGHT / 2);
    glVertex2f(carPosX - CAR_WIDTH / 2, CAR_POS_Y + CAR_HEIGHT / 2);
    glEnd();
}

void drawWhiteLines() {
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_LINES);
    // Left lane line
    glVertex2f(-LANE_WIDTH / 2, -1.0f);
    glVertex2f(-LANE_WIDTH / 2, 1.0f);
    // Right lane line
    glVertex2f(LANE_WIDTH / 2, -1.0f);
    glVertex2f(LANE_WIDTH / 2, 1.0f);
    glEnd();
}

void drawYellowLines() {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glBegin(GL_LINES);
    for (float i = -1.0f + roadOffset; i < 1.0f; i += 0.2f) {
        glVertex2f(-ROAD_WIDTH / 2, i);
        glVertex2f(ROAD_WIDTH / 2, i);
    }
    glEnd();
}

void drawRoad() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f); // Dark grey color for road
    glVertex2f(-ROAD_WIDTH / 2, -1.0f);
    glVertex2f(ROAD_WIDTH / 2, -1.0f);
    glVertex2f(ROAD_WIDTH / 2, 1.0f);
    glVertex2f(-ROAD_WIDTH / 2, 1.0f);
    glEnd();
}

void moveRoad() {
    roadOffset -= 0.02f;
    if (roadOffset < -0.2f) {
        roadOffset = 0.0f;
    }
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawSideOfRoad();
    drawRoad();
    drawWhiteLines();
    drawYellowLines();
    drawCar();

    glutSwapBuffers();
}

void initDisplay() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void timer(int) {
    moveRoad();
    glutPostRedisplay();  // Post a paint request to activate display()
    glutTimerFunc(16, timer, 0);  // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Car Racing Game");

    initDisplay();

    glutDisplayFunc(renderScene);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
