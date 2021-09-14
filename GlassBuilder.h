#ifndef GLASSBUILDER_H
#define GLASSBUILDER_H
#include <Eigen/Dense>
//#define WITH_QT
using namespace Eigen;
#ifdef WITH_QT
#include <QObject>
class GlassBuilder:public QObject
{
    Q_OBJECT
#else
class GlassBuilder
{
#endif
public:
    GlassBuilder();
};

#endif // GLASSBUILDER_H
