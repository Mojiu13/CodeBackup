#ifndef gaopeng
#define gaopeng
#include <QString>
#include <QVector>
#include <QMap>

typedef struct Arccell
{
    int path;
} Matrix[25][25];

typedef struct
{
    QString places[25];
    Matrix arcs;
    int vexnum, arcnum;
}Graph;

class gaopeng
{
public:
    gaopeng();
    Graph G;
    QVector<QPair<int,QPair<int,int> > > List;
    QMap<QString,int> mp;


    QString starcity;
    QString overcity;
    int st;
    int ed;
};

#endif //GAOPENG_H
