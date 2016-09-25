#include<iostream>	
#include <GL/glut.h>
typedef unsigned short int usi;
using namespace std;
#define xl2 -0.9
#define xl -0.3
#define x 0
#define xr 0.2
#define xr2 0.4
#define xr3 0.7
#define xr4 0.95
#define yd3 -0.8
#define yd2 -0.6
#define yd -0.2
#define y 0
#define yu 0.3
#define yu2 0.6

inline void trl(float x1,float y1,float x2,float y2,float x3,float y3){
	glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}

inline void qd(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4){
	glBegin(GL_QUADS);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glEnd();
}

void disp(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0.8,0.2,1);//green background;
	glColor3f(0.5, 0.7, 0.2);//brown triangles;
	trl(xl2,yd, xl,yd, xl,yu2);
	trl(xl,yd2, xl,yd, x,yd);
	trl(xl,yd, xr,yd, xl,yu);
	trl(xr,yd, xl,yu, xr3,yu);
	trl(xr,yd, xr3,yd, xr2,y);
	qd(xr2,y, xr3,yd,  xr4,y, xr3,yu);
	qd(xr3,yd, xr3,yd3,  xr4,yd2+0.1, xr4,y);
    glutSwapBuffers();
}

void mv(unsigned char key, int nx, int ny){
	switch(key){
		case 27: exit(0);//esc;
		case 43://+
			glTranslated(0.1,0.1,0);
		break;
		case 45://-
			glTranslated(-0.1,-0.1,0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(500,500);
	glutCreateWindow("lab1");
	glutDisplayFunc(disp);
	glutKeyboardFunc(mv);
	
	glutMainLoop();
	return 0;
}
