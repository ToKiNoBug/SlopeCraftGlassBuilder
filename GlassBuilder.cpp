#include "GlassBuilder.h"
/*
const ushort GlassBuilder::popSize=50;        //种群规模
const ushort GlassBuilder::maxGeneration=3000;      //最大代数
const ushort GlassBuilder::maxFailTimes=5000;
const double GlassBuilder::crossoverProb=0.8;      //交叉概率
const double GlassBuilder::mutateProb=0.05;     //变异概率
const double GlassBuilder::mutateIntense=1.0/100;      //变异强度
const double GlassBuilder::initializeTrueRate=0.75;
*/


double randD(){
    static std::default_random_engine generator(time(0));
    static std::uniform_real_distribution<double> rander(0,1);
    return rander(generator);
}

int randi(int low,int high) {
    static std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> rander(low,high);
    return rander(generator);
}

/*

GlassBuilder::GlassBuilder()
{
    population.resize(popSize);
    population.shrink_to_fit();
    fitness.resize(popSize);
    fitness.shrink_to_fit();
}

walkableMap glassMap2walkableMap(const glassMap * glass,
                                 const std::vector<TokiPos> * targetMap) {
    walkableMap res=*glass;
    for(auto jt=targetMap->cbegin();jt!=targetMap->cend();jt++)
        res(TokiRow(*jt),TokiCol(*jt))=GlassBuilder::blockType::target;
    return res;
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
return;
}

int caculateFitness(glassMap * glass,
                       const std::vector<TokiPos> * targetMap) {
walkableMap walkable=glassMap2walkableMap(glass,targetMap);
std::unordered_set<TokiPos> visited;
visited.clear();

TokiPos startPoint=TokiRC(0,0);
for(short r=0;r<glass->rows();r++)
    for(short c=0;c<glass->cols();c++) {
        if(!walkable(r,c)) continue;
        startPoint=TokiRC(r,c);
        c=glass->cols();
        r=glass->rows();
    }

countConnected(TokiRow(startPoint),TokiCol(startPoint),walkable,visited);

uint attachedTargets=0;
for(auto it=targetMap->cbegin();it!=targetMap->cend();it++) {
    if(visited.find(*it)!=visited.end())
        attachedTargets++;
}

int Fitness=0;

if(attachedTargets>=targetMap->size()) {
    Fitness=glass->size()+1;

    for(ushort r=0;r<glass->rows();r++)
        for(ushort c=0;c<glass->cols();c++) {
            if(glass->operator()(r,c)) {
                if(visited.find(TokiRC(r,c))==visited.end())
                    glass->operator()(r,c)=0;
                else
                Fitness--;
            }
        }

    /*for(uint i=0;i<glass->size();i++) {
        if(visited.find()
        if(glass->operator()(i))
            Fitness--;
    }
} else
    Fitness=attachedTargets-targetMap->size();

return Fitness;
}

glassMap GlassBuilder::makeBridge(const TokiMap & _targetMap,walkableMap* walkable) {

    /*std::vector<TokiPos> targetPoints;   //要连接的目标点
    std::vector<TokiPos> mutatePoints;     //所有可以突变的位点，
    rows=_targetMap.rows();
    cols=_targetMap.cols();
    targetPoints.clear();
    //forbiddenPoints.clear();
    mutatePoints.clear();
    for(short r=0;r<_targetMap.rows();r++)
        for(short c=0;c<_targetMap.cols();c++) {
            if(_targetMap(r,c))
                targetPoints.push_back(TokiRC(r,c));
            else
                mutatePoints.push_back(TokiRC(r,c));
        }
    targetPoints.shrink_to_fit();
    mutatePoints.shrink_to_fit();

    //初始化种群
    for(auto it=population.begin();it!=population.end();it++) {
        (*it).setOnes(_targetMap.rows(),_targetMap.cols());
        for(uint i=0;i<(*it).size();i++)
            (*it)(i)=randD()<=initializeTrueRate;
        for(auto jt=targetPoints.cbegin();jt!=targetPoints.cend();jt++)
            (*it)(TokiRow(*jt),TokiCol(*jt))=0;
    }

    run();

    if(walkable!=nullptr) {
        *walkable=glassMap2walkableMap(&population[eliteIndex],&targetPoints);
    }

    return population[eliteIndex];
}


void GlassBuilder::caculateAll() {
    //qDebug("caculateAll");
    std::queue<QFuture<int>> tasks;
    for(int i=0;i<popSize;i++) {
        tasks.push(
                    QtConcurrent::run(caculateFitness,&population[i],&targetPoints)
                    );
    }
    int i=0;
    while (!tasks.empty()) {
        tasks.front().waitForFinished();
        //qDebug()<<i;
        fitness[i++]=tasks.front().result();
        tasks.pop();
    }
}

void GlassBuilder::select() {
    //qDebug("select");
    ushort maxIdx=0;
    int maxVal=fitness[0];
    for(ushort i=0;i<popSize;i++) {
        if(fitness[i]>maxVal) {
            maxVal=fitness[i];
            maxIdx=i;
        }
    }

    eliteIndex=maxIdx;
    for(ushort i=0;i<popSize;i++)
        if(fitness[i]<0&&i!=eliteIndex)population[i]=population[eliteIndex];
}

void GlassBuilder::crossover() {    
    //qDebug("crossover");
    std::vector<ushort> crossoverLine;
    crossoverLine.resize(0);

    for(ushort i=0;i<popSize;i++) {
        if(i==eliteIndex)continue;
        if(randD()<=crossoverProb)
            crossoverLine.push_back(i);
    }
    std::random_shuffle(crossoverLine.begin(),crossoverLine.end());

    if(crossoverLine.size()%2==1)
        crossoverLine.pop_back();

    for(ushort i=0;i<crossoverLine.size()/2;i++) {
        ushort crossoverIdx=randi(1,population[0].cols()-1);
        ushort A=crossoverLine[2*i];
        ushort B=crossoverLine[2*i+1];
        population[A].leftCols(crossoverIdx).swap(
                    population[B].leftCols(crossoverIdx)
                    );
    }

}

void GlassBuilder::mutate() {
    ushort maxMutateTimes=std::max(1.0,ceil(mutateIntense*mutatePoints.size()));
    if(generations*2>=maxGeneration)maxMutateTimes=1;
    for(ushort i=0;i<popSize;i++) {
        if(i==eliteIndex)continue;

        if(randD()<=mutateProb)
            //qDebug()<<"变异"<<maxMutateTimes<<"次";
            for(ushort mutateTimes=0;
                mutateTimes<maxMutateTimes;
                mutateTimes++) {

                uint mutateIdx=randi(0,mutatePoints.size()-1);
                TokiPos point=mutatePoints[mutateIdx];
                population[i](TokiRow(point),TokiCol(point))=!population[i](TokiRow(point),TokiCol(point));
            }

    }
}

void GlassBuilder::run() {
    ushort failTimes=0;
    int lastFitness=-10000000;
    generations=0;
    emit progressRangeSet(0,maxGeneration,0);
    while(true) {
        caculateAll();
        select();
        generations++;
        if(generations%reportRate==0) {
            emit progressAdd(reportRate);
            emit keepAwake();
        }
        qDebug()<<"第"<<generations<<"代,最高适应度"<<fitness[eliteIndex];
        if(lastFitness==fitness[eliteIndex])
            failTimes++;
        else
            failTimes=0;
        lastFitness=fitness[eliteIndex];
        crossover();
        mutate();

        if(generations>maxGeneration||failTimes>=maxFailTimes)
            break;
    }
    emit progressRangeSet(0,maxGeneration,maxGeneration);
    caculateAll();
    select();
}

*/
