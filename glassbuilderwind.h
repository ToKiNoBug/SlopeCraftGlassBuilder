#ifndef GLASSBUILDERWIND_H
#define GLASSBUILDERWIND_H

#include <QMainWindow>
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
};
#endif // GLASSBUILDERWIND_H
