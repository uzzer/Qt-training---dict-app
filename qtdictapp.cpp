#include "qtdictapp.h"



qtDictApp::qtDictApp(QWidget *parent)
    : QWidget(parent)
{   

    //Weclome screen
    welcome_screen = new QVBoxLayout();
    QLabel *welcome_text = new QLabel("QtDictApp");
    QPushButton *connect_button = new QPushButton("Connect");
    welcome_screen->addWidget(welcome_text);
    welcome_screen->addWidget(connect_button);

    //Processing
    processing_screen = new QVBoxLayout();
    QLabel *processing_text = new QLabel("processing...");
    QPushButton *cancel_button = new QPushButton("Cancel");
    processing_screen->addWidget(processing_text);
    processing_screen->addWidget(cancel_button);

    //Result screen
    result_screen = new QVBoxLayout();
    QLabel *result_text = new QLabel("this is result");
    QPushButton *towelcome_button = new QPushButton("Back to welcome");
    result_screen->addWidget(result_text);
    result_screen->addWidget(towelcome_button);

    QStateMachine machine;

    QState *welcome_state = new QState(); machine.addState(welcome_state);
    QState *processing_state = new QState(); machine.addState(processing_state);
    QState *result_state = new QState(); machine.addState(result_state);

    connect(welcome_state, SIGNAL(entered()), this, SLOT(initWelcomeState()));
    welcome_state->addTransition(connect_button, SIGNAL(clicked()), processing_state);
    connect(processing_state, SIGNAL(entered()), this, SLOT(initProcessingState()));
    processing_state->addTransition(cancel_button, SIGNAL(clicked()), welcome_state);
    connect(result_state, SIGNAL(entered()), this, SLOT(initResultState()));
    result_state->addTransition(towelcome_button, SIGNAL(clicked()), welcome_state);
    connect(processing_state, SIGNAL(entered()), this, SLOT(initWelcomeState()));

    machine.setInitialState(welcome_state);
    machine.start();

}

void qtDictApp::initWelcomeState(){
    qDebug()<<"welcome state entered";
    this->setLayout(welcome_screen);
}
void qtDictApp::initProcessingState(){
    qDebug()<<"processing state entered";
    this->setLayout(processing_screen);
}
void qtDictApp::initResultState(){
    qDebug()<<"result state entered";
    this->setLayout(result_screen);
}

qtDictApp::~qtDictApp()
{

}
