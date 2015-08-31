#ifndef _LIGHT_H
#define _LIGHT_H

#include <Windows.h>
#include "gl/glut.h"
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Light {
public:
	Light();
	~Light();

	void enable();
	void disable();
	virtual void show() = 0;

public:
	GLfloat position[4];//��Դλ��
	GLfloat Model_Ambient[4]; //ȫ�ֻ�����
	static bool flag[2];

protected:
	static GLenum lightId[2];
	int id;
};

class SpotLight : public Light {
public:
	SpotLight();
	~SpotLight();

	virtual void show();

public:
	GLfloat ambient[4];//������ɷ�
	GLfloat diffuse[4];//������ɷ�
	GLfloat specular[4];//�����ɷ�
};

class DirectLight : public SpotLight {
public:
	DirectLight();
	~DirectLight();

	virtual void show();

public:
	GLfloat cutoff;
	GLfloat direction[4];
	GLfloat exponent;
};


#endif
