#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "configdialog.h"

namespace Ui {
class ConnectDialog;
}


class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

public slots:
    void runActions();
    void postPort(BasePort *port);

signals:
    void triggerPort(BasePort *port);

private:
    void createToolBar();
    Ui::ConnectDialog *ui;

    ConfigDialog *mConfigDialog = NULL;
};

#endif // CONNECTDIALOG_H
