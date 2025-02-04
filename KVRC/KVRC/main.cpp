/*
=======================
| Name: As Wasti      |
=======================
*/

#include <cmath>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Camera variables
float cameraDistance = 10.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
int lastMouseX, lastMouseY;
bool isDragging = false;

void drawCylinder(float radius, float height, int slices) {
    GLUquadric* quadric = gluNewQuadric();
    gluCylinder(quadric, radius, radius, height, slices, 1);
    gluDeleteQuadric(quadric);

    // bottom cap
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    gluDisk(quadric, 0.0f, radius, slices, 1);
    glPopMatrix();

    // top cap
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quadric, 0.0f, radius, slices, 1);
    glPopMatrix();
}

void drawCube(float width, float height, float depth) {
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawTrapezoid(float topWidth, float bottomWidth, float height, float depth) {
    float halfTopWidth = topWidth / 2.0f;
    float halfBottomWidth = bottomWidth / 2.0f;
    float halfDepth = depth / 2.0f;

    glBegin(GL_QUADS);
    // Front face
    glVertex3f(-halfTopWidth, height / 2.0f, halfDepth);
    glVertex3f(halfTopWidth, height / 2.0f, halfDepth);
    glVertex3f(halfBottomWidth, -height / 2.0f, halfDepth);
    glVertex3f(-halfBottomWidth, -height / 2.0f, halfDepth);

    // Back face
    glVertex3f(-halfTopWidth, height / 2.0f, -halfDepth);
    glVertex3f(halfTopWidth, height / 2.0f, -halfDepth);
    glVertex3f(halfBottomWidth, -height / 2.0f, -halfDepth);
    glVertex3f(-halfBottomWidth, -height / 2.0f, -halfDepth);

    // Left face
    glVertex3f(-halfTopWidth, height / 2.0f, halfDepth);
    glVertex3f(-halfTopWidth, height / 2.0f, -halfDepth);
    glVertex3f(-halfBottomWidth, -height / 2.0f, -halfDepth);
    glVertex3f(-halfBottomWidth, -height / 2.0f, halfDepth);

    // Right face
    glVertex3f(halfTopWidth, height / 2.0f, halfDepth);
    glVertex3f(halfTopWidth, height / 2.0f, -halfDepth);
    glVertex3f(halfBottomWidth, -height / 2.0f, -halfDepth);
    glVertex3f(halfBottomWidth, -height / 2.0f, halfDepth);

    // Top face
    glVertex3f(-halfTopWidth, height / 2.0f, halfDepth);
    glVertex3f(halfTopWidth, height / 2.0f, halfDepth);
    glVertex3f(halfTopWidth, height / 2.0f, -halfDepth);
    glVertex3f(-halfTopWidth, height / 2.0f, -halfDepth);

    // Bottom face
    glVertex3f(-halfBottomWidth, -height / 2.0f, halfDepth);
    glVertex3f(halfBottomWidth, -height / 2.0f, halfDepth);
    glVertex3f(halfBottomWidth, -height / 2.0f, -halfDepth);
    glVertex3f(-halfBottomWidth, -height / 2.0f, -halfDepth);
    glEnd();
}

void drawHead() {
    // Draw Head - Bottom part (Cube)
    glPushMatrix();
    glColor3f(1.0f, 0.55f, 0.0f);
    glTranslatef(0.0f, 1.3f, 0.0f);
    glScalef(1.05f, 1.0f, 1.05f);
    drawCube(1.0f, 1.0f, 1.0f);
    glPopMatrix();

    // Draw Head - Top part (Sphere)
    glPushMatrix();
    glColor3f(1.0f, 0.6f, 0.0f);
    glTranslatef(0.0f, 1.85f, 0.0f);
    glutSolidSphere(0.6f, 20, 20);
    glPopMatrix();

    // Draw Ears + Antennas
    for (int i = -1; i <= 1; i += 2) {
        // Ears
        glPushMatrix();
        glColor3f(0.9f, 0.45f, 0.0f);
        glTranslatef(i * 0.6f, 1.5f, 0.0f);
        glScalef(0.2f, 0.3f, 0.05f);
        drawCube(0.5f, 1.0f, 4.0f);
        glPopMatrix();

        // Antennas
        glPushMatrix();
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(i * 0.6f, 2.3f, -0.5f);
        glRotatef(60, 1.0f, 0.0f, 0.0f);
        drawCylinder(0.05f, 1.0f, 10);
        glPopMatrix();
    }

    // Draw Screen and Visor
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 1.4f, 0.54f);
    glScalef(0.8f, 0.5f, 0.05f);
    drawCube(1.0f, 1.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.0f);
    glTranslatef(0.0f, 1.8f, 0.8f);
    glScalef(1.2f, 0.1f, 0.5f);
    drawCube(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void drawNeck() {
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.95f, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    drawCylinder(0.2f, 0.3f, 20);
    glPopMatrix();
}

void drawBody() {
    // Draw Body and jetpack
    glPushMatrix();
    glColor3f(1.0f, 0.55f, 0.0f);
    glTranslatef(0.0f, 0.2f, 0.0f);
    drawTrapezoid(1.2f, 1.0f, 1.0f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8f, 0.45f, 0.0f);
    glTranslatef(0.0f, 0.3f, -0.4f);
    glScalef(0.7f, 0.9f, 0.3f);
    drawCube(1.0f, 1.0f, 1.0f);
    glPopMatrix();

    // Draw Black Ridge and Hips
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f);
    glTranslatef(0.0f, -0.35f, 0.0f);
    drawCube(1.0f, 0.1f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.9f, 0.5f, 0.1f);
    glTranslatef(0.0f, -0.6f, 0.0f);
    drawTrapezoid(1.0f, 0.7f, 0.4f, 0.5f);
    glPopMatrix();
}

void drawArm(bool isLeft) {
    float direction = isLeft ? -1.0f : 1.0f;

    // Connect Shoulder + Upper Arm
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.85f * direction, 0.9f, 0.0f);
    glutSolidSphere(0.25, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.55f, 0.0f);
    glTranslatef(0.85f * direction, 0.65f, 0.0f);
    glTranslatef(0.0f, -0.25f, 0.0f);
    drawCube(0.3f, 0.5f, 0.3f);
    glPopMatrix();
}

void drawLeg(bool isLeft) {
    float direction = isLeft ? -1.0f : 1.0f;

    // Draw Hip, Upper Leg, Knee, and Lower Leg
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.4f * direction, -0.75f, 0.0f);
    glutSolidSphere(0.25, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.55f, 0.0f);
    glTranslatef(0.4f * direction, -1.125f, 0.0f);
    glTranslatef(0.0f, -0.375f, 0.0f);
    drawCube(0.4f, 0.75f, 0.4f);
    glPopMatrix();
}

void drawBot() {
    drawHead();
    drawNeck();
    drawBody();
    drawArm(true);
    drawArm(false);
    drawLeg(true);
    drawLeg(false);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera
    glm::vec3 cameraPos = glm::vec3(cameraDistance * std::sin(cameraAngleY) * std::cos(cameraAngleX),
        cameraDistance * std::sin(cameraAngleX),
        cameraDistance * std::cos(cameraAngleY) * std::cos(cameraAngleX));
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    glMultMatrixf(glm::value_ptr(view));
    drawBot();

    glutSwapBuffers();
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;
        cameraAngleY += dx * 0.005f;
        cameraAngleX += dy * 0.005f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isDragging = false;
        }
    }
    else if (button == 3) {
        cameraDistance -= 0.5f;
        if (cameraDistance < 2.0f) cameraDistance = 2.0f;
        glutPostRedisplay();
    }
    else if (button == 4) {
        cameraDistance += 0.5f;
        glutPostRedisplay();
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.8f, 0.6f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("KVRC/XBOT 4000 - Love Death and Robots");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}