#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QToolBar>
#include <QAction>

#include <QDebug>

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    createToolBar();
}

ConnectDialog::~ConnectDialog()
{
    if(mConfigDialog != NULL){
        delete mConfigDialog;
    }
    delete ui;
}

void ConnectDialog::createToolBar(){
    QToolBar *bar = new QToolBar(tr("tool"),this);
    bar->setIconSize(QSize(20,20));

    QAction *connectAction = new QAction(bar);
    connectAction->setToolTip("Connect");
    connectAction->setObjectName("Connect");
    connectAction->setIcon(QIcon(":images/images/connect.png"));
    bar->addAction(connectAction);

    QAction *quickAction = new QAction(bar);
    quickAction->setToolTip("Quick Connect");
    quickAction->setObjectName("QuickConnect");
    quickAction->setIcon(QIcon(":images/images/quick_connect.png"));
    bar->addAction(quickAction);

    connect(connectAction,SIGNAL(triggered()),this,SLOT(runActions()));
    connect(quickAction,SIGNAL(triggered()),this,SLOT(runActions()));

}

void ConnectDialog::runActions(){
    QAction *action = qobject_cast<QAction*>(sender());
    qDebug() << action->objectName();
    if(action->objectName() == "QuickConnect"){
        mConfigDialog = new ConfigDialog(this);
        connect(mConfigDialog,SIGNAL(postPort(BasePort*)),this,SLOT(postPort(BasePort*)));
        mConfigDialog->show();
    }else if(action->objectName() == "Connect"){

    }
}

void ConnectDialog::postPort(BasePort *port){
    accept();
    emit triggerPort(port);
}
