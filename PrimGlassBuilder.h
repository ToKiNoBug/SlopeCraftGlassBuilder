#ifndef PRIMGLASSBUILDER_H
#define PRIMGLASSBUILDER_H


#include <QObject>

//using namespace Eigen;

#define WITH_QT

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <cmath>
#include "WaterItem.h"

#include <QtConcurrent>
#ifdef WITH_QT
    #include <QObject>
    #include <QRgb>
#else
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
#endif


using namespace Eigen;
typedef unsigned int ARGB;
typedef Array<ARGB,Dynamic,Dynamic> EImage;
typedef Array<uchar,Dynamic,Dynamic> TokiMap;
typedef TokiMap glassMap;
typedef TokiMap walkableMap;

extern const ARGB airColor;
extern const ARGB targetColor;
extern const ARGB glassColor;

class edge
{
public:
    edge();
    edge(TokiPos,TokiPos);
    edge(ushort r1,ushort c1,ushort r2,ushort c2);
    TokiPos beg;
    TokiPos end;
    int lengthSquare;
    bool connectWith(TokiPos) const;
    void drawEdge(glassMap &) const;
};


#ifdef WITH_QT
class PrimGlassBuilder : public QObject
{
    Q_OBJECT
public:
    explicit PrimGlassBuilder(QObject *parent = nullptr);
#else
class PrimGlassBuilder
{
public:
    PrimGlassBuilder();
#endif
    glassMap makeBridge(const TokiMap & _targetMap,walkableMap* walkable=nullptr);
#ifdef WITH_QT
signals:
    void progressRangeSet(int min,int max,int val);
    void progressAdd(int);
    void keepAwake();
#else

#endif
private:
    std::vector<TokiPos> targetPoints;
    std::list<edge> edges;
    std::vector<edge> tree;
    void addEdgesToGraph();
    void runPrim();
};

EImage TokiMap2EImage(const TokiMap&);

#endif // PRIMGLASSBUILDER_H
