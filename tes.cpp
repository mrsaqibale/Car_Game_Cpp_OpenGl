#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Car dimensions and position
const float CAR_WIDTH = 0.1f;
const float CAR_HEIGHT = 0.2f;
float carPosX = 0.0f;  // Center lane
float carPosY = -0.8f;  // Start near the bottom of the screen

// Road dimensions
const float ROAD_WIDTH = 0.6f;
const float LANE_WIDTH = ROAD_WIDTH / 3;
float roadOffset = 0.0f;  // Used to animate the moving road

// Other cars
const int NUM_CARS = 5;
float otherCars[NUM_CARS][2];  // Positions of other cars (x, y)

// Initialize random positions for other cars
void initOtherCars() {
    srand(time(0));
    for (int i = 0; i < NUM_CARS; ++i) {
        otherCars[i][0] = (rand() % 3 - 1) * LANE_WIDTH;  // -LANE_WIDTH, 0, or LANE_WIDTH
        otherCars[i][1] = rand() % 200 / 100.0f - 1.0f;  // Random y position between -1.0 and 1.0
    }
}

// Draw the green sides of the road
void drawSidesOfRoad() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-ROAD_WIDTH / 2, -1.0f);
    glVertex2f(-ROAD_WIDTH / 2, 1.0f);
    glVertex2f(-1.0f, 1.0f);

    glVertex2f(ROAD_WIDTH / 2, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(ROAD_WIDTH / 2, 1.0f);
    glEnd();
}

// Draw the road with three lanes
void drawRoad() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);  // Grey color for the road
    glVertex2f(-ROAD_WIDTH / 2, -1.0f);
    glVertex2f(ROAD_WIDTH / 2, -1.0f);
    glVertex2f(ROAD_WIDTH / 2, 1.0f);
    glVertex2f(-ROAD_WIDTH / 2, 1.0f);
    glEnd();
}

// Draw the white vertical lane dividers
void drawWhiteLines() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);  // White color
    glVertex2f(-LANE_WIDTH / 2, -1.0f);
    glVertex2f(-LANE_WIDTH / 2, 1.0f);
    glVertex2f(LANE_WIDTH / 2, -1.0f);
    glVertex2f(LANE_WIDTH / 2, 1.0f);
    glEnd();
}

// Draw the yellow horizontal lines to create the moving effect
void drawYellowLines() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color
    for (float i = -1.0f + roadOffset; i < 1.0f; i += 0.2f) {
        glVertex2f(-ROAD_WIDTH / 2, i);
        glVertex2f(ROAD_WIDTH / 2, i);
    }
    glEnd();
}

// Draw the player's car
void drawCar() {
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color for the car
    glVertex2f(carPosX - CAR_WIDTH / 2, carPosY - CAR_HEIGHT / 2);
    glVertex2f(carPosX + CAR_WIDTH / 2, carPosY - CAR_HEIGHT / 2);
    glVertex2f(carPosX + CAR_WIDTH / 2, carPosY + CAR_HEIGHT / 2);
    glVertex2f(carPosX - CAR_WIDTH / 2, carPosY + CAR_HEIGHT / 2);
    glEnd();
}

// Draw the other cars on the road
void drawOtherCars() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color for other cars
    for (int i = 0; i < NUM_CARS; ++i) {
        glVertex2f(otherCars[i][0] - CAR_WIDTH / 2, otherCars[i][1] - CAR_HEIGHT / 2);
        glVertex2f(otherCars[i][0] + CAR_WIDTH / 2, otherCars[i][1] - CAR_HEIGHT / 2);
        glVertex2f(otherCars[i][0] + CAR_WIDTH / 2, otherCars[i][1] + CAR_HEIGHT / 2);
        glVertex2f(otherCars[i][0] - CAR_WIDTH / 2, otherCars[i][1] + CAR_HEIGHT / 2);
    }
    glEnd();
}

// Update the positions of other cars
void updateOtherCars() {
    for (int i = 0; i < NUM_CARS; ++i) {
        otherCars[i][1] -= 0.01f;  // Move the car down
        if (otherCars[i][1] < -1.0f) {
            otherCars[i][1] = 1.0f;  // Reset position to the top
            otherCars[i][0] = (rand() % 3 - 1) * LANE_WIDTH;  // Random lane
        }
    }
}

// Render the entire scene
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawSidesOfRoad();
    drawRoad();
    drawWhiteLines();
    drawYellowLines();
    drawCar();
    drawOtherCars();

    glutSwapBuffers();
}

// Initialize display settings
void initDisplay() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// Handle keyboard input
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':  // Move left
            carPosX -= LANE_WIDTH;
            if (carPosX < -ROAD_WIDTH / 2 + LANE_WIDTH / 2) carPosX = -ROAD_WIDTH / 2 + LANE_WIDTH / 2;
            break;
        case 'd':  // Move right
            carPosX += LANE_WIDTH;
            if (carPosX > ROAD_WIDTH / 2 - LANE_WIDTH / 2) carPosX = ROAD_WIDTH / 2 - LANE_WIDTH / 2;
            break;
        case 'w':  // Move up
            carPosY += 0.1f;
            if (carPosY > 1.0f - CAR_HEIGHT / 2) carPosY = 1.0f - CAR_HEIGHT / 2;
            break;
        case 's':  // Move down
            carPosY -= 0.1f;
            if (carPosY < -1.0f + CAR_HEIGHT / 2) carPosY = -1.0f + CAR_HEIGHT / 2;
            break;
    }
}

// Timer function for animation
void timer(int) {
    roadOffset -= 0.02f;
    if (roadOffset < -0.2f) {
        roadOffset = 0.0f;
    }

    updateOtherCars();
    glutPostRedisplay();  // Post a paint request to activate display()
    glutTimerFunc(16, timer, 0);  // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Car Racing Game");

    initDisplay();
    initOtherCars();

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKeyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
