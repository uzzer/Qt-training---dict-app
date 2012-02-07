#include <QtGui/QApplication>
#include "qtdictapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtDictApp w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
