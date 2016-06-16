#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtCore/qmath.h>
#include "gl/GLU.h"
#include "math.h"
#include "objload.h"
#include "mainwindow.h"

#ifndef Pi
#define Pi 3.1415926
#endif

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QGLWidget *parent = 0);
    ~Widget();
    int xRotation() const { return xRot; }
    int yRotation() const { return yRot; }
    int zRotation() const { return zRot; }
    void ImportObjFile(QString path);//import obj file from path using ObjLoada    

private:
    Ui::Widget *ui;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void alwaysRotate();
    void IMURotate();

private:
    void drawTriangle();
    void drawObj();
    void IMUThread();

private:
    int xRot;
    int yRot;
    int zRot;
    QList<float> IMU,p,Q,R,z;
    int zTra;
    float mX,mY,mZ;
    double AngToRad;
    ObjLoad obj;
    bool isObjOn,isIMUon;
    QList<ObjLoad::Face> ObjFace;

    QColor faceColors[4];
    QPoint lastPos;
    QTimer *timer;
};

#endif // WIDGET_H
