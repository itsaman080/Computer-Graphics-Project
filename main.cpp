#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#define PI 3.14159265f

GLfloat ballRadius = 0.2f;
GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.007f;
GLfloat xAcceleration = 0.0000f;
GLfloat yAcceleration = -0.0005f;
int refreshMills = 30;

int score = 0;
int cur_mx = 0, cur_my = 0;
bool arcball_on = false;
bool gameStarted = false;
bool gameOver = false;
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
GLdouble windowWidth = 800;
GLdouble windowHeight = 800;

// Function to set color based on score
void color() {
    if (score <= 5)
        glColor3f(1.0, 0.0, 0.0); // Red for low score
    else
        glColor3ub(rand() % 250, rand() % 250, rand() % 250); // Random color for high score
}

// Function to display text at given position
void displayText(float x, float y, const char* text, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b); // Set text color
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
}

// Function to display the start screen
void startScreen() {
    displayText(-0.4f, 0.7f, "Computer Graphics Project", 0.0f, 1.0f, 0.0f); // Green color for title
    displayText(-0.3f, 0.6f, "Bouncing Ball Game", 1.0f, 1.0f, 1.0f); // White color for subtitle
    displayText(-0.4f, 0.4f, "Team Members:", 1.0f, 1.0f, 1.0f); // White color for team members
    displayText(-0.4f, 0.3f, "1. Adarsh Raj", 1.0f, 1.0f, 1.0f);
    displayText(-0.4f, 0.2f, "2. Bivek Sah", 1.0f, 1.0f, 1.0f);
    displayText(-0.4f, 0.1f, "3. Aman Kumar", 1.0f, 1.0f, 1.0f);
    displayText(-0.4f, 0.0f, "4. Anuradha Verma", 1.0f, 1.0f, 1.0f);
    displayText(-0.3f, -0.2f, "Press ENTER to Start", 0.0f, 1.0f, 0.0f); // Green color for prompt
}
/*void startScreen() {
    displayText(-0.9f, 0.7f, "Computer Graphics Project", 0.0f, 1.0f, 0.0f); // Green color for title
    displayText(-0.8f, 0.6f, "Bouncing Ball Game", 1.0f, 1.0f, 1.0f); // White color for subtitle
    displayText(-0.8f, 0.4f, "Team Members:", 1.0f, 1.0f, 1.0f); // White color for team members
    displayText(-0.8f, 0.3f, "1. Adarsh Raj", 1.0f, 1.0f, 1.0f);
    displayText(-0.8f, 0.2f, "2. Bivek Sah", 1.0f, 1.0f, 1.0f);
    displayText(-0.8f, 0.1f, "3. Aman Kumar", 1.0f, 1.0f, 1.0f);
    displayText(-0.8f, 0.0f, "4. Anuradha Verma", 1.0f, 1.0f, 1.0f);
    displayText(-0.8f, -0.2f, "Press ENTER to Start", 0.0f, 1.0f, 0.0f); // Green color for prompt
}*/
// Function to display the game over screen
void gameOverScreen() {
    displayText(-0.2f, 0.1f, "GAME OVER", 1.0f, 0.0f, 0.0f); // Red color for game over
    displayText(-0.3f, -0.1f, ("Final Score: " + std::to_string(score)).c_str(), 1.0f, 1.0f, 1.0f); // White color for final score
    displayText(-0.3f, -0.3f, "Press ENTER to Restart", 0.0f, 1.0f, 0.0f); // Green color for prompt
}

// Function to display the ball
void balldisp() {
    glLoadIdentity();
    glTranslatef(ballX, ballY, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    color(); // Set color for the ball
    glVertex2f(0.0f, 0.0f);
    int numSegments = 100;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) {
        angle = i * 2.0f * PI / numSegments;
        glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
    glEnd();

    xSpeed += xAcceleration;
    ySpeed += yAcceleration;
    ballX += xSpeed;
    ballY += ySpeed;

    if (ballX > ballXMax) {
        ballX = ballXMax;
        xSpeed = -xSpeed;
    } else if (ballX < ballXMin) {
        ballX = ballXMin;
        xSpeed = -xSpeed;
    }
    if (ballY > ballYMax) {
        ballY = ballYMax;
        ySpeed = -ySpeed;
    } else if (ballY < ballYMin) {
        ballY = ballYMin;
        ySpeed = -ySpeed;
    }
    if (ballY == ballYMin) {
        gameStarted = false;
        gameOver = true;
    }

    // Display the score while playing the game
    glColor3f(1.0, 0.0, 0.0); // Red color for the score
    glLoadIdentity();
    glRasterPos2f(-0.1, 0.9); // Position score display with padding from the top
    std::string scoreText = "SCORE: " + std::to_string(score);
    displayText(-0.1, 0.9, scoreText.c_str(), 1.0f, 1.0f, 1.0f); // White color for score text
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (gameStarted) {
        balldisp();
    } else if (gameOver) {
        gameOverScreen();
    } else {
        startScreen();
    }
    glutSwapBuffers();
}

// Mouse motion function
void onMotion(int x, int y) {
    if (arcball_on) {
        cur_mx = x;
        cur_my = y;
    }
}

// Reshape function
void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        clipAreaXLeft = -1.0 * aspect;
        clipAreaXRight = 1.0 * aspect;
        clipAreaYBottom = -1.0;
        clipAreaYTop = 1.0;
    } else {
        clipAreaXLeft = -1.0;
        clipAreaXRight = 1.0;
        clipAreaYBottom = -1.0 / aspect;
        clipAreaYTop = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
    ballXMin = clipAreaXLeft + ballRadius;
    ballXMax = clipAreaXRight - ballRadius;
    ballYMin = clipAreaYBottom + ballRadius;
    ballYMax = clipAreaYTop - ballRadius;
}

// Timer function
void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(refreshMills, Timer, 0);
}

// Mouse click function
void onMouse(int button, int state, int x, int y) {
    cur_mx = x;
    cur_my = y;
    GLfloat X = ((-((float)windowWidth / 2) + float(cur_mx)) / (float)(windowWidth))*2;
    GLfloat Y = ((+((float)windowHeight / 2) - float(cur_my)) / (float)(windowHeight))*2;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        arcball_on = true;
        if ((X >= (ballX - ballRadius) && Y >= (ballY - ballRadius)) &&
            (X <= (ballX + ballRadius) && Y <= (ballY + ballRadius))) {
            xSpeed += 0.01f;
            ySpeed += 0.02f;
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        arcball_on = false;
        if ((X >= (ballX - ballRadius) && Y >= (ballY - ballRadius)) &&
            (X <= (ballX + ballRadius) && Y <= (ballY + ballRadius))) {
            score += 1;
        }
    }
}

// Key press function
void onKeyPress(unsigned char key, int x, int y) {
    if (key == 13) { // Enter key
        if (gameOver) {
            gameOver = false;
            score = 0;
            ballX = 0.0f;
            ballY = 0.0f;
            xSpeed = 0.02f;
            ySpeed = 0.007f;
        }
        gameStarted = true;
    }
}

// Main function
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 100);
    glutCreateWindow("Bouncing Ball");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutKeyboardFunc(onKeyPress);
    glutTimerFunc(0, Timer, 0);

    glutMainLoop();
    return 0;
}
