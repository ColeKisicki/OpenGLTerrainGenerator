#include "Cube.hpp"
#include "CSCIx229.hpp"

void Cube::Display()
{
    if(!IsVisible) return;
    glPushMatrix();
    glShadeModel(SmoothShading ? GL_SMOOTH : GL_FLAT);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ObjectMaterial.shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ObjectMaterial.specularColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ObjectMaterial.emmisiveColor);
    //  Save transformation
    //  Offset
    glTranslated(Location.x, Location.y, Location.z);
    glRotated(Rotation.x, 1, 0, 0);
    glRotated(Rotation.y, 0, 1, 0);
    glRotated(Rotation.z, 0, 0, 1);
    glScaled(Scale.x, Scale.y, Scale.z);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glColor3f(1, 0, 0);
    glNormal3f(0, 0, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(+1, -1, 1);
    glVertex3f(+1, +1, 1);
    glVertex3f(-1, +1, 1);
    //  Back
    glColor3f(0, 0, 1);
    glNormal3f(0, 0, -1);
    glVertex3f(+1, -1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, +1, -1);
    glVertex3f(+1, +1, -1);
    //  Right
    glColor3f(1, 1, 0);
    glNormal3f(+1, 0, 0);
    glVertex3f(+1, -1, +1);
    glVertex3f(+1, -1, -1);
    glVertex3f(+1, +1, -1);
    glVertex3f(+1, +1, +1);
    //  Left
    glColor3f(0, 1, 0);
    glNormal3f(-1, 0, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, +1);
    glVertex3f(-1, +1, +1);
    glVertex3f(-1, +1, -1);
    //  Top
    glColor3f(0, 1, 1);
    glNormal3f(0, +1, 0);
    glVertex3f(-1, +1, +1);
    glVertex3f(+1, +1, +1);
    glVertex3f(+1, +1, -1);
    glVertex3f(-1, +1, -1);
    //  Bottom
    glColor3f(1, 0, 1);
    glNormal3f(0, -1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(+1, -1, -1);
    glVertex3f(+1, -1, +1);
    glVertex3f(-1, -1, +1);
    //  End
    glEnd();
    //  Undo transofrmations
    glPopMatrix();
}
