#include<GL/glut.h>
#include<input.h>

void Input::keyboard(unsigned char key, int x, int y) {
    if (gameOver) {
        if (key == 13) { // ASCII value for Enter key
            gameOver = false;
            score = 0;
            carPosX = 0.0f;
            carPosY = -0.8f;
            otherCars.clear();
            otherCars.push_back({ -0.4f, 1.0f, 0 });
            otherCars.push_back({ 0.0f, 1.5f, 1 });
            otherCars.push_back({ 0.4f, 2.0f, 2 });
            glutPostRedisplay();
            glutTimerFunc(50, update, 0);
        } else if (key == 27) { // ASCII value for Escape key
            exit(0);
        }
    }
}