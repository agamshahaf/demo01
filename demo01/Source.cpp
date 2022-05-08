#include <stdlib.h>
#include <glut.h>
#include <GLUT.h>
#include <stdio.h>
#include <math.h>
#include <iostream>


float PI = 3.1415926535897932384626433832795;
float R_MAX = 200; // The longest radius
float H_MAX = 15; // The height
float T_SCAN = 4; // The time it takes for one scan (seconds)
int t = 0; // The t of idle
float d_elev = 0; // elev view angle
float d_hor_view = 0; // horizontal view angle
int old_t;
int rtc;
// for singel target
int t1_t0 = glutGet(GLUT_ELAPSED_TIME);
float beem_x, beem_y, beem_z;
float t1_x, t1_y, t1_z;
bool targetExist = true;


// Drawing axes X and Y (north, south, east, west)
void drawLines() {
    glLineWidth(3);
    //    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    glColor3f(0.9, 0.3, 0.1);
    glBegin(GL_LINES);
    glVertex3f(R_MAX, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glColor3f(0.7, 0.7, 0.1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(-R_MAX, 0, 0);
    glVertex3f(0, R_MAX, 0);
    glVertex3f(0, -R_MAX, 0);
    glEnd();
    glColor3f(0.0, 0.5, 0.9);
    glBegin(GL_LINES);
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

// Create and show one target function
void drawTarget() {
    glPushMatrix();
    float speed = 600;  //knots
    float direction = 0;//compass
    float x0 = -100;    //absolute
    float y0 = 50;      //absolute
    float z0 = 60000;   // feet
    float angle = PI * float(-direction) / 180.0;
    float target1_rate = speed / 3600000;
    t1_x = x0 + (target1_rate * cosf(angle)) * (rtc - t1_t0);
    t1_y = y0 + (target1_rate * sinf(angle)) * (rtc - t1_t0);
    t1_z = z0 * 0.000164579;
    if (pow(powf(t1_x, 2.0) + powf(t1_y, 2.0), 0.5) < 200) {
        glTranslatef(t1_x, t1_y, t1_z);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidSphere(2, 4, 2);
    }
    glPopMatrix();
}

void drawdiamond()
{
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);

    for (float alfa = 0; alfa <= 2.0 * PI; alfa += PI / 3)
    {
        float r_ = 5;
        glVertex3f(r_ * sin(alfa), r_ * cos(alfa), 30);//output vertex
        glVertex3f(r_ * sin(alfa + PI / 3), r_ * cos(alfa + PI / 3), 30);
        glVertex3f(0, 0, 40);
    }


    glEnd();
}

// Create all four circles using the DrawCircle function
void drawCircles() {
    glColor3f(0.007843137254902, 0.6274509803921569, 0.7725490196078431);
    for (int j = 50; j < 201; j = j + 50)
    {
        DrawCircle(0.0, 0.0, j, 72);
    }
}

// Drawing and creation Beam
void drawBeam() {
    glColor3f(1.0, 1.0, 1.0); // change color
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    int e_angle = t % 10; // elevation
    int h_angle = t / 10; // horizontal
    float alpha = (1 + e_angle) * 0.04f * PI;
    beem_z = R_MAX * sinf(alpha);
    float R = R_MAX * cosf(alpha);
    if (beem_z > H_MAX) {
        float r = R * sinf(alpha) / cosf(alpha);
        beem_z = H_MAX;
    }
    // R_effective
    float theta = 2.0f * PI * float(h_angle) / float(10 * T_SCAN);//get the current angle
    beem_x = R * cosf(theta);//calculate the x component
    beem_y = R * sinf(theta);//calculate the y component
    glVertex3f(beem_x, beem_y, beem_z);
    // find the eq from 0,0,0, to x,y,z
    // find distance between line and t1_x,t1_y,t1_z
    // if distance < Const - write to console
    glEnd();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(d_elev, 1, 0, 0); // point of view elevation
    glRotatef(d_hor_view, 0, 0, 1); // point of view horizontal

    drawLines();
    drawCircles();
    drawBeam();
    //glPushMatrix();
    //glTranslatef(20, 30, 0);
    //drawdiamond();
    //glPopMatrix();
    if (targetExist) {
        drawTarget();
    }

    glutSwapBuffers();
    glFlush();
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        if (d_elev == 78) {
            d_elev = 0;
        }
        else {
            if (d_elev > 78) {
                d_elev -= 0.5;
            }
        }
    }
    if (key == GLUT_KEY_DOWN) {
        if (d_elev == 0) {
            d_elev = 78;
        }
        else {
            if (d_elev < 90) {
                d_elev += 0.5;
            }
        }
    }
    if (key == GLUT_KEY_RIGHT) {
        if (d_hor_view < 90) {
            d_hor_view += 5.0;
        }
    }
    if (key == GLUT_KEY_LEFT) {
        if (d_hor_view > -90) {
            d_hor_view -= 5.0;
        }
    }
    if (key == GLUT_KEY_F1) {
        //int i;
        //std::cout << "Please enter an integer value: ";
        //std::cin >> i;
        //printf("\n the number entered =%d ", i);
        printf("target on ! \n");
        targetExist = true;
    }
    if (key == GLUT_KEY_F2) {
        printf("target off ! \n");
        targetExist = false;
    }

    glutPostRedisplay();
}

void idle() {
    int dt = 0;
    int new_t;
    while (dt < 10) {
        new_t = glutGet(GLUT_ELAPSED_TIME);
        dt = (new_t - old_t);
        //printf("new_t =%d \n", new_t);
    }
    old_t = new_t;
    if (t < 100 * T_SCAN)
        t += 1;
    else
        t = 0;
    rtc = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
}

void Initialize() {
    old_t = glutGet(GLUT_ELAPSED_TIME);
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
