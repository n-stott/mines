#include "draw.h"

void draw() {
  glLineWidth(2.0);
  glBegin(GL_LINE_STRIP);
  glColor3f(1,1,1);
  glVertex3f(-1,0,-1);
  glVertex3f(-1,0,1);
  glVertex3f(0,0,0);
  glVertex3f(1,0,1);
  glVertex3f(1,0,-1);
  glEnd();
}