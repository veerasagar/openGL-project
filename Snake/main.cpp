#include <GL/glut.h>                            // Include the GLUT library and all its library components
#include <iostream>
#include <fstream>                              //required for the project
#include "game.h"

#define ROWS 40.0                        //defining the rows and columns
#define COLUMNS 40.0

std::ofstream ofile;
std::ifstream ifile;
bool game_over=false;
extern int sDirection;
int score=0;                            //initializing the score of the game to 0 

void init();
void display_callback();
void input_callback(int,int,int);
void reshape_callback(int,int);
void timer_callback(int);

int main(int argc,char**argv)
{
    glutInit(&argc,argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(10,10);                    //describing a window position
    glutInitWindowSize(600,600);                    //creaing a window
    glutCreateWindow("SNAKE GAME");                 //giving a window name
    glutDisplayFunc(display_callback);             // Register the display callback function
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(input_callback);
    glutTimerFunc(100,timer_callback,0);
    init();
    glutMainLoop();                               // Enter the GLUT event processing loop
    return 0;
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);                   // Clear the color buffer
    initGrid(COLUMNS,ROWS);
}

                                                    //Callbacks
void display_callback()
{
    if(game_over)
    {
        ofile.open("score.dat",std::ios::trunc);        //storing the result of the game in a different file  
        ofile<<score<<std::endl;
        ofile.close();
        ifile.open("score.dat",std::ios::in);
        char a[4];
        ifile>>a;
        std::cout<<a;
        char text[50]= "Your score : ";                //getting the score of the game played from the file 
        strcat(text,a);
        MessageBox(NULL,text,"Game Over",0);            //creating a window alert of the score
        exit(0);
    }
    glClear(GL_COLOR_BUFFER_BIT);                        // Clear the color buffer
    glLoadIdentity();
    draw_grid();                                        //drawing a grid of the game
    draw_food();                                        //rendering the food randomly
    draw_snake();                                        //rendering thw snake element
    glutSwapBuffers();
}
void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLfloat)w,GLfloat(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(100,timer_callback,0);
}
void input_callback(int key,int x,int y)
{
    switch(key)                                //givng the control of the snake to the user
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)                    //using the keyboard basic controls that is the 
            sDirection=UP;                      //basic up down left and right keys
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }
}
