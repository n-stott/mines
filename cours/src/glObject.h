#ifndef GLOBJECT_H
#define GLOBJECT_H

#include "Time.h"
#include "rgbImage.h"
#include <GL/glut.h>

class glObject {
public:
	glObject() {}
	virtual ~glObject() {};

	virtual void display(Time& time) = 0;
	virtual void lighting(Time& time) = 0;
	virtual void move(Time& time) = 0;

	GLuint   texture[2];         // Storage For One Texture ( NEW )
	void loadTextureFromFile(char *filename, int tex) {   
		glClearColor (0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_FLAT);
		glEnable(GL_DEPTH_TEST);
		RgbImage theTexMap( filename );

		glGenTextures(1, &texture[tex]);               // Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture[tex]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
	}
};

#endif