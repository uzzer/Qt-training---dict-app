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
