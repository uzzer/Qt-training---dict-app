#ifndef QTDICTAPP_H
#define QTDICTAPP_H

#include <QtGui/QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStateMachine>
#include <QState>
#include <QtDebug>
#include <QLayout>
#include <QLayoutItem>
#include <QStackedLayout>

class qtDictApp : public QWidget
{
    Q_OBJECT

    QStackedLayout *main_layout;
    QVBoxLayout *welcome_screen;
    QVBoxLayout *processing_screen;
    QVBoxLayout *result_screen;
    QStateMachine machine;



public:
    qtDictApp(QWidget *parent = 0);
    ~qtDictApp();

public slots:
    void initWelcomeState();
    void initProcessingState();
    void initResultState();
};

#endif // QTDICTAPP_H
