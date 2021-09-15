#include "PrimGlassBuilder.h"
const int INF=0x7FFFFFFF;
#ifdef WITH_QT
PrimGlassBuilder::PrimGlassBuilder(QObject *parent) : QObject(parent)
#else
PrimGlassBuilder::PrimGlassBuilder()
#endif
{

}

glassMap PrimGlassBuilder::makeBridge(const TokiMap & _targetMap,
                                      walkableMap* walkable) {

    targetPoints.clear();
    for(short r=0;r<_targetMap.rows();r++)
        for(short c=0;c<_targetMap.cols();c++) {
            if(_targetMap(r,c))
                targetPoints.push_back(TokiRC(r,c));
        }
    targetPoints.shrink_to_fit();

    addNodesEdgesToGraph();
    runPrim();

    glassMap result(_targetMap.rows(),_targetMap.cols());
    result.setZero();

    for(auto it=minSpawningTree.cbegin();it!=minSpawningTree.cend();it++){
        Vertex head=source(*it,graph);
        Vertex tail=target(*it,graph);
        TokiPos A=targetPoints[graph[head]];
        TokiPos B=targetPoints[graph[tail]];
        Vector2f start(TokiRow(A),TokiCol(A));
        Vector2f end(TokiRow(B),TokiCol(B));
        qDebug()<<"连接"<<'['<<start(0)<<','<<start(1)<<']'<<"与"<<'['<<end(0)<<','<<end(1)<<']';
        int stepCount=(end-start).array().abs().maxCoeff();
        Vector2f step=(end-start)/stepCount;
        Vector2f cur;
        for(int j=1;j<stepCount;j++) {
            cur=start+j*step;
            result(std::floor(cur(0)),std::floor(cur(1)))=1;
            result(std::ceil(cur(0)),std::ceil(cur(1)))=1;
        }
    }

    if(walkable!=nullptr)
        *walkable=result;

    for(auto it=targetPoints.cbegin();it!=targetPoints.cend();it++) {
        result(TokiRow(*it),TokiCol(*it))=0;
        walkable->operator()(TokiRow(*it),TokiCol(*it))=GlassBuilder::blockType::target;
    }
    return result;
}

void PrimGlassBuilder::addNodesEdgesToGraph() {
graph.clear();
/*
for(index i=0;i<targetPoints.size();i++)
    boost::add_vertex(i,graph);*/
int length;
TokiPos A,B;
for(index i=0;i<targetPoints.size();i++)
    for(index j=i+1;j<targetPoints.size();j++) {
        A=targetPoints[i];
        B=targetPoints[j];
        length=sqrt((TokiRow(A)-TokiRow(B))*(TokiRow(A)-TokiRow(B))+
                    (TokiCol(A)-TokiCol(B))*(TokiCol(A)-TokiCol(B)));
        boost::add_edge(i,j,length,graph);
    }
qDebug("插入了所有的边");
}

void PrimGlassBuilder::runPrim() {
    minSpawningTree.resize(boost::num_vertices(graph)-1);
    boost::prim_minimum_spanning_tree(graph,&minSpawningTree[0]);
    qDebug("prim算法完毕");
}
