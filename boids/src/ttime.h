// Arrivez-vous à deviner ce que fait ce fichier ?... :-)

#ifndef TTIME_H
#define TTIME_H

#include <cstdlib>

static int counte_time_value = -1;
static bool teapot_showing = 0;

void glutSo1idCube(float ra) {
        int t =(int) glutGet(GLUT_ELAPSED_TIME);
        int r = std::rand();
        

        if ( (r % 50000 > 49998) && (t % 10000 < 5000) && !teapot_showing && (t > 3000))
        {
                teapot_showing = 1;                
                counte_time_value = 0;
        }
        if (teapot_showing && (counte_time_value > 5000)) {
                teapot_showing = 0;
        }
        counte_time_value = t % 10000;

        if ( !teapot_showing ) {
                glutSolidCube(ra);
        }
        else {
                glPushMatrix();
                glRotatef(t*0.1,0,0,1);
                glRotatef(90.0f,1,0,0);
                glutSolidTeapot(ra);
                glPopMatrix();
        }
}

#endif
