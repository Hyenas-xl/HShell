#ifndef FILETOOL_H
#define FILETOOL_H

#include <QObject>
#include "config.h"

class FileTool : public QObject
{
    Q_OBJECT
public:
    explicit FileTool(QObject *parent = 0);

    static void saveConnections(QString file,Setting setting[],int num);
    static void loadConnections(QString file);
signals:

public slots:
};

#endif // FILETOOL_H
