#include "glassbuilderwind.h"

#include <QApplication>
#include <iostream>

using namespace Eigen;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    Array<uchar,Dynamic,Dynamic> test;

    test.setOnes(3,4);

    std::cout<<(int)test.sum()<<std::endl;
    std::cout<<test.cast<int>()<<std::endl;*/

    GlassBuilderWind w;
    w.show();
    return a.exec();
}
