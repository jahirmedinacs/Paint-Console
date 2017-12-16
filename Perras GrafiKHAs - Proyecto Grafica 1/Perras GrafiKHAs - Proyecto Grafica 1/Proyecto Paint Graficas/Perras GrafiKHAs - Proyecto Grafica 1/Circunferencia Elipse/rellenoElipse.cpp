
#include<windows.h>
#include<C:\GLUT\include\GL\glut.h>
#include <bits/stdc++.h>
using namespace std;

map< int, pair<int,int> > arreglo;

int X_c,Y_c;
long R_x,R_y;

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

void MidPoint(){
	float p;
	int x,y;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(7.0);
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

    glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
    for(map<int, pair<int,int> >::iterator it=arreglo.begin(); it!=arreglo.end(); it++){
        glVertex2d(it->second.first, it->first);
        glVertex2d(it->second.second, it-> first);
    }
	glEnd();
    glFlush();
}

void Init(){
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-200 , 200, -200 , 200);
}

int main(int argc, char **argv){
    cout<<"\n\t\tINGRESE EL CENTRO\n\n";
    cout<<"\t En x: "; cin>>X_c;
    cout<<"\n\t En y: "; cin>>Y_c;
    cout<<"\n\n\t\tINGRESE EL RADIO\n\n";
    cout<<"\t En X: "; cin>>R_x;
    cout<<"\n\t En Y: "; cin>>R_y;

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

