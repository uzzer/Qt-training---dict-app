/**
 * @file
 * @author  Mihhail Sidorin <msidorin@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This is main widget of Dictionary
 */

#define WELCOME_SCREEN_ID 0
#define CONNECT_SCREEN_ID 1
#define QUERY_SCREEN_ID 2
#define PROCESSING_SCREEN_ID 3
#define RESULT_SCREEN_ID 4

#define DICT_SERVER_PORT 2628

#include "qtdictapp.h"


/**
* Constructor that run the progeam
*
* @param parent parent element where to apply Qtwidget
*/
qtDictApp::qtDictApp(QWidget *parent)
    : QWidget(parent)
{   

    //Create base objects
    main_layout = new QStackedLayout();
    client = new QTcpSocket();

    //Describing states
    processing_state = new QState(); machine.addState(processing_state);
    connecting_state = new QState(); machine.addState(connecting_state);
    query_state = new QState(); machine.addState(query_state);
    result_state = new QState(); machine.addState(result_state);
    welcome_state = new QState(); machine.addState(welcome_state);

    //Implement states
    //ORDER IS IMPORTANT
    createWelcomeState();
    createConnectionState();
    createQueryState();
    createProcessingState();
    createResultState();

    connecting_state->addTransition(this,SIGNAL(goToQueryState()),query_state);
    connecting_state->addTransition(this,SIGNAL(goToWelcomeState()),welcome_state);
    query_state->addTransition(this,SIGNAL(goToWelcomeState()),welcome_state);

    //SetupUI
    main_layout->setCurrentIndex(WELCOME_SCREEN_ID);
    this->setLayout(main_layout);
    //launch machine
    machine.setInitialState(welcome_state);
    machine.start();

    //client setup
    connect(client, SIGNAL(connected()),this, SLOT(onClientConnected()));
    connect(client,SIGNAL(readyRead()),this,SLOT(readClient()));
    connect(client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(handleClientError(QAbstractSocket::SocketError)));
}

/**
*   Implement welcome state
*/
void qtDictApp::createWelcomeState(){
    qDebug()<<"welcome state creation";
    //UI
    QVBoxLayout *screen = new QVBoxLayout();
    QLabel *text = new QLabel("QtDictApp");
    screen->addWidget(text);
    server_host = new QComboBox;
    server_host->addItem("127.0.0.1");
    server_host->addItem("dict.org");
    server_host->addItem("dict1.us.dict.org");
    server_host->addItem("dict.saugus.net");
    server_host->addItem("dictd.xdsl.by");
    screen->addWidget(server_host);
    connect_button = new QPushButton("Connect");
    screen->addWidget(connect_button);
    //Add page to Stack
    QWidget *wrapper = new QWidget();
    wrapper->setLayout(screen);
    this->main_layout->addWidget(wrapper);
    //Add machine functional
    connect(welcome_state, SIGNAL(entered()), this, SLOT(initWelcomeState()));
    welcome_state->addTransition(connect_button, SIGNAL(clicked()), connecting_state);
}

/**
*   Implement connecting state
*/
void qtDictApp::createConnectionState(){
    qDebug()<<"conencting state creation";
    //UI
    QVBoxLayout *screen = new QVBoxLayout();
    QLabel *text = new QLabel("Connecting ...");
    screen->addWidget(text);
    cancelconnect_button = new QPushButton("Cancel");
    screen->addWidget(cancelconnect_button);
    //Add page to Stack
    QWidget *wrapper = new QWidget();
    wrapper->setLayout(screen);
    this->main_layout->addWidget(wrapper);
    //Add machine functional
    connect(connecting_state, SIGNAL(entered()), this, SLOT(initConnectState()));
    connecting_state->addTransition(cancelconnect_button, SIGNAL(clicked()), welcome_state);
}

/**
*   Implement query state
*/
void qtDictApp::createQueryState(){
    qDebug()<<"query state creation";
    //UI
    QVBoxLayout *screen = new QVBoxLayout();
    QLabel *text = new QLabel("Query state");
    screen->addWidget(text);
    queryfiled = new QLineEdit();
    screen->addWidget(queryfiled);
    send_query_button = new QPushButton("Query");
    screen->addWidget(send_query_button);
    cancelconnect2_button = new QPushButton("Cancel");
    screen->addWidget(cancelconnect2_button);
    //Add page to Stack
    QWidget *wrapper = new QWidget();
    wrapper->setLayout(screen);
    this->main_layout->addWidget(wrapper);
    //Add Query state functional
    connect(send_query_button,SIGNAL(clicked()),this,SLOT(startQuery()));
    //Add machine functional part
    connect(query_state, SIGNAL(entered()), this, SLOT(initQueryState()));
    query_state->addTransition(send_query_button, SIGNAL(clicked()), processing_state);
    query_state->addTransition(cancelconnect2_button, SIGNAL(clicked()), welcome_state);
}

void qtDictApp::createProcessingState(){
    qDebug()<<"processing state creation";
    //UI
    QVBoxLayout *screen = new QVBoxLayout();
    QLabel *text = new QLabel("Processing query ...");
    screen->addWidget(text);
    cancelconnect3_button = new QPushButton("Cancel");
    screen->addWidget(cancelconnect3_button);
    //Add page to Stack
    QWidget *wrapper = new QWidget();
    wrapper->setLayout(screen);
    this->main_layout->addWidget(wrapper);
    //Add machine functional
    connect(processing_state, SIGNAL(entered()), this, SLOT(initProcessingState()));
    processing_state->addTransition(cancelconnect3_button, SIGNAL(clicked()), welcome_state);
    processing_state->addTransition(client,SIGNAL(readyRead()),result_state);
}
void qtDictApp::createResultState(){
    qDebug()<<"result state creation";
    //UI
    QVBoxLayout *screen = new QVBoxLayout();
    QLabel *text = new QLabel("Result");
    screen->addWidget(text);
    resultarea = new  QTextEdit("Result area");
    screen->addWidget(resultarea);
    cancelconnect4_button = new QPushButton("Home");
    screen->addWidget(cancelconnect4_button);
    //Add page to Stack
    QWidget *wrapper = new QWidget();
    wrapper->setLayout(screen);
    this->main_layout->addWidget(wrapper);
    //Add machine functional
    connect(result_state, SIGNAL(entered()), this, SLOT(initResultState()));
    result_state->addTransition(cancelconnect4_button, SIGNAL(clicked()), query_state);
}


/**
* SLOT to intialize welcome state on activated
*/
void qtDictApp::initWelcomeState(){
    qDebug()<<"welcome state entered";
    main_layout->setCurrentIndex(WELCOME_SCREEN_ID);
}

/**
* SLOT to intialize connect state on activated
*/
void qtDictApp::initConnectState(){
    qDebug()<<"connect state entered";
    main_layout->setCurrentIndex(CONNECT_SCREEN_ID);
    connectToServer();
}

/**
* SLOT to intialize query state on activated
*/
void qtDictApp::initQueryState(){
    qDebug()<<"query state entered";
    main_layout->setCurrentIndex(QUERY_SCREEN_ID);
}

/**
* SLOT to intialize processing state on activated
*/
void qtDictApp::initProcessingState(){
    qDebug()<<"processing state entered";
    main_layout->setCurrentIndex(PROCESSING_SCREEN_ID);
}

/**
* SLOT to intialize result state on activated
*/
void qtDictApp::initResultState(){
    qDebug()<<"result state entered";
    main_layout->setCurrentIndex(RESULT_SCREEN_ID);
}


void qtDictApp::connectToServer(){
    qDebug()<<"connecting...";
    if(client->ConnectedState!=0){
       client->disconnectFromHost();
       //client->disconnect();
    }
    qDebug()<<"connecting to " <<server_host->currentText();
    client->connectToHost(server_host->currentText(), DICT_SERVER_PORT);
}

void qtDictApp::onClientConnected(){
    qDebug()<<"client connected";
    emit(goToQueryState());
    //client->write("DEFINE ! penguin");

}

void qtDictApp::readClient(){
    QByteArray answer = client->readAll();
    QString an(answer);
    resultarea->setText(answer);
    qDebug()<<"S:"<<an;
}

void qtDictApp::sendMessage(QString msg){
    qDebug()<<"client says C: DEFINE !"<<msg;
    client->write("DEFINE ! "+msg.toAscii());
    client->flush();
}

void qtDictApp::handleClientError(QAbstractSocket::SocketError socketError){
    qDebug()<<client->errorString();
    switch (socketError) {
         case QAbstractSocket::RemoteHostClosedError:
                emit(goToWelcomeState());
             break;
         case QAbstractSocket::HostNotFoundError:
                emit(goToWelcomeState());
             break;
         case QAbstractSocket::ConnectionRefusedError:
                emit(goToWelcomeState());
             break;
         default:
            break;
         }

}

void qtDictApp::startQuery(){
    sendMessage(queryfiled->text());
}



qtDictApp::~qtDictApp()
{

}
