#include "videolistelement.h"
#include "ui_videolistelement.h"
#include <QNetworkReply>
#include "YtDlpWrapper/YoutubeVideo.h"
#include <QNetworkAccessManager>
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

    // QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    // connect(nam, &QNetworkAccessManager::finished, this, &VideoListElement::downloadFinished);
    // const QUrl url = QUrl("https://i.imgur.com/YuLedcu.png");
    // QNetworkRequest request(url);
    // nam->get(request);

}


void VideoListElement::downloadThumbnailFinished(QNetworkReply *reply)
{
    QPixmap pm;
    pm.loadFromData(reply->readAll());
    ui->label->setPixmap(pm);
}

void VideoListElement::setup(YoutubeVideo data)
{
    this->setTitle(data.getName());
    this->setLength(data.getDuration());
    this->setThumbnail(data.getThumbnail());
}

void VideoListElement::setTitle(std::string title)
{
    ui->videoTitle->setText( QString::fromUtf8(title));
}
void VideoListElement::setThumbnail(std::string url)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    connect(nam, &QNetworkAccessManager::finished, this,&VideoListElement::downloadThumbnailFinished );
    const QUrl qurl = QUrl( QString::fromUtf8(url));
    QNetworkRequest request(qurl);
    nam->get(request);
}
void VideoListElement::setAudio()
{

}
void VideoListElement::setVideo()
{

}
void VideoListElement::addOrRemoveSponsorBlockElemnt(std::string element)
{

}
void VideoListElement::setLength(std::string length)
{
    qDebug()<<"settting legth: "<<length;
    QTime time = QDateTime::fromString( QString::fromUtf8(length),"m:ss").time();
    qDebug()<<"time converted: "<<time;
    ui->timeEnd->setTime(time);
    ui->sliderEnd->setMaximum(time.second()+time.minute()+time.hour());
     ui->sliderEnd->setValue(time.second()+time.minute()+time.hour());
     ui->sliderStart->setMaximum(time.second()+time.minute()+time.hour());
}



void VideoListElement::on_timeEnd_userTimeChanged(const QTime &time)
{

}

