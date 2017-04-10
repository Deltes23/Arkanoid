#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include "scena.h"


using namespace std;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	scena.inicjuj(); //inicluje scene
	glutMainLoop();
	return 0;
}

