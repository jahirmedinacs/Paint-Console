
#include<windows.h>
#include<C:\GLUT\include\GL\glut.h>
#include <bits/stdc++.h>
using namespace std;

map< int, pair<int,int> >arreglo;
int Radius, X_c, Y_c;

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
    int P,x,y;
    P = 1 - Radius;
    x = 0;
    y = Radius;
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2d(X_c + x,Y_c + y); guardar(X_c + x,Y_c + y);
        glVertex2d(X_c + x,Y_c - y); guardar(X_c + x,Y_c - y);
        glVertex2d(X_c - x,Y_c + y); guardar(X_c - x,Y_c + y);
        glVertex2d(X_c - x,Y_c - y); guardar(X_c - x,Y_c - y);
        glVertex2d(X_c + y,Y_c + x); guardar(X_c + y,Y_c + x);
        glVertex2d(X_c - y,Y_c + x); guardar(X_c - y,Y_c + x);
        glVertex2d(X_c + y,Y_c - x); guardar(X_c + y,Y_c - x);
        glVertex2d(X_c - y,Y_c - x); guardar(X_c - y,Y_c - x);

    while(x<=y){
        x++;
        if (P<0){
            P += 2 * x + 1;
        }
        else{
            P += 2 * (x - y) + 1;
            y--;
        }
        glVertex2d(X_c + x,Y_c + y); guardar(X_c + x,Y_c + y);
        glVertex2d(X_c + x,Y_c - y); guardar(X_c + x,Y_c - y);
        glVertex2d(X_c - x,Y_c + y); guardar(X_c - x,Y_c + y);
        glVertex2d(X_c - x,Y_c - y); guardar(X_c - x,Y_c - y);
        glVertex2d(X_c + y,Y_c + x); guardar(X_c + y,Y_c + x);
        glVertex2d(X_c - y,Y_c + x); guardar(X_c - y,Y_c + x);
        glVertex2d(X_c + y,Y_c - x); guardar(X_c + y,Y_c - x);
        glVertex2d(X_c - y,Y_c - x); guardar(X_c - y,Y_c - x);
    }
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINES);
    for(map< int, pair<int,int> >::iterator it=arreglo.begin(); it!=arreglo.end(); it++){
        //cout<<it->first<<" "<<it->second.first<<" "<<it->second.second<<endl;
        glVertex2d(it->second.first,it->first);
        glVertex2d(it->second.second,it->first);
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
    cout<<"\t\tALGORITMO DE CIRCUNFERENCIA\n";
    cout<<"\n\tEn X:  "; cin>>X_c;
    cout<<"\n\tEn Y:  "; cin>>Y_c;
    cout<<"\n\tRadio: "; cin>>Radius;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("RELLENO DE CIRCUNFERENCIA");
    Init();
    glutDisplayFunc(MidPoint);
    glutMainLoop();
    return 0;
}


