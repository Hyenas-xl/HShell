#ifndef BASEPORT_H
#define BASEPORT_H

#include <QByteArray>
#include <QIODevice>
#include <QObject>

class BasePort :public QObject
{
    Q_OBJECT
public:
    virtual QByteArray readAll() = 0;
    virtual void write(const QByteArray &data) = 0;
    virtual bool open(QIODevice::OpenMode mode) = 0;
    virtual void close() = 0;
    virtual bool isOpen() = 0;

signals:
    void readyRead();
};

#endif // BASEPORT_H
