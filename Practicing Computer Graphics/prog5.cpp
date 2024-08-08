#include <GL/glut.h>
#include <iostream>
//#include <cmath>

// Define the dimensions of the display
const int display_width = 800;
const int display_height = 600;

// Define the 3D object (a cube)
GLfloat vertices[][3] = {
    {-1, -1, -1},
    { 1, -1, -1},
    { 1,  1, -1},
    {-1,  1, -1},
    {-1, -1,  1},
    { 1, -1,  1},
    { 1,  1,  1},
    {-1,  1,  1}
};

GLuint edges[][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

GLfloat angle = 0;

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, (GLfloat)display_width / (GLfloat)display_height, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to draw the 3D object
void drawCube() {
    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        glVertex3fv(vertices[edges[i][0]]);
        glVertex3fv(vertices[edges[i][1]]);   //1
    }
    glEnd();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply transformations
    glTranslatef(0.0f, 0.0f, -5.0f); // Translation matrix
    glRotatef(angle, 1.0f, 1.0f, 0.0f); // Rotation matrix
    glScalef(1.5f, 1.5f, 1.5f); // Scaling matrix

    // Draw the 3D object
    drawCube();

    glutSwapBuffers();
}

// Timer callback function
void timer(int value) {
    angle += 1.0f;
    if (angle > 360) {
        angle -= 360;
    }
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(50, timer, 0); // Set the timer to call itself again after 33 ms (approx 30 FPS)
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(display_width, display_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Transformations with FreeGLUT");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(50, timer, 0); // Start the timer

    glutMainLoop();
    return 0;
}
