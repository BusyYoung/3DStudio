#ifndef TYPE_H_
#define TYPE_H_

#include <iostream>
#include <stdio.h>
#include "gl/glut.h"

#define MAX_NAME 30
#define MAX_VERTEX 256
#define MAX_FACE 100
#define MAX_LINE 100
#define MAX_VERTICES 256

using namespace std;

typedef struct polygon
{
	GLint xmin,xmax,ymin,ymax;/*��Χ��*/
	GLfloat xc,yc;/*����ε�����*/
	GLint nvertices; /*�������Ŀ*/
	GLfloat x[MAX_VERTICES];//����
	GLfloat y[MAX_VERTICES];
	GLfloat z[MAX_VERTICES];
}polygon;

typedef struct vertex3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}vVertex3,nVertex3;

typedef struct tVertex2   	
{
	GLfloat x;								//���ڼ�¼ÿ������X����
	GLfloat y;									//Y����
}tVertex2; 

typedef struct face
{
	unsigned int v[4];			//����Ϣ����
	unsigned int nv[4];		//��������Ϣ����
	unsigned int tv[4];		//������Ϣ����
	unsigned int vertexNum;				//3���㻹��4����
	string materialName;
	bool bMaterials;
}face;

typedef struct mMaterial{
	string newmtl;		//��������
	vVertex3 Ka;			//��������
	vVertex3 Kd;			//������
	vVertex3 Ks;			//���淴��
	GLfloat Ns;			//Shinness
	GLfloat illum;		//����ģ������
}mMaterial;

//����3D����Ķ�������
typedef struct mImport
{
	string materialPath;
	std::vector<vVertex3> vVertexes;
	std::vector<nVertex3> nVertexes;
	std::vector<tVertex2> tVertexes;
	std::vector<face> faces;
	std::vector<mMaterial> materials;
} mImport;

#endif