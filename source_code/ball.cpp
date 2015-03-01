using namespace std;
#include "p.o/controlcenter.h"
#include "p.o/baseclass.h"

class SimBall
{
public:
    XYF Load;
    int Mode;
    SimBall(float X,float Y,int M):Load(X,Y),Mode(M){}
};
class Ball:public Plugin_Base
{
    bool Dead;
    int Point;
    std::list<SimBall> AllBall;
    XYF Lo;
    NumberOut NO;
    long Time;
public:
    Ball():Plugin_Base("BBB"),Point(1000),Lo(0.0,-0.95),Time(0),Dead(false){}
    void FlatShow(ControlCenter *Data);
    void Accessorial(ControlCenter *Data, long L);
};
ControlCenter CC;
int main(int argc, char* argv[])
{
    PO_FONT::SetFont("font/fksnjt.ttc",50);
    CC.Regedit(new Ball);
    CC.Init(3);
    //glFrontFace(GL_CCW);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    while(CC.Running)
    {
        CC.Run();
        CC.Finish();
    }
    //error<<"ghdfgdfg"<<endl;
}
void Ball::FlatShow(ControlCenter *Data)
{
    if(!Dead)
    {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0,-0.95);
    glVertex2f(-1.0,-1.0);
    glVertex2f(Lo.X,-1.0);
    glVertex2f(Lo.X,-0.95);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex2f(1.0,-0.95);
    glVertex2f(1.0,-1.0);
    glVertex2f(Lo.X,-1.0);
    glVertex2f(Lo.X,-0.95);
    glEnd();
    for(std::list<SimBall>::iterator Po=AllBall.begin();Po!=AllBall.end();++Po)
    {
        if(Po->Mode==1)
            glColor3f(1.0,0.0,0.0);
        else if(Po->Mode==2)
            glColor3f(0.0,0.0,1.0);
        glBegin(GL_QUADS);
        glVertex2f(-0.05+Po->Load.X,+0.05+Po->Load.Y);
        glVertex2f(-0.05+Po->Load.X,-0.05+Po->Load.Y);
        glVertex2f(+0.05+Po->Load.X,-0.05+Po->Load.Y);
        glVertex2f(+0.05+Po->Load.X,+0.05+Po->Load.Y);
        glEnd();
    }
    NO.Show(Point,0.5,1.0,0.1);
    NO.Show(Time,0.5,0.9,0.1);
    }
    else{
        NO.Show(Point,-0.2,0.2,0.4);
        NO.Show(Time,-0.2,0.0,0.4);
    }
}


void Ball::Accessorial(ControlCenter *Data, long L)
{
    static bool Right=false;
    static bool Left=false;
    if(!Dead)
    {
        if(Point<=0_
            Dead=true;
        Time+=L;
        while(Handle<Information> Tem=GetInformation())
        {
            if(Tem->IsKeyDown())
            {
                if(Tem->Data1.uc=='a')
                    Left=true;
                else if(Tem->Data1.uc=='d')
                    Right=true;
            }else if(Tem->IsKeyUp())
            {
                if(Tem->Data1.uc=='a')
                    Left=false;
                else if(Tem->Data1.uc=='d')
                    Right=false;
            }
        }
        if(Right)
        {
            Lo.X+=0.0005*L;
            if(Lo.X>1.0)
                Lo.X=1.0;
        }
        if(Left)
        {
            Lo.X-=0.0005*L;
            if(Lo.X<-1.0)
                Lo.X=-1.0;
        }
        int K=rand()%100;
        if(K>98)
        {
            float Tem=(rand()%2000-1000)/1000.0;
            int M=(rand()%2+1);
            AllBall.push_back(SimBall(Tem,1.0,M));
        }
        for(std::list<SimBall>::iterator Po=AllBall.begin();Po!=AllBall.end();++Po)
        {
            Po->Load.Y-=0.00000001*Time*L;
            if(Po->Load.Distance(Lo)<=0.05)
            {
                Point-=80;
                AllBall.erase(Po--);
            }else if(Po->Load.Y<=-0.95)
            {
                if(Po->Mode==1)
                {
                    if(Po->Load.X<=Lo.X)
                        Point-=40;
                    else
                        Point+=30;
                }else if(Po->Mode==2)
                {
                    if(Po->Load.X<=Lo.X)
                        Point+=30;
                    else
                        Point-=40;
                }
                AllBall.erase(Po--);
            }
        }
    }
}
