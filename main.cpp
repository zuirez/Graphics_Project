#include<windows.h>
#include <GL/glut.h>
#define PI   3.141516
#include<math.h>
float aspect = 1920.0f / 1080.0f;

// Function for making circles - Nijhum
void circleFuncSun(float p1, float q1, float r1, int R1, int G1, int B1)
{
    GLfloat x = p1;
    GLfloat y = q1;
    GLfloat r = r1;

    int triangle = 100;
    float tp = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(R1, G1, B1);
    glVertex2f(x, y);

    for (int i = 0; i <= triangle; i++)
    {
        float angle = i * tp / triangle;
        glVertex2f(x + (r * cos(angle) / aspect), y + (r * sin(angle)));
    }

    glEnd();
}

// Function for making ovals - Rashed
void circleFunc(float p1, float q1, float r1, int R1, int G1, int B1)
{
    GLfloat x = p1;
    GLfloat y = q1;
    GLfloat r = r1;
    int R = R1;
    int G = G1;
    int B = B1;
    int triangle = 100;
    float tp = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(R, G, B);
    glVertex2f(x, y);
    for (int i = 0; i <= triangle; i++)
    {
        glVertex2f(x + (r * cos(i * tp / triangle)), y + (r * sin(i * tp / triangle)));
    }
    glEnd();
}

// Function for the objects made by Nijhum
void madeByNijhum() {
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
}

// Function for Watch Tower - Wakil
void drawWatchTower()
{
    glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
    glLineWidth(5.5f);

    glColor3f(0.45f, 0.10f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(0.80f, 0.30f);
        glVertex2f(0.90f, 0.20f);
        glVertex2f(0.8625f, 0.20f);
        glVertex2f(0.80f, 0.2667f);
    glEnd();

    glColor3f(0.72f, 0.55f, 0.28f);
    glBegin(GL_POLYGON);
        glVertex2f(0.8125f, 0.20f);
        glVertex2f(0.8625f, 0.20f);
        glVertex2f(0.8625f, 0.0933f);
        glVertex2f(0.8125f, 0.0933f);
    glEnd();

    glColor3f(0.72f, 0.18f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(0.80f, 0.30f);
        glVertex2f(0.70f, 0.20f);
        glVertex2f(0.90f, 0.20f);
    glEnd();

    glColor3f(0.90f, 0.72f, 0.42f);
    glBegin(GL_POLYGON);
        glVertex2f(0.7375f, 0.20f);
        glVertex2f(0.8625f, 0.20f);
        glVertex2f(0.8625f, 0.0933f);
        glVertex2f(0.7375f, 0.0933f);
    glEnd();

    glColor3f(0.55f, 0.82f, 1.00f);
    glBegin(GL_POLYGON);
        glVertex2f(0.75625f, 0.18f);
        glVertex2f(0.84375f, 0.18f);
        glVertex2f(0.84375f, 0.1533f);
        glVertex2f(0.75625f, 0.1533f);
    glEnd();

    glColor3f(0.78f, 0.58f, 0.30f);

    glBegin(GL_POLYGON);
        glVertex2f(0.7125f, 0.1733f);
        glVertex2f(0.7375f, 0.1733f);
        glVertex2f(0.7375f, 0.0933f);
        glVertex2f(0.7125f, 0.0933f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.8625f, 0.1733f);
        glVertex2f(0.8875f, 0.1733f);
        glVertex2f(0.8875f, 0.0933f);
        glVertex2f(0.8625f, 0.0933f);
    glEnd();

    glColor3f(0.55f, 0.34f, 0.16f);
    glBegin(GL_QUADS);

        glVertex2f(0.7469f, 0.0933f);
        glVertex2f(0.7531f, 0.0933f);
        glVertex2f(0.7219f,-0.0867f);
        glVertex2f(0.7156f,-0.0867f);

        glVertex2f(0.7844f, 0.0933f);
        glVertex2f(0.7906f, 0.0933f);
        glVertex2f(0.7781f,-0.0867f);
        glVertex2f(0.7719f,-0.0867f);

        glVertex2f(0.8094f, 0.0933f);
        glVertex2f(0.8156f, 0.0933f);
        glVertex2f(0.8281f,-0.0867f);
        glVertex2f(0.8219f,-0.0867f);

        glVertex2f(0.8469f, 0.0933f);
        glVertex2f(0.8531f, 0.0933f);
        glVertex2f(0.8844f,-0.0867f);
        glVertex2f(0.8781f,-0.0867f);

    glEnd();

    glColor3f(0.95f, 0.82f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(0.80f, 0.3467f);
        glVertex2f(0.8375f, 0.3333f);
        glVertex2f(0.80f, 0.3133f);
    glEnd();

    glColor3f(0.15f, 0.08f, 0.02f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.80f, 0.30f);
        glVertex2f(0.70f, 0.20f);
        glVertex2f(0.90f, 0.20f);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(0.80f, 0.30f); glVertex2f(0.80f, 0.20f);
        glVertex2f(0.75625f, 0.2533f); glVertex2f(0.84375f, 0.2533f);
        glVertex2f(0.73125f, 0.2267f); glVertex2f(0.86875f, 0.2267f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.7375f, 0.20f);
        glVertex2f(0.8625f, 0.20f);
        glVertex2f(0.8625f, 0.0933f);
        glVertex2f(0.7375f, 0.0933f);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(0.75625f, 0.18f); glVertex2f(0.84375f, 0.18f);
        glVertex2f(0.75625f, 0.1533f); glVertex2f(0.84375f, 0.1533f);
        glVertex2f(0.80f, 0.18f); glVertex2f(0.80f, 0.1533f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.7125f, 0.1733f);
        glVertex2f(0.7375f, 0.1733f);
        glVertex2f(0.7375f, 0.0933f);
        glVertex2f(0.7125f, 0.0933f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.8625f, 0.1733f);
        glVertex2f(0.8875f, 0.1733f);
        glVertex2f(0.8875f, 0.0933f);
        glVertex2f(0.8625f, 0.0933f);
    glEnd();

    glBegin(GL_LINES);

        glVertex2f(0.75f, 0.0933f); glVertex2f(0.7188f, -0.0867f);
        glVertex2f(0.7875f, 0.0933f); glVertex2f(0.7750f, -0.0867f);
        glVertex2f(0.8125f, 0.0933f); glVertex2f(0.8250f, -0.0867f);
        glVertex2f(0.85f, 0.0933f); glVertex2f(0.8813f, -0.0867f);

        glVertex2f(0.7250f, 0.0400f); glVertex2f(0.8750f, -0.0267f);
        glVertex2f(0.8750f, 0.0400f); glVertex2f(0.7250f, -0.0267f);

        glVertex2f(0.7375f, 0.0800f); glVertex2f(0.8625f, 0.0333f);
        glVertex2f(0.8625f, 0.0800f); glVertex2f(0.7375f, 0.0333f);

    glEnd();

    glBegin(GL_LINES);
        glVertex2f(0.80f, 0.30f);
        glVertex2f(0.80f, 0.3467f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.80f, 0.3467f);
        glVertex2f(0.8375f, 0.3333f);
        glVertex2f(0.80f, 0.3133f);
    glEnd();

    glPopAttrib();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    /* Sun - Rashed */
    circleFuncSun(0.88f, 0.88f, 0.1f, 255, 255, 0);



    /* Clouds - Rashed */

    // Cloud 1 - Rashed
    circleFuncSun(-0.58f, 0.88f, 0.08f, 255, 255, 255);
    circleFuncSun(-0.53f, 0.82f, 0.06f, 255, 255, 255);
    circleFuncSun(-0.49f, 0.77f, 0.045f, 255, 255, 255);
    circleFuncSun(-0.525f, 0.76f, 0.049f, 255, 255, 255);
    circleFuncSun(-0.565f, 0.742f, 0.058f, 255, 255, 255);
    circleFuncSun(-0.61f, 0.748f, 0.075f, 255, 255, 255);
    circleFuncSun(-0.66f, 0.742f, 0.058f, 255, 255, 255);
    circleFuncSun(-0.69f, 0.72f, 0.025f, 255, 255, 255);
    circleFuncSun(-0.71f, 0.745f, 0.045f, 255, 255, 255);
    circleFuncSun(-0.695f, 0.79f, 0.025f, 255, 255, 255);
    circleFuncSun(-0.67f, 0.81f, 0.045f, 255, 255, 255);
    circleFuncSun(-0.63f, 0.83f, 0.06f, 255, 255, 255);
    circleFuncSun(-0.58f, 0.78f, 0.06f, 255, 255, 255);

    // Cloud 2 - Rashed
    circleFunc(0.03f, 0.75f, 0.04f, 255, 255, 255); //left up
    circleFunc(0.10f, 0.79f, 0.07f, 255, 255, 255); // top big
    circleFunc(0.20f, 0.75f, 0.05f, 255, 255, 255); // right
    circleFunc(0.12f, 0.73f, 0.06f, 255, 255, 255); // 2nd top
    circleFunc(0.06f, 0.71f, 0.03f, 255, 255, 255); // left bottom
    circleFunc(0.18f, 0.80f, 0.03f, 255, 255, 255);

    // Cloud 3 - Rashed
    circleFunc(0.66f, 0.80f, 0.03f, 255, 255, 255);
    circleFunc(0.72f, 0.81f, 0.06f, 255, 255, 255);
    circleFunc(0.78f, 0.79f, 0.04f, 255, 255, 255);
    circleFunc(0.72f, 0.78f, 0.05f, 255, 255, 255);
    circleFunc(0.678f, 0.77f, 0.02f, 255, 255, 255);

    // Cloud 4 - Rashed
    circleFunc(-0.14f, 0.82f, 0.03f, 255, 255, 255);
    circleFunc(-0.08f, 0.84f, 0.06f, 255, 255, 255);
    circleFunc(-0.02f, 0.81f, 0.04f, 255, 255, 255);
    circleFunc(-0.08f, 0.80f, 0.05f, 255, 255, 255);
    circleFunc(-0.122f, 0.79f, 0.02f, 255, 255, 255);


    /* Mountains - Nahin */

    //mountain1
    glColor3ub(0,100,0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f,-0.34f);
        glVertex2f(-0.2f,-0.2f);
        glVertex2f(-0.3f,0.0f);
        glVertex2f(-0.4f,0.2f);
        glVertex2f(-0.6f,0.4f);
        glVertex2f(-1.0f,0.6f);
        glVertex2f(-1.0f,-0.2f);
    glEnd();

    //mountain2
    glColor3ub(19,109,21);
        glBegin(GL_POLYGON);
        glVertex2f(1.0f,0.2f);
        glVertex2f(0.8f,0.1f);
        glVertex2f(0.6f,-0.2f);
        glVertex2f(0.4f,-0.42f);
        glVertex2f(1.0f,-0.7f);
    glEnd();

    //mountain3
    glColor3ub(0,100,0);
        glBegin(GL_POLYGON);
        glVertex2f(0.9f,0.8f);
        glVertex2f(0.8f,0.7f);
        glVertex2f(0.6f,0.5f);
        glVertex2f(0.3f,-0.4f);
        glVertex2f(0.4f,-0.42f);
        glVertex2f(0.8f,0.001f);
        glVertex2f(1.0f,0.1f);
        glVertex2f(1.0f,0.8f);
    glEnd();

    //mountain4
    glColor3ub(19,109,21);
        glBegin(GL_POLYGON);
        glVertex2f(0.54f,0.3f);
        glVertex2f(0.1f,0.5f);
        glVertex2f(-0.1f,0.5f);
        glVertex2f(-0.2f,0.3f);
        glVertex2f(-0.29f,0.0f);
        glVertex2f(-0.1f,-0.34f);
        glVertex2f(-0.1f,-0.34f);
        glVertex2f(0.3f,-0.4f);
        glVertex2f(-0.2f,0.3f);
    glEnd();

    //ground
    glColor3ub(32,139,34);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.2f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.5f);
    glEnd();

    drawWatchTower();

    madeByNijhum();

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Dynamic Camping Scenario");
    glClearColor(0.0, 0.0, 1.0, 1.0); // blue background
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
