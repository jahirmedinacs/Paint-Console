#include <iostream>
#include <math.h>
#include <GL/glut.h>

#include <utility>

using namespace::std;



int rounder(double x){int  y = (x > (floor(x) +0.55555) ? floor(x + 0.5) : floor(x)); return y;}

void LineDDA(pair<double,double> P_o,pair<double,double> P_f)
{
	double dx=(P_f.first-P_o.first);
	double dy=(P_f.second-P_o.second);
	int steps;
	double xInc,yInc,x=P_o.first,y=P_o.second;

	steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
	steps *= 100;
	xInc=dx/(double)steps;
	yInc=dy/(double)steps; 

	glBegin(GL_POINTS);
  		glVertex2f(x,y); 
		int k;
		for(k=0;k<steps;k++)
		{	

			x+=xInc;
			y+=yInc;
			glVertex2f((x), (y));
		}

	glEnd();
}

void gridON()
{
	glBegin(GL_LINES);
		glVertex2i(-640, 0);
		glVertex2i(640, 0);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(0, -480);
		glVertex2i(0, 480);
	glEnd();
}

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-640 , 640, -480 , 480);
}

int main(int argc, char **argv)
{
	pair<double,double> coordinate1;
	pair<double,double> coordinate2;

	cout<<"Coordenada inicial\n";
	cout<<"\nX_1:\t"; cin>>coordinate1.first;
	cout<<"\nY_1:\t"; cin>>coordinate1.second;

	cout<<"Coordenada Final\n";
	cout<<"\nX_2:\t"; cin>>coordinate2.first;
	cout<<"\nY_2:\t"; cin>>coordinate2.second;

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
  	glutCreateWindow("DDA_Line");

	Init();

	glClear(GL_COLOR_BUFFER_BIT);

	gridON();

	LineDDA(coordinate1,coordinate2);

	glFlush();

	glutMainLoop();

	return 0;
}