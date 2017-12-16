#include <iostream>
#include <math.h>
#include <GL/glut.h>

#include "./rta.h"

#include <set>
#include <vector>
#include <utility>




int P_Radius = 100, P_X_c = 200, P_Y_c = 0;
int C_Radius = 100, C_X_c = 300, C_Y_c = 300;
int lados = 5;


int num_segments = 2000;

void centerTester(int x_o, int y_o, int x, int y)
{
	glBegin(GL_LINES);
			glVertex2i(x_o, y_o);
			glVertex2i(x, y);
	glEnd();
}

void pentagon()
{	
	centerTester(200,0,P_X_c,P_Y_c);

	vector< pair<int,int>  > coordinates;
	pair <int,int> carry;
	
	for (int j = 0; j < lados; j++)
    {
    	carry.first = P_X_c + rounder(P_Radius * sin(2.0*PI*j/lados) + 0.5);
    	carry.second = P_Y_c + rounder(P_Radius * cos(2.0*PI*j/lados) + 0.5);
    	coordinates.push_back(carry);
    }

   /******* ROTACION ************

    pair<int,double> auxiliarRotatingValues;

    carry.first = P_X_c;
    carry.second = P_Y_c;

    auxiliarRotatingValues = cuadrantAndAngleDetector(carry);

    coordinates = rotateVectorSet(coordinates,auxiliarRotatingValues.second);
	
	**********************************/

	int x_a,y_a,x_b,y_b;

	int lenght = coordinates.size();

    glColor3i(0.0,1.0,0.0);
	
	for(int i = 0; i<lenght;i++)
	{
		x_a = coordinates[i].first;
		y_a = coordinates[i].second;

		x_b = coordinates[(i+1)%lenght].first;
		y_b = coordinates[(i+1)%lenght].second;

		glBegin(GL_LINES);
			glVertex2i(x_a, y_a);
			glVertex2i(x_b, y_b);
		glEnd();
	}

}

void circle()
{	
	centerTester(0,0,C_X_c,C_Y_c);

    glColor3i(0.0,1.0,0.0);

	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * PI * float(ii) / float(num_segments); 

		float x = C_Radius * cosf(theta);
		float y = C_Radius * sinf(theta);

		glVertex2f(x + C_X_c, y + C_Y_c);

	} 
	glEnd();

}


void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-640 , 640, -480 , 480);
}


int main(int argc, char **argv)
{
	glutInit(&argc,argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowPosition(0,0);
  	glutInitWindowSize(640,480);
  	glutCreateWindow("So Much Things");

	Init();

	glClear(GL_COLOR_BUFFER_BIT);

	pentagon();
	circle();

	glFlush();

	/********************************************/

	int first_option;
	int second_option;
	float scal_fact;
	double angle;
	int new_X;
	int new_Y;

	pair<int,int> referentPoint;

	while(true)
	{
	
	cout<<"Modificar [1]Pentagono  [2]Circuferencia\n";
	cin>>first_option;
	
	switch(first_option)
	{	
		case 1:
			{
				cout<<"Ampliar[1] Rotar[2] Trazladar[3]\n";
				cin>>second_option;
				switch(second_option)
				{	
					case 1:
						{
							cout<<"Factor de Escalamiento?\n";
							cin>>scal_fact;

							P_Radius = rounder(P_Radius*scal_fact);
							
							glClear(GL_COLOR_BUFFER_BIT);
									pentagon();
									circle();
							glFlush();
							glutPostRedisplay();

						}
						break;
					case 2:
						{
							cout<<"Angulo de Rotacion?\n";

							cin>>angle;
							angle = toRadians(angle);

							pair<int,int> polygonCenter;
							polygonCenter.first = P_X_c;
							polygonCenter.second = P_Y_c;

							referentPoint.first = 200;
							referentPoint.second = 0;

							polygonCenter = rotateVector(polygonCenter,referentPoint,angle);

							P_X_c = polygonCenter.first;
							P_Y_c = polygonCenter.second;
							

							glClear(GL_COLOR_BUFFER_BIT);

									pentagon();

								circle();
							glFlush();
							glutPostRedisplay();
						}
						break;
					case 3:
						{
							cout<<"Trazladar?\n";
							
							cin>>new_X;
							cin>>new_Y;
							P_X_c += new_X;
							P_Y_c += new_Y;
							
							glClear(GL_COLOR_BUFFER_BIT);

									pentagon();
									circle();

							glFlush();
							glutPostRedisplay();
						}
						break;
					default:
						break;
				}
			}
			break;
	
		case 2:
			{
				cout<<"Ampliar[1] Rotar[2] Trazladar[3]\n";
				cin>>second_option;
				switch(second_option)
				{	
					case 1:
						{
							cout<<"Factor de Escalamiento?\n";
							cin>>scal_fact;

							C_Radius = rounder(C_Radius*scal_fact);
							
							glClear(GL_COLOR_BUFFER_BIT);

									pentagon();
									circle();

							glFlush();
							glutPostRedisplay();

						}
						break;
					case 2:
						{
							cout<<"Angulo de Rotacion?\n";

							cin>>angle;
							angle = toRadians(angle);

							pair<int,int> circleCenter;
							circleCenter.first = C_X_c;
							circleCenter.second = C_Y_c;

							referentPoint.first = 0;
							referentPoint.second = 0;

							circleCenter = rotateVector(circleCenter,referentPoint,angle);

							C_X_c = circleCenter.first;
							C_Y_c = circleCenter.second;

							glClear(GL_COLOR_BUFFER_BIT);

									circle();

								pentagon();
							glFlush();
							glutPostRedisplay();
						}
						break;
					case 3:
						{
							cout<<"Trazladar?\n";
							
							cin>>new_X;
							cin>>new_Y;
							C_X_c += new_X;
							C_Y_c += new_Y;
							
							glClear(GL_COLOR_BUFFER_BIT);

									pentagon();
									circle();

							glFlush();
							glutPostRedisplay();
						}
						break;
					default:
						break;
				}
			}
			break;
		default:
			return 0;
	}
	}


	/*
	bool doit;
	cin>>doit;

	if(doit == 1)
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glTranslatef(-200, -100, 0);
		glRotatef(90,0,0,1);
		pentagon(1);
		glPopMatrix();
		circle();
		glFlush();
		glutPostRedisplay();		
	}
	
	if(doit == 0)
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		pentagon(2);
		glPopMatrix();
		circle();
		glFlush();
		glutPostRedisplay();
	}
	*/

	
	glutMainLoop();


	return 0;
}
