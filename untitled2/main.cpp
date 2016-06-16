#include <iostream>
#include <QList>
using namespace std;
void swap(int &a,int &b)  //形参是引用类型
{
   int temp;
   temp=a;
   a=b;
   b=temp;
}
void changeQList(QList<int> *aa){
    (*aa)[2]=12;
}

class Test{
public:
    static void print1(){
        cout<<"1"<<endl;
    }
    static void print2(){
        cout<<"2"<<endl;
    }
//    Test(int t);
};

int main( )
{
QList<float> a,b;
a<<1<<2<<3;
b<<4<<4;
float *c;
for(int i=0;i<3;i++){
    *c=a[i];
    c++;
}
cout<<&a<<endl;
cout<<*c<<endl;
   return 0;
}
