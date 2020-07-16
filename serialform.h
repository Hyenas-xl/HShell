#ifndef SERIALFORM_H
#define SERIALFORM_H

#include <QWidget>
#include "config.h"
#include <QButtonGroup>

namespace Ui {
class SerialForm;
}

class SerialForm : public QWidget
{
    Q_OBJECT

public:
    explicit SerialForm(QWidget *parent = 0);
    ~SerialForm();

    bool loadSerialSetting(SerialSetting *setting);


private:
    Ui::SerialForm *ui;
    QButtonGroup* mButtonGroup;
};

#endif // SERIALFORM_H
