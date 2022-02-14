#include <stdlib.h>
#include <glut.h>
#include <GLUT.h>
#include <stdio.h>
#include <math.h>

// add const pi as float
float PI = 3.1415926535897932384626433832795;
float R_MAX = 200;
float H_MAX = 11;
float T_SCAN = 4;
float t = 18;

// ציור קוים
void drawLines() {
    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    glBegin(GL_LINES);
    glVertex3f(-200, 0, 0);
    glVertex3f(200, 0, 0);
    glVertex3f(0, -200, 0);
    glVertex3f(0, 200, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 11);
    glEnd();
}

// draw a circle by center, radius & segments
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * PI * float(i) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

// ציור עיגולים
void drawCircles() {
    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    for (int j = 50; j < 201; j = j + 50)
    {
        DrawCircle(0.0, 0.0, j, 72);
    }
}

// ציור קרן סריקה
void drawBeam() {
    glColor3f(1.0, 1.0, 1.0); // change color
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    float alpha = 0.2f * PI;
    float R = R_MAX * cosf(alpha);
    float z = R_MAX * sinf(alpha);
    // R_effective
    float theta = 2.0f * PI * float(t) / float(T_SCAN);//get the current angle
    float x = R * cosf(theta);//calculate the x component
    float y = R * sinf(theta);//calculate the y component
    glVertex3f(x, y, 0);
    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLines();
    drawCircles();
    drawBeam();

    glutSwapBuffers();
    glFlush();
}

void idle() {
    if (t < T_SCAN)
        t += (0.01);
    else
        t = 0;
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
    glutCreateWindow("אגם");
    Initialize();
    glutDisplayFunc(Draw);
    glutIdleFunc(idle);
//    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    glutMainLoop();
//    return 0;
}
