#include <iostream>
#include <math.h>
#include <GL/glut.h>

#include <set>
#include <vector>
#include <utility>

#define PI 3.14159265
using namespace::std;

/******* Funciones Utilitarias **********************/
int rounder(float x){int  y = (x > (floor(x) +0.55555) ? floor(x + 0.5) : floor(x)); return y;}
double toRadians(double x){return (x/180.0)*PI; }
double toSexage(double x){return (x/PI)*180.0; }
double absVector(pair<int,int> data){return sqrt(data.first*data.first + data.second*data.second);}
/**************************************************/

/***************** ROTATION ****************/

pair<int, double> cuadrantAndAngleDetector(pair<int,int> coordinates)
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

pair<int,int> rotateVector(pair<int,int> coordinates, pair<int,int> referentPoint, double angle)
{
	pair<int,double> auxiliarRotatingValues;
	pair<int,int> output;
	pair<int,int> auxiliarPivotPoint;

	auxiliarPivotPoint.first = coordinates.first - referentPoint.first;
	auxiliarPivotPoint.second = coordinates.second - referentPoint.second; 

	auxiliarRotatingValues = cuadrantAndAngleDetector(auxiliarPivotPoint);

	angle += auxiliarRotatingValues.second;

	output.first = rounder(absVector(auxiliarPivotPoint)*cos(angle));
	output.second = rounder(absVector(auxiliarPivotPoint)*sin(angle));	

	output.first += referentPoint.first;
	output.second += referentPoint.second;

	return output;
}

vector<pair <int,int> > rotateVectorSet( vector<pair <int,int> > input ,pair<int,int> referentPoint ,double angle)
{
	int lenght = input.size();
	vector<pair <int,int> > output;

	for(int i = 0; i < lenght; i++)
	{
		output.push_back(rotateVector(input[i],referentPoint,angle));
	}

	return output;
}



/******** Trazlation ********/

pair<int, int> translation(pair<int,int> input , pair<int,int> data)
{
	pair<int,int> output;

	output.first = data.first + input.first;
	output.second = data.second + input.second;

	return output;
}

/************* ESCALATION ********/

pair<int,int> escalation(pair<int,int> input, pair<float,float> data)
{
	pair<int,int> output;

	output.first = data.first*input.first;
	output.second = data.second*input.second;

	return output;
}
