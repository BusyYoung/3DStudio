#ifndef M_IMPORT_H
#define M_IMPORT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "gl/glut.h"
#include <stdio.h>
#include <vector>
#include "type.h"

//�������ඨ�壺
class objImporter
{
	private:
		mImport object;
	public:
		objImporter();
		int ProcessFileInfo(string);
		void saveObject(string FileName);
		void DrawObject();
		vector<string> split(string str,string pattern,int* count);		//�ַ�����ֺ���
};
#endif
