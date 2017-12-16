#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <set>
#include <vector>
#include <utility>
#include <bits/stdc++.h>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>


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
        , bool inputFill
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

/************* SAVE *************************/


double StringToDouble(string num)
{
    double temp = atof(num.c_str());
    return temp;
}

string DoubleToString(double num)
{
    char cad[10000];
    sprintf(cad,"%lf",num);
    string cad1=cad;
    return cad1;
}

string pairToString(pair<double,double> data)
{
    string output = "";
    output += "(\n";
    output += DoubleToString(data.first);    
    output += "\n";
    output += DoubleToString(data.second);
    output += "\n)\n";    
    output += "\n";

    return output;
}

string vectorToString(vector< pair<double,double> > vectorData)
{
    int lenght = vectorData.size();

    string output = "";

    output += "!\n";
    for(int ii = 0; ii < lenght ; ii ++)
    {
        output += pairToString(vectorData[ii]);
    }
    output += "?\n";

    return output;
}

string colorToString(color data)
{
    string output = "";

    output += "-\n";
    output += DoubleToString(data.red);
    output += "\n";
    output += DoubleToString(data.green);
    output += "\n";
    output += DoubleToString(data.blue);
    output += "\n";        
    output += "_\n";

    return output;
}

string boolToString(bool data)
{
    if(data)
        return "bool\n1";
    else
        return "bool\n0";
}

void save(stateContainer lastState)
{
    ofstream save;
    save.open("save.tpg");


    objectDrawn auxiliar;
    int lenght = lastState.size();

    for(int ii = 0; ii < lenght; ii ++)
    {
        auxiliar = lastState[ii];
        save<<"$\n";        

        if(auxiliar.objectType == 1)
        {
            save<<auxiliar.objectType<<endl;
            save<<pairToString((auxiliar.startPointLine));
            save<<pairToString((auxiliar.endPointLine));
            save<<colorToString((auxiliar.boundariesColor));
            save<<"0\n";
        }
        else if(auxiliar.objectType == 2)
        {
            save<<auxiliar.objectType<<endl;
            save<<pairToString((auxiliar.center));
            save<<DoubleToString((auxiliar.radius_1))<<endl;
            save<<DoubleToString((auxiliar.radius_2))<<endl;
            save<<boolToString((auxiliar.fill))<<endl;
            save<<colorToString((auxiliar.boundariesColor));
            save<<colorToString((auxiliar.insideColor));
            save<<"0\n";
        }
        else if(auxiliar.objectType == 3)
        {
            save<<auxiliar.objectType<<endl;
            save<<vectorToString((auxiliar.coordinates));
            save<<boolToString((auxiliar.fill))<<endl;
            save<<colorToString((auxiliar.boundariesColor));
            save<<colorToString((auxiliar.insideColor));
            save<<"0\n";
        }

        save<<"&\n";
    }

    save.close(); 
}

/*
stateContainer load(string fileDirecton)
{   
    stateContainer lastStateLoaded;

    objectDrawn auxiliar;

    ifstream load;
    load.open(fileDirecton);

    bool objectDrawnOn,line,elipse,polygon;
    bool color,vector,

    string carryString;
    while(!load.eof())
    {
        load>> carryString;

        if(carryString == "$")
        {

        }
        el
    }

}
*/

void objectDrawnList(stateContainer actualState)
{
    objectDrawn auxiliar;
    int lenght = actualState.size();
    for(int i = 0; i < lenght; i++)
    {   
        auxiliar = actualState[i];

        if(auxiliar.objectType == 1)
        {
            cout<<"\nRECTA\tINDICE:\t"<<i;
        }
        else if(auxiliar.objectType == 2)
        {
            cout<<"\nELIPSE\tINDICE:\t"<<i;
        }
        else if(auxiliar.objectType == 3)
        {
            cout<<"\nPOLIGONO\tINDICE:\t"<<i;
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
    pair<double,double> inputPoint ,center ,Point_o ,Point_f,dataEscalate,dataPivot,dataTranslate;
    double radius,radius_1,radius_2,angle;
    int sides,num;
    double inputCarry[5];
    bool fill;
    color boundarieColor;
    color fillColor;

    int internalChooser;
    int option;

    cout<<"[1]Dibuja Linea"<<endl;
    cout<<"[2]Dibuja Elipse"<<endl;
    cout<<"[3]Dibuja Poligono"<<endl;
    cout<<"[4]Modificar Elemento"<<endl;
    cout<<"[5]Guardar"<<endl;
    cout<<"[6]Salir"<<endl;
    cin>>option;

    if(option==1)
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
    else if(option==2)
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
        else if(internalChooser == 2)
        {   
            cout<<"\nCircunferencia\n";
            cout<<"\nRadio\t"; cin>>radius_1;
            radius_2 = radius_1;
        }
        else
            return actualState;  

        cout<<"\nRellenar? [1] Si [0] No\t"; cin>>fill;

        if(fill == true)
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
        else if(fill == false)
        {
            cout<<"\nColor Borde\n";
            cout<<"\nRojo\t"; cin>>boundarieColor.red;
            cout<<"\nVerde\t"; cin>>boundarieColor.green;
            cout<<"\nAzul\t"; cin>>boundarieColor.blue;
        }            
        else
            return actualState;  

            auxiliarObjectDrawn = objectDrawnConstructor(2,pairNull,pairNull,center,radius_1,radius_2,coordinatesNull,fill,boundarieColor,fillColor);

            actualState.PB(auxiliarObjectDrawn);

            return actualState;

    }
    else if(option==3)
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

                if(fill == true)
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
                else if(fill == false)
                {
                    cout<<"\nColor Borde\n";
                    cout<<"\nRojo\t"; cin>>boundarieColor.red;
                    cout<<"\nVerde\t"; cin>>boundarieColor.green;
                    cout<<"\nAzul\t"; cin>>boundarieColor.blue;
                }            
                else
                    return actualState;  

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

                    if(fill == true)
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
                    else if(fill == false)
                    {
                        cout<<"\nColor Borde\n";
                        cout<<"\nRojo\t"; cin>>boundarieColor.red;
                        cout<<"\nVerde\t"; cin>>boundarieColor.green;
                        cout<<"\nAzul\t"; cin>>boundarieColor.blue;
                    }
                    else
                        return actualState;  
    
                    auxiliarObjectDrawn = objectDrawnConstructor(3,pairNull,pairNull,pairNull,doubleNull,doubleNull,coordinates,fill,boundarieColor,fillColor);

                    actualState.PB(auxiliarObjectDrawn);

                    return actualState;
                }   
                else if( internalChooser == 2)
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
                else
                    return actualState;  

            }

        }

    else if(option==4)
    {
        int index;
        
        objectDrawnList(actualState);

        cout<<"\nFIGURA DE INDICE?:\t"; cin>>index;

        cout<<"[1]Escalamiento"<<endl;
        cout<<"[2]Rotar"<<endl;
        cout<<"[3]Trazladar"<<endl;
//
        cout<<"[4]Eliminar"<<endl;
        cin>>option;
//
        objectDrawn auxiliar = actualState[index];

        if(option == 1)
        {   
            cout<<"\nFactor de Escalamiento\t";
            cout<<"\nX\t"; cin>>dataEscalate.first;
            cout<<"\nY\t"; cin>>dataEscalate.second;

            if(auxiliar.objectType == 1)
            {   
                auxiliar.startPointLine = escalationPoint(auxiliar.startPointLine,dataEscalate);
                auxiliar.endPointLine = escalationPoint(auxiliar.endPointLine,dataEscalate);

                actualState[index] = auxiliar;
                return actualState;

            }
            else if(auxiliar.objectType == 2)
            {
                auxiliar.radius_1 *= dataEscalate.first;
                auxiliar.radius_2 *= dataEscalate.second;

                actualState[index] = auxiliar;
                return actualState;
            }
            else if(auxiliar.objectType == 3)
            {
                auxiliar.coordinates = escalationVector(auxiliar.coordinates,dataEscalate);
                
                actualState[index] = auxiliar;
                return actualState;
            }
            else
                return actualState;  
        }
        else if(option == 2)
        {
            cout<<"\nRotar Respecto Al Punto\t";
            cout<<"\nX\t"; cin>>dataPivot.first;
            cout<<"\nY\t"; cin>>dataPivot.second;
            cout<<"\nAngulo?\t";
            cin>>angle;

            if(auxiliar.objectType == 1)
            {   
                auxiliar.startPointLine = rotatePoint(auxiliar.startPointLine,dataPivot,angle);
                auxiliar.endPointLine = rotatePoint(auxiliar.endPointLine,dataPivot,angle);

                actualState[index] = auxiliar;
                return actualState;

            }
            else if(auxiliar.objectType == 2)
            {
                auxiliar.center = rotatePoint(auxiliar.center,dataPivot,angle);

                actualState[index] = auxiliar;
                return actualState;
            }
            else if(auxiliar.objectType == 3)
            {
                auxiliar.coordinates = rotateVector(auxiliar.coordinates,dataPivot,angle);
                
                actualState[index] = auxiliar;
                return actualState;
            }
            else
                return actualState;  
            
        }
        else if(option == 3)
        {
            cout<<"\nTrasaladar (X,Y) unidades\t";
            cout<<"\nX\t"; cin>>dataTranslate.first;
            cout<<"\nY\t"; cin>>dataTranslate.second;

            if(auxiliar.objectType == 1)
            {   
                auxiliar.startPointLine = translationPoint(auxiliar.startPointLine,dataTranslate);
                auxiliar.endPointLine = translationPoint(auxiliar.endPointLine,dataTranslate);

                actualState[index] = auxiliar;
                return actualState;

            }
            else if(auxiliar.objectType == 2)
            {
                auxiliar.center = translationPoint(center,dataTranslate);

                actualState[index] = auxiliar;
                return actualState;
            }
            else if(auxiliar.objectType == 3)
            {
                auxiliar.coordinates = translationVector(auxiliar.coordinates,dataTranslate);
                
                actualState[index] = auxiliar;
                return actualState;
            }
            else
                return actualState;   
        }
        else if(option == 4)
        {
            string option;
            cout<<"\nConfirmar\t";
            cout<<"\n[Y] -  [N]\t"; cin>>option;

            if(option == "Y")
            {
                actualState = actualState.erase(index);
                return actualState;
            }
            else
            {
                return actualState;
            }
    }
    else if(option == 5)
    {
        save(actualState);
        return actualState;
    }
    else
        return actualState;
}
