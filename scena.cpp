#include "scena.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <Windows.h>
using namespace std;

cScena scena;
void przerysuj(){
	scena.rysuj();
}
void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void klawisz(unsigned char znak, int x, int y){
	scena.klawisz(znak, x, y);
}

cScena::cScena() :
aktywny(-1), time(GetTickCount()) {
	{
		cOkrag *pr = new cOkrag(0.1);
		figury.push_back(pr);
		pr->setFizyka(0.0000001, -90);
		pr->setPredkosc(0.0001, 135);
	}
	{
		cProstokat *pr = new cProstokat(5, 0.5);
		pr->przesun(0, -2);
		figury.push_back(pr);
	}
	{
		cProstokat *pr = new cProstokat(0.5, 4);
		pr->przesun(2.5, 0.25);
		figury.push_back(pr);
	}
	{
		cProstokat *pr = new cProstokat(0.5, 4);
		pr->przesun(-2.5, 0.25);
		figury.push_back(pr);
	}

}

void cScena::rysuj() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	for (auto f : figury){
		f->rysuj();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void cScena::aktualizuj(){	
	//ti = 0;
	long long czas = GetTickCount(); //zwraca czas w [ms]
	cout << "czas scena" << czas-time<<endl;
	
	for(int i=0; i< figury.size();i++) 
		figury[i]->Aktualizuj(czas); //obliczanie nowych polozen
	//wykrywanie kolizji 
	for(int i=0; i< figury.size();i++) 
		for(int j=i+1;j< figury.size();j++) 
			if(figury[i]->Kolizja(*figury[j])) //znajduje kolizje 
			{ 
				//figury[0]->Odbicie(figury[0]->ZnajdzNormalna(*figury[j]));
				// tu mozna zareagowac na kolizje np. usuwajac „zbity” obiekt itp...
			} 
	time = czas;
}

void cScena::ustaw(int czas){
	time = GetTickCount()-czas;
}

void cScena::klawisz(unsigned char znak, int x, int y) {
	cout << "klawisz: " << znak;
	switch (znak) {
	case'p':{
		cProstokat *pr = new cProstokat(1,1);
		figury.push_back(pr);
		aktywny = figury.size() - 1;
		break;
	}
	case'o':{
		cOkrag *pr = new cOkrag(0.5);
		figury.push_back(pr);
		aktywny = figury.size() - 1;
		break;
	}
	case't':{
		cTrojkat *pr = new cTrojkat(1,1);
		figury.push_back(pr);
		aktywny = figury.size() - 1;
		break;
	}
	case 'a': {
		if (aktywny >= 0) {
			figury[aktywny]->przesun(-0.1, 0);
		}
		break;
	}
	case 's': {
		if (aktywny >= 0) {
			figury[aktywny]->przesun(0, -0.1);
		}		
			break;
		}
	case 'w': {
		if (aktywny >= 0) {
			figury[aktywny]->przesun(0, 0.1);
		}
		break;
	}

	case 'd': {
		if (aktywny >= 0) {
			figury[aktywny]->przesun(0.1, 0);
		}
		break;
	}
	case '+': {
		if (aktywny < figury.size() - 1) {
			aktywny++;
		}
		break;
	}
	case '-': {
		if (aktywny > 0) {
			aktywny--;
		}
		break;
	}
	case 'r': {
		if (aktywny >= 0) {
			figury[aktywny]->obroc(10);
			}	
		break;
	}
	case 'l': {
		if (aktywny >= 0) {
			figury[aktywny]->obroc(-10);
		}
		break;
	}
	}
	glutPostRedisplay();
}

void timer(int id){
	
	scena.aktualizuj();
	glutPostRedisplay(); 
	glutTimerFunc(50, timer, id);
	
}
void myszka(int button, int state, int x, int y){
	scena.onMouseButton(button, state, x, y);
}
void cScena::onMouseButton(int button, int state, int x, int y){
	double openglX = ((double)x - 400) / 800 * 6.68;
	double openglY = -((double)y - 300) / 600 * 5;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {	
		for (int i = 0; i < figury.size();i++){
			if (figury[i]->czyKliknieto(openglX, openglY))
			{
				aktywny = i;
				break;
			}
		}			
				cout << openglX << " " << openglY << "\t";		
	}
}
void cScena::inicjuj() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(600, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("cFigura");
	glutReshapeFunc(resize);
	glutDisplayFunc(::przerysuj);
	glutKeyboardFunc(::klawisz);
	//glutIdleFunc(idle);
	glutMouseFunc(::myszka);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, -.1, .1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	timer(1);
}
