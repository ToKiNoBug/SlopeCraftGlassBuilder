#ifndef PRIMGLASSBUILDER_H
#define PRIMGLASSBUILDER_H

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/properties.hpp>
#include<boost/property_map/property_map.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include "GlassBuilder.h"
#include <QObject>

//using namespace Eigen;
using namespace boost;

extern const int INF;
typedef uint index;

typedef boost::adjacency_list<vecS,vecS,undirectedS,index,int> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;


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
    Graph graph;
    std::vector<Edge> minSpawningTree;

    void addNodesEdgesToGraph();
    void runPrim();
};

#endif // PRIMGLASSBUILDER_H
