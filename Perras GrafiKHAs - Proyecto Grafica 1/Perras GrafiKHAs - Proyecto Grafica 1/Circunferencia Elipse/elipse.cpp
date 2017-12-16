#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace::std;

int X_c,Y_c;
long R_x,R_y;

void MidPoint()
{	
	float p;
	int x,y;

	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);  

	p=R_y*R_y-R_x*R_x*R_y+R_x*R_x/4;
	x=0;y=R_y;
	while(2.0*R_y*R_y*x <= 2.0*R_x*R_x*y)
	{
		if(p < 0)
		{
			x++;
			p = p+2*R_y*R_y*x+R_y*R_y;
		}
		else
		{
			x++;y--;
			p = p+2*R_y*R_y*x-2*R_x*R_x*y-R_y*R_y;
		}
        glVertex2d(X_c + x,Y_c + y);
        glVertex2d(X_c + x,Y_c - y);
        glVertex2d(X_c - x,Y_c + y);
        glVertex2d(X_c - x,Y_c - y);
   }

   p=R_y*R_y*(x+0.5)*(x+0.5)+R_x*R_x*(y-1)*(y-1)-R_x*R_x*R_y*R_y;
   while(y > 0)
   {
   		if(p <= 0)
		{
			x++;y--;
			p = p+2*R_y*R_y*x-2*R_x*R_x*y+R_x*R_x;
		}
		else
		{
			y--;
			p = p-2*R_x*R_x*y+R_x*R_x;
		}
        glVertex2d(X_c + x,Y_c + y);
        glVertex2d(X_c + x,Y_c - y);
        glVertex2d(X_c - x,Y_c + y);
        glVertex2d(X_c - x,Y_c - y);
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

  cout<<"Coordenada del Centro\n";
  cout<<"\nX_c:\t"; cin>>X_c;
  cout<<"\nY_c:\t"; cin>>Y_c;
  cout<<"Radios\n";
  cout<<"\nRadio X:\t"; cin>>R_x;
  cout<<"\nRadio Y:\t"; cin>>R_y;  


  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("MidPoint-Ellipse");

  Init();

  glutDisplayFunc(MidPoint);
  glutMainLoop();

  return 0;
}