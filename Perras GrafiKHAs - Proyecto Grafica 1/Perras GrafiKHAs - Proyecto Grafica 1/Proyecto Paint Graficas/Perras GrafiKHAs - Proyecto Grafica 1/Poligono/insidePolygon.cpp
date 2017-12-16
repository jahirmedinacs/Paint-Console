#include <bits/stdc++.h>
#include <math.h>
#include <GL/glut.h>

#include <stdlib.h>

#define PI acos(-1.0)
#define cua(x) (x)*(x)

double xCentro, yCentro, radio, lados, xi, yi, xj, yj, pi, pj, sum=0.0;
double axisx[1000], axisy[1000];

void inicializar()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}


void graficar()
{
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.0,1.0,0.0);
     double x, y, tempx, tempy;
     for (int i = 0; i <=lados; i++)
        {
            tempx=x;
            tempy=y;
            x = xCentro + radio * sin(2.0*PI*i/lados);
            y = yCentro + radio * cos(2.0*PI*i/lados);
            axisx[i]=x;
            axisy[i]=y;
            glBegin(GL_LINES);
                glVertex2f(tempx,tempy);
                glVertex2f(x,y);
            glEnd();
        }
     sum=0.0;
     for (int i = 0; i <lados; i++)
     {
         xi=axisx[i%(int)lados]-pi;
         xj=axisy[i%(int)lados]-pj ;
         yi=axisx[(i+1)%(int)lados]-pi;
         yj=axisy[(i+1)%(int)lados]-pj;
         sum+=acos(((xi*yi)+(xj*yj))/((sqrt(cua(xi)+cua(xj)))*(sqrt(cua(yi)+cua(yj)))))/ PI;// hallando el angulo entre vectores
     }

    if(sum==2.0)
        printf("El punto esta dentro del poligono\n");
    else
        printf("El punto esta afuera del poligono\n");

    glFlush();
}

void redimensionar(int w, int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-1,1,-1,1,-1,1);
    glOrtho(-640,640,-480,480,-1,1);

    graficar();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

        printf("Ingrese punto centro\n");
        scanf("%lf %lf",&xCentro,&yCentro);
        printf("Ingrese radio\n");
        scanf("%lf",&radio);
        printf("Ingrese numero lados\n");
        scanf("%lf",&lados);
        printf("Saber si un punto esta dentro del poligono\n");
        scanf("%lf %lf",&pi,&pj);

    glutInitWindowPosition(300,500);
    glutInitWindowSize(640,480);
    glutCreateWindow("Poligono");   

    inicializar();
    glutDisplayFunc(graficar);
    glutReshapeFunc(redimensionar);
    glutMainLoop();

    return EXIT_SUCCESS;
}
