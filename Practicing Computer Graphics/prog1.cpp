#include <iostream>
#include <string>
#include<stdio.h>
#include<math.h>
#include<gl/glut.h>

GLint X1,Y1,X2,Y2;
void LineBres(void)
{
glClear(GL_COLOR_BUFFER_BIT);
int dx=abs(X2-X1),dy=abs(Y2-Y1);
int p=2*dy-dx;
int twoDy=2*dy, twoDyDx=2*(dy-dx);
int p1, p2;

if(X1>X2)
{
p1=X2;
p2=Y2;
X2=X1;}
else
{
p1=X1; p2=Y1; X2=X2;
}
glBegin(GL_POINTS);
glVertex2i(p1,p2);
while(p1<X2)
{
p1++;
if(p<0)
p+=twoDy;
else
{
p2++;
p+=twoDyDx;
}
glVertex2i(p1,p2);
}
glEnd();
glFlush();
}
void Init()
{
glClearColor(1.0,1.0,1.0,0);
glColor3f(0.0,0.0,0.0);
glPointSize(4.0);
glViewport(0,0,50,50);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,50,0,50);
}
int main(int argc,char **argv)
{
printf("enter two points for draw lineBresenham:\n");
printf("\n enter point1(X1,Y1):");
scanf("%d%d",&X1,&Y1);
printf("\n enter point2(X2,Y2):");
scanf("%d%d",&X2,&Y2);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(300,400);
glutInitWindowPosition(0,0);
glutCreateWindow("LineBresenham");
Init();
glutDisplayFunc(LineBres);
glutMainLoop();
return 0;
}
