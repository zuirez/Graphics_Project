#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.141516
float aspect = 1920.0f / 1080.0f;

// 0 = Day, 1 = Monsoon, 2 = Night, 3 = Winter, 4 = Spring
int mode = 0;
float particleY[200];
float particleX[200];


// ==========================================================
// COLOR CLAMPING HELPERS (Prevents colors from breaking)
// ==========================================================
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

// ==========================================================
// COLOR TINTING HELPERS
// Automatically changes the season based on the mode!
// ==========================================================
void setTintColor(GLubyte r, GLubyte g, GLubyte b, int mode) {
    if (mode == 0) {
        glColor3ub(r, g, b); // Day - Normal Color
    }
    else if (mode == 1) {
        glColor3ub(r * 0.7, g * 0.75, b * 0.8); // Monsoon - Gray/Darker
    }
    else if (mode == 2) {
        glColor3ub(r * 0.25, g * 0.3, b * 0.45); // Night - Very Dark Blue tint
    }
    else if (mode == 3) {
        // Winter - Blend 75% toward pure white to simulate snow frost
        glColor3ub(clamp(r + (255 - r) * 0.75), clamp(g + (255 - g) * 0.75), clamp(b + (255 - b) * 0.85));
    }
    else if (mode == 4) {
        // Spring - Vibrant, slightly warmer colors
        glColor3ub(clamp(r * 1.15), clamp(g * 1.25), clamp(b * 0.95));
    }
}

void setTintColorF(float r, float g, float b, int mode) {
    if (mode == 0) glColor3f(r, g, b);
    else if (mode == 1) glColor3f(r * 0.7f, g * 0.75f, b * 0.8f);
    else if (mode == 2) glColor3f(r * 0.25f, g * 0.3f, b * 0.45f);
    else if (mode == 3) glColor3f(clampF(r + (1.0f - r) * 0.75f), clampF(g + (1.0f - g) * 0.75f), clampF(b + (1.0f - b) * 0.85f));
    else if (mode == 4) glColor3f(clampF(r * 1.15f), clampF(g * 1.25f), clampF(b * 0.95f));
}


// ==========================================================
// SHAPE HELPERS
// ==========================================================
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


// ==========================================================
// SCENE OBJECTS
// ==========================================================
void drawSunMoon(int mode) {
    if (mode == 0) circleFuncSun(0.88f, 0.88f, 0.1f, 255, 255, 0); // Day Sun
    else if (mode == 1) circleFuncSun(0.88f, 0.88f, 0.1f, 180, 180, 170); // Monsoon Sun
    else if (mode == 2) circleFuncSun(0.88f, 0.88f, 0.08f, 220, 230, 255); // Night Moon
    else if (mode == 3) circleFuncSun(0.88f, 0.88f, 0.09f, 240, 245, 255); // Winter Pale Sun
    else if (mode == 4) circleFuncSun(0.88f, 0.88f, 0.11f, 255, 240, 50);  // Spring Bright Sun
}

void drawClouds(int mode) {
    int wR = 255, wG = 255, wB = 255;
    int cR = 102, cG = 178, cB = 255;

    if (mode == 1) { // Monsoon
        wR = 150; wG = 160; wB = 160;
        cR = 100; cG = 110; cB = 120;
    } else if (mode == 2) { // Night
        wR = 50; wG = 60; wB = 80;
        cR = 30; cG = 40; cB = 60;
    } else if (mode == 3) { // Winter
        wR = 220; wG = 230; wB = 240;
        cR = 180; cG = 190; cB = 200;
    } else if (mode == 4) { // Spring
        wR = 255; wG = 255; wB = 255;
        cR = 130; cG = 200; cB = 255;
    }

    // Cloud 2
    circleFunc(0.03f, 0.75f, 0.04f, wR, wG, wB);
    circleFunc(0.115f, 0.79f, 0.07f, cR, cG, cB);
    circleFunc(0.10f, 0.79f, 0.07f, wR, wG, wB);
    circleFunc(0.19f, 0.80f, 0.03f, cR, cG, cB);
    circleFunc(0.18f, 0.80f, 0.03f, wR, wG, wB);
    circleFunc(0.21f, 0.75f, 0.05f, cR, cG, cB);
    circleFunc(0.20f, 0.75f, 0.05f, wR, wG, wB);
    circleFunc(0.12f, 0.73f, 0.06f, wR, wG, wB);
    circleFunc(0.06f, 0.71f, 0.03f, wR, wG, wB);

    // Cloud 3
    circleFunc(0.66f, 0.80f, 0.03f, wR, wG, wB);
    circleFunc(0.73f, 0.81f, 0.06f, cR, cG, cB);
    circleFunc(0.72f, 0.81f, 0.06f, wR, wG, wB);
    circleFunc(0.79f, 0.79f, 0.04f, cR, cG, cB);
    circleFunc(0.78f, 0.79f, 0.04f, wR, wG, wB);
    circleFunc(0.72f, 0.78f, 0.05f, wR, wG, wB);
    circleFunc(0.678f, 0.77f, 0.02f, wR, wG, wB);

    // Cloud 4
    circleFunc(-0.14f, 0.82f, 0.03f, wR, wG, wB);
    circleFunc(-0.07f, 0.84f, 0.06f, cR, cG, cB);
    circleFunc(-0.08f, 0.84f, 0.06f, wR, wG, wB);
    circleFunc(-0.01f, 0.81f, 0.04f, cR, cG, cB);
    circleFunc(-0.02f, 0.81f, 0.04f, wR, wG, wB);
    circleFunc(-0.08f, 0.80f, 0.05f, wR, wG, wB);
    circleFunc(-0.122f, 0.79f, 0.02f, wR, wG, wB);

    // Cloud 5
    circleFunc(-0.57f, 0.88f, 0.08f, cR, cG, cB);
    circleFunc(-0.58f, 0.88f, 0.08f, wR, wG, wB);
    circleFunc(-0.51f, 0.82f, 0.06f, cR, cG, cB);
    circleFunc(-0.52f, 0.82f, 0.06f, wR, wG, wB);
    circleFunc(-0.45f, 0.77f, 0.045f, cR, cG, cB);
    circleFunc(-0.46f, 0.77f, 0.045f, wR, wG, wB);
    circleFunc(-0.515f, 0.76f, 0.049f, cR, cG, cB);
    circleFunc(-0.525f, 0.76f, 0.049f, wR, wG, wB);
    circleFunc(-0.58f, 0.742f, 0.058f, wR, wG, wB);
    circleFunc(-0.67f, 0.742f, 0.058f, wR, wG, wB);
    circleFunc(-0.71f, 0.745f, 0.045f, wR, wG, wB);
    circleFunc(-0.695f, 0.79f, 0.025f, wR, wG, wB);
    circleFunc(-0.66f, 0.82f, 0.05f, wR, wG, wB);
    circleFunc(-0.58f, 0.78f, 0.06f, wR, wG, wB);
}

void drawEnvironment(int mode) {
    setTintColor(120, 200, 120, mode);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, 0.0f);   glVertex2f(-0.1f, 0.25f);
    glVertex2f(0.1f, 0.45f);   glVertex2f(0.3f, 0.6f);
    glVertex2f(0.5f, 0.45f);   glVertex2f(0.7f, 0.25f);
    glVertex2f(0.9f, 0.0f);
    glEnd();

    setTintColor(150, 220, 150, mode);
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 0.6f);    glVertex2f(0.5f, 0.45f);
    glVertex2f(0.7f, 0.25f);   glVertex2f(0.9f, 0.0f);
    glEnd();

    setTintColor(110, 190, 110, mode);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, 0.0f);   glVertex2f(-0.45f, 0.2f);
    glVertex2f(-0.3f, 0.35f);  glVertex2f(-0.15f, 0.2f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    setTintColor(150, 220, 150, mode);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, 0.35f);  glVertex2f(-0.15f, 0.2f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    setTintColor(100, 180, 100, mode);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.0f);   glVertex2f(-0.85f, 0.25f);
    glVertex2f(-0.7f, 0.45f);  glVertex2f(-0.55f, 0.3f);
    glVertex2f(-0.4f, 0.0f);
    glEnd();

    setTintColor(150, 220, 150, mode);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, 0.45f);  glVertex2f(-0.55f, 0.3f);
    glVertex2f(-0.4f, 0.0f);
    glEnd();

    setTintColor(90, 170, 90, mode);
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, 0.0f);    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.6f, 0.5f);    glVertex2f(0.8f, 0.3f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    setTintColor(150, 220, 150, mode);
    glBegin(GL_POLYGON);
    glVertex2f(0.6f, 0.5f);    glVertex2f(0.8f, 0.3f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    // River
    setTintColor(70, 130, 180, mode);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.62f, 0.0f);
    glVertex2f(0.18f, -0.3f);
    glVertex2f(0.4f, 0.0f);
    glEnd();

    setTintColor(20, 100, 20, mode);
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, -0.2f);   glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f, 0.45f);   glVertex2f(0.8f, 0.35f);
    glVertex2f(0.6f, 0.2f);    glVertex2f(0.4f, 0.0f);
    glEnd();

    setTintColor(19, 109, 21, mode);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.2f);  glVertex2f( 1.0f, -0.2f);
    glVertex2f( 1.0f,-1.0f);   glVertex2f(-1.0f,-1.0f);
    glEnd();

    setTintColor(34, 139, 34, mode);
    glBegin(GL_POLYGON);
    glVertex2f(0.4f, -0.3f);   glVertex2f(0.2f, -0.2f);
    glVertex2f(0.0f, -0.15f);  glVertex2f(-0.4f, 0.0f);
    glVertex2f(-0.6f, 0.1f);   glVertex2f(-0.8f, 0.2f);
    glVertex2f(-1.0f, 0.25f);  glVertex2f(-1.0f, -0.3f);
    glVertex2f(0.4f, -0.3f);
    glEnd();
}

// Function for the objects made by Nijhum
void madeByNijhum(int mode) {
    // Tent -----------------------------------------

    // shade 4
    glColor3ub(119, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.45f);
    glVertex2f(-0.81f, -0.76f);
    glVertex2f(-0.78f, -0.75f);
    glEnd();

    // shade 1
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.45f);
    glVertex2f(-0.79f, -0.79f);
    glVertex2f(-0.58f, -0.8f);
    glVertex2f(-0.5f, -0.4f);
    glEnd();

    // shade 2
    glColor3ub(159, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.4f);
    glVertex2f(-0.58f, -0.79f);
    glVertex2f(-0.5f, -0.77f);
    glEnd();

    // shade 3
    glColor3ub(179, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.4f);
    glVertex2f(-0.5f, -0.76f);
    glVertex2f(-0.4f, -0.76f);
    glEnd();

    // pilers
    glLineWidth(2.0f);
    glColor4ub(1, 1, 1, 255);
    glBegin(GL_LINES);
    glVertex2f(-0.4f,   -0.76f); // Piler 1 Start
    glVertex2f(-0.4f,   -0.74f); // Piler 1 End
    glVertex2f(-0.582f, -0.8f);  // Piler 2 Start
    glVertex2f(-0.582f, -0.78f); // Piler 2 End
    glVertex2f(-0.79f, -0.79f);  // Piler 3 Start
    glVertex2f(-0.79f, -0.77f);  // Piler 3 End
    glVertex2f(-0.81f, -0.76f);  // Piler 4 Start
    glVertex2f(-0.81f, -0.74f);  // Piler 4 End
    glEnd();


    // log ---------------------------------
    glBegin(GL_POLYGON);
    glColor3ub(101, 67, 33);
    glVertex2f(-0.4f, -0.60f);
    glVertex2f(-0.395f, -0.68f);
    glVertex2f(-0.22f, -0.65f);
    glVertex2f(-0.225f, -0.57f);
    glEnd();

    // log shade 1 ---------------------------
    glBegin(GL_POLYGON);
    glColor3ub(150, 75, 0);
    glVertex2f(-0.4f, -0.60f);
    glVertex2f(-0.395f, -0.68f);
    glVertex2f(-0.394f, -0.65f);
    glVertex2f(-0.397f, -0.68f);
    glVertex2f(-0.397f, -0.60f);
    glEnd();

    // log shade 2 ---------------------------
    glBegin(GL_POLYGON);
    glColor3ub(150, 75, 0);
    glVertex2f(-0.225f, -0.60f);
    glVertex2f(-0.221f, -0.65f);
    glVertex2f(-0.224f,  -0.64f);
    glVertex2f(-0.223f, -0.65f);
    glVertex2f(-0.222f, -0.57f);
    glEnd();

    // log upper part ------------------------
    glLineWidth(8.0f);
    glColor4ub(101, 67, 33, 255);
    glBegin(GL_LINES);
    glVertex2f(-0.35f, -0.60f); // Start
    glVertex2f(-0.33f, -0.57f); // End
    glEnd();

    // Stones around the fire -------------------------------
    glColor3ub(100, 100, 100);
    circleFunc(-0.32f, -0.78f, 0.045f, 100, 100, 100);

    // Individual rocks
    glColor3ub(120, 120, 120);
    circleFunc(-0.29f, -0.765f, 0.013f, 120, 120, 120);
    circleFunc(-0.32f, -0.755f, 0.012f, 130, 130, 130);
    circleFunc(-0.35f, -0.765f, 0.013f, 110, 110, 110);
    circleFunc(-0.36f, -0.785f, 0.011f, 125, 125, 125);
    circleFunc(-0.34f, -0.796f, 0.013f, 115, 115, 115);
    circleFunc(-0.30f, -0.796f, 0.012f, 120, 120, 120);
    circleFunc(-0.28f, -0.783f, 0.011f, 118, 118, 118);

    // wood pieces ------------------------
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(-0.355f, -0.790f);
    glVertex2f(-0.285f, -0.790f);
    glVertex2f(-0.285f, -0.778f);
    glVertex2f(-0.355f, -0.778f);
    glEnd();

    // second log (angled) -----------------
    glLineWidth(5.0f);
    glColor3ub(120, 70, 20);
    glBegin(GL_LINES);
    glVertex2f(-0.36f, -0.795f);
    glVertex2f(-0.29f, -0.770f);
    glVertex2f(-0.285f, -0.795f);
    glVertex2f(-0.355f, -0.770f);
    glEnd();

    // Ember glow ------------------------
    glColor3ub(180, 60, 0);
    circleFunc(-0.32f, -0.780f, 0.022f, 180, 60, 0);

    // Main flame --------------------
    glColor3ub(255, 120, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.335f, -0.778f);
    glVertex2f(-0.305f, -0.778f);
    glVertex2f(-0.315f, -0.748f);
    glVertex2f(-0.32f,  -0.738f);
    glVertex2f(-0.325f, -0.748f);
    glEnd();

    // Left sub-flame ------------------
    glColor3ub(255, 80, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.340f, -0.778f);
    glVertex2f(-0.320f, -0.778f);
    glVertex2f(-0.328f, -0.758f);
    glVertex2f(-0.336f, -0.750f);
    glEnd();

    // Right sub-flame ---------------------
    glColor3ub(255, 100, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.320f, -0.778f);
    glVertex2f(-0.300f, -0.778f);
    glVertex2f(-0.308f, -0.758f);
    glVertex2f(-0.304f, -0.752f);
    glEnd();

    // Inner yellow flame -------------------
    glColor3ub(255, 220, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.330f, -0.778f);
    glVertex2f(-0.310f, -0.778f);
    glVertex2f(-0.316f, -0.758f);
    glVertex2f(-0.32f,  -0.750f);
    glVertex2f(-0.324f, -0.758f);
    glEnd();

    // White-hot center spark -----------------
    glColor3ub(255, 255, 200);
    circleFunc(-0.32f, -0.768f, 0.007f, 255, 255, 200);

    // thin gray lines rising ----------------
    glLineWidth(1.5f);
    glColor3ub(180, 180, 180);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.320f, -0.738f);
    glVertex2f(-0.316f, -0.725f);
    glVertex2f(-0.323f, -0.712f);
    glVertex2f(-0.318f, -0.700f);
    glEnd();
    glColor3ub(160, 160, 160);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.324f, -0.742f);
    glVertex2f(-0.330f, -0.728f);
    glVertex2f(-0.325f, -0.714f);
    glEnd();

}

void drawWatchTower(float x, float y, float s, int mode) {
    glBegin(GL_QUADS);
        setTintColorF(0.45f, 0.28f, 0.14f, mode);
        glVertex2f(x - 0.07f * s, y);                 glVertex2f(x - 0.05f * s, y);
        glVertex2f(x - 0.05f * s, y + 0.25f * s);     glVertex2f(x - 0.07f * s, y + 0.25f * s);

        setTintColorF(0.35f, 0.20f, 0.10f, mode);
        glVertex2f(x + 0.05f * s, y);                 glVertex2f(x + 0.07f * s, y);
        glVertex2f(x + 0.07f * s, y + 0.25f * s);     glVertex2f(x + 0.05f * s, y + 0.25f * s);
    glEnd();

    setTintColorF(0.40f, 0.25f, 0.12f, mode);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.08f * s, y + 0.05f * s);     glVertex2f(x + 0.08f * s, y + 0.05f * s);
        glVertex2f(x + 0.08f * s, y + 0.07f * s);     glVertex2f(x - 0.08f * s, y + 0.07f * s);
        glVertex2f(x - 0.08f * s, y + 0.15f * s);     glVertex2f(x + 0.08f * s, y + 0.15f * s);
        glVertex2f(x + 0.08f * s, y + 0.17f * s);     glVertex2f(x - 0.08f * s, y + 0.17f * s);
    glEnd();

    glLineWidth(3.0f);
    setTintColorF(0.25f, 0.15f, 0.08f, mode);
    glBegin(GL_LINES);
        glVertex2f(x - 0.05f * s, y + 0.07f * s);     glVertex2f(x + 0.05f * s, y + 0.15f * s);
        glVertex2f(x - 0.05f * s, y + 0.15f * s);     glVertex2f(x + 0.05f * s, y + 0.07f * s);
        glVertex2f(x - 0.05f * s, y + 0.17f * s);     glVertex2f(x + 0.05f * s, y + 0.24f * s);
        glVertex2f(x - 0.05f * s, y + 0.24f * s);     glVertex2f(x + 0.05f * s, y + 0.17f * s);
    glEnd();

    setTintColorF(0.30f, 0.18f, 0.08f, mode);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.10f * s, y + 0.23f * s);     glVertex2f(x + 0.10f * s, y + 0.23f * s);
        glVertex2f(x + 0.10f * s, y + 0.25f * s);     glVertex2f(x - 0.10f * s, y + 0.25f * s);
    glEnd();

    setTintColorF(0.55f, 0.38f, 0.22f, mode);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.10f * s, y + 0.25f * s);     glVertex2f(x + 0.10f * s, y + 0.25f * s);
        glVertex2f(x + 0.10f * s, y + 0.27f * s);     glVertex2f(x - 0.10f * s, y + 0.27f * s);
    glEnd();

    setTintColorF(0.40f, 0.25f, 0.12f, mode);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        for(float lx = -0.09f; lx <= 0.09f; lx += 0.025f) {
            glVertex2f(x + lx * s, y + 0.27f * s);    glVertex2f(x + lx * s, y + 0.32f * s);
        }
        glVertex2f(x - 0.10f * s, y + 0.32f * s);     glVertex2f(x + 0.10f * s, y + 0.32f * s);
    glEnd();

    glBegin(GL_QUADS);
        setTintColorF(0.45f, 0.28f, 0.14f, mode);
        glVertex2f(x - 0.08f * s, y + 0.32f * s);     glVertex2f(x - 0.06f * s, y + 0.32f * s);
        glVertex2f(x - 0.06f * s, y + 0.35f * s);     glVertex2f(x - 0.08f * s, y + 0.35f * s);

        setTintColorF(0.35f, 0.20f, 0.10f, mode);
        glVertex2f(x + 0.06f * s, y + 0.32f * s);     glVertex2f(x + 0.08f * s, y + 0.32f * s);
        glVertex2f(x + 0.08f * s, y + 0.35f * s);     glVertex2f(x + 0.06f * s, y + 0.35f * s);
    glEnd();

    glBegin(GL_TRIANGLES);
        setTintColorF(0.45f, 0.22f, 0.12f, mode);
        glVertex2f(x - 0.12f * s, y + 0.35f * s);
        glVertex2f(x, y + 0.35f * s);
        glVertex2f(x, y + 0.40f * s);

        setTintColorF(0.30f, 0.12f, 0.05f, mode);
        glVertex2f(x, y + 0.35f * s);
        glVertex2f(x + 0.12f * s, y + 0.35f * s);
        glVertex2f(x, y + 0.40f * s);
    glEnd();

    setTintColorF(0.20f, 0.12f, 0.05f, mode);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x - 0.04f * s, y);                 glVertex2f(x - 0.04f * s, y + 0.25f * s);
        glVertex2f(x - 0.01f * s, y);                 glVertex2f(x - 0.01f * s, y + 0.25f * s);
        for(float ly = 0.02f; ly < 0.25f; ly += 0.025f) {
            glVertex2f(x - 0.04f * s, y + ly * s);    glVertex2f(x - 0.01f * s, y + ly * s);
        }
    glEnd();
}

void drawTree(float x, float y, float s, int mode) {
    setTintColor(110, 130, 40, mode);
    drawCircle(x - 0.10*s, y + 0.35*s, 0.13*s);

    setTintColor(130, 150, 40, mode);
    drawCircle(x - 0.01*s, y + 0.56*s, 0.13*s);
    drawCircle(x + 0.10*s, y + 0.49*s, 0.10*s);
    drawCircle(x - 0.08*s, y + 0.38*s, 0.13*s);
    drawCircle(x + 0.08*s + 0.02*s, y + 0.35*s, 0.13*s);

    setTintColor(139, 69, 19, mode);
    drawTriangle(x, y + 0.5*s, x - 0.02*s, y, x + 0.02*s, y);

    float midY = y + 0.2*s;
    drawTriangle(x, midY + 0.03*s, x, midY - 0.03*s, x + 0.08*s, y + 0.35*s);
    drawTriangle(x, midY + 0.03*s, x, midY - 0.03*s, x - 0.08*s, y + 0.33*s);
}

void drawTree2(float x, float y, float s, int mode) {
    setTintColor(90, 120, 30, mode);
    drawCircle(x - 0.02*s, y + 0.52*s, 0.18*s);
    drawCircle(x + 0.10*s, y + 0.33*s, 0.15*s);
    drawCircle(x - 0.12*s, y + 0.36*s, 0.16*s);
    drawCircle(x - 0.22*s, y + 0.20*s, 0.12*s);

    setTintColor(120, 160, 40, mode);
    drawCircle(x + 0.02*s, y + 0.56*s, 0.18*s);
    drawCircle(x + 0.14*s, y + 0.37*s, 0.15*s);
    drawCircle(x - 0.08*s, y + 0.40*s, 0.16*s);
    drawCircle(x - 0.18*s, y + 0.24*s, 0.12*s);

    setTintColor(139, 69, 19, mode);
    drawTriangle(x, y + 0.60*s, x - 0.03*s, y, x + 0.03*s, y);
    drawTriangle(x, y + 0.20*s, x, y + 0.12*s, x - 0.19*s, y + 0.26*s);
}

void drawTrees(int mode) {
    drawTree(0.11, -0.5, 0.75, mode);
    drawTree(0.95, -0.9, 0.9, mode);
    drawTree(-0.97, -0.75, 1.25, mode);
    drawTree(-0.5, 0.19, 0.15, mode);
    drawTree(-0.15, 0.19, 0.11, mode);
    drawTree(0.4, 0.4, 0.11, mode);

    drawTree2(-0.5, -0.35, 0.45, mode);
    drawTree2(0.45, -0.2, 0.5, mode);
    drawTree2(-0.4, 0.14, 0.15, mode);
    drawTree2(0.1, 0.12, 0.15, mode);
    drawTree2(0.8, -0.3, 0.65, mode);
}

void drawWeather(int mode) {
    if (mode == 1) { // Rain
        glColor3ub(180, 180, 255);
        glLineWidth(1.0);
        glBegin(GL_LINES);
        for(int i = 0; i < 200; i++) {
            glVertex2f(particleX[i], particleY[i]);
            glVertex2f(particleX[i] + 0.015f, particleY[i] - 0.08f);
        }
        glEnd();
    } else if (mode == 3) { // Snow
        glColor3ub(255, 255, 255); // Pure white snow
        glPointSize(3.0);
        glBegin(GL_POINTS);
        for(int i = 0; i < 200; i++) {
            glVertex2f(particleX[i], particleY[i]);
        }
        glEnd();
    }
}


// ==========================================================
// CORE GLUT FUNCTIONS
// ==========================================================
void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '1': mode = 0; break; // Day
        case '2': mode = 1; break; // Monsoon
        case '3': mode = 2; break; // Night
        case '4': mode = 3; break; // Winter
        case '5': mode = 4; break; // Spring
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
}

void update(int value) {
    for(int i = 0; i < 200; i++) {
        if (mode == 1) { // Rain speed
            particleY[i] -= 0.025;
        } else if (mode == 3) { // Snow speed and drift
            particleY[i] -= 0.005;
            particleX[i] += 0.002 * sin(particleY[i] * 10.0); // Make snow wave slightly

            if(particleX[i] > 1.0f) particleX[i] = -1.0f;
            if(particleX[i] < -1.0f) particleX[i] = 1.0f;
        }

        if(particleY[i] < -1) {
            particleY[i] = 1.0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void display() {
    // Set Sky Color based on mode
    if (mode == 0) glClearColor(0.6f, 0.9f, 1.0f, 1.0f);        // Day
    else if (mode == 1) glClearColor(0.4f, 0.5f, 0.6f, 1.0f);   // Monsoon
    else if (mode == 2) glClearColor(0.1f, 0.15f, 0.25f, 1.0f); // Night
    else if (mode == 3) glClearColor(0.75f, 0.85f, 0.9f, 1.0f); // Winter Frosty Sky
    else if (mode == 4) glClearColor(0.5f, 0.85f, 1.0f, 1.0f);  // Spring Bright Sky

    glClear(GL_COLOR_BUFFER_BIT);

    drawSunMoon(mode);
    drawClouds(mode);
    drawEnvironment(mode);
    drawWatchTower(0.3f, -0.2f, 1.0f, mode);
    madeByNijhum(mode);
    drawTrees(mode);

    drawWeather(mode); // Draws Rain for Monsoon, Snow for Winter

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Dynamic 5-Season Camping Scenario");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
