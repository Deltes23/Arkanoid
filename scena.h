#ifndef SCENA_H_
#define SCENA_H_

#include <vector>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include "figury.h"
#include "cFizyka.h"
#include <iostream>
using namespace std;
class cScena
{
public:
	cScena();

	void rysuj();
	void klawisz(unsigned char znak, int x, int y);
	void inicjuj();
	void onMouseButton(int button, int state, int x, int y);
	void aktualizuj();
	void ustaw(int czas);
private:
	int aktywny;
	long long time;
	vector<cFigura*> figury;
};
extern cScena scena;


#endif
