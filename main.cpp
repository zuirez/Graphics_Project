#include<windows.h>
#include <GL/glut.h>
#define PI   3.141516
#include<math.h>

// Function for making circles - Rashed
void circleFunc(float x, float y, float r, int R, int G, int B)
{
    GLfloat p1=x;
    GLfloat q1= y;
    GLfloat r1 = r;
    int tringle2=100;

    GLfloat tp2 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub ( R,G,B);
    glVertex2f (p1,q1);
    for(int i= 0;i<=tringle2; i++)
    {
        glVertex2f (p1+(r1*cos(i*tp2/tringle2)), q1+(r1*sin(i*tp2/tringle2)));
    }
    glEnd ();
}

// Function for making Tent - Nijhum
void tentFunc() {
    // shade 1
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.45f);
    glVertex2f(-0.89f, -0.89f);
    glVertex2f(-0.6f, -0.89f);
    glVertex2f(-0.46f, -0.38f);
    glEnd();

    // shade 2
    glColor3ub(159, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(-0.46f, -0.38f);
    glVertex2f(-0.6f, -0.89f);
    glVertex2f(-0.48f, -0.89f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Sun - Rashed
    circleFunc(0.8f, 0.8f, 0.08f, 255, 255, 0);

    // Cloud - Rashed
    circleFunc(-0.5f, 0.8f, 0.1f, 255, 255, 255);
    circleFunc(-0.3f, 0.8f, 0.1f, 255, 255, 255);
    circleFunc(-0.4f, 0.8f, 0.13f, 255, 255, 255);
    circleFunc(-0.6f, 0.8f, 0.05f, 255, 255, 255);

    // Tent - Nijhum
    tentFunc();

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
