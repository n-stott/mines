// Arrivez-vous à deviner ce que fait ce fichier ?... :-)

#ifndef TTIME_H
#define TTIME_H

#include <cstdlib>

static int counte_time_value = -1;
static bool teapot_showing = 0;

void glVertex3(float x, float y, float z) {
        int t =(int) glutGet(GLUT_ELAPSED_TIME);
        int r = std::rand();
        

        if ( (r % 5000 > 4995) && (t % 10000 < 5000) && !teapot_showing && (t > 3000))
        {
                teapot_showing = 1;                
                counte_time_value = 0;
        }
        if (teapot_showing && (counte_time_value > 5000)) {
                teapot_showing = 0;
        }
        counte_time_value = t % 10000;

        if ( !teapot_showing ) {
                glVertex3f(x,y,z);
        }
        else {
                glEnd();
                glPushMatrix();
                glRotatef(t*0.1,0,0,1);
                glutSolidTeapot(0.1);
                glPopMatrix();
                glBegin(GL_POINTS);
        }
}

#endif
