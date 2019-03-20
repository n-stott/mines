#ifndef DEMO1_H
#define DEMO1_H

#include "demo.h"
#include "readbmp.h"
#include "rgbImage.h"

#define PI 3.14159
// #define W 32
// #define W 512
// #define H 16.0
// #define H 256.0

// Wireframe sphere
class Demo1 : public Demo {
	
public:
	Demo1() : Demo(11,2), earth(0), clouds(0) {
		earth = readBMP("earth.bmp");
		clouds = readBMP("clouds.bmp");
		loadTextureFromFile( "earth.bmp", 0 );
		loadTextureFromFile( "clouds.bmp", 1 );
	}


	~Demo1() {}


	float getR(int i, int j, int id) {
		int W = 512; float H = 256.0;
		int jj = j + H/2;
		return (id ? int(earth[3*(jj*W+i)+0] & 0xff)/H : int(clouds[3*(jj*W+i)+0] & 0xff)/H);
	}


	float getG(int i, int j, int id) {
		int W = 512; float H = 256.0;
		int jj = j + H/2;
		return (id ? int(earth[3*(jj*W+i)+1] & 0xff)/H : int(clouds[3*(jj*W+i)+1] & 0xff)/H);
	}

	float getB(int i, int j, int id) {
		int W = 512; float H = 256.0;
		int jj = j + H/2;
		return (id ? int(earth[3*(jj*W+i)+2] & 0xff)/H : int(clouds[3*(jj*W+i)+2] & 0xff)/H);
	}

	GLUquadric* qobj = gluNewQuadric();

	void sphere_bad(float t) {
		int W = 512; float H = 256.0;
		glPushMatrix();
		glScalef(5.0,5.0,5.0);
		glRotatef(-50,0,0,1);
		glRotatef(-23,1,1,0);
		for(int i = 0; i < W; ++i) {
			for(int j = -H/2; j < H/2; ++j) {
				glBegin(GL_QUADS);
				glColor3f(getR(i,j,0), getG(i,j,0), getB(i,j,0));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					i++;
				glColor3f(getR(i,j,0), getG(i,j,0), getB(i,j,0));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					j++;
				glColor3f(getR(i,j,0), getG(i,j,0), getB(i,j,0));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					i--;
				glColor3f(getR(i,j,0), getG(i,j,0), getB(i,j,0));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					j--;
				glEnd();
			}
		}
		glScalef(1.01,1.01,1.01);
		glRotatef(0.003*t,0,0,1);
		for(int i = 0; i < W; ++i) {
			for(int j = -H/2; j < H/2; ++j) {
				glBegin(GL_QUADS);
				glColor4f(getR(i,j,1), getG(i,j,1), getB(i,j,1), (getR(i,j,1)));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					i++;
				glColor4f(getR(i,j,1), getG(i,j,1), getB(i,j,1), (getR(i,j,1)));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					j++;
				glColor4f(getR(i,j,1), getG(i,j,1), getB(i,j,1), (getR(i,j,1)));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					i--;
				glColor4f(getR(i,j,1), getG(i,j,1), getB(i,j,1), (getR(i,j,1)));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					j--;
				glEnd();
			}
		}
		glColor3f(1,1,1);
		if (subState > 0)
		glutWireSphere(1,W,H);
		glPushMatrix();
		glTranslatef(0,0,-2);
		glColor3f(1,1,1);
		gluCylinder(qobj, 0.02, 0.02, 4, 10, 10);
		glPopMatrix();
		glPopMatrix();
	}

	void loadTextureFromFile(char *filename, int tex)
{   
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   RgbImage theTexMap( filename );

   // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
   //    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

  
    glGenTextures(1, &texture[tex]);               // Create The Texture
    glBindTexture(GL_TEXTURE_2D, texture[tex]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      // Typical Texture Generation Using Data From The Bitmap
   
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

}

	void sphere_good(float t) {
		int W = 64; float H = 32.0;
   glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, texture[0]);
		glPushMatrix();
		glScalef(5.0,5.0,5.0);
		glRotatef(-50,0,0,1);
		glRotatef(-23,1,1,0);
		for(int i = 0; i < W; ++i) {
	      for(int j = -H/2; j < H/2; ++j) {
	      	glPointSize(5.0);
	        glBegin(GL_QUADS);
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          i++;
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          j++;
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          i--;
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          j--;
	        glEnd();
	      }
	    }
	    glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
     glBindTexture(GL_TEXTURE_2D, texture[1]);
		glScalef(1.01,1.01,1.01);
		glRotatef(0.003*t,0,0,1);
		for(int i = 0; i < W; ++i) {
	      for(int j = -H/2; j < H/2; ++j) {
	        glBegin(GL_QUADS);
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          i++;
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          j++;
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          i--;
	        glTexCoord2f(1.0*i/W, 0.5+j/H);
	        glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
	          glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
	          j--;
	        glEnd();
	      }
	    }
		if (subState > 0)
		glutWireSphere(1,W,H);
		// glPushMatrix();
		// glTranslatef(0,0,-2);
		// glColor3f(1,1,1);
		// gluCylinder(qobj, 0.02, 0.02, 4, 10, 10);
		// glPopMatrix();
		glPopMatrix();
	}

	void init() override {
		switch(state) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glDisable(GL_COLOR_MATERIAL);
				glDisable(GL_NORMALIZE);
				glShadeModel(GL_FLAT);	
				break;
			case 6:
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHTING);
				glDisable(GL_COLOR_MATERIAL);
				glEnable(GL_NORMALIZE);
				glShadeModel(GL_FLAT);		
				glEnable(GL_CULL_FACE);
				break;
			case 7:
			case 8:
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHTING);
				glDisable(GL_COLOR_MATERIAL);
				glEnable(GL_NORMALIZE);
				glShadeModel(GL_SMOOTH);		
				glEnable(GL_CULL_FACE);
				break;
			case 9:
			case 10:
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_BLEND);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHTING);
				glEnable(GL_COLOR_MATERIAL);
				glEnable(GL_NORMALIZE);
				glShadeModel(GL_SMOOTH);		
				glEnable(GL_CULL_FACE);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				gluQuadricNormals(qobj, GLU_SMOOTH);
				break;
		}
	}

	void lighting() override {
		float amb = -0.1;
		float ambientLight[] = { amb, amb, amb, 1.0f };
		float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float position[] = { -20.0f, 20.0f, 0.0f, 0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
	}

	void display(float t) override {

		float r = 5;

		switch(state) {
			case 0:
				glColor3f(1,1,1);
				glutWireSphere(r,4,4);
				break;
			case 1:
				glColor3f(1,1,1);
				glutWireSphere(r,8,8);
				break;
			case 2:
				glColor3f(1,1,1);
				glutWireSphere(r,20,20);
				break;
			case 3:
				glColor3f(1,1,1);
				glutWireSphere(r,50,50);
				break;
			case 4:
				glColor3f(1,1,1);
				glutWireSphere(r,10,10);
				break;
			case 5:
			case 6:
			case 7: {
				lighting();
				float amb[] = {0.1   ,0.1876,0.1745,1.0};
				float dif[] = {0.396 ,0.7415,0.6910,1.0};
				float spe[] = {0.2973,0.3082,0.3066,1.0};
				glMaterialfv(GL_FRONT, GL_AMBIENT,  amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE,  dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
				glMaterialf(GL_FRONT, GL_SHININESS,0.6*128);
				glutSolidSphere(r,10,10);
				break;
			}
			case 8: {
				lighting();
				float amb[] = {0.1   ,0.1876,0.1745,1.0};
				float dif[] = {0.396 ,0.7415,0.6910,1.0};
				float spe[] = {0.2973,0.3082,0.3066,1.0};
				glMaterialfv(GL_FRONT, GL_AMBIENT,  amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE,  dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
				glMaterialf(GL_FRONT, GL_SHININESS,0.6*128);
				glutSolidSphere(r,50,50);
				break;
			}
			case 9: {
				lighting();
				sphere_bad(t);
				break;
			}
			case 10: {
				lighting();
				sphere_good(t);
				break;
			}
		}
	}


	std::vector<char> earth;
	std::vector<char> clouds;

GLfloat xRotated, yRotated, zRotated;
GLuint   texture[2];         // Storage For One Texture ( NEW )

};


#endif