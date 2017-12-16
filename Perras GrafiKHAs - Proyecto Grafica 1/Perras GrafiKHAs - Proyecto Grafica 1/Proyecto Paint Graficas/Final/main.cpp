#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <set>
#include <vector>
#include <utility>

#include "./teamPgrafiKHAs.h"

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-640 , 640, -480 , 480);
}


int main(int argc, char **argv)
{
	int numberOfSides;
	pair<double,double> center;
	double radius;
	bool doit;

	color colorBoundaries;
	color colorFill;

    cout<<" Ingrese el centro en X :\n    >> "; cin>>center.first;
    cout<<" Ingrese el centro en Y :\n    >> "; cin>>center.second;
    cout<<" Ingrese el radio :\n    >> "; cin>>radius;
    cout<<" Ingrese los lados :\n    >> "; cin>>numberOfSides;
    cout<<" Pintar?:\n    >>"; cin>>doit;

    cout<<" Contorno\n ";
    cout<<" Rojo:\n"; cin>>colorBoundaries.red;
    cout<<" Verde:\n"; cin>>colorBoundaries.green;
    cout<<" Azul:\n"; cin>>colorBoundaries.blue;

    cout<<" Interior\n ";
    cout<<" Rojo:\n"; cin>>colorFill.red;
    cout<<" Verde:\n"; cin>>colorFill.green;
    cout<<" Azul:\n"; cin>>colorFill.blue;


    vector< pair< double,double> > polygon;
    polygon	 = regularPolygonGenerator(numberOfSides,center,radius);

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);

    glutCreateWindow("POLIGONO");
    Init();

    glClear(GL_COLOR_BUFFER_BIT);

    regularPolygonPlot(polygon,doit, colorBoundaries, colorFill);

    glFlush();

    glutMainLoop();

    return EXIT_SUCCESS;	
}
