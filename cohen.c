#include<stdio.h>
#include<GL/glut.h>
#include<stdbool.h>

double xmin = 50,ymin =50,xmax=100,ymax=100;
double xvmin = 200,yvmin = 200,xvmax = 300,yvmax = 300;
const int TOP = 8;
const int BOTTOM = 4;
const int RIGHT = 2;
const int LEFT = 1;

int ComputeOutCode(double x,double y);
void CohenSutherlandLineClipAndDraw(double x0,double y0,double x1,double y01){
	int outcode0,outcode1,outcodeOut;
	bool accept=false,done=false;
	outcode0=ComputeOutCode(x0,y0);
	outcode1=ComputeOutCode(x1,y01);
	do{
		if((outcode0|outcode1)==0)
		{
			accept = true;
			done = true;
		}
		else if(outcode0 & outcode1)
			done=true;
		else
		{
			double x,y;
			outcodeOut = outcode0?outcode0:outcode1;
			float slope = (y01 - y0)/(x1 - x0);
			if(outcodeOut & TOP)
			{
				x = x0+(1/slope)*(ymax-y0);
				y = ymax;
			}
			else if(outcodeOut & BOTTOM)
			{
				x = x0+(1/slope)*(ymin-y0);
				y = ymin;
			}
			else if(outcodeOut & RIGHT)
			{
				y = y0+slope*(xmax-x0);
				x=xmax;
			}
			else
			{
				y = y0+slope*(xmin-x0);
				x=xmin;
			}
			if(outcodeOut == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0,y0);
			}
			else
			{
				x1=x;
				y01=y;
				outcode1=ComputeOutCode(x1,y01);
			}
		}
	}
	while(!done);
	if(accept)
	{
		double sx = (xvmax-xvmin)/(xmax-xmin);
		double sy = (yvmax-yvmin)/(ymax-ymin);
		double vx0 = xvmin+(x0-xmin)*sx;
		double vy0 = yvmin+(y0-ymin)*sy;
		double vx1 = xvmin+(x1-xmin)*sx;
		double vy1 = yvmin+(y01-ymin)*sy;
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin,yvmin);
		glVertex2f(xvmax,yvmin);
		glVertex2f(xvmax,yvmax);
		glVertex2f(xvmin,yvmax);
		glEnd();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex2d(vx0,vy0);
		glVertex2d(vx1,vy1);
		glEnd();
	}
}
int ComputeOutCode(double x,double y)
{
	int code=0;
	if(y>ymax)
		code |= TOP;
	else if(y<ymin)
		code |= BOTTOM;
	if(x>xmax)
		code |= RIGHT;
	else if(x<xmin)
		code |= LEFT;
	return code;
}
void drawText(int x,int y,char *s)
{
	int i=0;
	glColor3f(0.0,0.0,0.0);
	glRasterPos2i(x,y);
	for(i=0;s[i]!='\0';i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
	}
}
void display()
{
	double x0=60,y0=20,x1=80,y01=120;
	double x10=80,y10=60,x11=120,y11=130;
	double x20=40,y20=110,x21=120,y21=110;
	double x30=53,y30=60,x31=90,y31=90;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(x0,y0);
	glVertex2d(x1,y01);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(x10,y10);
	glVertex2d(x11,y11);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(x20,y20);
	glVertex2d(x21,y21);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(x30,y30);
	glVertex2d(x31,y31);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
	drawText(410,450,"Varshith G");
	drawText(410,430,"1BI19CS181");
	CohenSutherlandLineClipAndDraw(x0,y0,x1,y01);
	CohenSutherlandLineClipAndDraw(x10,y10,x11,y11);
	CohenSutherlandLineClipAndDraw(x20,y20,x21,y21);
	CohenSutherlandLineClipAndDraw(x30,y30,x31,y31);
	glFlush();
}
void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cohen Suderland Line Clipping Algorithm");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}

	
	
