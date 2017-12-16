#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <set>
#include <vector>
#include <utility>
#include <bits/stdc++.h>

#include "./teamPgradiKHAs.h"

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-640 , 640, -480 , 480);
}


int main(int argc, char **argv)
{
	pair<double,double> inputPoint;
    double radio;
    int sides;
	double inputCarry[5];
	bool doit;
    glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(640,480);
            glutCreateWindow("Paint Team P-grafiKHAs");
	Init();

	glClear(GL_COLOR_BUFFER_BIT);
    
    color inputColor;
    int opcion;
    while(opcion!=3)
    {

        cout<<"[1]Dibuja Elipse"<<endl;
        cout<<"[2]Dibuja Poligono"<<endl;
        cout<<"[3]Salir"<<endl;
        cin>>opcion;
        if(opcion==1)
        {
                cout<<"\nRadio1\t"; cin>>inputCarry[0];
                cout<<"\nRadio2\t"; cin>>inputCarry[1];

                cout<<"\nCentro X\t"; cin>>inputPoint.first;
                cout<<"\nCentro Y\t"; cin>>inputPoint.second;

                cout<<"\nRellenar\t"; cin>>doit;

                cout<<"\nRojo\t"; cin>>inputColor.red;
                cout<<"\nVerde\t"; cin>>inputColor.green;
                cout<<"\nAzul\t"; cin>>inputColor.blue;


                elipse(inputPoint,inputCarry[0],inputCarry[1],doit,inputColor,inputColor);

                glFlush();

        }
        else if(opcion==2)
        {
                cout<<"\nCentro X\t"; cin>>inputPoint.first;
                cout<<"\nCentro Y\t"; cin>>inputPoint.second;

                cout<<"\nNumero de lados\t"; cin>>sides;

                cout<<"\nRadio \t";   cin>>radio;



                cout<<"\nRellenar\t"; cin>>doit;

                cout<<"\nRojo\t"; cin>>inputColor.red;
                cout<<"\nVerde\t"; cin>>inputColor.green;
                cout<<"\nAzul\t"; cin>>inputColor.blue;

                vector<pair<double,double> > pts=regularPolygonGenerator(sides,inputPoint,radio);
                debug("paso");
                regularPolygonPlot(pts,doit,inputColor,inputColor);

                glFlush();
        }

    }



	glutMainLoop();


	return 0;
}
