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
#include "./menuSaveAndLoad.h"

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