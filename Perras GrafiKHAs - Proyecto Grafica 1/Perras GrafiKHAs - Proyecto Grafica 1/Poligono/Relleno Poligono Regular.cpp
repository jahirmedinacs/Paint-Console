#include<windows.h>
#include<C:\GLUT\include\GL\glut.h>
#include <bits/stdc++.h>
using namespace std;

vector< pair<float,float> > vertices, puntos;

void Iniciar(){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-50,50,-50,50);
}

float redondeo(float valor){
    return floor(valor+0.5);
}

bool cmp(pair<float,float> a, pair<float,float> b){
    return a.second<b.second;
}

void inicializar(){
    for(int i=0; i<100; i++){
        puntos.push_back( pair<float,float> (1000,-1) );
    }
}

void graficar(){
    inicializar();
    glClear(GL_COLOR_BUFFER_BIT);
    int p1=-1, p2=1000;
    for(int i=1; i<vertices.size(); i++){
        pair<float,float> puntoI=vertices[i], puntoF=vertices[i-1];
        if(puntoI.second<=puntoF.second){
            float equis=puntoI.first, pendiente=(float)(puntoF.first-puntoI.first)/(puntoF.second-puntoI.second);
            for(int i=puntoI.second; i<=puntoF.second; i++){
                puntos[i].first=min(puntos[i].first,equis);
                equis+=pendiente;
            }
        }
        else{
            float equis=puntoF.first, pendiente=(float)(puntoI.first-puntoF.first)/(puntoI.second-puntoF.second);
            for(int i=puntoF.second; i<=puntoI.second; i++){
                puntos[i].first=min(puntos[i].first,equis);
                puntos[i].second=max(puntos[i].second,equis);
                equis+=pendiente;
            }
        }
        p1=max(p1,(int)puntoF.second);
        p2=min(p2,(int)puntoF.second);
    }
    glLineWidth(5.0);
    glColor3f(0.0,0.5,0.0);
    for(int i=p2; i<=p1; i++){
        glBegin(GL_LINES);
        glVertex2f(redondeo(puntos[i].first),redondeo((float)i));
        glVertex2f(redondeo(puntos[i].second),redondeo((float)i));
        glEnd();
    }
    glLineWidth(10.0);
    glColor3f(0.0,0.0,1.0);
    for(int i=1; i<vertices.size(); i++){
        glBegin(GL_LINES);
        glVertex2f(redondeo(vertices[i-1].first),redondeo(vertices[i-1].second));
        glVertex2f(redondeo(vertices[i].first),redondeo(vertices[i].second));
        glEnd();
    }
    glFlush();
}

/*
6
12 2
10 10
7 12
4 8
4 5
12 2
*/

int main(int argc, char**argv){
    int tam; float x,y;
    printf("\n\t\tALGORITMO DE RELLENO\n\n");
    printf("\tINGRESE CANTIDAD DE PUNTOS: "); scanf("%d",&tam); printf("\n");
    for(int i=0; i<tam; i++){
        printf("   En X: "); scanf("%f",&x);
        printf("   En Y: "); scanf("%f",&y); printf("\n");
        vertices.push_back(pair<float,float>(x,y));
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(600,500);
    glutCreateWindow("RELLENO");
    Iniciar();
    glutDisplayFunc(graficar);
    glutMainLoop();
    return EXIT_SUCCESS;
}

