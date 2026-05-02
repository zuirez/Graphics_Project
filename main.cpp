#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.141516
float aspect = 1920.0f / 1080.0f;

// Modes: 0=Day, 1=Monsoon, 2=Night, 3=Winter, 4=Evening
int mode = 0;
float particleY[200];
float particleX[200];

// Global variables
float cloudOffset = 0.0f;
float fireTime = 0.0f;
float windTime = 0.0f;
float starX[150];
float starY[150];

// Day/Night Auto-Cycle Variables
bool autoCycle = true;
int cycleTimer = 0;
int cycleIndex = 0;
int dayNightCycle[] = {0, 4, 2};

GLubyte clamp(int value) {
    if (value > 255) return 255;
    if (value < 0) return 0;
    return (GLubyte)value;
}

float clampF(float value) {
    if (value > 1.0f) return 1.0f;
    if (value < 0.0f) return 0.0f;
    return value;
}

// Seasonal Colors
void colorLeaves(int mode) {
    if      (mode == 0) glColor3ub(80,  160,  50);
    else if (mode == 1) glColor3ub(50,  120,  40);
    else if (mode == 2) glColor3ub(20,   50,  20);
    else if (mode == 3) glColor3ub(210, 230, 245);
    else if (mode == 4) glColor3ub(180,  90,  20);
}

void colorLeavesHighlight(int mode) {
    if      (mode == 0) glColor3ub(110, 190,  70);
    else if (mode == 1) glColor3ub( 70, 150,  55);
    else if (mode == 2) glColor3ub( 30,  70,  30);
    else if (mode == 3) glColor3ub(235, 245, 255);
    else if (mode == 4) glColor3ub(220, 120,  30);
}

void colorBark(int mode) {
    if      (mode == 0) glColor3ub(101,  67,  33);
    else if (mode == 1) glColor3ub( 80,  50,  25);
    else if (mode == 2) glColor3ub( 40,  25,  10);
    else if (mode == 3) glColor3ub(130,  90,  60);
    else if (mode == 4) glColor3ub(120,  70,  25);
}

void colorGround(int mode, int shade) {
    if (mode == 0) {
        if      (shade == 0) glColor3ub( 34, 139,  34);
        else if (shade == 1) glColor3ub( 70, 170,  60);
        else                 glColor3ub( 20, 110,  20);
    } else if (mode == 1) {
        if      (shade == 0) glColor3ub( 25, 100,  25);
        else if (shade == 1) glColor3ub( 45, 130,  40);
        else                 glColor3ub( 15,  80,  15);
    } else if (mode == 2) {
        if      (shade == 0) glColor3ub(  8,  35,   8);
        else if (shade == 1) glColor3ub( 15,  50,  15);
        else                 glColor3ub(  5,  25,   5);
    } else if (mode == 3) {
        if      (shade == 0) glColor3ub(210, 225, 240);
        else if (shade == 1) glColor3ub(230, 240, 250);
        else                 glColor3ub(190, 210, 230);
    } else if (mode == 4) {
        if      (shade == 0) glColor3ub(100,  90,  20);
        else if (shade == 1) glColor3ub(130, 110,  30);
        else                 glColor3ub( 80,  70,  15);
    }
}

void colorHill(int mode, int shade) {
    if (mode == 0) {
        if      (shade == 0) glColor3ub(120, 200, 120);
        else if (shade == 1) glColor3ub(150, 220, 150);
        else                 glColor3ub(100, 180, 100);
    } else if (mode == 1) {
        if      (shade == 0) glColor3ub( 80, 140,  80);
        else if (shade == 1) glColor3ub(100, 160, 100);
        else                 glColor3ub( 60, 120,  60);
    } else if (mode == 2) {
        if      (shade == 0) glColor3ub( 20,  50,  20);
        else if (shade == 1) glColor3ub( 30,  65,  30);
        else                 glColor3ub( 15,  40,  15);
    } else if (mode == 3) {
        if      (shade == 0) glColor3ub(200, 220, 235);
        else if (shade == 1) glColor3ub(220, 235, 245);
        else                 glColor3ub(180, 205, 225);
    } else if (mode == 4) {
        if      (shade == 0) glColor3ub(160, 110,  40);
        else if (shade == 1) glColor3ub(190, 140,  60);
        else                 glColor3ub(140,  90,  30);
    }
}

void colorRiver(int mode) {
    if      (mode == 0) glColor3ub( 70, 130, 180);
    else if (mode == 1) glColor3ub( 50, 100, 140);
    else if (mode == 2) glColor3ub( 20,  40,  80);
    else if (mode == 3) glColor3ub(180, 210, 235);
    else if (mode == 4) glColor3ub(180, 100,  40);
}

void drawCircle(float p1, float q1, float r1) {
    int n = 40;
    float tp = 2 * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(p1, q1);
    for(int i = 0; i <= n; i++) {
        glVertex2f(p1 + r1*cos(i*tp/n), q1 + r1*sin(i*tp/n));
    }
    glEnd();
}

void drawTriangle(float x1,float y1,float x2,float y2,float x3,float y3){
    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}

void circleFuncSun(float p1, float q1, float r1, int R1, int G1, int B1) {
    int triangle = 100;
    float tp = 2 * PI;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(R1, G1, B1);
    glVertex2f(p1, q1);
    for (int i = 0; i <= triangle; i++) {
        float angle = i * tp / triangle;
        glVertex2f(p1 + (r1 * cos(angle) / aspect), q1 + (r1 * sin(angle)));
    }
    glEnd();
}

void circleFunc(float p1, float q1, float r1, int R, int G, int B) {
    int triangle = 100;
    float tp = 2 * PI;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(R, G, B);
    glVertex2f(p1, q1);
    for (int i = 0; i <= triangle; i++) {
        glVertex2f(p1 + (r1 * cos(i * tp / triangle)), q1 + (r1 * sin(i * tp / triangle)));
    }
    glEnd();
}

// Sun / Moon
void drawSunMoon(int mode) {
    if      (mode == 0) circleFuncSun(0.88f, 0.88f, 0.10f, 255, 255,   0);
    else if (mode == 1) circleFuncSun(0.88f, 0.88f, 0.10f, 180, 180, 170);
    else if (mode == 2) circleFuncSun(0.88f, 0.88f, 0.08f, 220, 230, 255);
    else if (mode == 3) circleFuncSun(0.88f, 0.88f, 0.09f, 240, 245, 255);
    else if (mode == 4) circleFuncSun(0.88f, 0.88f, 0.10f, 255, 94,  0);

    if (mode == 2) {
        glColor3ub(255, 255, 230);
        glPointSize(1.8f);
        glBegin(GL_POINTS);
        for(int i = 0; i < 150; i++) {
            glVertex2f(starX[i], starY[i]);
        }
        glEnd();
    }
}

// Clouds
void drawCloudShapes(int wR, int wG, int wB, int cR, int cG, int cB) {
    // Cloud 2
    circleFunc(0.03f,  0.75f, 0.04f, wR, wG, wB);
    circleFunc(0.115f, 0.79f, 0.07f, cR, cG, cB);
    circleFunc(0.10f,  0.79f, 0.07f, wR, wG, wB);
    circleFunc(0.19f,  0.80f, 0.03f, cR, cG, cB);
    circleFunc(0.18f,  0.80f, 0.03f, wR, wG, wB);
    circleFunc(0.21f,  0.75f, 0.05f, cR, cG, cB);
    circleFunc(0.20f,  0.75f, 0.05f, wR, wG, wB);
    circleFunc(0.12f,  0.73f, 0.06f, wR, wG, wB);
    circleFunc(0.06f,  0.71f, 0.03f, wR, wG, wB);

    // Cloud 3
    circleFunc(0.66f,  0.80f, 0.03f, wR, wG, wB);
    circleFunc(0.73f,  0.81f, 0.06f, cR, cG, cB);
    circleFunc(0.72f,  0.81f, 0.06f, wR, wG, wB);
    circleFunc(0.79f,  0.79f, 0.04f, cR, cG, cB);
    circleFunc(0.78f,  0.79f, 0.04f, wR, wG, wB);
    circleFunc(0.72f,  0.78f, 0.05f, wR, wG, wB);
    circleFunc(0.678f, 0.77f, 0.02f, wR, wG, wB);

    // Cloud 4
    circleFunc(-0.14f,  0.82f, 0.03f, wR, wG, wB);
    circleFunc(-0.07f,  0.84f, 0.06f, cR, cG, cB);
    circleFunc(-0.08f,  0.84f, 0.06f, wR, wG, wB);
    circleFunc(-0.01f,  0.81f, 0.04f, cR, cG, cB);
    circleFunc(-0.02f,  0.81f, 0.04f, wR, wG, wB);
    circleFunc(-0.08f,  0.80f, 0.05f, wR, wG, wB);
    circleFunc(-0.122f, 0.79f, 0.02f, wR, wG, wB);

    // Cloud 5
    circleFunc(-0.57f,  0.88f, 0.08f, cR, cG, cB);
    circleFunc(-0.58f,  0.88f, 0.08f, wR, wG, wB);
    circleFunc(-0.51f,  0.82f, 0.06f, cR, cG, cB);
    circleFunc(-0.52f,  0.82f, 0.06f, wR, wG, wB);
    circleFunc(-0.45f,  0.77f, 0.045f, cR, cG, cB);
    circleFunc(-0.46f,  0.77f, 0.045f, wR, wG, wB);
    circleFunc(-0.515f, 0.76f, 0.049f, cR, cG, cB);
    circleFunc(-0.525f, 0.76f, 0.049f, wR, wG, wB);
    circleFunc(-0.58f,  0.742f,0.058f, wR, wG, wB);
    circleFunc(-0.67f,  0.742f,0.058f, wR, wG, wB);
    circleFunc(-0.71f,  0.745f,0.045f, wR, wG, wB);
    circleFunc(-0.695f, 0.79f, 0.025f, wR, wG, wB);
    circleFunc(-0.66f,  0.82f, 0.05f,  wR, wG, wB);
    circleFunc(-0.58f,  0.78f, 0.06f,  wR, wG, wB);
}

void drawClouds(int mode) {
    int wR, wG, wB, cR, cG, cB;

    if (mode == 0) {
        wR=255; wG=255; wB=255;
        cR=102; cG=178; cB=255;
    } else if (mode == 1) {
        wR=130; wG=135; wB=140;
        cR= 90; cG= 95; cB=105;
    } else if (mode == 2) {
        wR= 40; wG= 50; wB= 70;
        cR= 25; cG= 30; cB= 50;
    } else if (mode == 3) {
        wR=210; wG=220; wB=230;
        cR=170; cG=185; cB=200;
    } else {
        wR=255; wG=180; wB=120;
        cR=240; cG=130; cB= 80;
    }

    glPushMatrix();
    glTranslatef(cloudOffset, 0.0f, 0.0f);
    drawCloudShapes(wR, wG, wB, cR, cG, cB);
    glTranslatef(2.0f, 0.0f, 0.0f);
    drawCloudShapes(wR, wG, wB, cR, cG, cB);
    glPopMatrix();
}


void drawEnvironment(int mode) {
    // hills
    colorHill(mode, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.1f, 0.25f);
    glVertex2f( 0.1f, 0.45f);
    glVertex2f( 0.3f, 0.6f);
    glVertex2f( 0.5f, 0.45f);
    glVertex2f( 0.7f, 0.25f);
    glVertex2f( 0.9f, 0.0f);
    glEnd();

    colorHill(mode, 1);
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 0.6f);
    glVertex2f(0.5f, 0.45f);
    glVertex2f(0.7f, 0.25f);
    glVertex2f(0.9f, 0.0f);
    glEnd();

    colorHill(mode, 2);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.45f, 0.2f);
    glVertex2f(-0.3f, 0.35f);
    glVertex2f(-0.15f, 0.2f);
    glVertex2f( 0.0f, 0.0f);
    glEnd();

    colorHill(mode, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, 0.35f);
    glVertex2f(-0.15f, 0.2f);
    glVertex2f( 0.0f, 0.0f);
    glEnd();

    colorHill(mode, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(-0.85f, 0.25f);
    glVertex2f(-0.7f, 0.45f);
    glVertex2f(-0.55f, 0.3f);
    glVertex2f(-0.4f, 0.0f);
    glEnd();

    colorHill(mode, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, 0.45f);
    glVertex2f(-0.55f, 0.3f);
    glVertex2f(-0.4f, 0.0f);
    glEnd();

    colorHill(mode, 2);
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.6f, 0.5f);
    glVertex2f(0.8f, 0.3f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    colorHill(mode, 1);
    glBegin(GL_POLYGON);
    glVertex2f(0.6f, 0.5f);
    glVertex2f(0.8f, 0.3f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    // river
    colorRiver(mode);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.62f, 0.0f);
    glVertex2f( 0.18f, -0.3f);
    glVertex2f( 0.4f,  0.0f);
    glEnd();

    // field
    colorGround(mode, 2);
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f,  0.45f);
    glVertex2f(0.8f,  0.35f);
    glVertex2f(0.6f,  0.2f);
    glVertex2f(0.4f,  0.0f);
    glEnd();

    colorGround(mode, 0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f(-1.0f,-1.0f);
    glEnd();

    colorGround(mode, 1);
    glBegin(GL_POLYGON);
    glVertex2f( 0.4f, -0.3f);
    glVertex2f( 0.2f, -0.2f);
    glVertex2f( 0.0f, -0.15f);
    glVertex2f(-0.4f,  0.0f);
    glVertex2f(-0.6f,  0.1f);
    glVertex2f(-0.8f,  0.2f);
    glVertex2f(-1.0f,  0.25f);
    glVertex2f(-1.0f, -0.3f);
    glVertex2f( 0.4f, -0.3f);
    glEnd();
}

// fire glow
void drawFireGlow(float cx, float cy) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int n = 60;
    float tp = 2 * PI;

    float rx = 0.82f, ry = 0.35f;
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.6f, 0.7f, 0.1f, 0.0f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= n; i++) {
        float angle = i * tp / n;
        glColor4f(0.6f, 0.7f, 0.1f, 0.0f);
        glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
    }
    glEnd();

    rx = 0.63f; ry = 0.32f;
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.9f, 0.75f, 0.1f, 0.10f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= n; i++) {
        float angle = i * tp / n;
        glColor4f(0.7f, 0.65f, 0.05f, 0.0f);
        glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
    }
    glEnd();

    rx = 0.44f; ry = 0.19f;
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 0.80f, 0.1f, 0.18f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= n; i++) {
        float angle = i * tp / n;
        glColor4f(0.9f, 0.70f, 0.05f, 0.0f);
        glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
    }
    glEnd();

    rx = 0.20f; ry = 0.08f;
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 0.85f, 0.2f, 0.28f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= n; i++) {
        float angle = i * tp / n;
        glColor4f(1.0f, 0.75f, 0.1f, 0.0f);
        glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
    }
    glEnd();

    rx = 0.08f; ry = 0.04f;
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 0.90f, 0.4f, 0.40f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= n; i++) {
        float angle = i * tp / n;
        glColor4f(1.0f, 0.80f, 0.2f, 0.0f);
        glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
    }
    glEnd();

    glDisable(GL_BLEND);
}

// tent
void drawTent(int mode) {
    if      (mode == 0) glColor3ub(217, 207, 23);
    else if (mode == 1) glColor3ub(180, 165,  0);
    else if (mode == 2) glColor3ub( 70,  60,  0);
    else if (mode == 3) glColor3ub(200, 190, 120);
    else if (mode == 4) glColor3ub(235, 160,  0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.45f);
    glVertex2f(-0.81f, -0.76f);
    glVertex2f(-0.78f, -0.75f);
    glEnd();

    if      (mode == 0) glColor3ub(240, 220,  0);
    else if (mode == 1) glColor3ub(180, 165,  0);
    else if (mode == 2) glColor3ub( 90,  80,  0);
    else if (mode == 3) glColor3ub(220, 210, 140);
    else if (mode == 4) glColor3ub(255, 180,  0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.45f);
    glVertex2f(-0.79f, -0.79f);
    glVertex2f(-0.58f, -0.80f);
    glVertex2f(-0.5f,  -0.40f);
    glEnd();

    if      (mode == 0) glColor3ub(255, 235,  20);
    else if (mode == 1) glColor3ub(200, 185,  10);
    else if (mode == 2) glColor3ub(227, 224, 70);
    else if (mode == 3) glColor3ub(235, 225, 160);
    else if (mode == 4) glColor3ub(255, 200,  20);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.40f);
    glVertex2f(-0.58f,-0.79f);
    glVertex2f(-0.5f, -0.77f);
    glEnd();

    if      (mode == 0) glColor3ub(255, 245,  50);
    else if (mode == 1) glColor3ub(215, 200,  20);
    else if (mode == 2) glColor3ub(207, 204, 64);
    else if (mode == 3) glColor3ub(245, 240, 180);
    else if (mode == 4) glColor3ub(255, 215,  40);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.40f);
    glVertex2f(-0.5f, -0.76f);
    glVertex2f(-0.4f, -0.76f);
    glEnd();

    glLineWidth(2.0f);
    glColor3ub(180, 180, 180);
    glBegin(GL_LINES);
    glVertex2f(-0.4f,   -0.76f); glVertex2f(-0.4f,   -0.74f);
    glVertex2f(-0.582f, -0.80f); glVertex2f(-0.582f, -0.78f);
    glVertex2f(-0.79f,  -0.79f); glVertex2f(-0.79f,  -0.77f);
    glVertex2f(-0.81f,  -0.76f); glVertex2f(-0.81f,  -0.74f);
    glEnd();
}

void madeByNijhum(int mode) {

    // left tent
    drawTent(mode);

    // right tent
    glPushMatrix();
    glTranslatef(-0.30f, 0.0f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
    drawTent(mode);
    glPopMatrix();

    // log
    colorBark(mode);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f,   -0.60f);
    glVertex2f(-0.395f, -0.68f);
    glVertex2f(-0.22f,  -0.65f);
    glVertex2f(-0.225f, -0.57f);
    glEnd();

    if (mode == 2) glColor3ub(60, 40, 15);
    else           glColor3ub(150, 80, 20);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f,   -0.60f);
    glVertex2f(-0.395f, -0.68f);
    glVertex2f(-0.394f, -0.65f);
    glVertex2f(-0.397f, -0.68f);
    glVertex2f(-0.397f, -0.60f);
    glEnd();

    if (mode == 2) glColor3ub(60, 40, 15);
    else           glColor3ub(150, 80, 20);
    glBegin(GL_POLYGON);
    glVertex2f(-0.225f, -0.60f);
    glVertex2f(-0.221f, -0.65f);
    glVertex2f(-0.224f, -0.64f);
    glVertex2f(-0.223f, -0.65f);
    glVertex2f(-0.222f, -0.57f);
    glEnd();

    glLineWidth(8.0f);
    colorBark(mode);
    glBegin(GL_LINES);
    glVertex2f(-0.35f, -0.60f);
    glVertex2f(-0.33f, -0.57f);
    glEnd();

    // stones
    circleFunc(-0.32f, -0.78f, 0.045f, 90, 90, 90);
    circleFunc(-0.29f, -0.765f, 0.013f, 120, 120, 120);
    circleFunc(-0.32f, -0.755f, 0.012f, 130, 130, 130);
    circleFunc(-0.35f, -0.765f, 0.013f, 110, 110, 110);
    circleFunc(-0.36f, -0.785f, 0.011f, 125, 125, 125);
    circleFunc(-0.34f, -0.796f, 0.013f, 115, 115, 115);
    circleFunc(-0.30f, -0.796f, 0.012f, 120, 120, 120);
    circleFunc(-0.28f, -0.783f, 0.011f, 118, 118, 118);

    // wood
    colorBark(mode);
    glBegin(GL_POLYGON);
    glVertex2f(-0.355f, -0.790f);
    glVertex2f(-0.285f, -0.790f);
    glVertex2f(-0.285f, -0.778f);
    glVertex2f(-0.355f, -0.778f);
    glEnd();

    glLineWidth(5.0f);
    colorBark(mode);
    glBegin(GL_LINES);
    glVertex2f(-0.36f,  -0.795f);
    glVertex2f(-0.29f,  -0.770f);
    glVertex2f(-0.285f, -0.795f);
    glVertex2f(-0.355f, -0.770f);
    glEnd();

    if (mode != 0 && mode != 1 && mode != 4) {
        if (mode == 2 || mode == 3) {
            drawFireGlow(-0.32f, -0.790f);
        }

        // flame
        glPushMatrix();
        glTranslatef(-0.32f, -0.778f, 0.0f);

        float fireScaleY = 1.0f + 0.12f * sin(fireTime) + 0.06f * cos(fireTime * 2.3f);
        glScalef(1.0f, fireScaleY, 1.0f);

        glTranslatef(0.32f, 0.778f, 0.0f);

        glColor3ub(180, 60, 0);
        circleFunc(-0.32f, -0.780f, 0.022f, 180, 60, 0);

        glColor3ub(255, 120, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.335f, -0.778f);
        glVertex2f(-0.305f, -0.778f);
        glVertex2f(-0.315f, -0.748f);
        glVertex2f(-0.320f, -0.738f);
        glVertex2f(-0.325f, -0.748f);
        glEnd();

        glColor3ub(255, 80, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.340f, -0.778f);
        glVertex2f(-0.320f, -0.778f);
        glVertex2f(-0.328f, -0.758f);
        glVertex2f(-0.336f, -0.750f);
        glEnd();

        glColor3ub(255, 100, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.320f, -0.778f);
        glVertex2f(-0.300f, -0.778f);
        glVertex2f(-0.308f, -0.758f);
        glVertex2f(-0.304f, -0.752f);
        glEnd();

        glColor3ub(255, 220, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.330f, -0.778f);
        glVertex2f(-0.310f, -0.778f);
        glVertex2f(-0.316f, -0.758f);
        glVertex2f(-0.320f, -0.750f);
        glVertex2f(-0.324f, -0.758f);
        glEnd();

        circleFunc(-0.32f, -0.768f, 0.007f, 255, 255, 200);

        glLineWidth(1.5f);
        if (mode == 2 || mode == 4) glColor3ub(140, 140, 140);
        else                        glColor3ub(200, 200, 200);
        glEnable(GL_LINE_SMOOTH);
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.320f, -0.738f);
        glVertex2f(-0.316f, -0.725f);
        glVertex2f(-0.323f, -0.712f);
        glVertex2f(-0.318f, -0.700f);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.324f, -0.742f);
        glVertex2f(-0.330f, -0.728f);
        glVertex2f(-0.325f, -0.714f);
        glEnd();

        glPopMatrix();
    }
}

// watch tower
void drawWatchTower(float x, float y, float s, int mode) {
    float woodR, woodG, woodB;
    float woodDR, woodDG, woodDB;
    if (mode == 0) {
        woodR=0.45f;
        woodG=0.28f;
        woodB=0.14f;
        woodDR=0.25f;
        woodDG=0.15f;
        woodDB=0.08f;
    }
    else if (mode == 1) {
        woodR=0.35f;
        woodG=0.20f;
        woodB=0.10f;
        woodDR=0.18f;
        woodDG=0.10f;
        woodDB=0.05f;
    }
    else if (mode == 2) {
        woodR=0.10f;
        woodG=0.06f;
        woodB=0.03f;
        woodDR=0.05f;
        woodDG=0.03f;
        woodDB=0.01f;
    }
    else if (mode == 3) {
        woodR=0.55f;
        woodG=0.50f;
        woodB=0.45f;
        woodDR=0.35f;
        woodDG=0.30f;
        woodDB=0.28f;
    }
    else {
        woodR=0.55f;
        woodG=0.30f;
        woodB=0.10f;
        woodDR=0.30f;
        woodDG=0.15f;
        woodDB=0.05f;
    }

    glBegin(GL_QUADS);
        glColor3f(woodR, woodG, woodB);
        glVertex2f(x-0.07f*s, y);
        glVertex2f(x-0.05f*s, y);
        glVertex2f(x-0.05f*s, y+0.25f*s);
        glVertex2f(x-0.07f*s, y+0.25f*s);

        glColor3f(woodR*0.8f, woodG*0.8f, woodB*0.8f);
        glVertex2f(x+0.05f*s, y);
        glVertex2f(x+0.07f*s, y);
        glVertex2f(x+0.07f*s, y+0.25f*s);
        glVertex2f(x+0.05f*s, y+0.25f*s);
    glEnd();

    glColor3f(woodR*0.9f, woodG*0.9f, woodB*0.9f);
    glBegin(GL_QUADS);
        glVertex2f(x-0.08f*s, y+0.05f*s);
        glVertex2f(x+0.08f*s, y+0.05f*s);
        glVertex2f(x+0.08f*s, y+0.07f*s);
        glVertex2f(x-0.08f*s, y+0.07f*s);
        glVertex2f(x-0.08f*s, y+0.15f*s);
        glVertex2f(x+0.08f*s, y+0.15f*s);
        glVertex2f(x+0.08f*s, y+0.17f*s);
        glVertex2f(x-0.08f*s, y+0.17f*s);
    glEnd();

    glLineWidth(3.0f);
    glColor3f(woodDR, woodDG, woodDB);
    glBegin(GL_LINES);
        glVertex2f(x-0.05f*s, y+0.07f*s);
        glVertex2f(x+0.05f*s, y+0.15f*s);
        glVertex2f(x-0.05f*s, y+0.15f*s);
        glVertex2f(x+0.05f*s, y+0.07f*s);
        glVertex2f(x-0.05f*s, y+0.17f*s);
        glVertex2f(x+0.05f*s, y+0.24f*s);
        glVertex2f(x-0.05f*s, y+0.24f*s);
        glVertex2f(x+0.05f*s, y+0.17f*s);
    glEnd();

    glColor3f(woodR*0.7f, woodG*0.7f, woodB*0.7f);
    glBegin(GL_QUADS);
        glVertex2f(x-0.10f*s, y+0.23f*s);
        glVertex2f(x+0.10f*s, y+0.23f*s);
        glVertex2f(x+0.10f*s, y+0.25f*s);
        glVertex2f(x-0.10f*s, y+0.25f*s);
    glEnd();

    glColor3f(woodR+0.1f, woodG+0.1f, woodB+0.08f);
    glBegin(GL_QUADS);
        glVertex2f(x-0.10f*s, y+0.25f*s);
        glVertex2f(x+0.10f*s, y+0.25f*s);
        glVertex2f(x+0.10f*s, y+0.27f*s);
        glVertex2f(x-0.10f*s, y+0.27f*s);
    glEnd();

    glColor3f(woodR*0.9f, woodG*0.9f, woodB*0.9f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        for(float lx = -0.09f; lx <= 0.09f; lx += 0.025f) {
            glVertex2f(x+lx*s, y+0.27f*s);
            glVertex2f(x+lx*s, y+0.32f*s);
        }
        glVertex2f(x-0.10f*s, y+0.32f*s);
        glVertex2f(x+0.10f*s, y+0.32f*s);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(woodR, woodG, woodB);
        glVertex2f(x-0.08f*s, y+0.32f*s);
        glVertex2f(x-0.06f*s, y+0.32f*s);
        glVertex2f(x-0.06f*s, y+0.35f*s);
        glVertex2f(x-0.08f*s, y+0.35f*s);

        glColor3f(woodR*0.8f, woodG*0.8f, woodB*0.8f);
        glVertex2f(x+0.06f*s, y+0.32f*s);
        glVertex2f(x+0.08f*s, y+0.32f*s);
        glVertex2f(x+0.08f*s, y+0.35f*s);
        glVertex2f(x+0.06f*s, y+0.35f*s);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(woodR+0.05f, woodG+0.02f, woodB+0.02f);
        glVertex2f(x-0.12f*s, y+0.35f*s);
        glVertex2f(x,         y+0.35f*s);
        glVertex2f(x,         y+0.40f*s);

        glColor3f(woodR*0.7f, woodG*0.7f, woodB*0.7f);
        glVertex2f(x,         y+0.35f*s);
        glVertex2f(x+0.12f*s, y+0.35f*s);
        glVertex2f(x,         y+0.40f*s);
    glEnd();

    glColor3f(woodDR, woodDG, woodDB);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x-0.04f*s, y);
        glVertex2f(x-0.04f*s, y+0.25f*s);
        glVertex2f(x-0.01f*s, y);
        glVertex2f(x-0.01f*s, y+0.25f*s);
        for(float ly = 0.02f; ly < 0.25f; ly += 0.025f) {
            glVertex2f(x-0.04f*s, y+ly*s);
            glVertex2f(x-0.01f*s, y+ly*s);
        }
    glEnd();
}


// tree
void drawTree(float x, float y, float s, int mode) {
    float windX = 0.0f;
    if (mode == 1) {
        windX = 0.002f * sin(windTime + x * 10.0f) + 0.001f * cos(windTime * 1.5f);
    }

    colorLeaves(mode);
    drawCircle(x - 0.10*s + windX, y + 0.35*s, 0.13*s);

    colorLeavesHighlight(mode);
    drawCircle(x - 0.01*s + windX, y + 0.56*s, 0.13*s);
    drawCircle(x + 0.10*s + windX, y + 0.49*s, 0.10*s);
    drawCircle(x - 0.08*s + windX, y + 0.38*s, 0.13*s);
    drawCircle(x + 0.08*s + 0.02*s + windX, y + 0.35*s, 0.13*s);

    colorBark(mode);
    drawTriangle(x, y + 0.5*s, x - 0.02*s, y, x + 0.02*s, y);

    float midY = y + 0.2*s;
    drawTriangle(x, midY + 0.03*s, x, midY - 0.03*s, x + 0.08*s, y + 0.35*s);
    drawTriangle(x, midY + 0.03*s, x, midY - 0.03*s, x - 0.08*s, y + 0.33*s);
}

void drawTree2(float x, float y, float s, int mode) {
    float windX = 0.0f;
    if (mode == 1) {
        windX = 0.002f * sin(windTime + x * 10.0f) + 0.001f * cos(windTime * 1.5f);
    }

    colorLeaves(mode);
    drawCircle(x - 0.02*s + windX, y + 0.52*s, 0.18*s);
    drawCircle(x + 0.10*s + windX, y + 0.33*s, 0.15*s);
    drawCircle(x - 0.12*s + windX, y + 0.36*s, 0.16*s);
    drawCircle(x - 0.22*s + windX, y + 0.20*s, 0.12*s);

    colorLeavesHighlight(mode);
    drawCircle(x + 0.02*s + windX, y + 0.56*s, 0.18*s);
    drawCircle(x + 0.14*s + windX, y + 0.37*s, 0.15*s);
    drawCircle(x - 0.08*s + windX, y + 0.40*s, 0.16*s);
    drawCircle(x - 0.18*s + windX, y + 0.24*s, 0.12*s);

    colorBark(mode);
    drawTriangle(x, y + 0.60*s, x - 0.03*s, y, x + 0.03*s, y);
    drawTriangle(x, y + 0.20*s, x, y + 0.12*s, x - 0.19*s, y + 0.26*s);
}

void drawTrees(int mode) {
    drawTree( 0.11, -0.50, 0.75, mode);
    drawTree( 0.95, -0.90, 0.90, mode);
    drawTree(-0.97, -0.75, 1.25, mode);
    drawTree(-0.50,  0.19, 0.15, mode);
    drawTree(-0.15,  0.19, 0.11, mode);
    drawTree( 0.40,  0.40, 0.11, mode);

    drawTree2(-0.50, -0.35, 0.45, mode);
    drawTree2( 0.45, -0.20, 0.50, mode);
    drawTree2(-0.40,  0.14, 0.15, mode);
    drawTree2( 0.10,  0.12, 0.15, mode);
    drawTree2( 0.80, -0.30, 0.65, mode);
}


// weather
void drawWeather(int mode) {
    if (mode == 1) {
        glColor3ub(150, 160, 220);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        for(int i = 0; i < 200; i++) {
            glVertex2f(particleX[i], particleY[i]);
            glVertex2f(particleX[i] + 0.015f, particleY[i] - 0.08f);
        }
        glEnd();
    } else if (mode == 3) {
        glColor3ub(255, 255, 255);
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        for(int i = 0; i < 200; i++) {
            glVertex2f(particleX[i], particleY[i]);
        }
        glEnd();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '1': mode = 0; autoCycle = false; break;
        case '2': mode = 1; autoCycle = false; break;
        case '3': mode = 2; autoCycle = false; break;
        case '4': mode = 3; autoCycle = false; break;
        case '5': mode = 4; autoCycle = false; break;
        case 'c':
        case 'C': autoCycle = !autoCycle; break;
    }
    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1);
    for(int i = 0; i < 200; i++) {
        particleY[i] = (rand() % 200) / 100.0 - 1;
        particleX[i] = (rand() % 200) / 100.0 - 1;
    }

    for(int i = 0; i < 150; i++) {
        starX[i] = (rand() % 200) / 100.0f - 1.0f;
        starY[i] = (rand() % 100) / 100.0f + 0.2f;
    }
}

void update(int value) {
    cloudOffset -= 0.0004f;
    if (cloudOffset <= -2.0f) {
        cloudOffset += 2.0f;
    }

    fireTime += 0.1f;
    windTime += 0.04f;

    if (autoCycle) {
        cycleTimer++;
        if (cycleTimer > 300) {
            cycleIndex = (cycleIndex + 1) % 3;
            mode = dayNightCycle[cycleIndex];
            cycleTimer = 0;
        }
    }

    for(int i = 0; i < 200; i++) {
        if (mode == 1) {
            particleY[i] -= 0.025f;
        } else if (mode == 3) {
            particleY[i] -= 0.005f;
            particleX[i] += 0.002f * sin(particleY[i] * 10.0f);

            if(particleX[i] >  1.0f) particleX[i] = -1.0f;
            if(particleX[i] < -1.0f) particleX[i] =  1.0f;
        }

        if(particleY[i] < -1.0f) {
            particleY[i] = 1.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void display() {
    if      (mode == 0) glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    else if (mode == 1) glClearColor(0.38f, 0.44f, 0.52f, 1.0f);
    else if (mode == 2) glClearColor(0.05f, 0.08f, 0.18f, 1.0f);
    else if (mode == 3) glClearColor(0.72f, 0.82f, 0.90f, 1.0f);
    else if (mode == 4) glClearColor(0.95f, 0.55f, 0.20f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    drawSunMoon(mode);
    drawClouds(mode);
    drawEnvironment(mode);
    drawWatchTower(0.3f, -0.2f, 1.0f, mode);
    madeByNijhum(mode);
    drawTrees(mode);
    drawWeather(mode);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Dynamic Camping Scenario");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
