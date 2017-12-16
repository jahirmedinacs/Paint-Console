#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <set>
#include <vector>
#include <utility>
#include <bits/stdc++.h>
#include <stack>
#include <string>

#include "./proyectLibrarie.h"

struct objectDrawn
{
    int objectType;

    pair<double,double> startPointLine;
    pair<double,double> endPointLine;

    pair<double,double> center;
    double radius_1;
    double radius_2;

    vector< pair<double,double> > coordinates;

    bool fill;

    color boundariesColor;
    color insideColor;

};

objectDrawn objectDrawnConstructor(
        int inputObjectType
        , pair<double,double> inputStartPointLine
        , pair<double,double> inputEndPointLine
        , pair<double,double> inputCenter
        , double inputRadius_1
        , double inputRadius_2
        , vector< pair<double,double> > inputCoordinates
        ,bool inputFill
        , color inputBoundariesColor
        , color inputInsideColor)
    {
        objectDrawn output;

        output.objectType = inputObjectType;
        output.startPointLine = inputStartPointLine;
        output.endPointLine = inputEndPointLine;
        output.center = inputCenter;
        output.radius_1 = inputRadius_1;
        output.radius_2 = inputRadius_2;
        output.coordinates = inputCoordinates;
        output.fill = inputFill;
        output.boundariesColor = inputBoundariesColor;
        output.insideColor = inputInsideColor;

        return output;
    }

typedef vector< objectDrawn >  stateContainer;

typedef stack < stateContainer > eventStack;


vector< pair< double, double> > manualPolygonInput()
{
    int howmany;
    pair< double,double > inputCarry;
    vector< pair< double, double> > output;

    cout<<"\nNumero de Vertices?\t"; cin>>howmany;

    for(int i = 0; i < howmany; i++)
    {
        cout<<"\nX["<<i+1<<"]\t"; cin>>inputCarry.first;
        cout<<"\nY["<<i+1<<"]\t"; cin>>inputCarry.second;
        output.PB(inputCarry);
    }

    return output;
}

void startText()
{
    const char *string;
    string = "PROYECTO FINAL";
    int j = strlen( string );

    glColor3f( 0, 0, 0 );
    glRasterPos2f( 0, 0 );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-MAX_X, MAX_X, -MAX_Y , MAX_Y);
}

void displayActualDrawnContainer(stateContainer actualState)
{
    int lenght = actualState.size();

    objectDrawn auxiliar;

    for(int ii = 0; ii < lenght; ii ++)
    {   
        auxiliar = actualState[ii];

        if(auxiliar.objectType == 1)
        {
            line(auxiliar.startPointLine,auxiliar.endPointLine,auxiliar.boundariesColor);
        }
        else if(auxiliar.objectType == 2)
        {
            ellipse(auxiliar.center,auxiliar.radius_1,auxiliar.radius_2,auxiliar.fill,auxiliar.boundariesColor,auxiliar.insideColor);
        }
        else if(auxiliar.objectType == 3)
        {
            polygonPlot(auxiliar.coordinates,auxiliar.fill,auxiliar.boundariesColor,auxiliar.insideColor);
        }
        else
        {
            return;
        }
    }
}


stateContainer operationalMenu(stateContainer actualState)
{   
    objectDrawn auxiliarObjectDrawn;

    pair<double,double> pairNull;
    vector< pair<double,double> > coordinatesNull;
    double doubleNull;
    color colorNull;

    vector< pair<double,double> > coordinates;
    pair<double,double> inputPoint ,center ,Point_o ,Point_f;
    double radius,radius_1,radius_2;
    int sides,num;
    double inputCarry[5];
    bool fill;
    color boundarieColor;
    color fillColor;

    int internalChooser;
    int opcion;

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
            cout<<"\nLinea\n";
            cout<<"Primer Punto"<<endl;
            cout<<"\n X:\t"; cin>>Point_o.first;
            cout<<"\n Y:\t"; cin>>Point_o.second;

            cout<<"Segundo Punto"<<endl;
            cout<<"\n X:\t"; cin>>Point_f.first;
            cout<<"\n Y:\t"; cin>>Point_f.second;

            cout<<"\nColor De Linea\t";

            cout<<"\nRojo\t"; cin>>boundarieColor.red;
            cout<<"\nVerde\t"; cin>>boundarieColor.green;
            cout<<"\nAzul\t"; cin>>boundarieColor.blue;

            auxiliarObjectDrawn = objectDrawnConstructor(1,Point_o,Point_f,pairNull,doubleNull,doubleNull,coordinatesNull,false,boundarieColor,colorNull);

            actualState.PB(auxiliarObjectDrawn);

            return actualState;
    }
    else if(opcion==2)
    {   
        cout<<"\nElipse[1] Circunferencia[2]\n";
        cin>>internalChooser;   

        cout<<"\nCentro X\t"; cin>>center.first;
        cout<<"\nCentro Y\t"; cin>>center.second;

        if(internalChooser == 1)
        {   
            cout<<"\nElipse\n";
            cout<<"\nRadio1\t"; cin>>radius_1;
            cout<<"\nRadio2\t"; cin>>radius_2;
        }
        else
        {   
            cout<<"\nCircunferencia\n";
            cout<<"\nRadio\t"; cin>>radius_1;
            radius_2 = radius_1;
        }

        cout<<"\nRellenar? [1] Si [0] No\t"; cin>>fill;

        if(fill)
        {   
            cout<<"\nColor Borde\n";
            cout<<"\nRojo\t"; cin>>boundarieColor.red;
            cout<<"\nVerde\t"; cin>>boundarieColor.green;
            cout<<"\nAzul\t"; cin>>boundarieColor.blue;

            cout<<"\nColor Relleno\n";
            cout<<"\nRojo\t"; cin>>fillColor.red;
            cout<<"\nVerde\t"; cin>>fillColor.green;
            cout<<"\nAzul\t"; cin>>fillColor.blue;
        }
        else
        {
            cout<<"\nColor Borde\n";
            cout<<"\nRojo\t"; cin>>boundarieColor.red;
            cout<<"\nVerde\t"; cin>>boundarieColor.green;
            cout<<"\nAzul\t"; cin>>boundarieColor.blue;
        }

            auxiliarObjectDrawn = objectDrawnConstructor(2,pairNull,pairNull,center,radius_1,radius_2,coordinatesNull,fill,boundarieColor,fillColor);

            actualState.PB(auxiliarObjectDrawn);

            return actualState;

    }
    else if(opcion==3)
        {       
            cout<<"\nPoligono Regular[1] Poligono Cualquiera[2]\n";
            cin>>internalChooser;
            if(internalChooser == 1)
            {   
                cout<<"\nPoligono Regular\n";
                cout<<"\nCentro X\t"; cin>>center.first;
                cout<<"\nCentro Y\t"; cin>>center.second;

                cout<<"\nNumero de lados\t"; cin>>sides;

                cout<<"\nRadio \t";   cin>>radius;

                cout<<"\nRellenar? [1] Si [0] No\t"; cin>>fill;

                coordinates = regularPolygonGenerator(sides,center,radius);

                if(fill)
                {   
                    cout<<"\nColor Borde\n";
                    cout<<"\nRojo\t"; cin>>boundarieColor.red;
                    cout<<"\nVerde\t"; cin>>boundarieColor.green;
                    cout<<"\nAzul\t"; cin>>boundarieColor.blue;

                    cout<<"\nColor Relleno\n";
                    cout<<"\nRojo\t"; cin>>fillColor.red;
                    cout<<"\nVerde\t"; cin>>fillColor.green;
                    cout<<"\nAzul\t"; cin>>fillColor.blue;
                }
                else
                {
                    cout<<"\nColor Borde\n";
                    cout<<"\nRojo\t"; cin>>boundarieColor.red;
                    cout<<"\nVerde\t"; cin>>boundarieColor.green;
                    cout<<"\nAzul\t"; cin>>boundarieColor.blue;
                }

                auxiliarObjectDrawn = objectDrawnConstructor(3,pairNull,pairNull,pairNull,doubleNull,doubleNull,coordinates,fill,boundarieColor,fillColor);

                actualState.PB(auxiliarObjectDrawn);

                return actualState;

            }
            else
            {
                cout<<"\nPoligono Convexo[1] Poligono Concavo[2]\n";
                cin>>internalChooser;
                if(internalChooser == 1)
                {
                    coordinates = manualPolygonInput();
                    cout<<"\nRellenar? [1] Si [0] No\t"; cin>>fill;

                    if(fill)
                    {   
                        cout<<"\nColor Borde\n";
                        cout<<"\nRojo\t"; cin>>boundarieColor.red;
                        cout<<"\nVerde\t"; cin>>boundarieColor.green;
                        cout<<"\nAzul\t"; cin>>boundarieColor.blue;

                        cout<<"\nColor Relleno\n";
                        cout<<"\nRojo\t"; cin>>fillColor.red;
                        cout<<"\nVerde\t"; cin>>fillColor.green;
                        cout<<"\nAzul\t"; cin>>fillColor.blue;
                    }
                    else
                    {
                        cout<<"\nColor Borde\n";
                        cout<<"\nRojo\t"; cin>>boundarieColor.red;
                        cout<<"\nVerde\t"; cin>>boundarieColor.green;
                        cout<<"\nAzul\t"; cin>>boundarieColor.blue;
                    }
    
                    auxiliarObjectDrawn = objectDrawnConstructor(3,pairNull,pairNull,pairNull,doubleNull,doubleNull,coordinates,fill,boundarieColor,fillColor);

                    actualState.PB(auxiliarObjectDrawn);

                    return actualState;
                }   
                else
                {
                    coordinates = manualPolygonInput();
                    cout<<"\nColor Borde\n";
                    cout<<"\nRojo\t"; cin>>boundarieColor.red;
                    cout<<"\nVerde\t"; cin>>boundarieColor.green;
                    cout<<"\nAzul\t"; cin>>boundarieColor.blue;

                    auxiliarObjectDrawn = objectDrawnConstructor(3,pairNull,pairNull,pairNull,doubleNull,doubleNull,coordinates,false,boundarieColor,colorNull);

                    actualState.PB(auxiliarObjectDrawn);

                    return actualState;
                }

            }

        }

/*
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
*/
    else
        return actualState;
}