#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QNetworkReply>
#include <QSslConfiguration>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void LoadURL();
    void sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist);
    
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
