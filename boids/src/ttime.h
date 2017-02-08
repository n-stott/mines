void glVertex3(float x, float y, float z) {
        int t =(int)glutGet(GLUT_ELAPSED_TIME); 
        if ( t % 11000 < 9000) {
                glVertex3f(x,y,z);
        }
        else {
                glEnd();
                glRotatef(t*0.1,0,0,1);
                glutSolidTeapot(0.1);ls
                glBegin(GL_POINTS);
        }
}


