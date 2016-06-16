#ifndef OBJLOAD_H
#define OBJLOAD_H

#include <QtCore/qglobal.h>
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>
#include <QStringList>
#include <QMessageBox>

class ObjLoad
{

public:

    struct Vertex{//vertex
        float x;
        float y;
        float z;

        void set(QStringList sl){
			this->x=sl[1].toFloat();
            this->y=sl[2].toFloat();
            this->z=sl[3].toFloat();
        }

        void set(float xf,float yf,float zf){
            this->x=xf;
            this->y=yf;
            this->z=zf;
        }

        float getMax(){
            return qMax(qMax(this->x,this->y),qMax(this->y,this->z));
        }

        float getMin(){
            return qMin(qMin(this->x,this->y),qMin(this->y,this->z));
        }

        void init(){
            this->set(0,0,0);
        }

        void setX(float xf){
            this->x=xf;
        }

        void setY(float yf){
            this->y=yf;
        }

        void setZ(float zf){
            this->z=zf;
        }

        /**
        use to find the view volume
        **/
        void findMaxAbs(Vertex cmp){
            if(qAbs(this->x)<qAbs(cmp.x))
                this->setX(cmp.x);
            if(qAbs(this->y)<qAbs(cmp.y))
                this->setY(cmp.y);
            if(qAbs(this->z)<qAbs(cmp.z))
                this->setZ(cmp.z);
        }

        /**
        use to find the view volume
        **/
        void findMinAbs(Vertex cmp){
            if(qAbs(this->x)>qAbs(cmp.x))
                this->setX(cmp.x);
            if(qAbs(this->y)>qAbs(cmp.y))
                this->setY(cmp.y);
            if(qAbs(this->z)>qAbs(cmp.z))
                this->setZ(cmp.z);
        }
    };

    struct FaceIndex{//face index
        public:
        int a;
        int b;
        int c;
        void set(QStringList sl){
            this->a=sl[1].toInt();
            this->b=sl[2].toInt();
            this->c=sl[3].toInt();
        }
    };

    struct Normal{//normal
        float x;
        float y;
        float z;
        void set(QStringList sl){
            this->x=sl[1].toFloat();
            this->y=sl[2].toFloat();
            this->z=sl[3].toFloat();
        }        
    };

    struct Face{
        Vertex a;
        Vertex b;
        Vertex c;
        void set(QList<Vertex> ver,FaceIndex ind){
            this->a=ver[ind.a-1];
            this->b=ver[ind.b-1];
            this->c=ver[ind.c-1];
        }
        QString toQString(){
            QString temp="a.x:"+QString::number(this->a.x)+"\ta.y:"+QString::number(this->a.y)+"\ta.z:"+QString::number(this->a.z)+"\n"
                    +"b.x:"+QString::number(this->b.x)+"\tb.y:"+QString::number(this->b.y)+"\tb.z:"+QString::number(this->b.z)+"\n"
                    +"c.x:"+QString::number(this->c.x)+"\tc.y:"+QString::number(this->c.y)+"\tc.z:"+QString::number(this->c.z);
            return temp;
        }
    };

public:
    int Obj_Load(QString ObjPath, QList<Face> *obj);
    QList<Face> Obj_Load(QString ObjPath);
    QList<float> Kalman(QList<float> prior, QList<float> z, QList<float> *p, QList<float> Q, QList<float> R);
    void unittest(QString testobjname);//unit test
    void getMaxXYZ(float *x,float *y,float *z);
    void getMinXYZ(float *x,float *y,float *z);

private:
    void init();
    void isgetobj(QString ObjPath, int &objlength, float *tmX, float *tmY, float *tmZ);

private:
    QList<Vertex> Vertices;
    QList<FaceIndex> Indexs;
    QList<Normal> Normals;
    QList<Face> Faces;
    Face facetemp;
    Normal normaltemp;
    FaceIndex faceindextemp;
    Vertex vertextemp,MaxPoint,MinPoint;

};

#endif // OBJLOAD_H
