﻿#include <stdlib.h>
#include <glut.h>
#include <GLUT.h>
#include <stdio.h>
#include <math.h>

float PI = 3.1415926535897932384626433832795;
float R_MAX = 200;
float H_MAX = 50;
float T_SCAN = 4;
int t = 0;
float d_elev = 0;

// öéåø ÷åéí
void drawLines() {
    glLineWidth(3);
    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    glBegin(GL_LINES);
    glVertex3f(R_MAX, 0, 0);
    glVertex3f(-R_MAX, 0, 0);
    glVertex3f(0, R_MAX, 0);
    glVertex3f(0, -R_MAX, 0);
    glVertex3f(0, 0, H_MAX);
    glVertex3f(0, 0, 0);
    glEnd();
    glLineWidth(1);
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

// öéåø òéâåìéí
void drawCircles() {
    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    for (int j = 50; j < 201; j = j + 50)
    {
        DrawCircle(0.0, 0.0, j, 72);
    }
}

// öéåø ÷øï ñøé÷ä
void drawBeam() {
    glColor3f(1.0, 1.0, 1.0); // change color
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    int e_angle = t % 10; // elevation
    int h_angle = t / 10; // horizontal
    float alpha = (1 + e_angle) * 0.04f * PI;
    float z = R_MAX * sinf(alpha);
    float R = R_MAX * cosf(alpha);
    if (z > H_MAX) {
        float r = R * sinf(alpha) / cosf(alpha);
        z = H_MAX;
    }
    // R_effective
    float theta = 2.0f * PI * float(h_angle) / float(10 * T_SCAN);//get the current angle
    float x = R * cosf(theta);//calculate the x component
    float y = R * sinf(theta);//calculate the y component
    glVertex3f(x, y, z);
    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(d_elev, 1, 0, 0); // point of view

    drawLines();
    drawCircles();
    drawBeam();

    glutSwapBuffers();
    glFlush();
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        if (d_elev == 80) {
            d_elev = 0;
        }
        else {
            if (d_elev > 80) {
                d_elev -= 1;
            }
        }
    }
    if (key == GLUT_KEY_DOWN) {
        if (d_elev == 0) {
            d_elev = 80;
        }
        else {
            if (d_elev < 90) {
                d_elev += 1;
            }
        }
    }
    glutPostRedisplay();
}

void idle() {
    if (t < 100 * T_SCAN)
        t += 1;
    else
        t = 0;
    glutPostRedisplay();
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(250.0, -250.0, 250.0, -250.0, 250.0, -250.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int iArgc, char** cppArgv) {
    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Agam");
    Initialize();
    glutDisplayFunc(Draw);
    glutIdleFunc(idle);
    //    glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(SpecialKeys);

    glClear(GL_COLOR_BUFFER_BIT);

    glutMainLoop();
    //    return 0;
}
