#include "PrimGlassBuilder.h"

const int INF=0x7FFFFFFF;
const ARGB airColor=qRgb(255,255,255);
const ARGB targetColor=qRgb(0,0,0);
const ARGB glassColor=qRgb(128,128,128);
const ushort reportRate=50;

edge::edge() {
    beg=TokiRC(0,0);
    end=TokiRC(0,0);
    lengthSquare=0;
}

edge::edge(TokiPos A,TokiPos B) {
    ushort r1=TokiRow(A),c1=TokiCol(A);
    ushort r2=TokiRow(B),c2=TokiCol(B);
    beg=A;
    end=B;
    int rowSpan=r1-r2;
    int colSpan=c1-c2;
    lengthSquare=(rowSpan*rowSpan+colSpan*colSpan);
}

edge::edge(ushort r1,ushort c1,ushort r2,ushort c2) {
    beg=TokiRC(r1,c1);
    end=TokiRC(r2,c2);
    int rowSpan=r1-r2;
    int colSpan=c1-c2;
    lengthSquare=(rowSpan*rowSpan+colSpan*colSpan);
}

bool edge::connectWith(TokiPos P) const {
    return (beg==P)||(end==P);
}

void edge::drawEdge(glassMap & map) const {
    if(lengthSquare<=2)return;
    float length=sqrt(lengthSquare);
    Vector2f startPoint(TokiRow(beg),TokiCol(beg));
    Vector2f endPoint(TokiRow(end),TokiCol(end));
    Vector2f step=(endPoint-startPoint)/ceil(2.0*length);
    Vector2f cur;
    int stepCount=ceil(2.0*length);
    int r,c;
    for(int i=1;i<stepCount;i++) {
        cur=i*step+startPoint;
        r=floor(cur(0));
        c=floor(cur(1));
        if(r>=0&&r<map.rows()&&c>=0&&c<map.cols()) {
            map(r,c)=1;
            continue;
        }
        r=ceil(cur(0));
        c=ceil(cur(1));
        if(r>=0&&r<map.rows()&&c>=0&&c<map.cols())
            map(r,c)=1;
    }
}

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
    edges.clear();
    tree.clear();
    addEdgesToGraph();
    runPrim();

    glassMap result(_targetMap.rows(),_targetMap.cols());
    result.setZero();

    for(auto it=tree.cbegin();it!=tree.cend();it++)
        it->drawEdge(result);

    if(walkable!=nullptr)
        *walkable=result;

    for(auto it=targetPoints.cbegin();it!=targetPoints.cend();it++) {
        result(TokiRow(*it),TokiCol(*it))=0;
        walkable->operator()(TokiRow(*it),TokiCol(*it))=GlassBuilder::blockType::target;
    }
    return result;
}


void PrimGlassBuilder::addEdgesToGraph() {
    edges.clear();

    for(index i=0;i<targetPoints.size();i++)
        for(index j=i+1;j<targetPoints.size();j++) {
            edges.push_back(edge(targetPoints[i],targetPoints[j]));
        }

    qDebug("插入了所有的边");
}


void PrimGlassBuilder::runPrim() {
    tree.clear();
    //TokiPos x,y;
    std::unordered_set<TokiPos> found,unsearched;
    found.clear();
    unsearched.clear();
    found.emplace(targetPoints[0]);

    for(auto i=targetPoints.cbegin();;) {
        i++;
        if(i==targetPoints.cend())
            break;

        unsearched.emplace(*i);
    }

    while(!unsearched.empty()) {
        auto selectedEdge=edges.begin();

        //从列表中第一个元素开始搜索第一个可行边
        for(;;) {

            if(selectedEdge==edges.end()) {
                qDebug("错误！找不到可行边");
                break;
            }
            TokiPos z=selectedEdge->beg;
            TokiPos w=selectedEdge->end;
            bool fz=found.find(z)!=found.end();
            bool fw=found.find(w)!=found.end();

            if(fz&&fw) {
                selectedEdge=edges.erase(selectedEdge);//如果一条边的首尾都是已经被连接到的点，那么移除这条边
                continue;
            }
            bool uz=unsearched.find(z)!=unsearched.end();
            bool uw=unsearched.find(w)!=unsearched.end();
            if((fz&&uw)||(fw&&uz)) {
                //找到了第一条可行的边
                break;
            }
        }

        //从找到的第一条边开始，寻找长度最小的可行边
        for(auto it=selectedEdge;it!=edges.end();it++) {
            TokiPos x=it->beg,y=it->end;
            bool fx=found.find(x)!=found.end();
            bool fy=found.find(y)!=found.end();
            if(fx&&fy) {
                it=edges.erase(it);//如果一条边的首尾都是已经被连接到的点，那么移除这条边
                continue;
            }
            bool ux=unsearched.find(x)!=unsearched.end();
            bool uy=unsearched.find(y)!=unsearched.end();

            if((fx&&uy)||(fy&&ux)) {
                if(it->lengthSquare<selectedEdge->lengthSquare)
                    selectedEdge=it;
            }

        }

        //将选中边装入树中，
        //并从集合unsearched中删除选中边的两个端点，
        //向集合found中加入选中边的两个端点
        {
            TokiPos x=selectedEdge->beg;
            TokiPos y=selectedEdge->end;
            found.emplace(x);
            found.emplace(y);
            unsearched.erase(x);
            unsearched.erase(y);
            tree.push_back(*selectedEdge);
        }
    }
    qDebug("prim算法完毕");
}

EImage TokiMap2EImage(const TokiMap& tm) {
    EImage result(tm.rows(),tm.cols());
    result.setConstant(airColor);
    for(ushort r=0;r<tm.rows();r++)
        for(ushort c=0;c<tm.cols();c++) {
            if(tm(r,c)==1)
                result(r,c)=glassColor;
            if(tm(r,c)>1)
                result(r,c)=targetColor;
        }
    return result;
}
