#include "videolistelement.h"
#include "ui_videolistelement.h"
#include <QNetworkReply>
#include "YtDlpWrapper/YoutubeVideo.h"
#include <QNetworkAccessManager>
<<<<<<< HEAD
=======
#include <QMovie>
#include <QFileDialog>
#include "videolistelement.h"
#include "YtDlpWrapper/YoutubeVideo.h"
#include "YtDlpWrapper/YoutubeDownloader.h"
#include "Worker.h"
#include <QMovie>
#include <QFileDialog>
>>>>>>> playlist-download
VideoListElement::VideoListElement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoListElement)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie(":/gifs/assets/loading.gif");
    ui->loadingCricle->setMovie(movie);
    movie->start();
    ui->loadingCricle->hide();
    on_videoradio_clicked();
    ui->FormatDropDown->setVisible(false);
    ui->qualityDropDown->setVisible(false);
    setupWorkerDownloadTherad();
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
<<<<<<< HEAD
=======
    this->loaded=data;
>>>>>>> playlist-download
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
<<<<<<< HEAD
    ui->sliderEnd->setMaximum(time.second()+time.minute()+time.hour());
     ui->sliderEnd->setValue(time.second()+time.minute()+time.hour());
     ui->sliderStart->setMaximum(time.second()+time.minute()+time.hour());
=======
    int seconds=getSecondFromTime(time);
    ui->sliderEnd->setMaximum(seconds);
     ui->sliderEnd->setValue(seconds);
     ui->sliderStart->setMaximum(seconds);
>>>>>>> playlist-download
}



void VideoListElement::on_timeEnd_userTimeChanged(const QTime &time)
{

}

<<<<<<< HEAD
=======

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
    this->isAudio=true;
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
      this->isAudio=false;
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



void VideoListElement::setupWorkerDownloadTherad()
{
    threadDownload=new QThread();
    workerDownload=new Worker();
    workerDownload->moveToThread(threadDownload);
    //connect(workerDownload,SIGNAL(progresBarChanged(int)),ui->progressBar,SLOT(setValue(int)));
    connect(workerDownload,SIGNAL(videosListDownlaodRequest()),threadDownload,SLOT(start()));
    connect(threadDownload,SIGNAL(started()),workerDownload,SLOT(downloadStart()));
    // connect(workerDownload,SIGNAL(downloadFinished()),this,SLOT( onDownloadFinshed()));
    // connect(workerDownload,SIGNAL(downloadFinished()),threadDownload,SLOT(quit()),Qt::DirectConnection);
    connect(workerDownload,SIGNAL(downloadFinished()),this,SLOT( onDownloadFinshed()));
}


void VideoListElement::onDownloadFinshed()
{
    qDebug()<<"downalod finshed";;
    ui->loadingIndicator->hide();
    ui->downloadButton->setEnabled(true);
    ui->FormatDropDown->setEnabled(true);
    ui->qualityDropDown->setEnabled(true);
    ui->sliderEnd->setEnabled(true);
    ui->sliderStart->setEnabled(true);
    ui->timeEnd->setEnabled(true);
    ui->timeStart->setEnabled(true);
    ui->sponsorDropdown->setEnabled(true);
    ui->videoradio->setEnabled(true);
    ui->audioRadio->setEnabled(true);
         ui->loadingCricle->hide();

}

void VideoListElement::on_downloadButton_clicked()
{
    std::string format=this->isAudio?".mp3":".mp4";
    std::string defaultName=this->loaded.getName()+format;
    QString file = QFileDialog::getSaveFileName(this, tr("Save as..."),QString::fromLocal8Bit(defaultName.c_str()), tr(this->isAudio?".mp3":".mp4"));
    qDebug()<<"foramt: "<<format;
    if(file.length()>0)
    {
        qDebug()<<"selcted dir: "<<file;








        std::vector<DownloadRequest> requests;
        DownloadRequest request;
        request.setYtVideo(&loaded);
        request.setLocation(file.toStdString());
        request.setIsAudio(  isAudio);
        request.setOverwriteName(  true);
        // timeEdit.time().toString("h:m:s ap");
        // m:ss
        request.setVideoStart(ui->timeStart->dateTime().time().toString("m:ss").toStdString());
            request.setVideoStop(ui->timeEnd->dateTime().time().toString("m:ss").toStdString());

        int itemCount = ui->sponsorList->count();


        std::vector<std::string> blocks;
        for (int i = 0; i < itemCount; ++i) {
            QListWidgetItem* item = ui->sponsorList->item(i);
            qDebug() << item->text();
            blocks.push_back(item->text().toStdString());
        }
        request.setBlocks(blocks);
        requests.push_back(request);


 this->workerDownload->requestDownload(requests);




        qDebug()<<"downalod start";;
                ui->loadingCricle->show();
        ui->loadingIndicator->show();
        ui->downloadButton->setEnabled(false);
        ui->FormatDropDown->setEnabled(false);
        ui->qualityDropDown->setEnabled(false);
        ui->sliderEnd->setEnabled(false);
        ui->sliderStart->setEnabled(false);
        ui->timeEnd->setEnabled(false);
        ui->timeStart->setEnabled(false);
        ui->sponsorDropdown->setEnabled(false);
        ui->videoradio->setEnabled(false);
            ui->audioRadio->setEnabled(false);
    }
}

>>>>>>> playlist-download
