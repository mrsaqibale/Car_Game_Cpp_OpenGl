// by mrsaqibale
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include<time.h>

#include "display.h"
#include "input.h"
#include "display.h"

using namespace std;
float carPosX = 0.0f;   
float carPosY = -0.8f;  
int lane = 1;           
int score = 0;
bool gameOver = false;

struct OtherCar {
    float posX;
    float posY;
    int lane;
};

vector<OtherCar> otherCars;




// write display function calls
void display(){
    Display obj;
    obj.display();
}
// write keyboar function calls
void keyboard(){
    Input obj;
    obj.keyboard(unsigned char, int , int);
}
int main(int argc, char** argv) {
    srand(time(NULL));
    otherCars.push_back({ -0.4f, 1.0f, 0 });
    otherCars.push_back({ 0.0f, 1.5f, 1 });
    otherCars.push_back({ 0.4f, 2.0f, 2 });

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Car Game");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    // glutTimerFunc(50, update, 0);
    // glutSpecialFunc(specialInput);
    // glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
// g++ -o outputs/final 01PlayGround.cpp  display.cpp -lGL -lGLU -lglut
