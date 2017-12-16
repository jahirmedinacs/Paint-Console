#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace::std;


int rounder(double x){int  y = (x > (floor(x) +0.55555) ? floor(x + 0.5) : floor(x)); return y;}

void Bresenham(pair<double,double> P_o,pair<double,double> P_f)
{

  int deltax = P_f.first - P_o.first;
  int deltay = P_f.second - P_o.second;

  double error = 0.0;
  double deltaerror = (double)fabs((float)(deltay)/(float)(deltax));

  int y = Y_1;
  int i;

  int dy = (deltay > 0 ? 1 : -1);

  glClear(GL_COLOR_BUFFER_BIT);

  if ( deltax > 0 )
  {
    glBegin(GL_POINTS);

    for( i = 0; i < deltax; i++)
    {
      glVertex2d(X_1 + i, y);

      error += deltaerror;
      if (error >= 0.5)
      {
        y += dy;
        error -= 1.0f;
      }
    }
    glEnd();  
    glFlush();
  }
  else
  {
    glBegin(GL_POINTS);

    for( i = deltax; i < 0 ; i++)
    {
      
      glVertex2d(X_1 + i, y);

      error = error + deltaerror;
      if (error >= 0.5)
      {
        y += dy;
        error -= 1.0f;
      }
    }

    glEnd();
    glFlush();
  }
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

  Bresenham(coordinate1,coordinate2);

  glFlush();

  glutMainLoop();

  return 0;
}