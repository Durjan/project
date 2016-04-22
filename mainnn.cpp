#include <GL/gl.h>
#include <GL/glut.h>

//definicion de variables
double rotate_x=0;
double rotate_y=0;
double rotate_z=0;

GLfloat X=0.0f;
GLfloat Y=0.0f;
GLfloat Z=0.0f;
GLfloat scale=1.0f;


	
GLint ancho=000;
GLint alto=000;

int perspectiva = 0;

void reshape(int w, int h){
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if (perspectiva)
	   gluPerspective(80.0f, (float)w/(float)h, 0.2f, 30.0f);
	   
	else
	
	   glOrtho(-2,2,-2,2,-2,2);
	   
	 glMatrixMode(GL_MODELVIEW);
	 
	 ancho = w;
	 alto = h;
	
	}

void cubo (void){
	//primera cara
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex3f(  0.3, -0.3, -0.3 );      // V1 Blanco
    glVertex3f(  0.3,  0.3, -0.3 );      // V2 Amarillo
    glVertex3f( -0.3,  0.3, -0.3 );      // V3 es azul
    glVertex3f( -0.3, -0.3, -0.3 ); 
	glEnd();
	
	//lado trasero
	glBegin(GL_POLYGON);
	glColor3f(0,1,0);
	glVertex3f( 0.3, -0.3, 0.3 );
    glVertex3f( 0.3,  0.3, 0.3 );
    glVertex3f(-0.3,  0.3, 0.3 );
    glVertex3f(-0.3, -0.3, 0.3 );
	glEnd();
	
	//lado derecho
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
    glVertex3f(0.3, -0.3, -0.3 );
    glVertex3f(0.3,  0.3, -0.3 );
    glVertex3f(0.3,  0.3,  0.3 );
    glVertex3f(0.3, -0.3,  0.3 );
	glEnd();
	
	//lado izquierdo
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	 glVertex3f(-0.3, -0.3,  0.3 );
    glVertex3f(-0.3,  0.3,  0.3 );
    glVertex3f(-0.3,  0.3, -0.3 );
    glVertex3f(-0.3, -0.3, -0.3 );
	glEnd();
	
	//lado superior
	glBegin(GL_POLYGON);
	glColor3f(0,1,1);
	glVertex3f(0.3,  0.3,  0.3 );
    glVertex3f(0.3,  0.3, -0.3 );
    glVertex3f(-0.3,  0.3, -0.3 );
    glVertex3f(-0.3,  0.3,  0.3 );
	glEnd();
	
	//lado inferior
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
    glVertex3f(0.3, -0.3, -0.3 );
    glVertex3f(0.3, -0.3,  0.3 );
    glVertex3f(-0.3, -0.3,  0.3 );
    glVertex3f(-0.3, -0.3, -0.3 );
	glEnd();
	
	glFlush();
	}
	
void display(void){
	//borrar pantalla y z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	//resetear transformaciones
	glLoadIdentity();
	
	//Rotar en el eje x, y, z
	glRotatef( rotate_x, 1.0,0.0,0.0);
	glRotatef( rotate_y, 0.0,1.0,0.0);
	glRotatef( rotate_z, 0.0,0.0,1.0);
	
	glTranslatef(X, Y, Z);//transladar en los 3 ejes
	//otras transformaciones
	glScalef(scale, scale, scale);
        cubo();
	glFlush();
	
	glutSwapBuffers();
	
	}
void init(){
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	ancho = 800;
	alto = 600;
	
	}
	
void specialKeys(int key, int x, int y){
	
	//  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 7;
 
    //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 7;
    //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP)
        rotate_x += 7;
    //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
    //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
    //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;
 
    //  Solicitar actualización de visualización
    glutPostRedisplay();
	
	}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y)
{
    //control de teclas que hacen referencia a Escalar y transladar el cubo en los ejes X,Y,Z.
    switch (key)
    {
    case 's':
        scale=0.5;
        break;
    case 'd':
        scale=1.5;
        break;
    case 'x' :
        X += 0.1f;
        break;
    case 'X' :
        X -= 0.1f;
        break;
    case 'y' :
        Y += 0.1f;
        break;
    case 'Y' :
        Y -= 0.1f;
        break;
    case 'z':
        Z -= 0.1f;
        break;
    case 'Z':
        Z += 0.1f;
        break;
    case 'p':
    case 'P':
       perspectiva=1;
       reshape(ancho,alto);
       break;
       
    case 'o':
    case 'O':
       perspectiva=0;
       reshape(ancho,alto);
       break;
    case 'q':
        exit(0);			// exit
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (650, 550);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Clase 2");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
