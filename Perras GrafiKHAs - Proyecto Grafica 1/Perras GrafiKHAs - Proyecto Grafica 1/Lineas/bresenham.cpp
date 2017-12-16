#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace::std;

int X_1, Y_1, X_2, Y_2;

void bresenham()
{

  int deltax = X_2 - X_1;
  int deltay = Y_2 - Y_1;

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
  glutCreateWindow("Bresenham");

  Init();

  glutDisplayFunc(bresenham);
  glutMainLoop();

  return 0;
}
