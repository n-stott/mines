#ifndef EARTH_H
#define EARTH_H

#include "glObject.h"

#include "readbmp.h"
#include <math.h>

#define PI 3.14159


class Earth : public glObject {

public:
	Earth() {
		loadTextureFromFile( "earth.bmp", 0 );
		loadTextureFromFile( "clouds.bmp", 1 );
	}

	~Earth() {

	}

	void sphere(float W, float H) {
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
	}

	void lighting(Time& time) {
		float amb = 0.1;
		float ambientLight[] = { amb, amb, amb, 1.0f };
		float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float position[] = { -20.0f, 20.0f, 0.0f, 0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
	}

	void display(Time& time) {
		lighting(time);
		int W = 64; float H = 32.0;
   		glEnable(GL_TEXTURE_2D);
     	glBindTexture(GL_TEXTURE_2D, texture[0]);
		glPushMatrix();
			glScalef(5.0,5.0,5.0);
			glRotatef(-50,0,0,1);
			glRotatef(-23,1,1,0);
			sphere(W, H);
			glColor3f(0.6,0.6,0.6);

		    glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
	     	glBindTexture(GL_TEXTURE_2D, texture[1]);
	     	glPushMatrix();
				glScalef(1.01,1.01,1.01);
				glRotatef(0.001*time.t,0,0,1);
				sphere(W, H);
				glColor3f(1,1,1);
			glPopMatrix();
		glPopMatrix();
	}

	void move(Time& time) {}
	
};

#endif