#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    MainWindow w;
    w.show();
    xRot = 0;
        yRot = 0;
        zRot = 0;
        AngToRad=Pi/180;
        isObjOn=false;
        isIMUon=false;
        zTra=0;
        mX=0;
        p<<1<<1<<1;
        Q<<0.1<<0.1<<0.1;
        R<<1<<1<<1;

        faceColors[0] = Qt::red;
        faceColors[1] = Qt::green;
        faceColors[2] = Qt::blue;
        faceColors[3] = Qt::yellow;

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(alwaysRotate()));
//        timer->start(70);

//        obj.unittest("4");//start unit test

        ImportObjFile("E:\\hit\\test\\testtriangle\\testtriangle\\3.obj");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);
}

static float radius = 50.5f;

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
//    gluLookAt(radius*qCos(AngToRad*xRot), yRot, radius*qSin(AngToRad*xRot), 0, 0, 0, 0, 1, 0);
    if(isObjOn){
        drawObj();
    }
    else {
        drawTriangle();
    }
    glFlush();
}

void Widget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, (float)width / height, 1.0f, 1000.0f);
//    if (width <= height)
//        glOrtho(-mX*2,mX*2, -mX*2 * (GLfloat)height/(GLfloat)width, mX*2 * (GLfloat)height/(GLfloat)width, -mX*2, mX*2);
//    else
//        glOrtho(-mX*2*(GLfloat)width/(GLfloat)height, mX*2*(GLfloat)width/(GLfloat)height, -mX*2, mX*2, -mX*2, mX*2);
    glMatrixMode(GL_MODELVIEW);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    yRot+=4 * dy;
    xRot+=4 * dx;
    if (yRot>1.5*mX)
        yRot=1.5*mX;
    else if (yRot<-1.5*mX)
        yRot=-1.5*mX;
    updateGL();

    lastPos = event->pos();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    zTra+=event->delta()/120;
    radius+=event->delta()/120;
    updateGL();
}

static const GLfloat P1[3] = { 0.0, -1.0, +2.0 };
static const GLfloat P2[3] = { +1.73205081, -1.0, -1.0 };
static const GLfloat P3[3] = { -1.73205081, -1.0, -1.0 };
static const GLfloat P4[3] = { 0.0, +2.0, 0.0 };

static const GLfloat * const coords[4][3] = {
    { P1, P2, P3 }, { P1, P3, P4 }, { P1, P4, P2 }, { P2, P4, P3 }
};
void Widget::drawTriangle()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -50.0+zTra);
//    if(isTest)
//    {
        glRotatef(xRot, 1.0, 0.0, 0.0);
        glRotatef(yRot, 0.0, 1.0, 0.0);
        glRotatef(zRot, 0.0, 0.0, 1.0);
//    }
//    else
//    {
//        glRotatef(Pitch,0,1,0);
//        glRotatef(Yaw,sin(Pitch*AngToRad),0,cos(Pitch*AngToRad));
//        glRotated(Roll,1,0,0);
//    }


    for (int i = 0; i != 4; ++i) {
        //glLoadName(i);
        glBegin(GL_TRIANGLES);
        qglColor(faceColors[i]);
        for (int j = 0; j < 3; ++j) {
            glVertex3f(coords[i][j][0], coords[i][j][1],
                       coords[i][j][2]);
        }
        glEnd();

    }
}

void Widget::drawObj()//draw obj
{
//    glLoadIdentity();
//    drawTriangle();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(radius*qCos(AngToRad*xRot), yRot, radius*qSin(AngToRad*xRot), 0, 0, 0, 0, 1, 0);

//    glTranslatef(0.0, 0.0, -50.0+zTra);
//    glRotatef(xRot, 1.0, 0.0, 0.0);
//    glRotatef(yRot, 0.0, qCos(yRot*AngToRad), -qSin(yRot*AngToRad));
//    glRotatef(xRot, 0.0,1.0,0.0);
//    glRotatef(zRot, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
qglColor(Qt::green);
    for(int i=0;i<ObjFace.length();i++){        
        glVertex3f(ObjFace[i].a.x,ObjFace[i].a.y,ObjFace[i].a.z);
        glVertex3f(ObjFace[i].b.x,ObjFace[i].b.y,ObjFace[i].b.z);
        glVertex3f(ObjFace[i].c.x,ObjFace[i].c.y,ObjFace[i].c.z);
    }
//    QMessageBox::information(NULL, "Title", ObjFace[ObjFace.length()-1].toQString(), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    glFlush();
    glEnd();
}

void Widget::alwaysRotate()
{
    zRot += 2;
    updateGL();
}

void Widget::IMURotate()
{
    z=obj.Kalman(IMU,z,&p,Q,R);

    glRotatef(z[0],0,1,0);
    glRotatef(z[2],sin(z[0]*AngToRad),0,cos(z[0]*AngToRad));
    glRotated(z[1],1,0,0);
}

void Widget::IMUThread()
{
    //
    isIMUon=true;
}

void Widget::ImportObjFile(QString path)
{
    if(obj.Obj_Load(path,&ObjFace)==1){
        isObjOn=true;
        timer->stop();
        obj.getMaxXYZ(&mX,&mY,&mZ);
        mX=qMax(qMax(qAbs(mX),qAbs(mY)),qMax(qAbs(mY),qAbs(mZ)));
        radius=2*mX;
//        QMessageBox::information(NULL, "Title", QString::number(mX), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
//    ObjFace=obj.Obj_Load(path);
//    isObjOn=true;
//    timer->stop();
}
