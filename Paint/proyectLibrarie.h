#ifndef PROYECTLIBRARIE_H_INCLUDED
#define PROYECTLIBRARIE_H_INCLUDED

#include <iostream>
#include <math.h>

#include <GL/glut.h>
#include <stdlib.h>

#include <set>
#include <vector>
#include <map>
#include <utility>

/************ MACROS PROPIAS ***********/

#define REP(i, a) for( int i = 0; i < a; i++ )
#define RFOR(i,x,y) for(int i = x; i>= y; i--)
#define FOR(i,x,y) for (int i = x; i < y; i++)
#define ITFOR(it,A) for(typeof A.begin() it = A.begin(); it!=A.end(); it++)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define VE vector <int>
#define mset(A,x) memset(A, x, sizeof A)
#define PB push_back
#define ones(x) __builtin_popcount(x)
#define cua(x) (x)*(x)
#define debug(x) cout <<#x << " = " << x << endl
#define adebug(x,n) cout <<#x<<endl; REP(i,n)cout<<x[i]<<char(i+1==n?10:32)
#define mdebug(x,m,n) cout <<#x<<endl; REP(i,m)REP(j,n)cout<<x[i][j]<<char(j+1==n?10:32)
#define LSOne(S) (S&(-S))

/************* MACROS NUMERICAS ***********/
#define MAX_X 640
#define MAX_Y 480
#define PI acos(-1.0)

/**** ESPECIFICACION NAMESAPCE *******/

using namespace::std;

/******* TIPOS DE DATO PROPIO **********/

struct color
{
	double red;
	double green;
	double blue;
};

struct Ex{
    double x1;
    double x2;
};

struct Arista
{
    double xI;
    double yI;
    double xF;
    double yF;
};

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

pair<double,double> rotatePoint(pair<double,double> coordinates, pair<double,double> referentPoint, double angle)
{
    angle = toRadians(angle);
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

vector<pair <double,double> > rotateVector( vector<pair <double,double> > input ,pair<double,double> referentPoint ,double angle)
{   

	int lenght = input.size();
	vector<pair <double,double> > output;

	for(int i = 0; i < lenght; i++)
	{
		output.push_back(rotatePoint(input[i],referentPoint,angle));
	}

	return output;
}



/******** Translation ********/

pair<double, double> translationPoint(pair<double,double> input , pair<double,double> data)
{
	pair<double,double> output;

	output.first = data.first + input.first;
	output.second = data.second + input.second;

	return output;
}

vector< pair<double,double> > translationVector (vector< pair<double,double> > input, pair<double,double> data)
{
    vector< pair<double,double> > output;

    int lenght = input.size();

    for (int i = 0; i < lenght ;++i)
    {
        output.PB(translationPoint(input[i],data));
    }

    return output;
}


/************* ESCALATION ********/

pair<double,double> escalationPoint(pair<double,double> input, pair<double,double> data)
{
	pair<double,double> output;

	output.first = data.first*input.first;
	output.second = data.second*input.second;

	return output;
}

vector< pair<double,double> > escalationVector(vector< pair<double,double> > input, pair<double,double> data)
{
    vector< pair<double,double> >output;

    int lenght = input.size();

    for (int i = 0; i < lenght ;++i)
    {
        output.PB(escalationPoint(input[i],data));
    }

    return output;
}


/****** RECORTE *******/

vector< pair< double, double> > recorte(vector< pair< double, double> > inputVertexData ,double xmin,double xmax,double ymin,double ymax)
{
    vector<int> bin;
    vector< pair< double, double> > res;
    int t= inputVertexData.size();
    bin.assign(t<<1,0);
    for(int i=0;i<(t);i++)
    {
        if( inputVertexData[i].first<xmin)//izquierda
            bin[i]|=(1);
        if( inputVertexData[i].first>xmax)//derecha
            bin[i]|=(1<<1);
        if( inputVertexData[i].second<ymin)//abajo
            bin[i]|=(1<<2);
        if( inputVertexData[i].second>ymax)//arriba
            bin[i]|=(1<<3);
    }
    for(int i=0;i<t;i+=2)
    {
        if(bin[i]!=-1&&bin[i+1]!=-1)
        {
              if((bin[i]|bin[i+1])==0)
                {
                    bin[i]=-1;
                    bin[i+1]=-1;
                }
            else if((bin[i]&bin[i+1])!=0)
                {
                    glColor3f(0.0,0.0,0.0);
                }
            else if((bin[i]&bin[i+1])==0)
                {
                    for(int j=i;j<i+2;j++)
                    {
                        while(bin[j]!=0)
                        {
                            double m=(inputVertexData[i+1].second-inputVertexData[i].second)/(inputVertexData[i+1].first-inputVertexData[i].first);
                            if(bin[j]&(1))//izquierda
                            {
                                bin[j]-=1;
                                inputVertexData[j].second=inputVertexData[j].second+(((xmin*1.0)-inputVertexData[j].first)*m),inputVertexData[j].first=xmin;
                            }
                            if(bin[j]&(1<<1))//derecha
                            {
                                bin[j]-=2;
                                inputVertexData[j].second=inputVertexData[j].second+(((xmax*1.0)-inputVertexData[j].first)*m),inputVertexData[j].first=xmax;
                            }
                            if(bin[j]&(1<<2))//abajo
                            {
                                bin[j]-=4;
                                inputVertexData[j].first=inputVertexData[j].first+(((ymin*1.0)-inputVertexData[j].second)/m),inputVertexData[j/2].second=ymin;
                            }
                            if(bin[j]&(1<<3))//arriba
                            {
                                bin[j]-=8;
                                inputVertexData[j].first=inputVertexData[j].first+(((ymax*1.0)-inputVertexData[j].second)/m),inputVertexData[j/2].second=ymax;
                            }
                        }
                            res.PB(pair<double ,double > (inputVertexData[j].first,inputVertexData[j].second));
                    }

                }
        }

    }
    return res;
}

/************ DDA LINE ******************/

void line(pair<double,double> P_o,pair<double,double> P_f, color colorDataLine)
{
	double dx=(P_f.first-P_o.first);
	double dy=(P_f.second-P_o.second);
	int steps;
	double xInc,yInc,x=P_o.first,y=P_o.second;

	steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
	steps *= 100;
	xInc=dx/(double)steps;
	yInc=dy/(double)steps;

    glColor3f(colorDataLine.red,colorDataLine.green,colorDataLine.blue);
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

/************ SIDES GENERATOR********************/

vector< pair<double,double> > regularPolygonGenerator(int numberOfSides, pair<double,double> center, double radius)
{

	vector< pair<double,double>  > coordinates;
	pair <double,double> carry;

	for (int j = 0; j < numberOfSides; j++)
    {
    	carry.first = center.first + (radius * sin(2.0*PI*j/numberOfSides));
    	carry.second = center.second + (radius * cos(2.0*PI*j/numberOfSides));
    	coordinates.push_back(carry);
    }

    return coordinates;
}

/************** ANALIZADOR DE BORDES ****************/
map< int, pair<double,double> > boundariesContainer(double x, double y, map< int, pair<double,double> > mapOfBoundaries)
{
    if(mapOfBoundaries.count(y)>0){
        mapOfBoundaries[y].first=min(mapOfBoundaries[y].first,x);
        mapOfBoundaries[y].second=max(mapOfBoundaries[y].second,x);
    }
    else{
        mapOfBoundaries[y].first=x;
        mapOfBoundaries[y].second=x;
    }

    return mapOfBoundaries;
}

/******************* ELIPSE / CIRCUNFERENCIA ****************/
void ellipse(pair<double,double> centro, double radio1, double radio2, bool relleno, color colorDataBoundaries,color colorDataFill)
{
    double X_c = centro.first ,Y_c = centro.second;
    double R_x = radio1, R_y = radio2;
	double p;
	double x,y;

/************** FILLED ******************/
    if(relleno==true)
    {

        map< int, pair<double,double> > mapOfBoundaries;

        glColor3f(colorDataBoundaries.red,colorDataBoundaries.green,colorDataBoundaries.blue);
        glBegin(GL_POINTS);

    	p=R_y*R_y-R_x*R_x*R_y+R_x*R_x/4;
    	x=0;
    	y=R_y;

        while(2.0*R_y*R_y*x <= 2.0*R_x*R_x*y){
            if(p < 0){
    			x++;
    			p = p+2*R_y*R_y*x+R_y*R_y;
    		}
    		else{
    			x++;
    			y--;
    			p = p+2*R_y*R_y*x-2*R_x*R_x*y-R_y*R_y;
    		}
            glVertex2d(X_c + x,Y_c + y);
                mapOfBoundaries =  boundariesContainer(X_c + x, Y_c + y, mapOfBoundaries);
            glVertex2d(X_c + x,Y_c - y);
                mapOfBoundaries =  boundariesContainer(X_c + x, Y_c - y, mapOfBoundaries);
            glVertex2d(X_c - x,Y_c + y);
                mapOfBoundaries =  boundariesContainer(X_c - x, Y_c + y, mapOfBoundaries);
            glVertex2d(X_c - x,Y_c - y);
                mapOfBoundaries =  boundariesContainer(X_c - x, Y_c - y, mapOfBoundaries);
        }

        p=R_y*R_y*(x+0.5)*(x+0.5)+R_x*R_x*(y-1)*(y-1)-R_x*R_x*R_y*R_y;
        while(y > 0){
       		if(p <= 0){
    			x++;y--;
    			p = p+2*R_y*R_y*x-2*R_x*R_x*y+R_x*R_x;
    		}
    		else{
    			y--;
    			p = p-2*R_x*R_x*y+R_x*R_x;
    		}
            glVertex2d(X_c + x,Y_c + y);
                mapOfBoundaries =  boundariesContainer(X_c + x, Y_c + y, mapOfBoundaries);
            glVertex2d(X_c + x,Y_c - y);
                mapOfBoundaries =  boundariesContainer(X_c + x, Y_c - y, mapOfBoundaries);
            glVertex2d(X_c - x,Y_c + y);
                mapOfBoundaries =  boundariesContainer(X_c - x, Y_c + y, mapOfBoundaries);
            glVertex2d(X_c - x,Y_c - y);
                mapOfBoundaries =  boundariesContainer(X_c - x, Y_c - y, mapOfBoundaries);
        }
    	glEnd();


        glColor3f(colorDataFill.red,colorDataFill.green,colorDataFill.blue);
        glBegin(GL_LINES);
        for(map<int, pair<double,double> >::iterator it=mapOfBoundaries.begin(); it!=mapOfBoundaries.end(); it++)
        {
            double xi = it->second.first, yi = it->first;
            double xf = it->second.second, yf = it-> first;
            glVertex2f(xi, yi);
            glVertex2f(xf, yf);

            glVertex2f(xi, yi+0.5);
            glVertex2f(xf, yf+0.5);
        }
        glEnd();
    }
    else/************ NOT FILLED ********************/
    {

        glColor3f(colorDataBoundaries.red,colorDataBoundaries.green,colorDataBoundaries.blue);
        glBegin(GL_POINTS);

        p=R_y*R_y-R_x*R_x*R_y+R_x*R_x/4;
        x=0;
        y=R_y;

        while(2.0*R_y*R_y*x <= 2.0*R_x*R_x*y){
            if(p < 0){
                x++;
                p = p+2*R_y*R_y*x+R_y*R_y;
            }
            else{
                x++;
                y--;
                p = p+2*R_y*R_y*x-2*R_x*R_x*y-R_y*R_y;
            }
            glVertex2d(X_c + x,Y_c + y);
            glVertex2d(X_c + x,Y_c - y);
            glVertex2d(X_c - x,Y_c + y);
            glVertex2d(X_c - x,Y_c - y);
        }

        p=R_y*R_y*(x+0.5)*(x+0.5)+R_x*R_x*(y-1)*(y-1)-R_x*R_x*R_y*R_y;
        while(y > 0){
            if(p <= 0){
                x++;y--;
                p = p+2*R_y*R_y*x-2*R_x*R_x*y+R_x*R_x;
            }
            else{
                y--;
                p = p-2*R_x*R_x*y+R_x*R_x;
            }
            glVertex2d(X_c + x,Y_c + y);
            glVertex2d(X_c + x,Y_c - y);
            glVertex2d(X_c - x,Y_c + y);
            glVertex2d(X_c - x,Y_c - y);
        }
        glEnd();

    }
}

double doubleCuter(double n){return (1.0*round(n*100))/100;}

/************* VERTEX GENERATOR ***********/

pair< set< double> , vector<Arista> > vertexGenerator(vector< pair<double,double> > coordinates)
{

    vector<Arista> vertexOutput;
    set<double> ySetOutput;

    int x, y, auxX, auxY;

    int lenght = coordinates.size();

    Arista auxiliarSide;

    for (int i = 0; i <lenght; i++)
    {
        x = coordinates[i].first;
        y = coordinates[i].second;

        auxX = coordinates[(i+1)%lenght].first;
        auxY = coordinates[(i+1)%lenght].second;

        ySetOutput.insert(y);

        auxiliarSide.xI = auxX;
        auxiliarSide.yI = auxY;
        auxiliarSide.xF = x;
        auxiliarSide.yF = y;
        vertexOutput.push_back(auxiliarSide);
    }

    pair< set< double> , vector<Arista> > output;

    output.first = ySetOutput;
    output.second = vertexOutput;

    return output;
}

/************ REGULAR POLYGON ************/

void polygonPlot(vector< pair<double,double> > coordinates , bool paint,  color colorDataBoundaries,color colorDataFill)
{

/************* FILLED **************/
    if(paint)
    {
        double yMenor,yMayor;
        set<double>con;
        set<double>::iterator it;
        set<double>::iterator iter;
        vector< set<double> >equis;

        pair< set< double> , vector<Arista> > auxiliarFillData;

        auxiliarFillData = vertexGenerator(coordinates);

        set <double> auxiliarYCordinates = auxiliarFillData.first;
        vector<Arista> vertexContainer = auxiliarFillData.second;

        yMenor = *(auxiliarYCordinates.begin());
        yMayor = *(auxiliarYCordinates.rbegin());
        auxiliarYCordinates.clear();

        for(double i=yMenor; i<=yMayor; i+=0.25)
        {
            equis.push_back(con);
            auxiliarYCordinates.insert(i);
        }

        for(int i=0; i<(int)vertexContainer.size(); i++)
        {
            glColor3f(colorDataBoundaries.red,colorDataBoundaries.green,colorDataBoundaries.blue);
            glBegin(GL_LINES);
                glVertex2f(vertexContainer[i].xI, vertexContainer[i].yI);
                glVertex2f(vertexContainer[i].xF, vertexContainer[i].yF);
            glEnd();
        }

        double xi, yi, xf, yf, auxX, auxY;

        for(int i=0; i<(int)vertexContainer.size(); i++)
        {
            xi = vertexContainer[i].xI;
            yi = vertexContainer[i].yI;
            xf = vertexContainer[i].xF;
            yf = vertexContainer[i].yF;
            if(yf<yi)
            {
                auxX = xi; xi = xf; xf = auxX;
                auxY = yi; yi = yf; yf = auxY;
            }
            double invP = doubleCuter((1.0*(xf - xi))/(4*(yf - yi)));
            if(yi != yf)
            {
                int aux;
                for(double j=yi; j<=yf; j+=0.25)
                {
                    aux = j*4 - yMenor*4;
                    if(j==yi)
                    {
                        equis[aux].insert(xi);
                    }
                    else
                    {
                        xi = xi + invP;
                        xi = doubleCuter(xi);
                        equis[aux].insert(xi);
                    }
                    if(j==yf)
                    {
                        equis[aux].insert(xf);
                    }
                }

            }
            else
            {
                int aux = yi*4 - yMenor*4;
                equis[aux].insert(xi);
                equis[aux].insert(xf);
            }
        }

        int k=-1;
        double x0, x1;
        for(iter = auxiliarYCordinates.begin(); iter!=auxiliarYCordinates.end(); iter++)
        {
                k++;
                x0 = *(equis[k].begin());
                x1 = *(equis[k].rbegin());
                glColor3f(colorDataFill.red,colorDataFill.green,colorDataFill.blue);
                glBegin(GL_LINES);
                    glVertex2f(x0, *iter);
                    glVertex2f(x1, *iter);
                glEnd();
        }
    }

/******* NOT FILLED ****/
    else
    {
        int lenght = coordinates.size();

        for(int i=0; i< lenght ; i++)
        {
            glColor3f(colorDataBoundaries.red,colorDataBoundaries.green,colorDataBoundaries.blue);
            glBegin(GL_LINES);
                glVertex2f(coordinates[i].first, coordinates[i].second);
                glVertex2f(coordinates[(i+1)%lenght].first, coordinates[(i+1)%lenght].second);
            glEnd();
        }
    }
} 

void razonT(int opc)   
{
    switch (opc)
    {
        case 1:
            for(float i=-20; i<20; i+=0.1){
                glBegin(GL_POINTS);
                    glVertex2f(i, sin(i));
                glEnd();
            }
            break;
        case 2:
            for(float i=-20; i<20; i+=0.1){
                glBegin(GL_POINTS);
                    glVertex2f(i, cos(i));
                glEnd();
            }
            break;
        case 3:
            for(float i=-20; i<20; i+=0.1){
                glBegin(GL_POINTS);
                    glVertex2f(i, tan(i));
                glEnd();
            }
            break;
    }
    glFlush();
}

#endif // PROYECTLIBRARIE_H_INCLUDED
