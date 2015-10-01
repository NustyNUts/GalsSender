#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QTextStream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    QFile* coordsFile;
    QFile* galsFile;
    QString fileCoordsName;
    QString fileGalsName;
    QTcpSocket* socket;
    QTimer* rcTimer;
    QTimer* coordsSendTimer;
    QTimer* galsSendTimer;
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_cordsSendButton_clicked();

    void on_toolButton_clicked();

    void connected();

    void tryReconnect();

    void openConnection();

    void sendCoords();

    void sendGals();

    void on_toolButton_2_clicked();

    void on_GalsSendButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
