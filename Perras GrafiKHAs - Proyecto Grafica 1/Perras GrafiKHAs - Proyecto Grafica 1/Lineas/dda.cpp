#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace::std;

double X_1, Y_1, X_2, Y_2;

float rounder(float data)
{
  return floor(data + 0.5);
}

void LineDDA()
{
  double dx=(X_2-X_1);
  double dy=(Y_2-Y_1);
  double steps;
  float xInc,yInc,x=X_1,y=Y_1;

  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps; 

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);

  glVertex2d(x,y);
  
  int k;
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    glVertex2d(rounder(x), rounder(y));
  }

  glEnd();
  glFlush();
}

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(0 , 640, 0 , 480);
}

int main(int argc, char **argv)
{

  cout<<"Coordenada inicial\n";
  cout<<"\nX_1:\t"; cin>>X_1;
  cout<<"\nY_1:\t"; cin>>Y_1;

  cout<<"Coordenada Final\n";
  cout<<"\nX_2:\t"; cin>>X_2;
  cout<<"\nY_2:\t"; cin>>Y_2;  


  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(320,240);
  glutCreateWindow("DDA_Line");

  Init();

  glutDisplayFunc(LineDDA);
  glutMainLoop();

  return 0;
}