#ifndef GLASSBUILDERWIND_H
#define GLASSBUILDERWIND_H

#include <QMainWindow>
#include <QImage>
#include "GlassBuilder.h"
QT_BEGIN_NAMESPACE
namespace Ui { class GlassBuilderWind; }
QT_END_NAMESPACE



class GlassBuilderWind : public QMainWindow
{
    Q_OBJECT

public:
    GlassBuilderWind(QWidget *parent = nullptr);
    ~GlassBuilderWind();

private:
    Ui::GlassBuilderWind *ui;
    GlassBuilder * algo;
    TokiMap raw;
    TokiMap builded;
};

QImage EImage2QImage(const EImage & ei,ushort scale);
#endif // GLASSBUILDERWIND_H
