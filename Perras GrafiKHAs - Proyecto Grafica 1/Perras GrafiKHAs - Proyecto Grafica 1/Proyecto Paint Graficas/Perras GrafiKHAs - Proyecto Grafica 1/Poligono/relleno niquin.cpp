#include <bits/stdc++.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <set>
#include <math.h>
#include "./teamPgradiKHAs.h"
#define PI acos(-1.0)

using namespace std;

void Inicio()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-640, 640, -480, 480);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char *argv[])
{	
	int numberOfSides;
	pair<double,double> center;
	double radius;
	bool doit;

    cout<<" Ingrese el centro en X :\n    >> "; cin>>center.first;
    cout<<" Ingrese el centro en Y :\n    >> "; cin>>center.second;
    cout<<" Ingrese el radio :\n    >> "; cin>>radius;
    cout<<" Ingrese los lados :\n    >> "; cin>>numberOfSides;
    cout<<" Pintar?:\n    >>"; cin>>doit;

    vector< pair< double,double> > polygon;
    polygon	 = regularPolygonGenerator(numberOfSides,center,radius);

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);

    glutCreateWindow("POLIGONO");
    Inicio();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    regularPolygonPlot(polygon,doit);

    glFlush();

    glutMainLoop();

    return EXIT_SUCCESS;
}
