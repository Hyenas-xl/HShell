/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "console.h"

#include <QScrollBar>

#include <QtCore/QDebug>
#include <QTextBlock>
#include <QTextCodec>
#include <QApplication>

Console::Console(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(false)
{
    document()->setMaximumBlockCount(200);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    mHistoryCommand = new HistoryCommand;
}

void Console::putData(const QByteArray &data)
{
    QTextCodec *tc = QTextCodec::codecForName("UTF8");
    QString value =tc->toUnicode(data);
    insertPlainText(QString(value));

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Console::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void Console::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Return:
        sendCommand();
        break;
    case Qt::Key_Up:
        loadHistoryCommand(true);
        break;
    case Qt::Key_Down:
        loadHistoryCommand(false);
        break;
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    {
        QString line = document()->lastBlock().text();
//        qDebug() << line.length() << " start index:" << startIndex();
        if(line.length() <= startIndex()){
            break;
        }
    }
//    case Qt::Key_Right:
    default:
        if (localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
//        emit getData(e->text().toLocal8Bit());
    }
}

int Console::startIndex(){
    QString line = document()->lastBlock().text();
    int idx = 0;
    int idx1 = line.indexOf('$');
    int idx2 = line.indexOf('#');
    if(idx1 != -1 && idx2 != -1){
        idx = idx1 > idx2 ? idx2 : idx1;
    }else if( idx1 != -1 && idx2 == -1){
        idx = idx1;
    }else if( idx1 == -1 && idx2 != -1){
        idx = idx2;
    }else{
        idx = line.indexOf(':');
        if(idx != -1){
            return idx+2;
        }
        return 0;
    }

    return idx+2;
}

void Console::sendCommand(){
    mHistoryStep = -1;
    QString line = document()->lastBlock().text();
    QString command = QString("%1\r").arg(line.mid(startIndex()));
    emit getData(command.toUtf8());
    if(line != NULL){
        if(!line.isEmpty()){
            line = line.mid(startIndex()).trimmed();
            if(!line.isEmpty()){
                qDebug() << "Add command : " << line;
                mHistoryCommand->addCommand(line);
            }
        }

    }
}

void Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Console::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}

void Console::loadHistoryCommand(bool history){
    mHistoryStep += history? 1: -1;
    if(mHistoryStep < -1){
        mHistoryStep = -1;
    }
    if(mHistoryStep >= 0){
        QString command = mHistoryCommand->lastCommand(mHistoryStep);
        qDebug() << "commond: " << command  << " mHistoryStep:" << mHistoryStep;
        if(command != NULL){
            textCursor().beginEditBlock();
            QString line = document()->lastBlock().text();
            int num = line.length()-startIndex();
            qDebug() << line  << " " << num;
            while(num-->0){
                textCursor().deletePreviousChar();
            }
            textCursor().endEditBlock();
            insertPlainText(command);
        }
    }
}


QString HistoryCommand::lastCommand(int start){
    if(mCommands.size() == 0){
        return NULL;
    }
    if(mCommands.size() > start){
        return mCommands.value(mCommands.size() - start -1);
    }else{
        QApplication::beep();
        return mCommands.value(0);
    }
}

void HistoryCommand::addCommand(QString command){
    mCommands << command;
}
