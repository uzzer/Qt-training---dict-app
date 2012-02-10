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
 * This is header of main widget of Dictionary
 */

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
#include <QLineEdit>
#include <QtNetwork>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QDataStream>

class qtDictApp : public QWidget
{
    Q_OBJECT

    QStateMachine machine;
    QStackedLayout *main_layout;

    QState *welcome_state;
        QPushButton *connect_button;

    QState *connecting_state;
        QPushButton *cancelconnect_button;

    QState *query_state;
        QLineEdit *queryfiled;
        QPushButton *send_query_button;
        QPushButton *cancelconnect2_button;

    QState *processing_state;

    QState *result_state;

    QTcpSocket *client;

public:
    qtDictApp(QWidget *parent = 0);
    ~qtDictApp();
    //stateMachine
    void createWelcomeState();
    void createConnectionState();
    void createQueryState();
    void createProcessingState();
    void createResultState();
    //DICT
    void connectToServer();
    void sendMessage(QString msg);


public slots:
    //stateMachine
    void initWelcomeState();
    void initConnectState();
    void initQueryState();
    void initProcessingState();
    void initResultState();
    //DICT
    void onClientConnected();
    void readClient();
    void handleClientError(QAbstractSocket::SocketError);

signals:
    void goToQueryState();
    void goToWelcomeState();
};

#endif // QTDICTAPP_H
