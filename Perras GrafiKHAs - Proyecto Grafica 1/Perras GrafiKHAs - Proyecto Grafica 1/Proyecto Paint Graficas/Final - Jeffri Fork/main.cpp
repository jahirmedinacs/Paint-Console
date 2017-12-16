#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <set>
#include <vector>
#include <utility>
#include <bits/stdc++.h>

#include "teamPgrafiKHAs.h"

struct pentagon{
    vector< pair <double, double> > vertices;
    bool fill;
    color input;
    pentagon(vector< pair <double, double> > t1,bool t2,color t3)
    {
        vertices=t1;
        fill=t2;
        input=t3;
    }
};
struct line{
    pair<double,double>O;
    pair<double,double>F;
    bool fill;
    color input2;
    line( pair <double, double>  t0, pair <double, double> t1,bool t2,color t3)
    {
        O=t0;
        F=t1;
        fill=t2;
        input2=t3;
    }
};

struct circle{
    pair<double,double>O;
    double radio1;
    double radio2;
    bool fill;
    color input3;

    circle( pair <double, double> t1,bool t2,color t3,double t4,double t5)
    {
        O=t1;
        fill=t2;
        input3=t3;
        radio1=t4;
        radio2=t5;
    }
};
void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-640, 640, -480 , 480);
}



int main(int argc, char **argv)
{
    vector<pentagon>coleccionPentagon;
    vector<circle>coleccionCircle;
    vector<line>coleccionLine;
	pair<double,double> inputPoint,Point_o,Point_f;
    double radio;
    int sides,num;
	double inputCarry[5];
	bool doit;
    glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(640,480);
            glutCreateWindow("Paint Team P-grafiKHAs");
	Init();

	glClear(GL_COLOR_BUFFER_BIT);
        color inputColor,defaultColor={1,1,1};
    int opcion,opcion2;
    while(opcion!=7)
    {
        cout<<"[1]Dibuja Linea"<<endl;
        cout<<"[2]Dibuja Elipse"<<endl;
        cout<<"[3]Dibuja Poligono"<<endl;
        cout<<"[4]Transladar"<<endl;
        cout<<"[5]Escalar"<<endl;
        cout<<"[6]Rotar"<<endl;
        cout<<"[7]Salir"<<endl;
        cin>>opcion;
        if(opcion==1)
        {
                cout<<"Primer Punto"<<endl;
                cout<<"\n X:\t"; cin>>Point_o.first;
                cout<<"\n Y:\t"; cin>>Point_o.second;

                cout<<"Segundo Punto"<<endl;
                cout<<"\n X:\t"; cin>>Point_f.first;
                cout<<"\n Y:\t"; cin>>Point_f.second;

                cout<<"\nRellenar\t"; cin>>doit;

                cout<<"\nRojo\t"; cin>>inputColor.red;
                cout<<"\nVerde\t"; cin>>inputColor.green;
                cout<<"\nAzul\t"; cin>>inputColor.blue;

                Line(Point_o,Point_f,inputColor);
                coleccionLine.PB(line(Point_o,Point_f,true,inputColor));
                glFlush();

        }
        if(opcion==2)
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
                coleccionCircle.PB(circle(inputPoint,doit,inputColor,inputCarry[0],inputCarry[1]));
                glFlush();

        }
        else if(opcion==3)
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
                regularPolygonPlot(pts,doit,inputColor,inputColor);
                coleccionPentagon.PB(pentagon(pts,doit,inputColor));
                glFlush();
        }
        else if(opcion==4)
        {
            cout<<"[1]Modifique linea\n"<<endl;
            cout<<"[2]Modifique Elipse\n"<<endl;
            cout<<"[3]Modifique Poligono\n"<<endl;
            cin>>opcion2;
            cout<<"Ingrese numero de figura a modificar"<<endl;//falta validar
            cin>>num;
            pair<double,double>vectorT;
            cout<<"Ingrese factor de escalamiento en X";cin>>vectorT.first;
            cout<<"Ingrese factor de escalamiento en Y";cin>>vectorT.second;

            if(opcion2==1)
            {
                Line(coleccionLine[num].O,coleccionLine[num].F,defaultColor);
                coleccionLine[num].O=translation(vectorT,coleccionLine[num].O);
                coleccionLine[num].F=translation(vectorT,coleccionLine[num].F);
                Line(coleccionLine[num].O,coleccionLine[num].F,coleccionLine[num].input2);
                glFlush();
            }
            else if(opcion2==2)
            {
                elipse(coleccionCircle[num].O,coleccionCircle[num].radio1,coleccionCircle[num].radio2,1,defaultColor,defaultColor);
                coleccionCircle[num].O=translation(vectorT,coleccionCircle[num].O);
                elipse(coleccionCircle[num].O,coleccionCircle[num].radio1,coleccionCircle[num].radio2,coleccionCircle[num].fill,coleccionCircle[num].input3,coleccionCircle[num].input3);
                glFlush();
            }
            else
            {
                regularPolygonPlot(coleccionPentagon[num].vertices,1,defaultColor,defaultColor);

                vector<pair<double,double> >newPoints;
                REP(i,coleccionPentagon[num].vertices.size())
                {
                    pair<double,double> temp;
                    temp=translation(vectorT,coleccionPentagon[num].vertices[i]);
                    newPoints.PB( pair<double,double> (temp));
                }
                coleccionPentagon[num].vertices=newPoints;

                regularPolygonPlot(coleccionPentagon[num].vertices,coleccionPentagon[num].fill,coleccionPentagon[num].input,coleccionPentagon[num].input);

                glFlush();
            }
        }
        else if(opcion==5)
        {
            cout<<"[1]Modifique linea"<<endl;
            cout<<"[2]Modifique Elipse"<<endl;
            cout<<"[3]Modifique Poligono"<<endl;
            cin>>opcion2;
            cout<<"Ingrese numero de figura a modificar"<<endl;//falta validar
            cin>>num;

            pair<double,double>vectorT;
            cout<<"Ingrese factor de escalamiento en X";cin>>vectorT.first;
            cout<<"Ingrese factor de escalamiento en Y";cin>>vectorT.second;

            if(opcion2==1)
            {
                Line(coleccionLine[num].O,coleccionLine[num].F,defaultColor);
                coleccionLine[num].O=escalation(vectorT,coleccionLine[num].O);
                coleccionLine[num].F=escalation(vectorT,coleccionLine[num].F);
                Line(coleccionLine[num].O,coleccionLine[num].F,coleccionLine[num].input2);
                glFlush();
            }
            else if(opcion2==2)
            {
                elipse(coleccionCircle[num].O,coleccionCircle[num].radio1,coleccionCircle[num].radio2,1,defaultColor,defaultColor);
                coleccionCircle[num].O=escalation(vectorT,coleccionCircle[num].O);
                elipse(coleccionCircle[num].O,coleccionCircle[num].radio1,coleccionCircle[num].radio2,coleccionCircle[num].fill,coleccionCircle[num].input3,coleccionCircle[num].input3);
                glFlush();
            }
            else
            {
                regularPolygonPlot(coleccionPentagon[num].vertices,1,defaultColor,defaultColor);

                vector<pair<double,double> >newPoints;
                REP(i,coleccionPentagon[num].vertices.size())
                {
                    pair<double,double> temp;
                    temp=escalation(vectorT,coleccionPentagon[num].vertices[i]);
                    newPoints.PB( pair<double,double> (temp));
                }
                coleccionPentagon[num].vertices=newPoints;

                regularPolygonPlot(coleccionPentagon[num].vertices,coleccionPentagon[num].fill,coleccionPentagon[num].input,coleccionPentagon[num].input);

                glFlush();
            }
        }
        else if(opcion==6)
        {
            cout<<"[1]Modifique linea"<<endl;
            cout<<"[2]Modifique Elipse"<<endl;
            cout<<"[3]Modifique Poligono"<<endl;
            cin>>opcion2;
            cout<<"Ingrese numero de figura a modificar"<<endl;//falta validar
            cin>>num;
            double angle;
            pair<double,double>vectorT;
            cout<<"Ingrese punto de rote X\n";cin>>vectorT.first;
            cout<<"Ingrese punto de rote Y\n";cin>>vectorT.second;
            cout<<"Ingrese angulo\n";cin>>angle;

            if(opcion2==1)
            {
                Line(coleccionLine[num].O,coleccionLine[num].F,defaultColor);
                coleccionLine[num].O=rotateVector(coleccionLine[num].O,vectorT,angle);
                coleccionLine[num].F=rotateVector(coleccionLine[num].F,vectorT,angle);
                Line(coleccionLine[num].O,coleccionLine[num].F,coleccionLine[num].input2);
                glFlush();
            }
            else if(opcion2==2)
            {
                elipse(coleccionCircle[num].O,coleccionCircle[num].radio1,coleccionCircle[num].radio2,1,defaultColor,defaultColor);
                coleccionCircle[num].O=rotateVector(coleccionCircle[num].O,vectorT,angle);
                elipse(coleccionCircle[num].O,coleccionCircle[num].radio1,coleccionCircle[num].radio2,coleccionCircle[num].fill,coleccionCircle[num].input3,coleccionCircle[num].input3);
                glFlush();
            }
            else
            {
                regularPolygonPlot(coleccionPentagon[num].vertices,1,defaultColor,defaultColor);

                vector<pair<double,double> >newPoints;
                REP(i,coleccionPentagon[num].vertices.size())
                {
                    pair<double,double> temp;
                    temp=rotateVector(coleccionPentagon[num].vertices[i],vectorT,angle);
                    newPoints.PB( pair<double,double> (temp));
                }
                coleccionPentagon[num].vertices=newPoints;

                regularPolygonPlot(coleccionPentagon[num].vertices,coleccionPentagon[num].fill,coleccionPentagon[num].input,coleccionPentagon[num].input);

                glFlush();
            }
        }
        system("pause");
        system("cls");
    }



	glutMainLoop();


	return 0;
}
