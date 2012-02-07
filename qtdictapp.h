#ifndef QTDICTAPP_H
#define QTDICTAPP_H

#include <QtGui/QWidget>
#include <QObject>

class qtDictApp : public QWidget
{
    Q_OBJECT

public:
    qtDictApp(QWidget *parent = 0);
    ~qtDictApp();
};

#endif // QTDICTAPP_H
