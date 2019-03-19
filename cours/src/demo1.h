#ifndef DEMO1_H
#define DEMO1_H

#include "demo.h"
#include "readbmp.h"

#define PI 3.14159
#define W 512
#define H 256.0

// Wireframe sphere
class Demo1 : public Demo {
	
public:
	Demo1() : Demo(10), earth(0) {
		earth = readBMP("earth.bmp");
		clouds = readBMP("clouds.bmp");
	}


	~Demo1() {}


	float getR(int i, int j, int id) {
		int jj = j + H/2;
		switch (id) {
			case 0:
				return int(earth[3*(jj*W+i)+0] & 0xff)/H;
			case 1:
				return int(clouds[3*(jj*W+i)+0] & 0xff)/H;
		}
	}


	float getG(int i, int j, int id) {
		int jj = j + H/2;
		switch (id) {
			case 0:
				return int(earth[3*(jj*W+i)+1] & 0xff)/H;
			case 1:
				return int(clouds[3*(jj*W+i)+1] & 0xff)/H;
		}
	}

	float getB(int i, int j, int id) {
		int jj = j + H/2;
		switch (id) {
			case 0:
				return int(earth[3*(jj*W+i)+2] & 0xff)/H;
			case 1:
				return int(clouds[3*(jj*W+i)+2] & 0xff)/H;
		}
	}

	GLUquadric* qobj = gluNewQuadric();

	void sphere(float t) {
		glPushMatrix();
		glScalef(5.0,5.0,5.0);
		glRotatef(-50,0,0,1);
		glRotatef(-23,1,1,0);
		for(int i = 0; i < W; ++i) {
			for(int j = -H/2; j < H/2; ++j) {
				glBegin(GL_POINTS);
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
		glPushMatrix();
		glTranslatef(0,0,-2);
		glColor3f(1,1,1);
		gluCylinder(qobj, 0.02, 0.02, 4, 10, 10);
		glPopMatrix();
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
				glMaterialf(GL_FRONT, GL_SHININESS,0.6*H/2);
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
				glMaterialf(GL_FRONT, GL_SHININESS,0.6*H/2);
				glutSolidSphere(r,50,50);
				break;
			}
			case 9: {
				lighting();
				// glMaterialf(GL_FRONT, GL_SHININESS,0.6*H/2);
				sphere(t);
				break;
			}
		}
	}


	std::vector<char> earth;
	std::vector<char> clouds;

};


#endif