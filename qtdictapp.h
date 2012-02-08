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

class qtDictApp : public QWidget
{
    Q_OBJECT

    QStateMachine machine;
    QStackedLayout *main_layout;

    //QWidget *welcome_wrapper;
    QVBoxLayout *welcome_screen;
        QPushButton *connect_button;
    QState *welcome_state;

    QVBoxLayout *connecting_screen;
        QPushButton *cancelconnect_button;
    QState *connecting_state;

    QVBoxLayout *query_screen;
    QState *query_state;

    QVBoxLayout *processing_screen;
    QState *processing_state;

    QVBoxLayout *result_screen;
    QState *result_state;



public:
    qtDictApp(QWidget *parent = 0);
    ~qtDictApp();
    void createWelcomeState();
    void createConnectionState();
    void createQueryState();
    void createProcessingState();
    void createResultState();

public slots:
    void initWelcomeState();
    void initConnectState();
    void initQueryState();
    void initProcessingState();
    void initResultState();
};

#endif // QTDICTAPP_H
