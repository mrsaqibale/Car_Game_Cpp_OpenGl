#include <GL/glut.h>

void drawBuilding(float x, float baseY, int stories) {
    float storyHeight = 0.2f;
    float buildingWidth = 0.2f;
    float roomWidth = buildingWidth / 2.0f;

    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the building

    // Draw the stories
    for (int i = 0; i < stories; ++i) {
        float y = baseY + i * storyHeight;

        // Draw the story rectangle
        glBegin(GL_QUADS);
        glVertex2f(x - buildingWidth / 2.0f, y);
        glVertex2f(x + buildingWidth / 2.0f, y);
        glVertex2f(x + buildingWidth / 2.0f, y + storyHeight);
        glVertex2f(x - buildingWidth / 2.0f, y + storyHeight);
        glEnd();

        // Draw the rooms within the story
        glColor3f(0.8f, 0.8f, 0.0f); // Slightly different color for room separation
        for (int j = 0; j < 2; ++j) {
            float roomX = x - buildingWidth / 2.0f + j * roomWidth;

            // Draw room separation lines
            glBegin(GL_LINES);
            glVertex2f(roomX, y);
            glVertex2f(roomX, y + storyHeight);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the first building with 4 stories
    drawBuilding(-0.5f, -0.8f, 4);

    // Draw the second building with 6 stories
    drawBuilding(0.5f, -0.8f, 6);

    glutSwapBuffers();
}

void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Light blue sky background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Building View");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
