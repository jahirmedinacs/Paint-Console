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
    Init();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);

    regularPolygonPlot(polygon,doit);

    glFlush();

    glutMainLoop();

    return EXIT_SUCCESS;


/*
	pair<double,double> inputPoint;
	double inputCarry[5];
	bool doit;

	color inputColor;

	cout<<"\nRadio1\t"; cin>>inputCarry[0];
	cout<<"\nRadio2\t"; cin>>inputCarry[1];

	cout<<"\nCentro X\t"; cin>>inputPoint.first;
	cout<<"\nCentro Y\t"; cin>>inputPoint.second;

	cout<<"\nRellenar\t"; cin>>doit;

	cout<<"\nRojo\t"; cin>>inputColor.red;
	cout<<"\nVerde\t"; cin>>inputColor.green;
	cout<<"\nAzul\t"; cin>>inputColor.blue;

	glutInit(&argc,argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowPosition(0,0);
  	glutInitWindowSize(640,480);
  	glutCreateWindow("Paint Team P-grafiKHAs");

	Init();

	glClear(GL_COLOR_BUFFER_BIT);

	elipse(inputPoint,inputCarry[0],inputCarry[1],doit,inputColor,inputColor);

	glFlush();

	
	
	glutMainLoop();

*/

	return 0;
}
