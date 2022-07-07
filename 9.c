#include<windows.h>
#include<GL/glut.h>

int le[500], re[500], outline = 0 , edgefill = 0;;
void intersection(int x1, int x2, int y1, int y2){
if(y1 > y2){
    int t = y1;
    y1 = y2;
    y2 = t;

    t = x1;
    x1 = x2;
    x2 = t;
}


int m = x2 - x1;
if(y2!=y1)
m = (x2 - x1) / (y2-y1);

int x = x1;

for(int y = y1;  y <= y2; y++){
        if(x < le[y]) le[y] = x;
        if(x > re[y]) re[y] = x;

        x += m;

}

}
void myDisplay(){
glClear(GL_COLOR_BUFFER_BIT);
GLint p2[2] = {250,125};
GLint p1[2] = {125,250};
GLint p3[2] = {375,250};
GLint p4[2] = {250,375};
//polygon
if(outline == 1){
glBegin(GL_LINE_LOOP);
glVertex2iv(p1);
glVertex2iv(p2);
glVertex2iv(p3);
glVertex2iv(p4);
glEnd();
}


for(int i = 0 ; i < 500; i++){
    le[i] = 500;
    re[i] = 0 ;
}
intersection(p1[0], p1[1], p2[0],p2[1]);
intersection(p2[0], p2[1], p3[0],p3[1]);
intersection(p3[0], p3[1], p4[0],p4[1]);
intersection(p4[0], p4[1], p1[0],p1[1]);


//printing
if(edgefill == 1){
    for(int y  = 0 ;  y  <500 ; y++)
for(int x = le[y] ; x <= re[y] ; x++){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
glFlush();
}
}
void Menu(int id){
    if(id == 1 ){
        outline = 1;
    }
    else if(id == 2)
        edgefill = 1;
    else if( id == 0)
    exit(0);

    edgefill = 1;
    glutPostRedisplay();


}
void Myinit(){
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,500,0,500);
glMatrixMode(GL_MODELVIEW);

glutCreateMenu(Menu);
glutAddMenuEntry("with outline" , 1);
glutAddMenuEntry("without outline", 2);
glutAddMenuEntry("Exit",0);
glutAttachMenu(GLUT_RIGHT_BUTTON);


}
int main(int argc, char **argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
glutInitWindowPosition(0,0);
glutInitWindowSize(500, 500);
glutCreateWindow("ScanFill");
Myinit();
glutDisplayFunc(myDisplay);
glutMainLoop();
}
