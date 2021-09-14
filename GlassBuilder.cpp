#include "GlassBuilder.h"

const ushort GlassBuilder::popSize=100;        //种群规模
const ushort GlassBuilder::maxGeneration=500;      //最大代数
const double GlassBuilder::crossoverProb=0.8;      //交叉概率
const double GlassBuilder::mutateProb=0.01;     //变异概率
const double GlassBuilder::mutateIntense=0.02;      //变异强度
double randD(){
    static std::default_random_engine generator(time(0));
    static std::uniform_real_distribution<double> rander(0,1);
    return rander(generator);
}
int randi(int low,int high) {
    static std::default_random_engine generator(time(0));
    static std::uniform_int_distribution<int> rander(low,high);
    return rander(generator);
}

GlassBuilder::GlassBuilder()
{
    population.resize(popSize);
}

void countConnected(ushort begRow,ushort begCol,
                    const walkableMap& walkable,
                    std::unordered_set<TokiPos>& visited) {
    //根据四连通原则遍历每个连通的元素，并装入visited集合中
if(!walkable(begRow,begCol))
    return;
if(visited.find(TokiRC(begRow,begCol))!=visited.end())
    return;

visited.emplace(TokiRC(begRow,begCol));

if(begRow>=1&&
        walkable(begRow-1,begCol)&&
        (visited.find(TokiRC(begRow-1,begCol))==visited.end())) {
    countConnected(begRow-1,begCol,walkable,visited);
}

if(begRow+1<walkable.rows()&&
        walkable(begRow+1,begCol)&&
        (visited.find(TokiRC(begRow+1,begCol))==visited.end())) {
    countConnected(begRow+1,begCol,walkable,visited);
}

if(begCol>=1&&
        walkable(begRow,begCol-1)&&
        (visited.find(TokiRC(begRow,begCol-1))==visited.end())) {
    countConnected(begRow,begCol-1,walkable,visited);
}

if(begCol+1<walkable.cols()&&
        walkable(begRow,begCol+1)&&
        (visited.find(TokiRC(begRow,begCol+1))==visited.end())) {
    countConnected(begRow,begCol+1,walkable,visited);
}
}
