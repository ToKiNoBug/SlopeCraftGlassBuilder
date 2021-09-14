#include "glassbuilderwind.h"
#include "ui_glassbuilderwind.h"

GlassBuilderWind::GlassBuilderWind(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlassBuilderWind)
{
    ui->setupUi(this);

    algo=new GlassBuilder;

    raw.setZero(64,64);
    short targets[][2]={{0,0},{60,6},{5,34},{30,60},{6,60},{50,40},{20,30},{20,3}};

    for(ushort r=0;r<raw.rows();r++)
        for(ushort c=0;c<raw.cols();c++) {
            if(randD()<1.0/32)
                raw(r,c)=GlassBuilder::blockType::target;
        }


    /*for(ushort i=0;i<sizeof(targets)/(2*sizeof(short));i++) {
        raw(targets[i][0],targets[i][1])=GlassBuilder::blockType::target;
    }*/

    QImage temp=EImage2QImage(TokiMap2EImage(raw),4);
    ui->before->setPixmap(QPixmap::fromImage(temp));

    connect(algo,&GlassBuilder::progressRangeSet,
            this,&GlassBuilderWind::progressRangeSet);
    connect(algo,&GlassBuilder::progressAdd,
            this,&GlassBuilderWind::progressAdd);
    connect(algo,&GlassBuilder::keepAwake,
            this,&GlassBuilderWind::keepAwake);
}

QImage EImage2QImage(const EImage & ei,ushort scale) {
    QImage qi(ei.cols()*scale,ei.rows()*scale,QImage::Format::Format_ARGB32);
    QRgb * CL=nullptr;
    for(int r=0;r<qi.height();r++) {
        CL=(QRgb *)qi.scanLine(r);
        for(int c=0;c<qi.width();c++)
            CL[c]=ei(r/scale,c/scale);
    }
    return qi;
}

GlassBuilderWind::~GlassBuilderWind()
{
    delete algo;
    delete ui;
}


void GlassBuilderWind::on_buildBridge_clicked() {
    glassMap result=algo->makeBridge(raw,&builded);
    ui->after->setPixmap(QPixmap::fromImage(
                             EImage2QImage(TokiMap2EImage(builded),4)));
}

void GlassBuilderWind::progressRangeSet(int min,int max,int val) {
ui->progressBar->setRange(min,max);
ui->progressBar->setValue(val);
}
void GlassBuilderWind::progressAdd(int delta) {
ui->progressBar->setValue(ui->progressBar->value()+delta);
}
void GlassBuilderWind::keepAwake() {
    QCoreApplication::processEvents();
}
