#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QKeyEvent>
#include "connectdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createToolBar();

public slots:
    void serialOPerate();
    void serialData();
    void writeData(const QByteArray &data);

    void triggerPort(BasePort *port);

private:
    Ui::MainWindow *ui;
    bool mIsCommand = false;
    int mLength = -1;
    ConnectDialog *connectDialog = NULL;
    BasePort *mPort = NULL;
};

#endif // MAINWINDOW_H
