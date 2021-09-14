#include "glassbuilderwind.h"
#include "ui_glassbuilderwind.h"

GlassBuilderWind::GlassBuilderWind(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlassBuilderWind)
{
    ui->setupUi(this);
}

GlassBuilderWind::~GlassBuilderWind()
{
    delete ui;
}

