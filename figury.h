#ifndef FIGURY_H_
#define FIGURY_H_
#include "cFizyka.h"
class cFigura: public CFizyka{
protected:
	float R,G,B;
	float alpha;
public:
		cFigura();
		virtual void rysuj()=0; // virtual szuka najblizszej kompatybilnej metody, =0 sprawia ze nie ma definicji tej metody
		void przesun(float dx, float dy);
		void obroc(float dalpha);
		virtual float pole() = 0;
		virtual float obwod() = 0;
		float getAlpha();
		void rotateTo(float kat);
		virtual bool czyKliknieto(float _x, float _y) = 0;
};
class cProstokat: public cFigura{
protected:
	float a,b;
public:
	cProstokat();
	cProstokat(float _a, float _b);
	void rysuj();
	void zmienRozmiar(float _a, float _b);
	float pole();
	float obwod();
	bool czyKliknieto(float _x, float _y);
};
class cOkrag :public cFigura{
protected:
	float rad;
public:
	cOkrag(float _r);
	void rysuj();
	float pole();
	float obwod();
	bool czyKliknieto(float _x, float _y);
};
class cTrojkat :public cFigura{
protected:
	float a,h;
public:
	cTrojkat(float _a,float _h);
	void rysuj();
	float pole();
	float obwod();
	bool czyKliknieto(float _x, float _y);
};
#endif
/*
rzutowanie:cKlocek *k = dynamic.cast<cKlocek*>(tab[i]);
if(k!=NULL) <=> to jest klocek

*/