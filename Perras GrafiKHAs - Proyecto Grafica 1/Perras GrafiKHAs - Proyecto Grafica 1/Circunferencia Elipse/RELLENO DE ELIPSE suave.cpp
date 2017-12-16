
#include<windows.h>
#include<C:\GLUT\include\GL\glut.h>
#include <bits/stdc++.h>
using namespace std;

map< int, pair<int,int> > arreglo;

pair<int,int> centro;
int radio1,radio2;
bool relleno;

void guardar(int x, int y){
    if(arreglo.count(y)>0){
        arreglo[y].first=min(arreglo[y].first,x);
        arreglo[y].second=max(arreglo[y].second,x);
    }
    else{
        arreglo[y].first=x;
        arreglo[y].second=x;
    }
}

void rellenar(){
    if(relleno==true){
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINES);
        for(map<int, pair<int,int> >::iterator it=arreglo.begin(); it!=arreglo.end(); it++){
            int xi = it->second.first, yi = it->first;
            int xf = it->second.second, yf = it-> first;
            glVertex2f((float)xi, (float)yi);
            glVertex2f((float)xf, (float)yf);

            glVertex2f((float)xi, (float)yi+0.5);
            glVertex2f((float)xf, (float)yf+0.5);
        }
        glEnd();
    }
}

void MidPoint(){
    int X_c = centro.first ,Y_c = centro.second;
    long R_x = radio1, R_y = radio2;
	float p;
	int x,y;
	glClear(GL_COLOR_BUFFER_BIT);
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
        glVertex2d(X_c + x,Y_c + y); guardar(X_c + x, Y_c + y);
        glVertex2d(X_c + x,Y_c - y); guardar(X_c + x, Y_c - y);
        glVertex2d(X_c - x,Y_c + y); guardar(X_c - x, Y_c + y);
        glVertex2d(X_c - x,Y_c - y); guardar(X_c - x, Y_c - y);
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
        glVertex2d(X_c + x,Y_c + y); guardar(X_c + x, Y_c + y);
        glVertex2d(X_c + x,Y_c - y); guardar(X_c + x, Y_c - y);
        glVertex2d(X_c - x,Y_c + y); guardar(X_c - x, Y_c + y);
        glVertex2d(X_c - x,Y_c - y); guardar(X_c - x, Y_c - y);
    }
	glEnd();
	rellenar();
    glFlush();
}

void Init(){
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-200 , 200, -200 , 200);
}

int main(int argc, char **argv){
    cout<<"\n\t\tINGRESE EL CENTRO\n\n";
    cout<<"\t En x: "; cin>>centro.first;
    cout<<"\n\t En y: "; cin>>centro.second;
    cout<<"\n\n\t\tINGRESE EL RADIO\n\n";
    cout<<"\t En X: "; cin>>radio1;
    cout<<"\n\t En Y: "; cin>>radio2;
    cout<<"\n\tDesea rellenarlo? [1 = SI || 0 = NO] \n\t    >>"; cin>>relleno;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("RELLENO DE ELIPSE");

    Init();
    glutDisplayFunc(MidPoint);
    glutMainLoop();

    return 0;
}

