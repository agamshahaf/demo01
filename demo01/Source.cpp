#include <stdlib.h>
#include <glut.h>
#include <GLUT.h>
#include <stdio.h>
#include <math.h>

// add const pi as float

// draw a circle by center, radius & segments
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}


void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    // draw lines
    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    glBegin(GL_LINES);
    glVertex3f(200, 0, 0);
    glVertex3f(-200, 0, 0);
    glVertex3f(0, 200, 0);
    glVertex3f(0, -200, 0);
    glVertex3f(0, 0, 15);
    glVertex3f(0, 0, 0);
    glEnd();
    // draw circles
    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    for (int j = 50; j < 201; j = j + 50)
    {
        DrawCircle(0.0, 0.0, j, 72);
    }
    // draw beam
    //glColor3f(0.0, 1.0, 0.0); - change color
    //glBegin(GL_LINES);
    //glVertex3f(0, 0, 0);
   // glVertex3f(0, 0, 0);
   // glEnd();


    glFlush();
}

void idle() {
    // t
    glutPostRedisplay();
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-250.0, 250.0, -250.0, 250.0, 0.0,15.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int iArgc, char** cppArgv) {
    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("авн");
    Initialize();
    glutDisplayFunc(Draw);
    glClear(GL_COLOR_BUFFER_BIT);

    glutMainLoop();
    return 0;
}
