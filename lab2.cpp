#include<iostream>
#include<math.h>
#include<GL/glut.h>
#include <chrono>
#include <ctime>

#define wsz 500
#define cx 100
#define cy 5
#define cz 10
#define slt 10
#define ndts 3
#define brdr -5
#define dltbo 1
typedef unsigned short int usi;
using namespace std;
GLuint lst;
float alpha=0.0, na=0.0;
double lgth=2, nl=1.5;
double cfx=lgth*cos(alpha),cfy=lgth,cfz=lgth*sin(alpha),lfx=nl*cos(na),lfy=nl,lfz=lgth*sin(na);
chrono::time_point<chrono::system_clock> strt, nd;

static void init(){
	lst=glGenLists(3);
	glNewList(lst,GL_COMPILE );//WireSphere;
	glColor3f (1.0, 1.0, 1.0);//white;
	glPushMatrix();
	glTranslated(dltbo,0,0);
	glutWireSphere(1,slt,slt);
	glPopMatrix();
	glEndList();
	glNewList(lst+1,GL_COMPILE );//SolidCone;
	glColor3f (0, 1.0, 0);//green;
	glPushMatrix();
	glTranslated(0,dltbo,0);
	glutSolidCone(0.5,0.5,slt,slt);
	glPopMatrix();
	glEndList();
	glNewList(lst+2,GL_COMPILE );//glVertexPointer;
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f (0, 0, 1.0);//blue;
	GLfloat marr[ndts][3]; GLfloat dlt=-brdr;
	for(usi i=0;i<ndts;i++){
		marr[i][0]=(GLfloat)dlt;
		marr[i][1]=(GLfloat)dlt;
		marr[i][2]=(GLfloat)sin(dlt);
		dlt+=brdr/50.0;
	}
	glVertexPointer(3, GL_FLOAT, 0, marr);
	glPushMatrix();
	glTranslated(0,0,dltbo);
	glDrawArrays(GL_POLYGON,0,(3*ndts));
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glEndList();
	//glShadeModel(GL_FLAT);
	glClearColor(0.,0.,0.,1.0);//black background;
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);//double sided lighting calculations;
	glEnable(GL_NORMALIZE);//automatically rendering the normals to unit length;
	strt = chrono::system_clock::now();
}

void disp(){
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	GLfloat light0_diffuse[] = {0.5,0.5,0.5};
    GLfloat light0_direction[] = {lfx,lfy,lfz, 0.0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    GLfloat material_diffuse[]={11./sqrt(22),11./sqrt(22),0.,0.};
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,material_diffuse);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslated(dltbo,0.,0.);
	glCallList(lst);
	//glTranslated(0.,dltbo,0.0);
	glCallList(lst+1);
	//glTranslated(0.,0.,dltbo);
	//glCallList(lst+2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glViewport(0, 0, wsz, wsz);
	gluPerspective(130.0, 1.0, 0.1, 100.0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	gluLookAt(cfx,cfy,cfz, 0, 0, 0,0,1,0);
	//cout<<"cfx="<<cfx<<" cfy="<<cfy<<" cfz="<<cfz<<'\n';
	//glTranslated(-cx/wsz+0.0,-cy/wsz+0.0,-cz/wsz+0.0);
	glutSwapBuffers();
	glFlush ();
	glDisable(GL_LIGHT0);
}

void normkeys(unsigned char key,int x,int y){
	switch(key){
		case 'w':
			glTranslated(0.1,0.,0.);
			glutPostRedisplay();
		break;
		case 's':
			glTranslated(-0.1,0.,0.);
			glutPostRedisplay();
		break;
		case 'd':
			glTranslated(0.,0.,-0.1);
			glutPostRedisplay();
		break;
		case 'a':
			glTranslated(0.,0.,0.1);
			glutPostRedisplay();
		break;
	}
}

void speckeys(int key,int x,int y){
	switch(key){
		case GLUT_KEY_F1:
			glRotatef(10.,1.,0.,0.);
			glutPostRedisplay();
		break;
		case GLUT_KEY_F2:
			glRotatef(10.,0.,1.,0.);
			glutPostRedisplay();
		break;
		case GLUT_KEY_F3:
			glRotatef(10.,0.,0.,1.);
			glutPostRedisplay();
		break;
		/*case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;*/
	}
}

void reshape(int w,int h){
   glViewport( 0, 0, ( GLsizei ) w, ( GLsizei ) h );
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective( 30, ( GLfloat ) w / ( GLfloat ) h, 1.0, 100.0 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
   //gluLookAt(0,0,10,0,0,0,0,1,0);
}

void tf1(int value){
	if(alpha>=360) alpha=0;
	else alpha+=1;
	cfx=lgth*cos(alpha);cfz=lgth*sin(alpha);
	//cout<<"alpha="<<alpha<<'\n';
	glutPostRedisplay();
	glutTimerFunc(500,tf1,1);
}

void idlf(){
	nd=chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = nd-strt;
	if(elapsed_seconds.count()<0.002) return;
	else{
		if(na>=360) na=0;
		else na+=1;
		lfx=nl*cos(na);lfz=nl*sin(na);
		strt = chrono::system_clock::now();
		glutPostRedisplay();
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(wsz,wsz);
	glutCreateWindow("lab2");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(disp);
	glutKeyboardFunc(normkeys);
	glutSpecialFunc(speckeys);
	glutTimerFunc(500,tf1,1);
	glutIdleFunc(idlf);
	glutMainLoop();
	return 0;
}
