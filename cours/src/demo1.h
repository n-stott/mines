#ifndef DEMO1_H
#define DEMO1_H

#include "glscene.h"

// Wireframe sphere
class Demo1 :  public glScene {
	
public:

	static void display();
	static void systemEvolution();

	Demo1() : nbStates(11), nbSubStates(2), earth(0), clouds(0) {
		earth = readBMP("earth2k.bmp");
		clouds = readBMP("clouds2k.bmp");
		loadTextureFromFile( "earth.bmp", 0 );
		loadTextureFromFile( "clouds.bmp", 1 );
	}


	~Demo1() {}


	float getR(int i, int j, int id) {
		int W = 512; float H = 256.0;
		int jj = j + H/2;
		return (!id ? int(earth[3*(jj*W+i)+0] & 0xff)/H : int(clouds[3*(jj*W+i)+0] & 0xff)/H);
	}


	float getG(int i, int j, int id) {
		int W = 512; float H = 256.0;
		int jj = j + H/2;
		return (!id ? int(earth[3*(jj*W+i)+1] & 0xff)/H : int(clouds[3*(jj*W+i)+1] & 0xff)/H);
	}

	float getB(int i, int j, int id) {
		int W = 512; float H = 256.0;
		int jj = j + H/2;
		return (!id ? int(earth[3*(jj*W+i)+2] & 0xff)/H : int(clouds[3*(jj*W+i)+2] & 0xff)/H);
	}

	GLUquadric* qobj = gluNewQuadric();

	void bad_earth(float W, float H, int id) {
		for(int i = 0; i < W; ++i) {
			for(int j = -H/2; j < H/2; ++j) {
				glBegin(GL_QUADS);
				glColor3f(getR(i,j,id), getG(i,j,id), getB(i,j,id));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					i++;
				glColor3f(getR(i,j,id), getG(i,j,id), getB(i,j,id));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					j++;
				glColor3f(getR(i,j,id), getG(i,j,id), getB(i,j,id));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					i--;
				glColor3f(getR(i,j,id), getG(i,j,id), getB(i,j,id));
				glNormal3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H));
					glVertex3f( cos(i*PI/H)*cos(j*PI/H), sin(i*PI/H)*cos(j*PI/H), sin(j*PI/H) );
					j--;
				glEnd();
			}
		}
	}

	void bad_clouds(float W, float H, int id) {
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
	}






	void sphere_bad(float t) {
		int W = 512; float H = 256.0;
		glPushMatrix();
			glScalef(5.0,5.0,5.0);
			glRotatef(-50,0,0,1);
			glRotatef(-23,1,1,0);
			bad_earth(W, H, 0);
			glScalef(1.01,1.01,1.01);
			glRotatef(0.001*t,0,0,1);
			bad_clouds(W,H,1);
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

	void sphere_good(float t) {
		int W = 64; float H = 32.0;
   		glEnable(GL_TEXTURE_2D);
     	glBindTexture(GL_TEXTURE_2D, texture[0]);
		glPushMatrix();
			glScalef(5.0,5.0,5.0);
			glRotatef(-50,0,0,1);
			glRotatef(-23,1,1,0);
			sphere(W, H);
			glColor3f(0.6,0.6,0.6);
			if (subState > 0)
				glutWireSphere(1,W,H);

		    glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
	     	glBindTexture(GL_TEXTURE_2D, texture[1]);
	     	glPushMatrix();
				glScalef(1.01,1.01,1.01);
				glRotatef(0.001*t,0,0,1);
				sphere(W, H);
				glColor3f(1,1,1);
				if (subState > 0)
					glutWireSphere(1,W,H);
			glPopMatrix();
		glPopMatrix();
	}

	void init()  {
		switch(state) {
			case -1:
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				glLineWidth(2.0);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glDisable(GL_COLOR_MATERIAL);
				glDisable(GL_NORMALIZE);
				glShadeModel(GL_FLAT);	
				break;
			case 6:
				glLineWidth(2.0);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHTING);
				glDisable(GL_COLOR_MATERIAL);
				glEnable(GL_NORMALIZE);
				glShadeModel(GL_FLAT);		
				glEnable(GL_CULL_FACE);
				break;
			case 7:
			case 8:
				glLineWidth(2.0);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHTING);
				glDisable(GL_COLOR_MATERIAL);
				glEnable(GL_NORMALIZE);
				glShadeModel(GL_SMOOTH);		
				glEnable(GL_CULL_FACE);
				break;
			case 9:
			case 10:
				gluQuadricNormals(qobj, GLU_SMOOTH);
				glLineWidth(3.0);
				break;
		}
	}

	void lighting()  {
		float amb = 0.1;
		float ambientLight[] = { amb, amb, amb, 1.0f };
		float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float position[] = { -20.0f, 20.0f, 0.0f, 0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
	}

	void display(float t)  {

		float r = 5;

		switch(state) {
			case -1:
			switch (subState) {
			case 0:
				glBegin(GL_LINES);
				glVertex3f(1,1,-2);
				glVertex3f(1,-2,1);
				glEnd();
				break;
			case 1:
				glBegin(GL_LINE_LOOP);
				glVertex3f(1,1,-2);
				glVertex3f(1,-2,1);
				glVertex3f(-2,1,1);
				glEnd();
				break;
			case 2:
				glBegin(GL_LINE_LOOP);
				glVertex3f(1,1,1);
				glVertex3f(1,1,-1);
				glVertex3f(1,-1,-1);
				glVertex3f(1,-1,1);
				glVertex3f(-1,-1,1);
				glVertex3f(-1,-1,-1);
				glVertex3f(-1,1,-1);
				glVertex3f(-1,1,1);
				glEnd();
				break;
			case 3:
				glBegin(GL_QUADS);
				glVertex3f(1,-1,0);
				glVertex3f(1,1,0);
				glVertex3f(-1,1,0);
				glVertex3f(-1,-1,0);
				glEnd();
				break;
			case 4:
				glBegin(GL_TRIANGLES);
				glVertex3f(1,1,-2);
				glVertex3f(1,-2,1);
				glVertex3f(-2,1,1);
				glEnd();
				break;
			}
				break;
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

	void next() {
		// if (state < nbStates-1) {
			state++;
			subState = 0;
		// }
		init();
	}
	void prev() {
		// if (state > 0) {
			state--;
			subState = 0;
		// }
		init();
	}

	void snext() {
		// if (subState < nbSubStates-1)
			subState++;
		init();
	}
	void sprev() {
		// if (subState > 0)
			subState--;
		init();
	}
	unsigned int state = -1;
	unsigned int subState = 0;


private:
	unsigned int nbStates = 1;
	unsigned int nbSubStates = 1;

};

void Demo1::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	//Camera setup
	camera.lookAt();
    //Display functions
    display(t);

	glutSwapBuffers();
}

void Demo1::systemEvolution() {
	updateTime();
}



#endif