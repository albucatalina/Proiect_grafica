#include "glos.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glaux.h>
#include <math.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);

static GLfloat x = 0, y = 0, alfa = 0, s = 0;

GLfloat ctrlpoints[4][3] = {
    //puncte de control pt tulpina
    { 10, 40, 0.0}, { 10, 60, 0.0},
    {18, 60, 0.0}, {20.0, 80.0, 0.0}
};

GLfloat ctrlpoints2[4][4][3] = {
    //puncte de control pt frunza
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{-10, 4, 2}, {-5, 4, -3}, {5, 4, -3}, {10, 4, 2}},
    {{-5, 8, 2}, {-3, 8, -3}, {3, 8, -3}, {5, 8, 2}},
    {{0, 15, -10}, {0, 15, -10}, {0, 15, -10}, {0, 15, -10}}
};


void initlights(void)
{
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    //componenta ambientala din sursa 0 este lumina cu intensitate 0
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    //componenta difuza din sursa 0 este lumina cu intensitate 1 
    //pentru fiecare componenta de culoare R, G, B
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //componenta speculara din sursa 0 este lumina cu intensitate 1 
    //pentru fiecare componenta de culoare
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);  //activare iluminare
    glEnable(GL_LIGHT0);    //activare sursa 0

    //ca sa se vada si culorile
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    
}

void myinit (void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); //activare test de adancime
    glDepthFunc(GL_LESS);   //modelul de comparatie in testul de adancime
    glEnable(GL_LINE_SMOOTH);

    //tulpina
    glEnable(GL_MAP1_VERTEX_3);	//se valideaza un anumit tip de evaluare
    glShadeModel(GL_FLAT); 	//umbrire constanta pe poligoane
    glLineStipple(1, 0x0F0F);

    //frunza
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
        0, 1, 12, 4, &ctrlpoints2[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3); 
    glEnable(GL_AUTO_NORMAL); //setari pt
    glEnable(GL_NORMALIZE);   //iluminare
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0); //intervale de esantionare
    initlights();

}


void CALLBACK MutaStanga(void)
{
    x -= 10;
}

void CALLBACK MutaDreapta(void)
{
    x += 10;
}

void CALLBACK MutaSus(void)
{
    y -= 10;
}

void CALLBACK MutaJos(void)
{
    y += 10;
}

void CALLBACK rot_z_up(void)
{
    alfa += 10;
}

void CALLBACK rot_z_down(void)
{
    alfa -= 10;
}

//pt sursa
void CALLBACK RotesteStanga(void)
{
    s -= 10;
}

void CALLBACK RotesteDreapta(void)
{
    s += 10;
}

void tulpina(void)
{
    glLineWidth(3);
    glColor3f(0, 1, 0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glBegin(GL_LINE_STRIP);		//se deseneaza curba prin segmente de dreapta
        for (int i = 0; i <= 30; i++)
            glEvalCoord1f((GLfloat)i / 30.0);
    glEnd();
}

void frunza(void)
{
    glColor3f(0, 1, 0);
    glScalef(1, 2, 2);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
}

void floare(void)
{
    GLUquadricObj* f = gluNewQuadric();
    glRotatef(90, 1, 0, 0);
    for (int i = 0; i < 5; i++)
    {
        glRotatef(70, 0, 0, 1);
        glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    }
    glColor3f(1, 1, 0);
    glTranslatef(0, 0, -3);
    gluSphere(f, 2, 30, 30);
    glTranslatef(0, 0, 3);
}

void CALLBACK display (void)
{
    GLfloat position[] = { 0.0, 120.0, 80.0, 1.0 };  //pozitia sursei de lumina

    GLfloat mat_ambientGhiveci[] = { 0.0, 0.0, 1.0, 1.0 };//coeficient de reflexie ambientala
    GLfloat mat_diffuseGhiveci[] = { 0.0, 0.0, 1.0, 1.0 };//coeficient de reflexie difuza

    GLfloat mat_ambientFrunza[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_diffuseFrunza[] = { 0.0, 1.0, 0.0, 1.0 };

    GLfloat mat_ambientFloareRosie[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuseFloareRosie[] = { 1.0, 0.0, 0.0, 1.0 };

    GLfloat mat_ambientFloareMov[] = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat mat_diffuseFloareMov[] = { 1.0, 0.0, 1.0, 1.0 };

    GLfloat mat_ambientFloareCyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuseFloareCyan[] = { 0.0, 1.0, 1.0, 1.0 };


    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };//coeficient de reflexie speculara
    GLfloat high_shininess[] = { 100.0 };//exponentul de reflexie speculara
    

    GLUquadricObj* ghiveci = gluNewQuadric();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //sterge buffer-ul de culoare
    
    glLoadIdentity ();  //initializeaza matricea curenta de modelare-vizualizare, setata ca fiind matrice identitate

    glPushMatrix();

#pragma region sursa
        glPushMatrix();
            glRotatef(s, 0, 1, 0);
            glLightfv(GL_LIGHT0, GL_POSITION, position);

            glPushMatrix();
                glTranslatef(0.0, 120.0, 80.0);
                glColor3f(1, 1, 0);
                glDisable(GL_LIGHTING);
                auxSolidSphere(15);
                glEnable(GL_LIGHTING);
            glPopMatrix();
        glPopMatrix();
#pragma endregion

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glRotatef(x, 0, 1, 0);  //rotire pe axa y
        glRotatef(y, 1, 0, 0);  //rotire pe axa x
        glRotatef(20, 1, 0, 0);  //sa se vada toate de sus    


#pragma region ghiveci
        glPushMatrix();
            //nisip
            glDisable(GL_LIGHTING);
            glRotatef(-90, 1, 0, 0);
            glTranslatef(0, 0, 40);
            glColor3f(0, 0, 0);
            gluDisk(ghiveci, 0, 25, 100, 100);
            glEnable(GL_LIGHTING);
            
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientGhiveci);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseGhiveci);
            
            glTranslatef(0, 0, -40);
            glColor3f(0, 0, 1);
            gluCylinder(ghiveci, 20, 32, 50, 100, 100);
            gluDisk(ghiveci, 0, 20, 100, 100);

            glColor3f(0, 0, 0.8);
            glTranslatef(0, 0, 35);
            gluCylinder(ghiveci, 35, 35, 15, 100, 100);
            gluDisk(ghiveci, 30, 35, 100, 100);
            glTranslatef(0, 0, 15);
            gluDisk(ghiveci, 30, 35, 100, 100);
        glPopMatrix();
#pragma endregion

#pragma region floare rosie
        glPushMatrix();
            glTranslatef(10, 0, 10);
            glRotatef(alfa, 0, 1, 0);
            glTranslatef(-10, 0, -10);

            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFrunza);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFrunza);
                glTranslatef(0, 0, 10);
                tulpina();
            glPopMatrix();

            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFrunza);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFrunza);
                glTranslatef(10, 40, 10);
                glRotatef(70, 0, 1, 0);
                frunza();
            glPopMatrix();

            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFloareRosie);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFloareRosie);
                glTranslatef(20, 80, 10);
                glRotatef(-30, 0, 0, 1);
                glColor3f(1, 0, 0);
                floare();
            glPopMatrix();
        glPopMatrix();
#pragma endregion

#pragma region floare mov
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFrunza);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFrunza);
            glTranslatef(-15, 0, 0);
            glRotatef(45, 0, 1, 0);
            tulpina();
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFrunza);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFrunza);
            glTranslatef(-8, 40, -10);
            glRotatef(-90, 0, 1, 0);
            frunza();
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFloareMov);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFloareMov);
            glTranslatef(0, 80, -15);
            glRotatef(10, 0, 0, 1);
            glColor3f(1, 0, 1);
            floare();
        glPopMatrix();
#pragma endregion

#pragma region floare albastra
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFrunza);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFrunza);
            glTranslatef(-5, 0, 15);
            glRotatef(150, 0, 1, 0);
            tulpina();
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFrunza);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFrunza);
            glTranslatef(-13, 40, 10);
            glRotatef(90, 0, 1, 0);
            frunza();
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientFloareCyan);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseFloareCyan);
            glTranslatef(-23, 80, 5);
            glRotatef(40, 0, 0, 1);
            glColor3f(0, 1, 1);
            floare();
        glPopMatrix();
#pragma endregion

    glPopMatrix();

    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    //transformare izotropica
    if (!h) return;
    glViewport(0, 0, w, h);	//desemneaza dimensiunea viewportului
    glMatrixMode(GL_PROJECTION); //se comuta pe matricea curenta de proiectie
    glLoadIdentity();
    if (w <= h)		
    glOrtho (-160.0, 160.0,   //xleft, xright
             160.0*(GLfloat)h/(GLfloat)w, -160.0*(GLfloat)h/(GLfloat)w,  //ybottom, ytop
             -500.0, 500.0);   //znear, zfar
    else 
    glOrtho (-160.0*(GLfloat)w/(GLfloat)h, 160.0*(GLfloat)w/(GLfloat)h, 
            -160.0, 160.0,
            -500.0, 500.0);
    glMatrixMode(GL_MODELVIEW);  //indica faptul ca transformarile urmatoare vor afecta matricea curenta de 
                                //modelare-vizualizare si nu matricea de proiectie

}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB | AUX_DEPTH); //creeaza o fereastra cu un singur buffer de culoare
    auxInitPosition (0, 0, 300, 200);  //pozitia ferestrei si dimensiunea acesteia
    auxInitWindow ("Ghiveci cu flori");  //deschide fereastra
    myinit ();

	auxKeyFunc (AUX_LEFT, MutaStanga); //asociaza tastei AUX_LEFT functia de tip callback MutaStanga
	auxKeyFunc (AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);

    //rotire
    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);

    //rotire sursa
    auxKeyFunc(AUX_A, RotesteStanga);
    auxKeyFunc(AUX_S, RotesteDreapta);
    auxKeyFunc(AUX_a, RotesteStanga);
    auxKeyFunc(AUX_s, RotesteDreapta);
	
    auxReshapeFunc (myReshape);  //inregistreaza in sistemul de operare functia de tip callback myReshape
    auxMainLoop(display); //inregistreaza in sistemul de operare functia display
    return(0);
}
