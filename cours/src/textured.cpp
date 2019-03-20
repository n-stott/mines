#include <stdlib.h>
#include <GL/glut.h>
#include "rgbImage.h"
#include <math.h>
#define PI 3.14159
#define W 36.0
#define H 18.0
GLfloat xRotated, yRotated, zRotated;
GLuint   texture[1];         // Storage For One Texture ( NEW )
/*
* Read a texture map from a BMP bitmap file.
*/
void loadTextureFromFile(char *filename)
{   
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   RgbImage theTexMap( filename );

   // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
   //    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

  
   glGenTextures(1, &texture[0]);               // Create The Texture
      glBindTexture(GL_TEXTURE_2D, texture[0]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      // Typical Texture Generation Using Data From The Bitmap
   
      glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

}

void sphere(float t) {
    glPushMatrix();
    // glScalef(5.0,5.0,5.0);
    glRotatef(-50,0,0,1);
    glRotatef(-23,1,1,0);
    for(int i = 0; i < W; ++i) {
      for(int j = -H/2; j < H/2; ++j) {
        glBegin(GL_QUADS);
        glTexCoord2f(i/W, 0.5+j/H);
        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
          i++;
        glTexCoord2f(i/W, 0.5+j/H);
        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
          j++;
        glTexCoord2f(i/W, 0.5+j/H);
        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
          i--;
        glTexCoord2f(i/W, 0.5+j/H);
        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
          j--;
        glEnd();
      }
    }
    glPopMatrix();
  }

/*
* Draw the texture in the OpenGL graphics window
*/
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, texture[0]);
   glLoadIdentity();
   glTranslatef(0.0,0.0,-5);
     glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);
    sphere(1);
   // glutSolidTeapot(1);
   // glutSolidSphere(1,50,50);
   glFlush();
   glDisable(GL_TEXTURE_2D);
  
}

void resizeWindow(int x, int y)
{
if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

char* filename = "./earth.bmp";
void idleFunc(void)
{

     yRotated += 0.01;
     zRotated += 0.01;
    drawScene();
}
// int main(int argc, char** argv)
// {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(240, 240);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow(argv[0]);

//    loadTextureFromFile( filename );
   
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(resizeWindow);
//    glutKeyboardFunc(keyboard);
//      glutIdleFunc(idleFunc);
//    glutMainLoop();
//    return 0;
// }

