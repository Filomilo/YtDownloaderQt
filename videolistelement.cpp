#include "videolistelement.h"
#include "ui_videolistelement.h"
#include <QNetworkReply>
#include "YtDlpWrapper/YoutubeVideo.h"
#include <QNetworkAccessManager>
#include <QMovie>

VideoListElement::VideoListElement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoListElement)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie(":/gifs/assets/loading.gif");
    ui->loadingCricle->setMovie(movie);
    movie->start();
    ui->loadingCricle->hide();
}

int getSecondFromTime(QTime time)
{
    return  time.second()+time.minute()*60+time.hour()*60*60;
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
    int seconds=getSecondFromTime(time);
    ui->sliderEnd->setMaximum(seconds);
     ui->sliderEnd->setValue(seconds);
     ui->sliderStart->setMaximum(seconds);
}



void VideoListElement::on_timeEnd_userTimeChanged(const QTime &time)
{

}


void VideoListElement::on_audioRadio_clicked()
{
    ui->FormatDropDown->clear();
    ui->FormatDropDown->addItem("mp3");
    ui->FormatDropDown->addItem("wav");
    ui->qualityDropDown->clear();
    ui->qualityDropDown->addItem("80");
    ui->qualityDropDown->addItem("120");
    ui->qualityDropDown->addItem("240");
    ui->qualityDropDown->addItem("360");
}


void VideoListElement::on_videoradio_clicked()
{
    ui->FormatDropDown->clear();
    ui->FormatDropDown->addItem("mp4");
    ui->FormatDropDown->addItem("mkv");
    ui->qualityDropDown->clear();
    ui->qualityDropDown->addItem("144");
    ui->qualityDropDown->addItem("240");
    ui->qualityDropDown->addItem("360");
    ui->qualityDropDown->addItem("480");
    ui->qualityDropDown->addItem("720");
    ui->qualityDropDown->addItem("1080");
}


void VideoListElement::on_sponsorDropdown_textActivated(const QString &arg1)
{
    QList<QListWidgetItem*> foundItems = ui->sponsorList->findItems(arg1, Qt::MatchExactly);

    if (!foundItems.isEmpty()) {
        qDebug() << "Found items with text" << arg1 << ":";
        for (QListWidgetItem* item : foundItems) {

            int row =  ui->sponsorList->row(item);
            ui->sponsorList->takeItem(row);
            delete item;
        }
    } else {
        ui->sponsorList->addItem(arg1);
    }
}


void VideoListElement::on_sliderStart_sliderMoved(int position)
{
    QTime a(0,0,0);
    a = a.addSecs(int(position));
    ui->timeStart->setTime(a);
    // qDebug()<<"changed start slider: "<<a;
    resolveEndTime();
}


void VideoListElement::on_sliderEnd_valueChanged(int value)
{
    QTime a(0,0,0);
    a = a.addSecs(int(value));
    ui->timeEnd->setTime(a);
    // qDebug()<<"changed start slider: "<<a;
    resolveStartTime();
}


void VideoListElement::on_timeEnd_timeChanged(const QTime &time)
{
    ui->sliderEnd->setValue(getSecondFromTime(time));
    resolveStartTime();
}


void VideoListElement::on_timeStart_userTimeChanged(const QTime &time)
{
    ui->sliderStart->setValue(getSecondFromTime(time));
    resolveEndTime();
}

void VideoListElement::resolveStartTime()
{
    int secStart=ui->sliderStart->value();
    int secEnd=ui->sliderEnd->value();
    // qDebug()<<"RESOLVE START TIMR: "<<secStart<<" "<<secEnd;
    if(secStart>secEnd)
    {
        ui->sliderStart->setValue(secEnd);
        on_sliderStart_sliderMoved(secEnd);
    }
}
void VideoListElement::resolveEndTime(){
    int secStart=ui->sliderStart->value();
    int secEnd=ui->sliderEnd->value();
    if(secStart>secEnd)
    {
        ui->sliderEnd->setValue(secStart);
        on_sliderEnd_valueChanged(secStart);
    }
}
