// TP 3 - MO2D
// 

#include <iostream> // cout
#include <cstdlib> // exit
#include <cmath> // fabs
#include <fstream> // file io
#include <GL/glut.h>
#include "teclado.h"
#include "uglyfont.h"

using namespace std;

//------------------------------------------------------------
// variables globales
int
  w=800,h=600; // tamanio inicial de la ventana

double 
  AvionX=400, 
  AvionY=300, 
  AvionAng=0, 
  ArmaAng=0,
  ArmaTamanio=0;

const double PI=4*atan(1.0);
bool cl_info=true; // informa por la linea de comandos

// Inicio la clase Teclado con las teclas que se usaran
Teclado teclado (' ','w','s','a','d',' ',' ');

// Defino los valores de z usados para dibujar cada parte
const double
  zArmas = 0.1,
  zAla = 0.2,
  zCuerpo = 0.3,
  zCabina = 0.4,
  zFaro = 0.1,
  zPunto = 0.5,
  zPiso = 0.0,
  zTexto = 0.95,
  zSueloHangar = 0.05,
  zParedHangar = 0.06;

//============================================================
// Variables y funciones para texturas
GLuint texid[5];

//Textura 1D
const int stripeImageWidth = 32;
GLubyte stripeImage[stripeImageWidth][4];
void makeStripeImage(void){
  int j, rojo,verde,azul,alpha;
  for (j = 0; j < stripeImageWidth; j++){
    alpha=255;
    if(j<16) {rojo=16;verde=64;azul=8;}else{rojo=16;verde=4;azul=64;}
    stripeImage[j][0] = (GLubyte) rojo;
    stripeImage[j][1] = (GLubyte) verde;
    stripeImage[j][2] = (GLubyte) azul;
    stripeImage[j][3] = (GLubyte) alpha;
  }
}

//Textura Check
const int checkImageWidth = 32;
const int checkImageHeight = 32;
//static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLubyte otherImage[checkImageHeight][checkImageWidth][4];

void makeCheckImage(void){
  int i, j, c;
  for (i = 0; i < checkImageHeight; i++) {
    for (j = 0; j < checkImageWidth; j++) {
      /*c = (((i&0x8)==0)^((j&0x8)==0))*255;
      checkImage[i][j][0] = (GLubyte) c;
      checkImage[i][j][1] = (GLubyte) c;
      checkImage[i][j][2] = (GLubyte) c;
      checkImage[i][j][3] = (GLubyte) 255;*/
      
      c = (((i&0x10)==0)^((j&0x10)==0))*255;
      otherImage[i][j][0] = (GLubyte) c;
      otherImage[i][j][1] = (GLubyte) 0;
      otherImage[i][j][2] = (GLubyte) 0;
      otherImage[i][j][3] = (GLubyte) 255;
    }
  }
}

bool mipmap_ppm(const char *ifile){
  char dummy; int maxc,wt,ht;
  ifstream fileinput(ifile, ios::binary);
  if (!fileinput.is_open()) {cerr<<"Not found"<<endl; return false;}
  fileinput.get(dummy);
  if (dummy!='P') {cerr<<"Not P6 PPM file"<<endl; return false;}
  fileinput.get(dummy);
  if (dummy!='6') {cerr<<"Not P6 PPM file"<<endl; return false;}
  fileinput.get(dummy);
  dummy=fileinput.peek();
  if (dummy=='#') do {
    fileinput.get(dummy);
  } while (dummy!=10);
  fileinput >> wt >> ht;
  fileinput >> maxc;
  fileinput.get(dummy);
  
  unsigned char *img=new unsigned char[3*wt*ht];
  fileinput.read((char *)img, 3*wt*ht);
  fileinput.close();
  //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, wt, ht,  GL_RGB, GL_UNSIGNED_BYTE, img);
  // conversion a rgba alpha=255-(r+g+b)/3 (blanco=transparente, negro=opaco)
  unsigned char *imga=new unsigned char[4*wt*ht];
  unsigned char r,g,b;
  for (int i=0;i<wt*ht;i++){
    r=imga[4*i+0]=img[3*i+0];
    g=imga[4*i+1]=img[3*i+1];
    b=imga[4*i+2]=img[3*i+2];
    imga[4*i+3]=((r+g+b==765)? 0: 255);
  }
  delete[] img;
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, wt, ht,  GL_RGBA, GL_UNSIGNED_BYTE, imga);
  delete[] imga;
  return true;
}

//============================================================

void DibujarCabina() {
  glColor3d(0.6,0.7,0.9);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2d(0,	0);
  for(double r=0; r<PI*2; r+=0.1)
    glVertex2d(cos(r), sin(r));
  glVertex2d(1.0,0.0);
  glEnd();
}

void DibujarCuerpo() {
  glColor3d(0.4,0.4,0.4);
  glBegin( GL_TRIANGLE_FAN );
  glVertex2d(0.0,	0.0);
  glVertex2d(0.0,	70.0);
  glVertex2d(-8, 35.0);
  glVertex2d(-10,	-30.0);
  glVertex2d(0.0,	-15.0);
  glVertex2d(10, -30.0);
  glVertex2d(8,	35.0);
  glVertex2d(0.0,	70.0);
  glEnd();
}

void DibujarAla() {
  //glColor3d(0.7,0.7,0.7);
  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,texid[4]);
  glBegin( GL_TRIANGLE_FAN );
  glTexCoord2f(0.0,0.0); glVertex2d(35,10);
  glTexCoord2f(0.0,1.0); glVertex2d(0.0,20.0); 
  glTexCoord2f(1.0,0.0); glVertex2d(0.0,0.0); 
  glTexCoord2f(0.0,1.0); glVertex2d(35,4);
  glTexCoord2f(1.0,0.0); glVertex2d(50.0,0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void DibujarFaro() {
  //glColor3d(0.75,0.75,0); // Color amarillo
  glBegin( GL_TRIANGLES);
  glColor3f(1,0,0); glVertex2d(0,65);
  glColor3f(0,1,0); glVertex2d(-20,100);
  glColor3f(0,0,1); glVertex2d(20,100);
  glEnd();
}

void DibujarArmas() {
  //glColor3d(1,0,0); // Color rojo
  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,texid[1]);
  glBegin(GL_QUADS); // Arma derecha
  glTexCoord2f(0.0,0.0); glVertex2d(12,1);
  glTexCoord2f(0.0,1.0); glVertex2d(12,38);
  glTexCoord2f(1.0,0.0); glVertex2d(15,1);
  glTexCoord2f(1.0,1.0); glVertex2d(15,38);
  glEnd();
  glBegin(GL_QUADS); // Arma izquierda
  glTexCoord2f(0.0,0.0); glVertex2d(-12,1);
  glTexCoord2f(0.0,1.0); glVertex2d(-12,38);
  glTexCoord2f(1.0,0.0); glVertex2d(-15,1);
  glTexCoord2f(1.0,1.0); glVertex2d(-15,38);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void DibujarAvion() {
  glPushMatrix();// inicio push1

  // Posiciona y rota el Avion en el modelo
  glTranslated(AvionX,AvionY,0);
  glRotated(AvionAng,0,0,1);  
  
  //Dibujo armas en matriz hija del Avion
  glPushMatrix();
  glTranslated(0,0,zArmas);
  DibujarArmas();
  glPopMatrix();
  
  //Dibujamos las distintas partes de la nave, aplicando las transformaciones necesarias
  //Ala derecha
  glPushMatrix();
  glTranslated(0,0,zAla);
  DibujarAla();
  glPopMatrix();

  //Ala izquierda
  glPushMatrix();
  glTranslated(0,0,zAla);
  glScaled(-1,1,1); //Con este escalamiento logramos reflejar (x = -AnchoAla * x)  
  DibujarAla();
  glPopMatrix();
  
  //Cuerpo
  glTranslated(0,0,zCuerpo);
  DibujarCuerpo();
  
  //Cabina
  glPushMatrix();
  glTranslated(0,0,zCabina);
  glScaled(6,12,1);
  DibujarCabina();
  glPopMatrix();
  
  // Faro
  glPushMatrix();
  glTranslated(0,0,zFaro);
  DibujarFaro();
  glPopMatrix();
    
  // Luego de aplicar la traslacion (AvionX,AvionY) y la rotacion (AvionAng) inicial 
  // dibuja un punto en la posición 0,0 (es solo para ayuda)
  glTranslated(0,0,zPunto);
  glColor3f(0.0f,0.0f,0.0f);
  glPointSize(5.0);
  glBegin(GL_POINTS);
  glVertex2d(0.0,0.0);
  glEnd();
    
  glPopMatrix();// fin push1
}

void DibujarParedHangar() {
  //glColor3f(1.f,0.f,0.f);
  glLineWidth(5.0);
  glEnable(GL_TEXTURE_1D); glBindTexture(GL_TEXTURE_1D,texid[0]);
  glBegin(GL_LINES);
  glTexCoord1f(0); glVertex2i(300,400); glTexCoord1f(20); glVertex2i(300,200);
  glTexCoord1f(0); glVertex2i(300,200); glTexCoord1f(20); glVertex2i(500,200);
  glTexCoord1f(0); glVertex2i(500,200); glTexCoord1f(20); glVertex2i(500,400);
  glEnd();
  glDisable(GL_TEXTURE_1D);
}

void DibujarTexto() {
  static int posTexto_x=10, posTexto_y=580;
  glColor3f(1,1,1); // Color blanco
  glLineWidth(1.0); // Tamaño de la linea
  string cadena = "Trabajo Practico N° 3 - Nahuel Lattessi";  
  
  glPushMatrix();
  glTranslatef(posTexto_x,posTexto_y,zTexto);
  glScalef(12.0,12.0,1.0);//fuente de 10 pixel
  YsDrawUglyFont(cadena.c_str(),0);//Descentrado
  glPopMatrix();
  
  if(posTexto_x >= w){ 
    posTexto_x=10;
  } else 
    posTexto_x += 1;
}

void DibujarPiso(){
  glTranslated(0,0,zPiso);
  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,texid[2]);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0); glVertex2i(0,0); 
  glTexCoord2f(3, 0); glVertex2i(w,0);
  glTexCoord2f(3, 3); glVertex2i(w,h);
  glTexCoord2f(0, 3); glVertex2i(0,h);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void DibujarSueloHangar(){
  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,texid[3]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.00,0.37333); glColor3f(0,1,0); glVertex3f(300,400,0);
  glTexCoord2f(0.00,0.65666); glColor3f(0,1,1); glVertex3f(300,200,0);
  glTexCoord2f(0.25,0.65666); glColor3f(1,1,1); glVertex3f(500,200,0);
  glTexCoord2f(0.25,0.37333); glColor3f(1,1,0); glVertex3f(500,400,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
};

void DibujarHangar(){
  //Suelo
  glPushMatrix();
  glTranslated(0,0,zSueloHangar);
  DibujarSueloHangar();
  glPopMatrix();
  
  //Pared
  glPushMatrix();
  glTranslated(0,0,zParedHangar);
  DibujarParedHangar();
  glPopMatrix();
}

//============================================================
// callbacks

//------------------------------------------------------------

// arma un un nuevo buffer (back) y reemplaza el framebuffer
void Display_cb() {
  // arma el back-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// rellena con color de fondo
  
  /*
  // dibuja un punto en la posición x,y que querramos visualizar (es solo para probar)
  glColor3f(1.0f,0.0f,0.0f);
  glPointSize(5.0);
  glBegin(GL_POINTS);
  glVertex2d(50,50);
  glEnd();
  */
  
  DibujarPiso();
  
  DibujarHangar();
  
  DibujarAvion();
  
  DibujarTexto();
  
  glutSwapBuffers(); // lo manda al monitor
  
  // chequea errores
  int errornum=glGetError();
  while(errornum!=GL_NO_ERROR){
    if (cl_info){
      if(errornum==GL_INVALID_ENUM)
        cout << "GL_INVALID_ENUM" << endl;
      else if(errornum==GL_INVALID_VALUE)
        cout << "GL_INVALID_VALUE" << endl;
      else if (errornum==GL_INVALID_OPERATION)
        cout << "GL_INVALID_OPERATION" << endl;
      else if (errornum==GL_STACK_OVERFLOW)
        cout << "GL_STACK_OVERFLOW" << endl;
      else if (errornum==GL_STACK_UNDERFLOW)
        cout << "GL_STACK_UNDERFLOW" << endl;
      else if (errornum==GL_OUT_OF_MEMORY)
        cout << "GL_OUT_OF_MEMORY" << endl;
    }
    errornum=glGetError();
  }
}

//------------------------------------------------------------
// Maneja cambios de ancho y alto de la ventana
void Reshape_cb(int width, int height){
  // cout << "reshape " << width << "x" << height << endl;
  if (!width||!height) return; // minimizado ==> nada
  w=width; h=height;
  glViewport(0,0,w,h); // región donde se dibuja (toda la ventana)
  // rehace la matriz de proyección (la porcion de espacio visible)
  glMatrixMode(GL_PROJECTION);  glLoadIdentity();
  glOrtho(0,w,0,h,-1,1); // unidades = pixeles
  // las operaciones subsiguientes se aplican a la matriz de modelado GL_MODELVIEW
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay(); // avisa que se debe redibujar
}

//------------------------------------------------------------
// Teclado

// Maneja pulsaciones del teclado (ASCII keys)
// x,y posicion del mouse cuando se teclea (aqui no importan)
void Keyboard_cb(unsigned char key,int x,int y) {
  // Convierte AvionAng de grados a radianes
  double ang=AvionAng*PI/180.0;
  switch(key){
  case 'w':
  case 'W':
    // double sin(double ang); // Calcula el seno de ang medido en radianes
    AvionX-=5*sin(ang);
    AvionY+=5*cos(ang);
    glutPostRedisplay();
    break;
  case 's':
  case 'S':
    AvionX+=5*sin(ang);
    AvionY-=5*cos(ang);
    glutPostRedisplay();
    break;
  case 'a':
  case 'A':
    AvionAng+=2;
    glutPostRedisplay();
    break;
  case 'd':
  case 'D':
    AvionAng-=2;
    glutPostRedisplay();
    break;
  case 27:
    exit(EXIT_SUCCESS);
    break;
  }
}

// Special keys (non-ASCII)
// teclas de funcion, flechas, page up/dn, home/end, insert
void Special_cb(int key,int xm=0,int ym=0) {
  if (key==GLUT_KEY_F4 && glutGetModifiers()==GLUT_ACTIVE_ALT) // alt+f4 => exit
    exit(EXIT_SUCCESS);
}

// Idle callback
// Para controlar el tiempo
void Idle_cb() {
  static unsigned int lt=0;
  int dt = glutGet(GLUT_ELAPSED_TIME) - lt;
  if(dt > 60) {
    
    // Convierte AvionAng de grados a radianes
    double ang=AvionAng*PI/180.0;
    
    if ( teclado.Salir() ) {
      exit( EXIT_SUCCESS );
    }
    if ( teclado.Adelante() ) {
      AvionX-=5*sin(ang);
      AvionY+=5*cos(ang);
    }
    if ( teclado.Atras() ) {
      AvionX+=5*sin(ang);
      AvionY-=5*cos(ang);
    }
    if ( teclado.Izquierda() ) {
      AvionAng+=2;
    }
    if ( teclado.Derecha() ) {
      AvionAng-=2;
    }
    
    lt = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
  }
}

//------------------------------------------------------------
void inicializa() {
  // GLUT
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);// pide color RGB y double buffering
  glutInitWindowSize(w,h); glutInitWindowPosition(10,10);
  glutCreateWindow("TP N°3 - Nahuel Lattessi"); // crea el main window

  // declara los callbacks, los que (aun) no se usan (aun) no se declaran
  glutDisplayFunc(Display_cb);
  glutReshapeFunc(Reshape_cb);
  //glutKeyboardFunc(Keyboard_cb);
  //glutSpecialFunc(Special_cb);
  teclado.Iniciar();
  glutIdleFunc(Idle_cb);

  // OpenGL
  //glClearColor(0.01f,0.01f,0.01f,1.f); // color de fondo
  // Activo el zbuffer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0, 1.0);
  glClearDepth(1.0);
  
  // Inicializo texturas
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(5,texid);
  
  // Textura1 = 1D // Stripe
  makeStripeImage();
  glBindTexture(GL_TEXTURE_1D, texid[0]);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_DECAL);
  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
  
  // Textura2 = 2D // Check
  makeCheckImage();
  glBindTexture(GL_TEXTURE_2D, texid[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, otherImage);
    
  // Textura3 = 2D // Pasto
  glBindTexture(GL_TEXTURE_2D, texid[2]);
  mipmap_ppm("Assets/grass.ppm");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  
  // Textura4 = 2D // Cubo
  glBindTexture(GL_TEXTURE_2D, texid[3]);
  mipmap_ppm("Assets/cubo.ppm");
  
  // Textura5 // Spry para el ala
  glBindTexture(GL_TEXTURE_2D, texid[4]);
  mipmap_ppm("Assets/Spry.ppm");

  // las operaciones subsiguientes se aplican a la matriz de modelado GL_MODELVIEW
  glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

//------------------------------------------------------------
// main
int main(int argc,char** argv) {
  // teclas a utilizar
  cout << "Teclas a utilizar:" << endl;
  cout << "w: avanza" << endl;
  cout << "s: retrocede" << endl;
  cout << "d: gira en sentido horario" << endl;
  cout << "a: gira en sentido antihorario" << endl;
  
  glutInit(&argc,argv); // inicialización interna de GLUT
  inicializa(); // define el estado inicial de GLUT y OpenGL
  glutMainLoop(); // entra en loop de reconocimiento de eventos
  return 0; // nunca se llega acá, es sólo para evitar un warning
}
