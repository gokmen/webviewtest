#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSslConfiguration sslCfg = QSslConfiguration::defaultConfiguration();
    QList<QSslCertificate> ca_list = sslCfg.caCertificates();
    QList<QSslCertificate> ca_new = QSslCertificate::fromData("CaCertificates");
    ca_list += ca_new;

    sslCfg.setCaCertificates(ca_list);
    sslCfg.setProtocol(QSsl::AnyProtocol);
    QSslConfiguration::setDefaultConfiguration(sslCfg);

    connect(ui->webView->page()->networkAccessManager(),
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                this,
                SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> & )));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(LoadURL()));
}

void Widget::LoadURL()
{
    qDebug() << "Loading: https://graph.facebook.com/btaylor";
    ui->webView->load(QUrl("https://graph.facebook.com/btaylor"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist)
{
    qDebug() << "---frmBuyIt::sslErrorHandler: ";
    foreach (QSslError err, errlist)
        qDebug() << "ssl error: " << err;
    qnr->ignoreSslErrors();
}
