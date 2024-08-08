#include <GL/glut.h>
#include <cmath>

// Function to initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Set perspective projection
    glMatrixMode(GL_MODELVIEW);
}

// Function to draw a cuboid
void drawCuboid(float x, float y, float z, float length, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);  // Set the color for the cuboid using RGB values.
    glPushMatrix();   // Save the current transformation matrix.
    glTranslatef(x, y, z);  // Translate the cuboid to the specified position (x, y, z).
    glScalef(length, width, height);  // Scale the cuboid to the specified dimensions.
    glutSolidCube(1.0);  // Draw a unit cube (1x1x1) which is then scaled to the desired size.
    glPopMatrix();      // Restore the original transformation matrix.
}

// Function to draw a cylinder

void drawCylinder(float x, float y, float z, float radius, float height, float r, float g, float b) {
    glColor3f(r, g, b);  // Set the color for the cylinder using RGB values.
    glPushMatrix();       // Save the current transformation matrix.
    glTranslatef(x, y, z);    // Translate the cylinder to the specified position (x, y, z).
    glRotatef(-45, 1.0, 0.0, 0.0); // Rotate to align with the z-axis
    GLUquadric* quad = gluNewQuadric();  // Create a new quadric object.
    gluCylinder(quad, radius, radius, height, 50, 50);   // Draw the cylinder with the specified radius and height.
    gluDeleteQuadric(quad);   // Delete the quadric object to free memory.
    glPopMatrix();     // Restore the original transformation matrix.

}

// Function to translate a 3D object
void translate(float dx, float dy, float dz) {
    glTranslatef(dx, dy, dz);
}

// Function to rotate a 3D object
void rotate(float angle, float x, float y, float z) {
    glRotatef(angle, x, y, z);
}

// Function to scale a 3D object
void scale(float sx, float sy, float sz) {
    glScalef(sx, sy, sz);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera view

    // Draw a cuboid
    glPushMatrix();
    drawCuboid(-2, -2, 0, 2, 2, 2, 0.0f, 0.0f, 1.0f);

    // Translate the cuboid
    translate(4, 0, 0);
    drawCuboid(0, -1, 0, 2, 2, 2, 0.0f, 1.0f, 0.0f);

    // Rotate the cuboid
    glPushMatrix();
    rotate(45, 0, 1, 0);
    drawCuboid(-2, -1, 0, 2, 2, 2, 1.0f, 0.0f, 0.0f);
    glPopMatrix();

    // Scale the cuboid
    glPushMatrix();
    scale(1.5, 1.5, 1.5);
    drawCuboid(-2, -1, 0, 2, 2, 2, 0.5f, 0.0f, 0.5f);
    glPopMatrix();
    glPopMatrix();

    // Draw a cylinder
    glPushMatrix();
    drawCylinder(2, 2, 0, 1, 5, 1.0f, 0.0f, 0.0f);

    // Translate the cylinder
    translate(-2, -2, 0);
    drawCylinder(0, 2, 1, 1, 1, 0.0f, 1.0f, 0.0f);

    // Rotate the cylinder
    glPushMatrix();
    rotate(30, 1, 0, 0);
    drawCylinder(2, 2, -2, 1, 3, 0.0f, 0.0f, 1.0f);
    glPopMatrix();

    // Scale the cylinder
    glPushMatrix();
    scale(1.5, 1.5, 1.5);
    drawCylinder(5, 0, 0, 1, 8, 0.5f, 0.5f, 0.0f);
    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();  // Swap the buffers to display the rendered frame

}

// Timer callback function
void timer(int value) {
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(33, timer, 0); // Set the timer to call itself again after 33 ms (approx 30 FPS)
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("3D Geometric Operations with FreeGLUT");

    init();
    glutDisplayFunc(display);
   //glutTimerFunc(33, timer, 0); // Start the timer

    glutMainLoop();
    return 0;
}
