#include<bits/stdc++.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include<windows.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>

#define PI acos(-1.0)
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

using namespace std;

struct node{
    double a,b,c,d;
    node(double a2,double b2,double c2,double d2)
    {
        a=a2;
        b=b2;
        c=c2;
        d=d2;
    }
};
int xCentro,yCentro,radio,lados,p1x,p1y,p2x,p2y,xmin,xmax,ymin,ymax;
vector<node>arr;
vector<int> bin;
void inicializar()
{
     glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10.0,10.0,-10.0,10.0);

}

void graficarpoligono()
{
    glColor3f(0.0,1.0,0.0);
     double x,y,tempx,tempy;
     for (int i = 0; i <=lados; i++)
        {
            tempx=x;
            tempy=y;
            x = xCentro + radio * sin(2.0*PI*i/lados);
            y = yCentro + radio * cos(2.0*PI*i/lados);

            if(i!=0)
            {
                glBegin(GL_LINES);
                    glVertex2f(tempx,tempy);
                    glVertex2f(x,y);
                glEnd();
                arr.PB(node(tempx*1.0,tempy*1.0,x*1.0,y*1.0));
            }

        }
}
void graficarlinea()
{
    glColor3f(0.0,1.0,0.0);
            arr.PB(node(p1x*1.0,p1y*1.0,p2x*1.0,p2y*1.0));
            glBegin(GL_LINES);
                glVertex2f(p1x,p1y);
                glVertex2f(p2x,p2y);
            glEnd();

}
vector< pair< double, double> > recorte()
{
    vector< pair< double, double> > res;
    int t=arr.size();
    bin.assign(t<<1,0);
    for(int i=0;i<(t);i++)
    {
        if(arr[i].a<xmin)//izquierda
            bin[(2*i)]|=(1);
        if(arr[i].a>xmax)//derecha
            bin[(2*i)]|=(1<<1);
        if(arr[i].b<ymin)//abajo
            bin[(2*i)]|=(1<<2);
        if(arr[i].b>ymax)//arriba
            bin[(2*i)]|=(1<<3);
        if(arr[i].c<xmin)//izquierda
            bin[(2*i)+1]|=(1);
        if(arr[i].c>xmax)//derecha
            bin[(2*i)+1]|=(1<<1);
        if(arr[i].d<ymin)//abajo
            bin[(2*i)+1]|=(1<<2);
        if(arr[i].d>ymax)//arriba
            bin[(2*i)+1]|=(1<<3);
    }
    for(int i=0;i<(t<<1);i+=2)
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
                            double m=(arr[j/2].d-arr[j/2].b)/(arr[j/2].c-arr[j/2].a);
                            if(bin[j]&(1))//izquierda
                            {
                                bin[j]-=1;
                                double temp;
                                if(j&1)
                                        arr[j/2].d=arr[j/2].d+(((xmin*1.0)-arr[j/2].c)*m),arr[j/2].c=xmin;
                                else
                                        arr[j/2].b=arr[j/2].b+(((xmin*1.0)-arr[j/2].a)*m),arr[j/2].a=xmin;

                            }
                            if(bin[j]&(1<<1))//derecha
                            {
                                bin[j]-=2;
                                if(j&1)
                                     arr[j/2].d=arr[j/2].d+(((xmax*1.0)-arr[j/2].c)*m), arr[j/2].c=xmax;
                                else
                                        arr[j/2].b=arr[j/2].b+(((xmax*1.0)-arr[j/2].a)*m),arr[j/2].a=xmax;
                            }
                            if(bin[j]&(1<<2))//abajo
                            {
                                bin[j]-=4;
                                if(j&1)
                                        arr[j/2].c=arr[j/2].c+(((ymin*1.0)-arr[j/2].d)/m),arr[j/2].d=ymin;
                                else
                                        arr[j/2].a=arr[j/2].a+(((ymin*1.0)-arr[j/2].b)/m),arr[j/2].b=ymin;
                            }
                            if(bin[j]&(1<<3))//arriba
                            {
                                bin[j]-=8;
                                if(j&1)
                                        arr[j/2].c=arr[j/2].c+(((ymax*1.0)-arr[j/2].d)/m),arr[j/2].d=ymax;
                                else
                                        arr[j/2].a=arr[j/2].a+(((ymax*1.0)-arr[j/2].b)/m),arr[j/2].b=ymax;
                            }
                        }
                        if(j&1)
                            res.PB(pair<double ,double > (arr[j/2].c,arr[j/2].d));
                        else
                            res.PB(pair<double ,double > (arr[j/2].a,arr[j/2].b));
                    }

                }
        }

    }
    return res;
}
void redimensionar(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50,50,-50,50,-1,1);
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(300,500);

    glutInitWindowSize(400,300);

    glutCreateWindow("Poligono");

    inicializar();
    glClear(GL_COLOR_BUFFER_BIT);
    int opcion=0;
    vector< pair< double, double> > recortemain;
    while(opcion!=4)
    {
        printf("[1] .Dibujar Linea\n");
        printf("[2] .Dibujar Poligono\n");
        printf("[3] .Algoritmo recorte\n");
        printf("[4] .Salir\n");
        scanf("%d",&opcion);
        if(opcion==1)
        {
            printf("Ingrese punto A\n");
            scanf("%d %d",&p1x,&p1y);
            printf("Ingrese Punto B\n");
            scanf("%d %d",&p2x,&p2y);
            graficarlinea();
            glutReshapeFunc(redimensionar);
            glFlush();
        }
        else if(opcion==2)
        {
            printf("Ingrese punto centro\n");
            scanf("%d %d",&xCentro,&yCentro);
            printf("Ingrese radio\n");
            scanf("%d",&radio);
            printf("Ingrese numero lados\n");
            scanf("%d",&lados);
            graficarpoligono();
            glutReshapeFunc(redimensionar);
            glFlush();
        }
        else if(opcion==3)
        {
            printf("Ingrese xmin y xmax\n");
            scanf("%d %d",&xmin,&xmax);
            printf("Ingrese ymin y ymax\n");
            scanf("%d %d",&ymin,&ymax);
            recortemain = recorte();
            glutReshapeFunc(redimensionar);
            glFlush();
        }
        int t=recortemain.size();
        REP(i,t)
        {
            printf("%lf %lf\n",recortemain[i].first,recortemain[i].second);

        }
        system("pause");
        system("cls");
    }

    glutMainLoop();

    return EXIT_SUCCESS;
}
