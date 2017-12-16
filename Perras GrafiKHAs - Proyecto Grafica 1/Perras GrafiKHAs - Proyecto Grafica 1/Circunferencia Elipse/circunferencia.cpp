#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace::std;

int Radius, X_c, Y_c;

void Draw(int x,int y,int X_c,int Y_c)
{

        
}

void MidPoint()
{
    int P;
    int x,y;
    P = 1 - Radius;
    x = 0;
    y = Radius;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
        glVertex2d(X_c + x,Y_c + y);
        glVertex2d(X_c + x,Y_c - y);
        glVertex2d(X_c - x,Y_c + y);
        glVertex2d(X_c - x,Y_c - y);
        glVertex2d(X_c + y,Y_c + x);
        glVertex2d(X_c - y,Y_c + x);
        glVertex2d(X_c + y,Y_c - x);
        glVertex2d(X_c - y,Y_c - x);
    
    while(x<=y)
    {
        x++;
        if (P<0)
        {
            P += 2 * x + 1;
        }
        else
        {
            P += 2 * (x - y) + 1;
            y--;
        }
        glVertex2d(X_c + x,Y_c + y);
        glVertex2d(X_c + x,Y_c - y);
        glVertex2d(X_c - x,Y_c + y);
        glVertex2d(X_c - x,Y_c - y);
        glVertex2d(X_c + y,Y_c + x);
        glVertex2d(X_c - y,Y_c + x);
        glVertex2d(X_c + y,Y_c - x);
        glVertex2d(X_c - y,Y_c - x);
    }
    
    glEnd();  
    glFlush();

}


void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(0 , 160, 0 , 120);
}

int main(int argc, char **argv)
{

  cout<<"Coordenada del Centro\n";
  cout<<"\nX_c:\t"; cin>>X_c;
  cout<<"\nY_c:\t"; cin>>Y_c;
  cout<<"\nRadio:\t"; cin>>Radius;  


  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("MidPoint-Circle");

  Init();

  glutDisplayFunc(MidPoint);
  glutMainLoop();

  return 0;
}
