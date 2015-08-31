#pragma once
#include "StdAfx.h"
class Material
{
public:
	Material();
	~Material();

	void show();
	static void enable();
	static void disable();

	void brass();//��ͭ
	void bronze();//��ͭ
	void gold();//��
	void wax();//����
	void silver();//��
	void emerald();//���
	void obsidian();//����ʯ
	void blackPlastic();//������
	void blackRubber();//����
	void setMaterial(int index);
	void reset();
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;//���淴��ϵ��

private:
	static bool flag;

};

