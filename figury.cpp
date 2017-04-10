#include "figury.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cmath>

cProstokat::cProstokat() :a(1), b(.1) {	
	granica.xa = -a / 2;
	granica.ya = -b / 2;
	granica.xb = a / 2;
	granica.yb = b / 2;
}

cProstokat::cProstokat(float _a, float _b) :a(_a), b(_b) {
	granica.xa = -a / 2;
	granica.ya = -b / 2;
	granica.xb = a / 2;
	granica.yb = b / 2;
}

void cProstokat::rysuj() {
	glPushMatrix();
	glColor3f(R, G, B);
	glTranslatef(x, y, 0);
	glRotatef(alpha, 0, 0, 1);
	glBegin(GL_POLYGON);
		glVertex2f(a / 2, b / 2);
		glVertex2f(-a / 2, b / 2);
		glVertex2f(-a / 2, -b / 2);
		glVertex2f(a / 2, -b / 2);
	glEnd();
	glPopMatrix();

}
bool cProstokat::czyKliknieto(float _x, float _y){
	if (fabs(_x - x) < a / 2 && fabs(_y - y) < b / 2)
		return 1;
	else
		return 0;
}
float cProstokat::pole(){
	return a*b;
}

float cProstokat::obwod(){
	return 2 * a + 2 * b;
}

float cFigura::getAlpha(){
	return alpha;
}

void cFigura::rotateTo(float kat){
	alpha = kat;
}

void cFigura::przesun(float dx, float dy) {
	x += dx;
	y += dy;
}
cFigura::cFigura() :
		R(1), G(0), B(0), alpha(0) {
}

void cFigura::obroc(float dalpha) {
	alpha += dalpha;
	rysuj();
}

void cProstokat::zmienRozmiar(float a, float b) {
	this->a = a;
	this->b = b;
	rysuj();
}

cOkrag::cOkrag(float _r):rad(_r){
}
void cOkrag::rysuj(){
	glPushMatrix();
	glColor3f(R, G, B);
	glTranslatef(x, y, 0);
	glBegin(GL_POLYGON);
	for (int angle = 0; angle < 365; angle = angle + 5)
	{
		float angle_radians = angle * (float)3.14159 / (float)180;
		float _x = rad * (float)cos(angle_radians);
		float _y = rad * (float)sin(angle_radians);
		glVertex2f(_x, _y);
	}
	glEnd();
	glPopMatrix();
	granica.xa = -rad;
	granica.ya = -rad;
	granica.xb = rad;
	granica.yb = rad;
}
float cOkrag::pole(){
	return 3.14*rad*rad;
}
float cOkrag::obwod(){
	return 3.14 * 2 * rad;
}
bool cOkrag::czyKliknieto(float _x, float _y){
	if (fabs(_x - x)*fabs(_x - x) + fabs(_y - y)*fabs(_y - y) < rad*rad)
		return 1;
	else
		return 0;
}

cTrojkat::cTrojkat(float _a, float _h) :a(_a), h(_h){

}
void cTrojkat::rysuj(){
	glPushMatrix();
	glColor3f(R, G, B);
	glTranslatef(x, y, 0);
	glRotatef(alpha, 0, 0, 1);
	glBegin(GL_POLYGON);
		glVertex2f(a / 2, -h / 2);
		glVertex2f(-a / 2, -h / 2);
		glVertex2f(0, h / 2);
	glEnd();
	glPopMatrix();
	granica.xa = -a / 2;
	granica.ya = -h / 2;
	granica.xb = a / 2;
	granica.yb = h / 2;
}
float cTrojkat::pole(){
	return a*h;
}
float cTrojkat::obwod(){
	return a + sqrt(4 * h*h + a*a);
}
bool cTrojkat::czyKliknieto(float _x, float _y){
	if (fabs(_x - x) < a / 2 && fabs(_y - y) < h / 2)
		return 1;
	else
		return 0;
}