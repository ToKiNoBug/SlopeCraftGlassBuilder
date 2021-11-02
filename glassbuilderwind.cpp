#include "glassbuilderwind.h"
#include "ui_glassbuilderwind.h"

GlassBuilderWind::GlassBuilderWind(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlassBuilderWind)
{
    ui->setupUi(this);

    algo=new PrimGlassBuilder;

    connect(algo,&PrimGlassBuilder::progressRangeSet,
            this,&GlassBuilderWind::progressRangeSet);
    connect(algo,&PrimGlassBuilder::progressAdd,
            this,&GlassBuilderWind::progressAdd);
    connect(algo,&PrimGlassBuilder::keepAwake,
            this,&GlassBuilderWind::keepAwake);

    on_refresh_clicked();
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
    std::clock_t curTime=std::clock();
    glassMap result=algo->makeBridge(raw,&builded);
    std::cerr<<"Time cost : "
            <<1000.0*double(std::clock()-curTime)/CLOCKS_PER_SEC<<"ms"<<std::endl;
    ui->after->setPixmap(QPixmap::fromImage(
                             EImage2QImage(TokiMap2EImage(builded),1)));
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

void GlassBuilderWind::on_refresh_clicked()
{
    //short targets[][2]={{0,0},{60,6},{5,34},{30,60},{6,60},{50,40},{20,30},{20,3}};
    raw.setZero(512,512);

    Eigen::ArrayXXd randD(raw.rows(),raw.cols());
    randD.setRandom();
    randD=randD.abs();

    for(ushort r=0;r<raw.rows();r++)
        for(ushort c=0;c<raw.cols();c++) {
            if(randD(r,c)<1.0/128)
                raw(r,c)=PrimGlassBuilder::blockType::target;
        }

    raw.block(100,200,120,50)=PrimGlassBuilder::blockType::target;

    QImage temp=EImage2QImage(TokiMap2EImage(raw),1);
    ui->before->setPixmap(QPixmap::fromImage(temp));
    /*for(ushort i=0;i<sizeof(targets)/(2*sizeof(short));i++) {
        raw(targets[i][0],targets[i][1])=GlassBuilder::blockType::target;
    }*/
}

