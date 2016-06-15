//
//  main.cpp
//  project1
//
//  Created by Ashley Vo on 4/26/16.
//  CIN:303479558
//  Copyright © 2016 Ashley Vo. All rights reserved.
//

#ifdef _WIN32
#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#import <unistd.h>
#include <math.h>
#endif
#define PI 3.14159265

using namespace std;

const int screenWidth = 800;
const int screenHeight = 500;

//beginning point of floor
int floor_x=0;
int floor_y=50;

//beginning point of tank
int tank_x=10;
int tank_y=floor_y+.1;

//tank dimensions
int tank_width=125;
int tank_height=50;

//nozzle start
double nozz_x=(tank_x+tank_width)/2;
double nozz_y=(tank_y+tank_height);
double angle=45.0;




//arc T
double T=80 * 2 * sin((PI/180)*angle)/9.8;

//bullet
double t_pos=T/15;
double bullet_s_x= nozz_x+80*cos((PI/180) *angle)*t_pos;
double bullet_s_y= nozz_y+80*sin((PI/180) *angle)*t_pos - (.5*(9.8) * (t_pos*t_pos));
double bullet_c_x = bullet_s_x;
double bullet_c_y= bullet_s_y;
bool isShot = false;
bool currentlyShot=false;
double current_angle;
double current_nozz_x;
double current_nozz_y;
double bull_vel=.1;


//Target information
bool move_tar=false;
double tar_x;
double tar_y;
int move_angle;
double tar_center_x=tar_x;
double tar_center_y=tar_y;
int radius = 50;
int x_velocity=5;
int y_velocity=5;



//Hit flag
bool isHit=false;
int isHitTimer=0;

//Miss
bool isMiss=false;
int isMissTimer=0;


//Window INIT
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);		// background color is white
    glColor3f(0.0f, 0.0f, 0.0f);			// drawing color is black
    glMatrixMode(GL_PROJECTION);			// set "camera shape"
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}


//move target
void ToggleTarget(){
    if(!move_tar){
        move_tar=true;
        move_angle=rand()%360;
        cout<<"move at a "<<move_angle<<" degrees"<<endl;
    }
    else{
        move_tar=false;
    }
}

//HIT
void Hit(){
    currentlyShot=false;
    isShot=false;
    t_pos=T/15;
    move_tar=false;
    //cout<<"HIT"<<endl;
    
}


//Moving everything
void myIdle()
{
    sleep(.01);
    if(isHit){
        isHitTimer++;
        if(isHitTimer>18)
        {
            isHitTimer=0;
            isHit=false;
        }
    }
    if(isMiss){
        isMissTimer++;
        if(isMissTimer>18)
        {
            isMissTimer=0;
            isMiss=false;
        }
    }
    if(move_tar) //move target
    {


        if(tar_x+ x_velocity*cos(PI/180 * move_angle) + radius>screenWidth )
        {
            
            x_velocity=-1*x_velocity;
            cout<<"HIT SIDE"<<endl;
        }
        if(tar_x+ x_velocity*cos(PI/180 * move_angle) - radius<0)
        {
            x_velocity=-1*x_velocity;
            cout<<"HIT Left SIDE"<<endl;
        }
        if(tar_y+ sin(PI/180 * move_angle) + radius>screenHeight )
        {
            y_velocity=-1*y_velocity;
            cout<<"HIT TOP"<<endl;
        }
        if(tar_y+ sin(PI/180 * move_angle) - radius<floor_y)
        {
            y_velocity=-1*y_velocity;
            cout<<"HIT Bottom"<<endl;
        }
        
        
        tar_x = tar_x+ x_velocity*cos(PI/180 * move_angle);
        tar_y = tar_y+ y_velocity*sin(PI/180* move_angle);
        
       // cout<<tar_x<<tar_y<<endl;
        //cout<<cos(PI/180 * 45);
        

    }
    //move bullet
    if( t_pos<T && currentlyShot){
        //cout<<"t_pos "<<t_pos<< "T "<<T<<endl;
        t_pos+=bull_vel;
        bullet_c_x= current_nozz_x+80*cos((PI/180) *current_angle)*t_pos;
        bullet_c_y= current_nozz_y+80*sin((PI/180) *current_angle)*t_pos - (.5*(9.8) * (t_pos*t_pos));
        
    }
    else if(t_pos>=T){
        currentlyShot=false;
        isShot=false;
        t_pos=T/15;
        isMiss=true;
    }
    if(currentlyShot){
        
        
            //distance between points
        double distance = sqrt( pow(bullet_c_x-tar_x,2)+pow(bullet_c_y-tar_y,2));
        
            cout<<distance<<endl;
            if(distance<radius ){
                isHit=true;
                cout<<"HIT"<<endl;
                Hit();
                
            }
        
               // cout<<"looking..."<<endl;
        
        
        //cout<<"in loop "<<k<<endl;
        
    }
    
    glutPostRedisplay();
    
}




//MOUSE INPUT
void myMouse(int button, int state, int x, int y){
    if(state==GLUT_DOWN){
        y=screenHeight-y;
        
        double deltaY = y - nozz_y;
        double deltaX = x - nozz_x;
        cout<<atan2(deltaY,deltaX)<<endl;
        angle=(atan2(deltaY,deltaX) *180.0/PI);
        cout<<"angle is "<<angle<<endl;;
        if(angle<45){
            angle=45;
        }
        else if(angle>75)
        {
            angle=75;
        }
        cout<<"clicked: "<<x<<" "<<y<<endl;
    }
    glutPostRedisplay();
}

//MOVING MOUSE INPUT

void myMotion(int x, int y){
    y=screenHeight-y;
    
    double deltaY = y - nozz_y;
    double deltaX = x - nozz_x;
    cout<<atan2(deltaY,deltaX)<<endl;
    angle=(atan2(deltaY,deltaX) *180.0/PI);
    cout<<"angle is "<<angle<<endl;;
    if(angle<45){
        angle=45;
    }
    else if(angle>75)
    {
        angle=75;
    }
    glutPostRedisplay();
    
}



//KEYBOARD INPUT
void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{

    switch(theKey){
        case 'q':
            exit(0);
        break;
        case 'Q':
            exit(0);
        break;
        case'a':
            if(tank_x>10)
            {
                tank_x=tank_x-5;
                nozz_x=nozz_x-5;
                
            }
        break;
        case'd':
            if(tank_x<screenWidth-tank_width-50)
            {
                tank_x=tank_x+5;
                nozz_x=nozz_x+5;
            }
            //cout<<"press d... x is "<<tank_x<<endl;
            break;
        case'w':
            if(angle<75)
            {
                angle++;
            }
            //cout<<"press d... x is "<<tank_x<<endl;
            break;
        case's':
            if(angle>45)
            {
                angle--;
            }
            //cout<<"press d... x is "<<tank_x<<endl;
            break;
        case 27: //the escape key that resets everything to default
         //   cout<<"You pressed the esc key"<<endl;
            tar_x=(rand()%(screenWidth-(2*radius)) )+radius;
            tar_y=(rand()%(screenHeight-floor_y-(2*radius)) )+ (floor_y+radius);
            tank_x=10;
            tank_y=floor_y+.1;
            nozz_x=(tank_x+tank_width)/2;
            nozz_y=(tank_y+tank_height);
            angle=45;
            move_tar=false;
            isShot=false;
            currentlyShot=false;
            x_velocity=5;
            y_velocity=5;
            bull_vel=.1;
            isMiss=false;
            isHit=false;
            
            break;
        case 'm':
            ToggleTarget();
            break;
        case 'M':
            ToggleTarget();
            break;
        case '+':
            if(move_tar){
                if(x_velocity<0){
                    x_velocity=x_velocity-5;
                }
                else{
                    x_velocity=x_velocity+5;
                }
                if(y_velocity>0)
                {
                    y_velocity=y_velocity+5;
                }
                else{
                    y_velocity=y_velocity-5;
                }
            }
           // cout<<x_velocity << y_velocity;
        break;
        case '-':
            if(move_tar){
            if(x_velocity<-5){
                x_velocity=x_velocity+5;
            }
            else if(x_velocity>5){
                x_velocity=x_velocity-5;
            }
            if(y_velocity>5)
            {
                y_velocity=y_velocity-5;
            }
            else if(y_velocity<-5){
                y_velocity=y_velocity+5;
            }
            }
            break;
        case 32:
            if(!currentlyShot){
                //cout<<"spacebar"<<endl;
                if(isShot){
                    isShot=false;
                }
                else{
                    isShot=true;
                }
            }
            break;
            
    }
    glutPostRedisplay();
    
}

//SPECIAL KEYBOARD INPUT
void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    cout<<"key: "<<theKey<<endl;
    switch(theKey) {
        case GLUT_KEY_UP:
            bull_vel=bull_vel+.05;
            break;
        case GLUT_KEY_DOWN:
            if(bull_vel>.1)
            {
                bull_vel=bull_vel-.05;
            }
            break;
      default:
            break;		      // do nothing
    }
    
    glutPostRedisplay(); // implicitly call myDisplay
}




//---------Draw floor
void drawFloor(){
    
    glBegin(GL_LINE_LOOP);
        glVertex2d(floor_x,floor_y);
        glVertex2d(floor_x+screenWidth,floor_y);
    glEnd();
}

//-------------Draw tank
void drawTank(){
    
    //Draw base
    glColor3f(96.0/255,240.0/255,240.0/255); //turquoise color
    glBegin(GL_POLYGON);
    glVertex2d(tank_x, tank_y); //bottom left
    glVertex2d(tank_x+tank_width, tank_y);// bottom_right
    glVertex2d(tank_x+tank_width, tank_y+tank_height); //top_right
    glVertex2d(tank_x, tank_y+tank_height); //top_left
    glEnd();
    glColor3d(0, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2d(tank_x, tank_y); //bottom left
        glVertex2d(tank_x+tank_width, tank_y);// bottom_right
        glVertex2d(tank_x+tank_width, tank_y+tank_height); //top_right
        glVertex2d(tank_x, tank_y+tank_height); //top_left
    glEnd();
    
    
    //draw top
    glColor3f(96.0/255,240.0/255,240.0/255); //turquoise color

    glBegin(GL_POLYGON);
    glVertex2d(tank_x+(tank_width/8), tank_y+tank_height);//bottom left
    glVertex2d(tank_x+(7*tank_width/8), tank_y+tank_height); //bottom_right
    glVertex2d(tank_x+(4*tank_width/8), tank_y+(7*tank_height/4)); //top_right
    glVertex2d(tank_x +(1*tank_width/8), tank_y+(7*tank_height/4)); //top_left
    glEnd();
        glColor3d(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(tank_x+(tank_width/8), tank_y+tank_height);//bottom left
    glVertex2d(tank_x+(7*tank_width/8), tank_y+tank_height); //bottom_right
    glVertex2d(tank_x+(4*tank_width/8), tank_y+(7*tank_height/4)); //top_right
    glVertex2d(tank_x +(1*tank_width/8), tank_y+(7*tank_height/4)); //top_left
    glEnd();
}
//DRAW MISS SIGN
void draw_X(){
    
    if(isMiss){
        glColor3f(1,0,0);
    }
    else
    {
        glColor3f(1,1,1);
    }
    glLineWidth(10);
    glBegin(GL_LINE_STRIP);
    glVertex2d(400,400);
    glVertex2d(450,450);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(400, 450);
    glVertex2d(450,400);
    glEnd();
    glColor3f(0,0,0);
    
}

//-----------Drawing the target
void drawtarget(){
    
    if(isHit&& isHitTimer%2==0){
        glColor3f(1,0,0);
    }
    else{
        glColor3f(8.0/255,230.0/255,21.0/255);
    }
    
    double tar_center_x=tar_x;
    double tar_center_y=tar_y;
    glBegin(GL_POLYGON);
    
        for(double k=0;k<=1;k=k+.05){
            
            glVertex2d(tar_x+radius*cos(2*PI*k),tar_y+radius*sin(2*PI*k) );
            //cout<<"in loop "<<k<<endl;
            
        }
    glEnd();
    glColor3f(0,0,0);
    
}

//------------drawing the Nozzle
void drawNozzle(){
    
    double tempx=nozz_x;
    double tempy=nozz_y;
        T= 80 * 2 * sin((PI/180)*angle)/9.8;
    if(currentlyShot){
    glBegin(GL_LINE_STRIP);
    for(double t=0;t<T;t=t+.01)
    {
        
        tempx = current_nozz_x+80*cos((PI/180) *current_angle)*t; //tempx+(4)*cos(2*PI)*t;
        tempy = current_nozz_y+80*sin((PI/180) *current_angle)*t - (.5*(9.8) * (t*t));
        glVertex2d(tempx, tempy);
       // cout<<"drawing proj: "<<t<<endl;
        
    }
    glEnd();
    }
    

    
    glColor3f(96.0/255,240.0/255,240.0/255);
    glLineWidth(10);
    glBegin(GL_LINE_STRIP);
    for(double t=0;t<T/15;t=t+.01)
    {
        
        tempx = nozz_x+80*cos((PI/180) *angle)*t; //tempx+(4)*cos(2*PI)*t;
        tempy = nozz_y+80*sin((PI/180) *angle)*t - (.5*(9.8) * (t*t));
        glVertex2d(tempx, tempy);
        
    }
    glEnd();
    bullet_s_x= nozz_x+80*cos((PI/180) *angle)*T/15;
    bullet_s_y= nozz_y+80*sin((PI/180) *angle)*(T/15) - (.5*(9.8) * ((T/15)*(T/15)));

    glLineWidth(1);
}

void drawBullet(){
    if(isShot){
        bullet_c_x=bullet_s_x;
        bullet_c_y=bullet_s_y;
        glPointSize(10);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
            glVertex2d(bullet_c_x, bullet_c_y);
        glEnd();
        glPointSize(1);
        glColor3f(0, 0, 0);
        isShot=false;
        currentlyShot=true;
        current_angle=angle;
        current_nozz_x=nozz_x;
        current_nozz_y=nozz_y;
    }
    else if(currentlyShot){
        glPointSize(10);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2d(bullet_c_x, bullet_c_y);
        glEnd();
        glPointSize(1);
        glColor3f(0, 0, 0);
    }
}


//------------Draws everything
void myDisplay(void)
{
 //   sleep(.1);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glLineWidth(3);
    drawFloor();
    draw_X();
    glLineWidth(1);
    drawNozzle();
    glLineWidth(1);
    drawTank();
    drawtarget();
    drawBullet();
    

    
    glutSwapBuffers();	// send all output to display

}



//------------MAIN
int main(int argc, char** argv){
    
    srand ((unsigned)time(NULL));
    
    tar_x=(rand()%(screenWidth-(2*radius)) )+radius;
    tar_y=(rand()%(screenHeight-floor_y-(2*radius)) )+ (floor_y+radius);
    cout<<tar_x<<" " <<tar_y<<endl;
//    cout<<"Starting program...";
    glutInit(&argc, argv);												// initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	// set display mode
    glutInitWindowSize(screenWidth, screenHeight);// set window size
    glutInitWindowPosition(100, 150);							// set window position on screen
    glutCreateWindow("Tank Shooter");	// open the screen window
    
    glutIdleFunc(myIdle); //IDLE
    
    //glutIdleFunc(myidle2);
    glutDisplayFunc(myDisplay);		// register redraw function
    //glutMouseFunc(myMouse);				// register mouse callback function
    //glutKeyboardFunc(myKeyboard);	// register keyboard callback function
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutSpecialFunc(mySpecialKeyboard);
    myInit();
    
    glutMainLoop();		// go into a perpetual loop
    return 0;
    
    return 0;
}