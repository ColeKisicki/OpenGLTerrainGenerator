#include "CSCIx229.hpp"
#include "Scene.hpp"
#include "Terrain.hpp"
#include "Camera.hpp"
#include "glm/glm.hpp"
#include <ctime>
#include <random>

int th = 0;     //  Azimuth of view angle
int ph = 0;     //  Elevation of view angle
int fov = 55;   //  Field of view (for perspective)
int obj = 0;    //  Scene/opbject selection
double asp = 1; //  Aspect ratio
double dim = 3; //  Size of world



/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   glClearColor(0.53f, 0.8f, 0.86f, 1.0f);

   double Ex = -2 * dim * Sin(th) * Cos(ph);
   double Ey = +2 * dim * Sin(ph);
   double Ez = +2 * dim * Cos(th) * Cos(ph);
   gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
   Scene::GetScene()->RenderScene();

   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim > 1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(fov, asp, dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Reproject
   Project(fov, asp, dim);
   glutIdleFunc(idle);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height)
{
   //  Ratio of the width to the height of the window
   asp = (height > 0) ? (double)width / height : 1;
   //  Set the viewport to the entire window
   glViewport(0, 0, RES * width, RES * height);
   //  Set projection
   Project(fov, asp, dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char *argv[])
{
   Terrain t;
   //  Initialize GLUT
   glutInit(&argc, argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(400, 400);
   glutCreateWindow("Terrain Generator");

#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit() != GLEW_OK)
      Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
