#define GLUT_DISABLE_ATEXIT_HACK
#define _USE_MATH_DEFINES
#define v(x) x/255.0
#include <iostream>
#include <cmath>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan(fovy * 3.14159265 / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void display();
void reshape(int,int);
void timer(int);
void move(int,int);
void init();

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1536,864);
	glutCreateWindow("title");
	glutFullScreen(); 
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutPassiveMotionFunc(move);
	init();
	
	glutMainLoop();//in loop
	return 0;
}

float mx,my;
float dis=-8.0;

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear
	glLoadIdentity();
	
	glTranslatef(0.0,-1.0,dis);
	glRotatef(mx,0.0,1.0,0.0);
	
	glutSolidTeapot(1.0);
	
	glutSwapBuffers();
}

void reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80,16.0/9.0,2.0,50.0);
	//gluPerspective(80,16.0/9.0,2.0,50.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int){
	glutPostRedisplay();
	glutTimerFunc(1000.0/60.0,timer,0);
	if (GetKeyState(0x57)&0x8000){
		if (dis<-5.0) dis+=0.1;
	}else if (GetKeyState(0x53)&0x8000){
		if (dis>-20.0) dis-=0.1;
	}
	if (GetKeyState(0x1B)&0x8000){//按ESC退出 
		exit(0);
	}
}

void move(int x,int y){
	mx+=(x-glutGet(GLUT_SCREEN_WIDTH)/2)*0.1;
	my+=(y-glutGet(GLUT_SCREEN_HEIGHT)/2)*0.1;
	glutWarpPointer(glutGet(GLUT_SCREEN_WIDTH)/2,glutGet(GLUT_SCREEN_HEIGHT)/2);
}

void init(){
    glClearColor(v(135),v(206),v(250),1.0);  //背景色
    //材质反光性设置
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glShadeModel(GL_SMOOTH);           //多变性填充模式

    //材质属性
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //灯光设置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

    glEnable(GL_LIGHTING);   //开关:使用光
    glEnable(GL_LIGHT0);     //打开0#灯
    glEnable(GL_DEPTH_TEST); //打开深度测试
}
