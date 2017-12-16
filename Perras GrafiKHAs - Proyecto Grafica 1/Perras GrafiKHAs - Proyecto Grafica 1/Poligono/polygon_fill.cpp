#include <iostream>
#include <math.h>
#include <GL/glut.h>

#include <set>
#include <vector>
#include <utility>

#define PI 3.141592
using namespace::std;

int rounder(float x){int  y = (x > (floor(x) +0.55555) ? floor(x + 0.5) : floor(x)); return y;}

vector< pair<int,int>  > coordinates;

int Radius, X_c, Y_c;
int X_max,Y_max,X_min,Y_min;


void PolygonFill()
{	
	X_max ++:
	X_min --;

	int lenght = coordinates.size();

	glClear(GL_COLOR_BUFFER_BIT);
    glColor3i(0.0,1.0,0.0);

    int rastrerLenght = Y_max - Y_min +1;
 //  set<int>[] Boundaries = new set<int>[rastrerLenght];
	vector< set <int> > Boundaries;
	Boundaries.reserve(rastrerLenght);

	int x_a,y_a;
	int x_b,y_b;
	float inverse_m;

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

		inverse_m = (y_b-y_a > 0 ? (x_b-x_a*1.0)/(y_b-y_a*1.0) : (y_b-y_a*1.0)/(x_b-x_a*1.0));

		for(int j = )


	}

	glFlush();
}


void showVector(vector< pair<int,int> > data)
{
	vector< pair<int,int> >::iterator jj = data.begin();
	pair< int , int > carry;
	int vertex = 1;

	while(jj != data.end())
	{
		carry = *jj;
		cout<<"Vertice["<<vertex<<"]\tX:\t"<<carry.first<<"\tY:\t"<<carry.second<<"\n";
		vertex ++;	
		jj++;
	}

	cout<<" "<<X_max<<" "<<X_min<<" "<<Y_max<<" "<< Y_min;
}

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-640 , 640, -480 , 480);
}	

int main(int argc, char **argv)
{
	int x_temp,y_temp;
	int lados;	
	bool autogenerate = true;

	pair <int,int> carry;
	
	/*
	cout<<"Autogenrar?\n";
	cin>>autogenerate;
	*/

	if(!autogenerate)
	{
		cout<<"#ro de vertices\n";
		cin>>lados;
		
		for(int j = lados; j>0; j --)
		{
			cout<<"Ingrese Cordenadas - [q] salir\n";
			cin>>x_temp; cin>>y_temp;
			carry.first = x_temp;
			carry.second = y_temp;		
			coordinates.push_back(carry);
		}
	}
	else
	{
		cout<<"#ro de vertices \n";
		cin>>lados;

		cout<<"Centro \n";
		cin>>X_c; cin>>Y_c;

		cout<<"Radio \n";
		cin>>Radius;

	    Y_max = Y_c + rounder(Radius * cos(2.0*PI*0/lados) + 0.5);
	    Y_min = Y_c + rounder(Radius * cos(2.0*PI*0/lados) + 0.5);

		X_max = X_c + rounder(Radius * sin(2.0*PI*0/lados) + 0.5);
	    X_min = X_c + rounder(Radius * sin(2.0*PI*0/lados) + 0.5);

	    for (int j = 0; j < lados; j++)
	    {
	    	carry.first = X_c + rounder(Radius * sin(2.0*PI*j/lados) + 0.5);
	    	carry.second = Y_c + rounder(Radius * cos(2.0*PI*j/lados) + 0.5);

			X_max = (carry.first> X_max ? carry.first : X_max);
			X_min = (carry.first< X_min ? carry.first : X_min);

			Y_max = (carry.second> Y_max ? carry.second : Y_max);
			Y_min = (carry.second< Y_min ? carry.second : Y_min);	    	

	    	coordinates.push_back(carry);
	    }

	}

	showVector(coordinates);
				
	glutInit(&argc,argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowPosition(0,0);
  	glutInitWindowSize(640,480);
  	glutCreateWindow("Polygon Fill");

	Init();

	glutDisplayFunc(PolygonFill);
	glutMainLoop();


	return 0;
}
