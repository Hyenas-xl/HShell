#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>

class HistoryCommand;

class Console : public QPlainTextEdit
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit Console(QWidget *parent = 0);

    void putData(const QByteArray &data);

    void setLocalEchoEnabled(bool set);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    void sendCommand();
    void loadHistoryCommand(bool history);

    int startIndex();

    bool localEchoEnabled;
    HistoryCommand *mHistoryCommand;
    int mHistoryStep = -1;
};

class HistoryCommand{

public:
    QString lastCommand(int start);
    void addCommand(QString command);

private:
    QList<QString> mCommands;
};

#endif // CONSOLE_H
