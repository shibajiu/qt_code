#ifndef OBJLOAD_H
#define OBJLOAD_H

#include "objload_global.h"

class OBJLOADSHARED_EXPORT ObjLoad
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
    };

    struct FaceIndex{//face index
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
    };

public:
    int Obj_Load(QString ObjPath, QList<Face> obj);
    QList<Face> Obj_Load(QString ObjPath);
    QList<float> Kalman(QList<int> prior, QList<int> z, QList<float> p, QList<float> Q, QList<float> R);

private:
    void init();

private:
    QList<Vertex> Vertices;
    QList<FaceIndex> Indexs;
    QList<Normal> Normals;
    QList<Face> Faces;
    Face facetemp;
    Normal normaltemp;
    FaceIndex faceindextemp;
    Vertex vertextemp;

};

#endif // OBJLOAD_H
