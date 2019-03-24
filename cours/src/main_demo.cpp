#include "glscene.h"
#include "earth.h"

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) 
{
	glScene::_createWindow_(argc, argv);
	glScene::_setCallbacks_();

	glScene::addObject(new Earth());

	glScene::_start_();
	
	return 0;
}
