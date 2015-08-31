#include "StdAfx.h"
#include "ModelPainter.h"

using namespace std;

//���º����������Ķ���Ĭ���ӽ�Ϊz�����ϵ��ӽǣ�
//!!!!!!����ĺ���û��ʵ������Ϣ�ĵ��룺

void ModelPainter::DrawSphere(GLfloat fRadius, GLint iSlices,GLint iStacks)
{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
	GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
	GLfloat ds = 1.0f / (GLfloat) iSlices;
	GLfloat dt = 1.0f / (GLfloat) iStacks;
	GLfloat t = 1.0f;	
	GLfloat s = 0.0f;
	GLint i, j;     // Looping variables

	for (i = 0; i < iStacks; i++) 
	{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));

		glBegin(GL_TRIANGLE_STRIP);
		s = 0.0f;
		for ( j = 0; j <= iSlices; j++)
			{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
			glTexCoord2f(s, t);
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);

			x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
			s += ds;
			glNormal3f(x, y, z);
			glVertex3f(x * fRadius, y * fRadius, z * fRadius);
		}
		glEnd();
		t -= dt;
	}
}

void ModelPainter::DrawCylinder(GLfloat r, GLfloat height,GLint longitude,GLint latitude)
{
	GLfloat dtheta = 2.0f * (GLfloat)pi / (GLfloat)longitude;
	GLfloat dh = height / (GLfloat)latitude;
	GLfloat du = 1.0f / longitude;
	GLfloat dv =  1.0f/ latitude;
	GLfloat u= 0.0f;
	GLfloat v =1.0f;
	GLfloat x,y,z,ax,ay,az;
	GLint count =0;
	GLint i,j;
	GLfloat dr = r /(GLfloat)latitude;

	//�����棺
	for(i =0 ; i<latitude;i++)
	{
		GLfloat h	= (GLfloat)(i*dh);
		GLfloat aboveh = (GLfloat)(h+dh);

		glBegin(GL_TRIANGLE_STRIP);
		u= 0.0f;
		for(j = 0; j<=longitude;j++){

			GLfloat theta = (GLfloat)(j*dtheta);
			GLfloat sintheta = (GLfloat)(sin(theta));
			GLfloat costheta = (GLfloat)(cos(theta));
			
			x = costheta * r;
			y = sintheta * r;
			z = h;

			glTexCoord2f(u, v);
			glNormal3f(costheta, sintheta, 0);
			glVertex3f(x, y, z);

			//��ͬһ�����ϲ�ͬγ�ȵ�����һ��
			ax = costheta * r;
			ay = sintheta * r;
			az = aboveh;

			glTexCoord2f(u, v -dv);
			glNormal3f(costheta, sintheta, 0);
			glVertex3f(ax, ay, az);
			u += du;
		}
		glEnd();
		v-=dv;
	}

	//���������:
	DrawCircle(r,0,latitude,longitude,false);
	DrawCircle(r,height,latitude,longitude,true);
}

void ModelPainter::DrawCube(GLfloat length,GLfloat width,GLfloat height)
{
	GLfloat x = length/2.0;
	GLfloat y = height/2.0;
	GLfloat z = width/2.0;

	//TO-DO glEnable(GL_TEXTURE_2D)����
	glBegin(GL_QUADS);
		//����
		glVertex3f(x,y,z);glTexCoord2f(1.0,0.0);
		glVertex3f(x,-y,z);glTexCoord2f(1.0,1.0);
		glVertex3f(-x,-y,z);glTexCoord2f(0.0,1.0);
		glVertex3f(-x,y,z);glTexCoord2f(0.0,0.0);
		//����
		glVertex3f(-x,-y,z);glTexCoord2f(0.0,1.0);
		glVertex3f(-x,y,z);glTexCoord2f(0.0,0.0);
		glVertex3f(-x,y,-z);glTexCoord2f(1.0,0.0);
		glVertex3f(-x,-y,-z);glTexCoord2f(1.0,1.0);
		//����
		glVertex3f(-x,-y,-z);glTexCoord2f(1.0,1.0);
		glVertex3f(-x,y,-z);glTexCoord2f(1.0,0.0);
		glVertex3f(x,y,-z);glTexCoord2f(0.0,0.0);
		glVertex3f(x,-y,-z);glTexCoord2f(0.0,1.0);
		//����
		glVertex3f(x,y,z);glTexCoord2f(1.0,0.0);
		glVertex3f(x,-y,z);glTexCoord2f(1.0,1.0);
		glVertex3f(x,y,-z);glTexCoord2f(0.0,0.0);
		glVertex3f(x,-y,-z);glTexCoord2f(0.0,1.0);
		//����
		glVertex3f(-x,-y,z);
		glVertex3f(x,-y,z);
		glVertex3f(x,-y,-z);
		glVertex3f(-x,-y,-z);
		//����
		glVertex3f(-x,y,z);
		glVertex3f(x,y,z);
		glVertex3f(x,y,-z);
		glVertex3f(-x,y,-z);
	glEnd();

}

void ModelPainter::DrawPrismoid(GLint surfaceNum, GLfloat height,GLfloat r)
{
	int j;
	//����������εķָ�Ƕȣ�
	GLfloat dtheta = 2.0f * pi/((GLfloat)surfaceNum);
	glBegin(GL_TRIANGLE_STRIP);
		for(j = 0; j <= surfaceNum;j++)
		{
			GLfloat theta = (GLfloat)((j-1/2) * dtheta);
			GLfloat costheta = (GLfloat)(cos(theta));
			GLfloat sintheta = (GLfloat)(sin(theta));

			GLfloat x = r*costheta;
			GLfloat y = r*sintheta;
			GLfloat z = 0;
			
			glVertex3f(x,y,z);

			GLfloat ax = x;
			GLfloat ay = y;
			GLfloat az = height;

			glVertex3f(ax,ay,az);
		}
	glEnd();

	//��������棺
	DrawPolygon(surfaceNum,0.0f,r);
	DrawPolygon(surfaceNum,height,r);
}

void ModelPainter::DrawCone(GLfloat base,GLfloat height,GLint longitude,GLint latitude)
{
	int i,j;
	GLfloat dh = height / ((GLfloat)latitude);
	GLfloat dtheta = 2.0 * pi/((GLfloat)longitude);
	GLfloat du = 1.0 / ((GLfloat)longitude);
	GLfloat dv = 1.0/((GLfloat)latitude);
	GLfloat cotalpha = base/height;
	GLfloat u =0.0f;
	GLfloat v =1.0f;
	GLfloat x,y,z,ax,ay,az;

	for(i=0;i<latitude;i++)
	{
		GLfloat h = dh * i;
		GLfloat aboveh = h + dh;
		GLfloat rh = height - h;		//���׾�
		GLfloat aboverh = height - aboveh;
		GLfloat r = rh *cotalpha;
		GLfloat abover = aboverh * cotalpha;
		glBegin(GL_TRIANGLE_STRIP);
			GLfloat u = 0.0f;
			for(j=0;j<=longitude;j++)
			{
				GLfloat theta = dtheta *j;
				GLfloat sintheta = (GLfloat)(sin(theta));
				GLfloat costheta = (GLfloat)(cos(theta));
			
				x = costheta * r;
				y = sintheta * r;
				z = h;
				ax = costheta *abover;
				ay = sintheta * abover;
				az = aboveh;
				glTexCoord2f(u,v);glVertex3f(x,y,z);
				glTexCoord2f(u,v-dv);glVertex3f(ax,ay,az);
				u += du;
			}
		glEnd();
		v -= dv;
	}
	//�����棺
	DrawCircle(base,0,latitude,longitude,false);
}

void ModelPainter::DrawTrustum(GLint surfaceNum, GLfloat height,GLfloat r,GLfloat scale)
{
	int j;
	//����������εķָ�Ƕȣ�
	GLfloat dtheta = 2.0f * pi/((GLfloat)surfaceNum);
	glBegin(GL_TRIANGLE_STRIP);
		for(j = 0; j <= surfaceNum;j++)
		{
			GLfloat theta = (GLfloat)((j-1/2) * dtheta);
			GLfloat costheta = (GLfloat)(cos(theta));
			GLfloat sintheta = (GLfloat)(sin(theta));

			GLfloat x = r*costheta;
			GLfloat y = r*sintheta;
			GLfloat z = 0;
			
			glVertex3f(x,y,z);

			GLfloat ax = (GLfloat)(x*scale);
			GLfloat ay = (GLfloat)(y*scale);
			GLfloat az = height;

			glVertex3f(ax,ay,az);
		}
	glEnd();

	//��������棺
	DrawPolygon(surfaceNum,0.0f,r);
	DrawPolygon(surfaceNum,height,r*scale);
}

void ModelPainter::DrawCircle(GLfloat r,GLfloat zdata,GLint rsplit,GLint thetasplit,bool upNormal =false)
{
	int i,j;
	GLfloat dtheta = 2.0* pi / thetasplit;
	GLfloat dr = r /rsplit;

	for(i=0;i<rsplit;i++)
	{
		GLfloat radius = (GLfloat)(i*dr);
		GLfloat nextRadius = radius + dr;

		glBegin(GL_TRIANGLE_STRIP);
			for(j=0;j<=thetasplit;j++)
			{
				GLfloat theta = (GLfloat)(j*dtheta);
				GLfloat costheta = (GLfloat)(cos(theta));
				GLfloat sintheta = (GLfloat)(sin(theta));

				GLfloat x =  (GLfloat)(radius *costheta);
				GLfloat y =  (GLfloat)(radius *sintheta);
				GLfloat z = zdata;
				if(!upNormal)
					glNormal3f(0.0,0.0,-1);
				else
					glNormal3f(0.0,0.0,1);
				glVertex3f(x,y,z);

				GLfloat ax =  (GLfloat)(nextRadius *costheta);
				GLfloat ay =  (GLfloat)(nextRadius *sintheta);
				GLfloat az = zdata;

				if(!upNormal)
					glNormal3f(0.0,0.0,-1);
				else
					glNormal3f(0.0,0.0,1);

				glVertex3f(ax,ay,az);
			}
		glEnd();
	}
}

void ModelPainter::DrawPolygon(GLint surfaceNum, GLfloat zdata,GLfloat r)
{
	int j;
	//����������εļнǽǶȣ�
	GLfloat dtheta = 2.0f * pi/((GLfloat)surfaceNum);
	glBegin(GL_TRIANGLE_STRIP);
	for (j = 0; j <= surfaceNum; j++)
	{
		GLfloat theta = (GLfloat)((j - 1 / 2) * dtheta);
		GLfloat costheta = (GLfloat)(cos(theta));
		GLfloat sintheta = (GLfloat)(sin(theta));

		GLfloat x = r*costheta;
		GLfloat y = r*sintheta;
		GLfloat z = zdata;

		glVertex3f(x, y, z);
		glVertex3f(0.0, 0.0, zdata);
	}
	glEnd();
}