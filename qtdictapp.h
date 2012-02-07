#ifndef QTDICTAPP_H
#define QTDICTAPP_H

#include <QtGui/QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStateMachine>
#include <QtDebug>

class qtDictApp : public QWidget
{
    Q_OBJECT

    QVBoxLayout *welcome_screen;
    QVBoxLayout *processing_screen;
    QVBoxLayout *result_screen;

public:
    qtDictApp(QWidget *parent = 0);
    ~qtDictApp();

public slots:
    void initWelcomeState();
    void initProcessingState();
    void initResultState();
};

#endif // QTDICTAPP_H
