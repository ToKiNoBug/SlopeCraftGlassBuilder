#ifndef GLASSBUILDER_H
#define GLASSBUILDER_H

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
#ifdef WITH_QT
class GlassBuilder:public QObject
{
    Q_OBJECT
#else
class GlassBuilder
{
#endif
public:
    enum blockType{
        air=0,
        glass=1,
        target=127
    };
    static const ushort popSize;        //种群规模
    static const ushort maxGeneration;      //最大代数
    static const double crossoverProb;      //交叉概率
    static const double mutateProb;     //变异概率
    static const double mutateIntense;      //变异强度
    GlassBuilder();
    glassMap makeBridge(const TokiMap & _targetMap);
    const TokiMap& getTargetMap() const;
    const TokiMap& getBuildableMap() const;
#ifdef WITH_QT
signals:
    void progressRangeSet(int min,int max,int val);
    void progressAdd(int);
#endif
private:
    std::vector<TokiPos> targetPoints;   //要连接的目标点，也是不可以搭桥的地方
    //std::vector<TokiPos> forbiddenPoints;    //
    std::vector<TokiPos> mutatePoints;     //所有可以突变的位点，

    std::vector<glassMap> population;        //每个个体都是一个glassMap
    std::vector<double> fitness;        //适应度函数，越大越好
    ushort rows;
    ushort cols;
    ushort eliteIndex;      //精英个体的索引位置
    ushort generations;

    /*
    ushort mapRows() const;
    ushort mapCols() const;*/

    void run();

    //void initialize();
    void caculateAll();
    void select();
    void crossover();
    void mutate();
    uint dims() const;
};

walkableMap glassMap2walkableMap(const glassMap * glass,
                                 const std::vector<TokiPos> * targetMap);

double caculateFitness(const glassMap * glass,
                       const std::vector<TokiPos> * targetMap);

void countConnected(ushort begRow,ushort begCol,
                    const walkableMap& walkable,
                    std::unordered_set<TokiPos>& visited);

double randD();

int randi(int,int);

EImage TokiMap2EImage(const TokiMap&);

#endif // GLASSBUILDER_H
