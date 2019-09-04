#pragma once
#include "Vecteur3D.h"

class Particule
{

private:

	Vecteur3D pos_;
	Vecteur3D vit_;
	Vecteur3D g_;

	float massInv_;
	float d_;
	float m_;

	float r_;
	float v_;
	float b_;

public:

	Particule(float g, Vecteur3D pos, Vecteur3D vit, float m, float d, float r, float v, float b);

	~Particule();

	void setPos(Vecteur3D pos) { pos_ = pos; };
	void setVit(Vecteur3D vit) { vit_ = vit; };
	void setG(Vecteur3D g) { g_ = g; };
	void setD(float d) { d_ = d; };
	void setM(float m) { m_ = m; };
	void setMassInv(float massInv) { massInv_ = massInv; };
	void setR(float r) { r_ = r; };
	void setV(float v) { v_ = v; };
	void setB(float b) { b_ = b; };

	Vecteur3D getPos() { return pos_; };
	Vecteur3D getVit() { return vit_; };
	Vecteur3D getG() { return g_; };
	float getD() { return d_; };
	float getM() { return m_; };
	float getMassInv() { return massInv_; };
	float getR() { return r_; };
	float getV() { return v_; };
	float getB() { return b_; };

	void integrer(float t);
};

