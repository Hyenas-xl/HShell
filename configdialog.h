#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include "serialform.h"
#include <baseport.h>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

private slots:
    void currentIndexChanged(QString name);
    void accept();

signals:
    void postPort(BasePort *port);


private:
    Ui::ConfigDialog *ui;
    SerialForm *mSerialForm = NULL;
};

#endif // CONFIGDIALOG_H
