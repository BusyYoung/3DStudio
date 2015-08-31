#include "m_import.h"
#include "StdAfx.h"
using namespace std;

//�ຯ��ʵ�֣�

	//��ʼ�����캯��
objImporter::objImporter()
{
}

//������Ϣ����Ӧ�Ľṹ��
int objImporter::ProcessFileInfo(string FileAddress)
{
	int count;
	vVertex3 vertex;
	nVertex3 normal;
	tVertex2 texture;
	mMaterial* mat = NULL;
	face surface;
	string strBuff;			//���ڶ�ȡ�ļ��е�ÿһ��
	string keyWord;		//��¼ÿһ�еĹؼ���
	string materials;		//��¼ÿһ��group�Ĳ�����Ϣ
	string tempString;		//���ڼ�¼�����string��Ϣ
	string faceMaterial;	//��������Ϣ�ļ�¼
	bool isMaterial = false; 
	vector<string> result;
	//��ʼ����
	surface.vertexNum = 0;
	for(int k=0; k<4;k++) {
		surface.nv[k] = 0;
		surface.tv[k] = 0;
		surface.v[k] = 0;
		surface.bMaterials = false;
	}
	//��ʼ���ļ���
	ifstream infile; 
	infile.open(FileAddress);
	if (!infile.good()){
		cout << "�ļ�û�б��ɹ���!" << endl;
		return - 1;
	}
	while(getline(infile,strBuff,'\n')){
		istringstream stream(strBuff);
		stream >> keyWord;
		//������Ϣ����:
		if(keyWord == "mtllib"){
			stream >> materials;
			object.materialPath = materials; 
		}
		//������Ϣ����:
		else if (keyWord == "v"){
			stream >> vertex.x >> vertex.y >> vertex.z;
			object.vVertexes.push_back(vertex);
		}
		//������Ϣ����:
		else if(keyWord == "vt"){
			stream >> texture.x >> texture.y;
			object.tVertexes.push_back(texture);
		}
		//��������Ϣ����:
		else if(keyWord == "vn"){
			stream >> normal.x >> normal.y >> normal.z;
			object.nVertexes.push_back(normal);
		}
		//��������Ϣ��
		else if (keyWord == "usemtl"){
			stream >> faceMaterial;
			isMaterial = true;
		}
		//����Ϣ����(�˴�count�����д�):
		else if(keyWord == "f"){

			while(stream >> tempString){
				count = 0;
				result = split(tempString,"/",&count);
				if(count == 1)
					surface.v[surface.vertexNum] = atoi(result[0].c_str());
				else if (count == 2){	
					surface.v[surface.vertexNum] = atoi(result[0].c_str());
					surface.tv[surface.vertexNum] = atoi(result[1].c_str());
				}
				else if(count == 3){
					surface.v[surface.vertexNum] = atoi(result[0].c_str());
					surface.tv[surface.vertexNum] = atoi(result[1].c_str());
					surface.nv[surface.vertexNum] = atoi(result[2].c_str());
				}
				surface.vertexNum++;
			}
			if (isMaterial){
				surface.materialName = faceMaterial;
				surface.bMaterials = true;
			} else {
 				surface.materialName = "";
			}
			object.faces.push_back(surface);
			surface.vertexNum = 0;
		}	
	}
	infile.close();
	//������������Ϣ��
	ifstream inMaterialFile;
	inMaterialFile.open(object.materialPath);
	if (!inMaterialFile.good()){
		cout << "�����ļ�û�б��ɹ���" << endl;
		return -2; 
	}
	while (getline(inMaterialFile, strBuff, '\n')){
		istringstream materialStream(strBuff);
		materialStream >> keyWord;
		if (keyWord == "newmtl"){
			if (mat == NULL){
				mat = new mMaterial;
				materialStream >> mat->newmtl;
			}
			else{
				object.materials.push_back(*mat);
				delete mat;
				mat = new mMaterial;
				materialStream >> mat->newmtl;
			}
		}
		else if (keyWord == "Ka"){
			materialStream >> mat->Ka.x 
				>> mat->Ka.y >> mat->Ka.z;
		}
		else if (keyWord == "Kd"){
			materialStream >> mat->Kd.x
				>> mat->Kd.y >> mat->Kd.z;
		}
		else if (keyWord == "Ks"){
			materialStream >> mat->Ks.x
				>> mat->Ks.y >> mat->Ks.z;
		}
		else if (keyWord == "illum"){
			materialStream >> mat->illum;
		}
		else if (keyWord == "Ns"){
			materialStream >> mat->Ns;
		}
	}
	object.materials.push_back(*mat);
	inMaterialFile.close();

	return 1;


}

void objImporter::DrawObject(){
	int i = 0;
	int k = 0;

	//glPushMatrix();
	for (i = 0; i < object.faces.size(); i++){
		if (object.faces[i].materialName != ""){
			for (k = 0; k < object.materials.size(); k++){
				if (object.materials[k].newmtl == object.faces[i].materialName){
					GLfloat mat_ambient[] = { object.materials[k].Ka.x, object.materials[k].Ka.y, object.materials[k].Ka.z, 1.0f };
					GLfloat mat_diffuse[] = { object.materials[k].Kd.x, object.materials[k].Kd.y, object.materials[k].Kd.z, 1.0f };
					GLfloat mat_specular[] = { object.materials[k].Ks.x, object.materials[k].Ks.y, object.materials[k].Ks.z, 1.0f };
					//glLightModelf(GL_LIGHT_MODEL_AMBIENT, object.materials[k].illum);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, object.materials[k].Ns);
					break;
				}
			}
		}
		if (object.faces[i].vertexNum == 3)
			glBegin(GL_TRIANGLES);
		else if (object.faces[i].vertexNum == 4)
			glBegin(GL_TRIANGLES);
		for (int j = 0; j < object.faces[i].vertexNum; j++){
			int iv = object.faces[i].v[j]-1;
			int ivt = object.faces[i].tv[j]-1;
			int ivn = object.faces[i].nv[j]-1;
			glNormal3f(object.nVertexes[ivn].x, object.nVertexes[ivn].y, object.nVertexes[ivn].z);
			glTexCoord2f(object.tVertexes[ivt].x, object.tVertexes[ivt].y);
			glVertex3f(object.vVertexes[iv].x, object.vVertexes[iv].y, object.vVertexes[iv].z);
		}
		glEnd();
	}
			
	//glPopMatrix();
}

vector<string> objImporter::split(string str,string pattern,int* count)
{
	string::size_type pos;
	vector<string> result;
	str+=pattern;//��չ�ַ����Է������
	unsigned int size=str.size();
	for(unsigned int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos < size)
		{
			string s=str.substr(i,pos-i);
			result.push_back(s);
			(*count)++;
			i=pos+pattern.size()-1;
		}
	}		
	return result;
}

void objImporter::saveObject(string fileAddress){
	ofstream outfile;
	outfile.open(fileAddress, ios::out);
	int vertexIter;
	int tVertexIter;
	int nVertexIter;
	int materialIter;
	int faceIter;
	outfile << "mtllib " << object.materialPath << '\n';
	for (vertexIter = 0; vertexIter  < object.vVertexes.size(); vertexIter++){
		outfile << "v" << " " << object.vVertexes[vertexIter].x << " " 
			<< object.vVertexes[vertexIter].y << " " 
			<< object.vVertexes[vertexIter].z << '\n';
	}
	for (tVertexIter = 0; tVertexIter < object.tVertexes.size(); tVertexIter++){
		outfile << "vt" << " " << object.tVertexes[tVertexIter].x << " "
			<< object.tVertexes[tVertexIter].y << '\n';
	}
	for (nVertexIter = 0; nVertexIter < object.nVertexes.size(); nVertexIter++){
		outfile << "vn" << " " << object.nVertexes[nVertexIter].x << " "
			<< object.nVertexes[nVertexIter].y << " "
			<< object.nVertexes[nVertexIter].z << '\n';
	}
	for (faceIter = 0; faceIter < object.faces.size(); faceIter++){
		outfile << "usemtl" << " " << object.faces[faceIter].materialName << '\n';
		for (int num = 0; num < object.faces[faceIter].vertexNum; num++){
			if (num == 0){
				outfile << "f" << " ";
			}
			outfile << object.faces[faceIter].v[num] << '/'
				<< object.faces[faceIter].tv[num] << '/'
				<< object.faces[faceIter].nv[num];
			if (num != (object.faces[faceIter].vertexNum - 1))
				outfile << " ";
			else
				outfile << '\n';
		}
	}

	outfile.close();
}
