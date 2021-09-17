#ifndef PRIMGLASSBUILDER_H
#define PRIMGLASSBUILDER_H

#include "GlassBuilder.h"
#include <QObject>

//using namespace Eigen;

extern const int INF;
typedef uint index;

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

#endif // PRIMGLASSBUILDER_H
