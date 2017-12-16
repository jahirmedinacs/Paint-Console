#include <iostream>
#include <math.h>
#include <GL/glut.h>

#include <set>
#include <vector>
#include <utility>

#define MAX_X 640
#define MAX_Y 480
#define PI 3.14159265
using namespace::std;

/******* Funciones Utilitarias **********************/
int rounder(double x){int  y = (x > (floor(x) +0.55555) ? floor(x + 0.5) : floor(x)); return y;}
double toRadians(double x){return (x/180.0)*PI; }
double toSexage(double x){return (x/PI)*180.0; }
double absVector(pair<int,int> data){return sqrt(data.first*data.first + data.second*data.second);}
/**************************************************/

/************** GRILLA ************/
void gridON()
{
	glBegin(GL_LINES);
		glVertex2i(-MAX_X, 0);
		glVertex2i(MAX_X, 0);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(0, -MAX_Y);
		glVertex2i(0, MAX_Y);
	glEnd();
}

/***************** ROTATION ****************/

pair<int, double> cuadrantAndAngleDetector(pair<double,double> coordinates)
{	
	pair<int,double> output;

/**** REGULAR ANGLES ****/
	if( coordinates.first > 0 and coordinates.second > 0 )
	{
		output.first = 1;
		output.second = atan(abs((coordinates.second*1.0)/coordinates.first));
	}
	else if( coordinates.first < 0 and coordinates.second > 0 )
	{
		output.first = 2;
		output.second = PI - atan(abs((coordinates.second*1.0)/coordinates.first));
	}
	else if( coordinates.first < 0 and coordinates.second < 0 )
	{
		output.first = 3;
		output.second = PI + atan(abs((coordinates.second*1.0)/coordinates.first));
	}
	else if( coordinates.first > 0 and coordinates.second < 0 )
	{
		output.first = 4;
		output.second = 2*PI - atan(abs((coordinates.second*1.0)/coordinates.first));		
	}
/***** EXCEPTIONS ******/
	else if(coordinates.first == 0 and coordinates.second == 0)
	{
		output.first = 0;
		output.second = 0.0;
	}
	else if(coordinates.first == 0 and coordinates.second > 0)
	{
		output.first = 0;
		output.second = PI/2;
	}
	else if(coordinates.first < 0 and coordinates.second == 0)
	{
		output.first = 0;
		output.second = PI;
	}
	else if(coordinates.first == 0 and coordinates.second < 0)
	{
		output.first = 0;
		output.second = 3*PI/2;
	}	
	else if(coordinates.first > 0 and coordinates.second == 0)
	{
		output.first = 0;
		output.second = 2*PI;
	}

	return output;
}

pair<double,double> rotateVector(pair<double,double> coordinates, pair<double,double> referentPoint, double angle)
{
	pair<int,double> auxiliarRotatingValues;
	pair<double,double> output;
	pair<double,double> auxiliarPivotPoint;

	auxiliarPivotPoint.first = coordinates.first - referentPoint.first;
	auxiliarPivotPoint.second = coordinates.second - referentPoint.second; 

	auxiliarRotatingValues = cuadrantAndAngleDetector(auxiliarPivotPoint);

	angle += auxiliarRotatingValues.second;

	output.first = absVector(auxiliarPivotPoint)*cos(angle);
	output.second = absVector(auxiliarPivotPoint)*sin(angle);	

	output.first += referentPoint.first;
	output.second += referentPoint.second;

	return output;
}

vector<pair <double,double> > rotateVectorSet( vector<pair <double,double> > input ,pair<double,double> referentPoint ,double angle)
{
	int lenght = input.size();
	vector<pair <double,double> > output;

	for(int i = 0; i < lenght; i++)
	{
		output.push_back(rotateVector(input[i],referentPoint,angle));
	}

	return output;
}



/******** Trazlation ********/

pair<double, double> translation(pair<double,double> input , pair<double,double> data)
{
	pair<double,double> output;

	output.first = data.first + input.first;
	output.second = data.second + input.second;

	return output;
}

/************* ESCALATION ********/

pair<double,double> escalation(pair<double,double> input, pair<double,double> data)
{
	pair<double,double> output;

	output.first = data.first*input.first;
	output.second = data.second*input.second;

	return output;
}

/************ DDA LINE ******************/

void Line(pair<double,double> P_o,pair<double,double> P_f)
{
	double dx=(P_f.first-P_o.first);
	double dy=(P_f.second-P_o.second);
	int steps;
	double xInc,yInc,x=P_o.first,y=P_o.second;

	steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
	steps *= 100;
	xInc=dx/(double)steps;
	yInc=dy/(double)steps; 

	glBegin(GL_POINTS);
  		glVertex2f(x,y); 
		int k;
		for(k=0;k<steps;k++)
		{	

			x+=xInc;
			y+=yInc;
			glVertex2f((x), (y));
		}

	glEnd();
}