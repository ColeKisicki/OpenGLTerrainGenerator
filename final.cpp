#include "CSCIx229.hpp"
#include "Scene.hpp"
#include "Terrain.hpp"
#include "Cube.hpp"
#include "basic_structures.hpp"
#include "Camera.hpp"
#include "MarchingCubeObject.hpp"
#include "glm/glm.hpp"
#include <ctime>
#include <random>
#include <iostream>

int fov = 55;    //  Field of view (for perspective)
double asp = 1;  //  Aspect ratio
double dim = 20; //  Size of world

int frameCount = 0;   // Count of frames rendered
int currentTime = 0;  // Current time
int previousTime = 0; // Time at the previous frame

// Function to calculate and display FPS
void displayFPS()
{
   frameCount++;
   currentTime = glutGet(GLUT_ELAPSED_TIME);

   int timeInterval = currentTime - previousTime;
   if (timeInterval > 1000)
   {
      float fps = frameCount * 1000.0f / timeInterval;
      std::cout << "FPS: " << fps << std::endl;

      frameCount = 0;
      previousTime = currentTime;
   }
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // glEnable(GL_CULL_FACE);
   // glCullFace(GL_BACK);
   displayFPS(); // Call function to display FPS
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   glClearColor(0.53f, 0.8f, 0.86f, 1.0f);
   Scene::GetScene()->RenderScene();

   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
   //  Tell GLUT it is necessary to redisplay the scene
   // glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
   //  PageUp key - increase dim
   if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim > 1)
      dim -= 0.1;
   //  Update projection
   Project(fov, asp, dim);
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

   // Handle camera movement
   Scene::GetScene()->GetCamera()->HandleKeyPress(ch);
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
   glutPostRedisplay();
}

void motion(int x, int y)
{
   Scene::GetScene()->GetCamera()->HandleMouse(x, y);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char *argv[]) {
    // Initialize GLUT
    glutInit(&argc, argv);
    // Request double buffered, true color window with Z buffering at 600x600
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Terrain Generator");

#ifdef USEGLEW
    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        Fatal("Error initializing GLEW\n");
    }
#endif

    // ... Your existing setup for light, cube, etc ...

    // Create an instance of MarchingCubes
    auto* terrain = new Terrain(0.5f); // Example isolevel
    terrain->GenerateTerrain();
    // Generate the mesh (you need to define how to populate your density grid)
    terrain->GenerateMesh(); 
    // Initialize shaders for MarchingCubes
    terrain->InitializeShaders();
    // Prepare the mesh for rendering
    terrain->PrepareVertexData();

    Scene::GetScene()->AddSceneObject(terrain);
    

    auto Sun = new Light();
    Sun->SetLocation(glm::vec3(100.f,100.f,100.f));
    Scene::GetScene()->AddLight(Sun);

    // Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(motion); // Use passive motion function

    // Check for any OpenGL errors
    ErrCheck("init");

    // Enter the GLUT event processing loop
    glutMainLoop();
    return 0;
}
