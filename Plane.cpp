#include "Plane.hpp"
#include "CSCIx229.hpp"

void Plane::Display()
{
    if (!IsVisible)
        return;
    //  Save transformation
    glPushMatrix();
    glShadeModel(SmoothShading ? GL_SMOOTH : GL_FLAT);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ObjectMaterial.shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ObjectMaterial.specularColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ObjectMaterial.emmisiveColor);

    //  Offset
    glTranslated(Location.x, Location.y, Location.z);
    glRotated(Rotation.x, 1, 0, 0);
    glRotated(Rotation.y, 0, 1, 0);
    glRotated(Rotation.z, 0, 0, 1);
    glScaled(Scale.x, Scale.y, Scale.z);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_POLYGON);
    //
    glColor3f(1,1,1);
    glNormal3f(0, 1, 0);

    glTexCoord2f(1*textureScale, 0*textureScale);
    glVertex3f(1, 0, 1);
    glTexCoord2f(1*textureScale, 1*textureScale);
    glVertex3f(1, 0, -1);
    glTexCoord2f(0*textureScale, 1*textureScale);
    glVertex3f(-1, 0, -1);
    glTexCoord2f(0*textureScale, 0*textureScale);
    glVertex3f(-1, 0, 1);

    //  End
    glEnd();
    //  Undo transofrmations
    glPopMatrix();
}
