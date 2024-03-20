#include "videolistelement.h"
#include "ui_videolistelement.h"
#include <QNetworkReply>
VideoListElement::VideoListElement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoListElement)
{
    ui->setupUi(this);
}

VideoListElement::~VideoListElement()
{
    delete ui;
}

void VideoListElement::on_pushButton_5_clicked()
{

}


void VideoListElement::on_pushButton_clicked()
{
   // ui->videoThumbnail->load(QUrl::fromUserInput("https://imgur.com/a/xpJ2PqM"));

    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    connect(nam, &QNetworkAccessManager::finished, this, &VideoListElement::downloadFinished);
    const QUrl url = QUrl("https://i.imgur.com/YuLedcu.png");
    QNetworkRequest request(url);
    nam->get(request);

}


void VideoListElement::downloadFinished(QNetworkReply *reply)
{
    QPixmap pm;
    pm.loadFromData(reply->readAll());
    ui->label->setPixmap(pm);
}
