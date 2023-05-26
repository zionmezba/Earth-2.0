#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>
#include "SOIL.h"

GLuint earthTex;
GLuint skyBg;
GLuint moonTex;
GLuint sunTex;
GLuint comTex;

float rotationAngle = 0.0f;       // Current rotation angle
float cameraDistance = 4.5f;      // Distance of the camera from the origin
GLfloat moonRadius = 0.2f;        // Radius of the moon
GLfloat moonDistance = 1.9f;      // Distance of the moon from the Earth
GLfloat moonRotationSpeed = 1.0f; // Rotation speed of the moon around the Earth

GLfloat cometRadius = 0.1f;              // Radius of the comet
GLfloat cometSpeed = 0.05f;              // Speed of the comet
GLfloat cometPosX, cometPosY, cometPosZ; // Position of the comet
GLfloat cometVelX, cometVelY, cometVelZ; // Velocity of the comet

bool cometLaunched = false; // Flag to indicate if the comet is launched
GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = 5.0f;
GLfloat viewRotateX = 0.0f;
GLfloat viewRotateY = 0.0f;

void loadEarthTex()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &earthTex);
    glBindTexture(GL_TEXTURE_2D, earthTex);

    int width, height;
    unsigned char *image = SOIL_load_image("F:/CSE~DIU/ZiON/Graphics/Earth 2.0/earth_texture.png", &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void loadSky()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &skyBg);
    glBindTexture(GL_TEXTURE_2D, skyBg);

    int width, height;
    unsigned char *image2 = SOIL_load_image("F:/CSE~DIU/ZiON/Graphics/Earth 2.0/sky_bg2.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    SOIL_free_image_data(image2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void loadMoonTex()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &moonTex);
    glBindTexture(GL_TEXTURE_2D, moonTex);

    int width, height;
    unsigned char *image3 = SOIL_load_image("F:/CSE~DIU/ZiON/Graphics/Earth 2.0/mon_tex2.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
    SOIL_free_image_data(image3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void loadSunTex()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &sunTex);
    glBindTexture(GL_TEXTURE_2D, sunTex);

    int width, height;
    unsigned char *image3 = SOIL_load_image("F:/CSE~DIU/ZiON/Graphics/Earth 2.0/sun_tex.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
    SOIL_free_image_data(image3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void loadComTex()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &comTex);
    glBindTexture(GL_TEXTURE_2D, comTex);

    int width, height;
    unsigned char *image3 = SOIL_load_image("F:/CSE~DIU/ZiON/Graphics/Earth 2.0/comet_tex.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
    SOIL_free_image_data(image3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void lighting()
{
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Set up the light parameters
    GLfloat lightPosition[] = {100.0f, 100.0f, 100.0f, 0.0f };
    GLfloat lightAmbient[] = {1.0f, 0.95f, 0.9f, 1.0f };
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = {10.0f, 10.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    // Enable depth testing
    //glEnable(GL_DEPTH_TEST);
}

void drawSphere(double radius, int slices, int stacks)
{
    glPushMatrix();
    glRotatef(rotationAngle, 1.0f, 1.0f, 0.0f); // Rotate along the y-axis
    glRotatef(-10.0f, 1.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, earthTex);
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, slices, stacks);
    gluDeleteQuadric(quadric);
    glPopMatrix();
}

void drawMoonSphere(double radius, int slices, int stacks)
{
    // Render the Moon
    glPushMatrix();
    glRotatef(rotationAngle * moonRotationSpeed, 0.0f, 1.0f, 0.0f); // Rotate the moon around the Earth
    glTranslatef(moonDistance, 0.0f, 0.0f);  // Translate the moon to its orbit distance from the Earth
    // glutSolidSphere(moonRadius, 20, 20); // Render the moon as a solid sphere
    glBindTexture(GL_TEXTURE_2D, moonTex);
    GLUquadric *quadric2 = gluNewQuadric();
    gluQuadricTexture(quadric2, GL_TRUE);
    gluSphere(quadric2, moonRadius, slices, stacks);
    gluDeleteQuadric(quadric2);
    glPopMatrix();
}

void drawSunSphere(double radius, int slices, int stacks)
{
    // Render the Sun
    glPushMatrix();
    glTranslatef(2.4, 2.5f, 0.0f);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, sunTex);
    GLUquadric *quadric2 = gluNewQuadric();
    gluQuadricTexture(quadric2, GL_TRUE);
    gluSphere(quadric2, radius, slices, stacks);
    gluDeleteQuadric(quadric2);
    glPopMatrix();
}

void drawComet(double radius, int slices, int stacks)
{
    // Render the Comet
    glPushMatrix();
    //glRotatef(rotationAngle * moonRotationSpeed, 0.0f, 1.0f, 0.0f); // Rotate the moon around the Earth
    glTranslatef(cometPosX, cometPosY, cometPosZ);
    glRotatef(rotationAngle, 0.1f, 1.0f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, comTex);
    GLUquadric *quadric2 = gluNewQuadric();
    gluQuadricTexture(quadric2, GL_TRUE);
    gluSphere(quadric2, radius, slices, stacks);
    gluDeleteQuadric(quadric2);
    glPopMatrix();
}

void drawBackground()
{
    glBindTexture(GL_TEXTURE_2D, skyBg);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -2.0f);
    glEnd();
}

void launchComet()
{
    GLfloat modelviewMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    GLfloat projectionMatrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Render the comet if it is launched
    if (cometLaunched)
    {
        glPushMatrix();
        drawComet(0.1, 10, 10);
        glPopMatrix();

        // Update the position of the comet
        cometPosX += cometVelX;
        cometPosY += cometVelY;
        cometPosZ += cometVelZ;

        // Check if the comet has reached the Earth
        GLfloat distance = sqrt(pow(cometPosX - 0.0f, 2) + pow(cometPosY - 0.0f, 2) + pow(cometPosZ - 0.0f, 2));
        if (distance <= 0.5f + cometRadius)
        {
            // Comet has reached the Earth, reset the comet
            cometLaunched = false;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, cameraDistance, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Render the starry background
    glPushMatrix();
    glScalef(4.0f, 3.0f, 1.0f);
    drawBackground();
    glPopMatrix();

    lighting();
    // Render the Moon sphere
    glPushMatrix();
    drawMoonSphere(0.2, 20, 20);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    lighting();
    // Render the Earth sphere
    glPushMatrix();
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Orbit a the origin
    drawSphere(1.0, 50, 50);
    glPopMatrix();
    glDisable(GL_LIGHTING);
    drawSunSphere(.1,30,30);
    launchComet();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value)
{
    rotationAngle += 0.4f; // Adjust the rotation speed

    if (rotationAngle >= 360.0f)
    {
        rotationAngle -= 360.0f;
    }

    rotationAngle += 0.5f; // Adjust the rotation speed of the Earth if desired
    if (rotationAngle >= 360.0f)
        rotationAngle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    const float cameraSpeed = 5.1f; // Adjust the camera speed
    const float cameraSpeedZ = 0.1f;
    switch (key)
    {
    case 'a':
        rotationAngle -= cameraSpeed;
        break;
    case 'd':
        rotationAngle += cameraSpeed;
        break;
    case 'w':
        cameraDistance -= cameraSpeedZ;
        break;
    case 's':
        cameraDistance += cameraSpeedZ;
        break;
    case 'q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !cometLaunched)
    {
        // Get the window width and height
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        // Convert the mouse coordinates to NDC (Normalized Device Coordinates)
        GLfloat ndcX = (2.0f * x) / windowWidth - 1.0f;
        GLfloat ndcY = 1.0f - (2.0f * y) / windowHeight;

        // Convert NDC to view space coordinates
        GLfloat viewMatrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);

        GLfloat invViewMatrix[16];
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);
        glRotatef(viewRotateY, 1.0f, 0.0f, 0.0f);
        glRotatef(viewRotateX, 0.0f, 1.0f, 0.0f);
        glGetFloatv(GL_MODELVIEW_MATRIX, invViewMatrix);

        GLfloat viewX = ndcX * invViewMatrix[0] + ndcY * invViewMatrix[4] + invViewMatrix[12];
        GLfloat viewY = ndcX * invViewMatrix[1] + ndcY * invViewMatrix[5] + invViewMatrix[13];
        GLfloat viewZ = ndcX * invViewMatrix[2] + ndcY * invViewMatrix[6] + invViewMatrix[14];

        // Calculate the direction vector from the camera position to the click position
        GLfloat directionX = viewX - cameraX;
        GLfloat directionY = viewY - cameraY;
        GLfloat directionZ = viewZ - cameraZ;

        // Normalize the direction vector
        GLfloat length = sqrt(directionX * directionX + directionY * directionY + directionZ * directionZ);
        directionX /= length;
        directionY /= length;
        directionZ /= length;

        // Set the position and velocity of the comet
        cometPosX = cameraX;
        cometPosY = cameraY;
        cometPosZ = cameraZ;
        cometVelX = directionX * cometSpeed;
        cometVelY = directionY * cometSpeed;
        cometVelZ = directionZ * cometSpeed;

        // Launch the comet
        cometLaunched = true;
    }

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Earth 2.0");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    loadEarthTex();
    loadSky();
    loadMoonTex();
    loadSunTex();
    loadComTex();
    glutTimerFunc(16, update, 0); // Start the update loop
    PlaySound("bgm.wav", 0, SND_FILENAME);
    glutMainLoop();
    return 0;
}
