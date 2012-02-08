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

#define DICT_SERVER_IP 127.0.0.1
#define DICT_SERVER_PORT 2626

#include "qtdictapp.h"


/**
* Constructor that run the progeam
*
* @param parent parent element where to apply Qtwidget
*/
qtDictApp::qtDictApp(QWidget *parent)
    : QWidget(parent)
{   

    main_layout = new QStackedLayout();

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

    //SetupUI
    main_layout->setCurrentIndex(WELCOME_SCREEN_ID);
    this->setLayout(main_layout);
    //launch machine
    machine.setInitialState(welcome_state);
    machine.start();


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

void qtDictApp::createQueryState(){}
void qtDictApp::createProcessingState(){}
void qtDictApp::createResultState(){}


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
    this->setLayout(result_screen);
    main_layout->setCurrentIndex(RESULT_SCREEN_ID);
}

qtDictApp::~qtDictApp()
{

}
