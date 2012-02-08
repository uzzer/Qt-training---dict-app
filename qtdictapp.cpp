#include "qtdictapp.h"



qtDictApp::qtDictApp(QWidget *parent)
    : QWidget(parent)
{   

    main_layout = new QStackedLayout();

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

    QWidget *welcome_wrapper = new QWidget();
    welcome_wrapper->setLayout(welcome_screen);
    QWidget *processing_wrapper = new QWidget();
    processing_wrapper->setLayout(processing_screen);
    QWidget *result_wrapper = new QWidget();
    result_wrapper->setLayout(result_screen);

    main_layout->addWidget(welcome_wrapper);
    main_layout->addWidget(processing_wrapper);
    main_layout->addWidget(result_wrapper);
    main_layout->setCurrentIndex(0);

    this->setLayout(main_layout);

    //Describing states
    QState *welcome_state = new QState(); machine.addState(welcome_state);
    QState *processing_state = new QState(); machine.addState(processing_state);
    QState *result_state = new QState(); machine.addState(result_state);

    //Connecting states

    connect(welcome_state, SIGNAL(entered()), this, SLOT(initWelcomeState()));
    welcome_state->addTransition(connect_button, SIGNAL(clicked()), processing_state);

    connect(processing_state, SIGNAL(entered()), this, SLOT(initProcessingState()));
    processing_state->addTransition(cancel_button, SIGNAL(clicked()), welcome_state);

    connect(result_state, SIGNAL(entered()), this, SLOT(initResultState()));
    result_state->addTransition(towelcome_button, SIGNAL(clicked()), welcome_state);

    //launch machine
    machine.setInitialState(welcome_state);
    machine.start();

}

void qtDictApp::initWelcomeState(){
    qDebug()<<"welcome state entered";
    main_layout->setCurrentIndex(0);
}
void qtDictApp::initProcessingState(){
    qDebug()<<"processing state entered";
    main_layout->setCurrentIndex(1);
}
void qtDictApp::initResultState(){
    qDebug()<<"result state entered";
    this->setLayout(result_screen);
    main_layout->setCurrentIndex(2);
}

qtDictApp::~qtDictApp()
{

}
