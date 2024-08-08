#include <GL/glut.h>
#include <iostream>

// Define the dimensions of the canvas
const int canvas_width = 500;
const int canvas_height = 500;

// Define the initial object (a square)
GLfloat obj_points[][2] = { {100, 100}, {200, 100}, {200, 200}, {100, 200} };
const int num_points = sizeof(obj_points) / sizeof(obj_points[0]);

// Define the transformation parameters
GLfloat translation_x = 100;
GLfloat translation_y = 50;
GLfloat rotation_angle = 45;
GLfloat scaling_factor = 1.5;

// Function to initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, canvas_width, 0, canvas_height); // Set the coordinate system
}

// Function to draw the objects on the canvas
void drawObjects() {
    // Draw the initial object (a square)
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(obj_points[i][0], obj_points[i][1]);
    }
    glEnd();

    // Apply transformations and draw translated object
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(translation_x, translation_y, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(obj_points[i][0], obj_points[i][1]);
    }
    glEnd();
    glPopMatrix();

    // Apply transformations and draw rotated object
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(obj_points[0][0], obj_points[0][1], 0.0);
    glRotatef(rotation_angle, 0.0, 0.0, 1.0);
    glTranslatef(-obj_points[0][0], -obj_points[0][1], 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(obj_points[i][0], obj_points[i][1]);
    }
    glEnd();
    glPopMatrix();

    // Apply transformations and draw scaled object
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(obj_points[0][0], obj_points[0][1], 0.0);
    glScalef(scaling_factor, scaling_factor, 1.0);
    glTranslatef(-obj_points[0][0], -obj_points[0][1], 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_points; ++i) {
        glVertex2f(obj_points[i][0], obj_points[i][1]);
    }
    glEnd();
    glPopMatrix();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the objects on the canvas
    drawObjects();

    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(canvas_width, canvas_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations with FreeGLUT");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
