#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <set>
#include <vector>
#include <utility>
#include <bits/stdc++.h>
#include <stack>
#include <string>
#include <fsteam>
#include <sstream>

#include "./proyectLibrarie.h"
#include "./menuSaveAndLoad.h"

/*********** SAVE AND LOAD *************/

double StringToDouble(String num)
{
    double temp = atof(num.c_str());
    return temp;
}

string DoubletoString(double num)
{
        char cad[10000];
        sprintf(cad,"%lf",num);
        string cad1=cad;
        return cad1;
}

string pairToString(pair<double,double> data)
{
    string output = "";
    output += DoubleToString(data.first);    
    output += "\n";
    output += DoubleToString(data.second);    
    output += "\n";

    return output;
}

string vectorToString(vector< pair<double,double> > vectorData)
{
    int lenght = vectorData.size();

    string output = "";

    output += "!\n";
    for(int ii = 0, ii < lenght , ii ++)
    {
        output += pairToString(vectorData[ii]);
    }
    output += "?\n";
}

string colorToString()

void save(stateContainer lastState)
{
    ofstream save;
    save.open("save.tpg");


    objectDrawn auxiliar;
    int lenght = lastState.size();

    for(int ii = 0, ii < lenght , ii ++)
    {
        auxiliar = lastState[ii];
        save<<"$\n";        

        if(auxiliar.inputObjectType == 1)
        {
            save<<auxiliar.inputObjectType<<endl;
            save<<pairToString((auxiliar.startPointLine));
            save<<pairToString((auxiliar.endPointLine));


        }
        else if(auxiliar.inputObjectType == 2)
        {

        }
        else if(auxiliar.inputObjectType == 3)
        {

        }

        save<<"&\n"
    }   
}

/*********************************/

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(MAX_X,MAX_Y);
            glutCreateWindow("Proyecto Final - Computacion Grafica");
    Init();

    glClear(GL_COLOR_BUFFER_BIT);
        startText();
    glFlush();

    eventStack principalEventStack;
    eventStack auxiliarEventStack;

    stateContainer auxiliarStateContainer;

    principalEventStack.push(auxiliarStateContainer);

    while(true)
    {    
        auxiliarStateContainer = principalEventStack.top();

        auxiliarStateContainer = operationalMenu(auxiliarStateContainer);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
            displayActualDrawnContainer(auxiliarStateContainer);

        glFlush();
        glutPostRedisplay();


        principalEventStack.push(auxiliarStateContainer);

    }

	glutMainLoop();

	return 0;
}