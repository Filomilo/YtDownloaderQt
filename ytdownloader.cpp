#include "ytdownloader.h"
#include "ui_ytdownloader.h"
#include "videolistelement.h"
#include "YtDlpWrapper/YoutubeVideo.h"
#include "YtDlpWrapper/YoutubeDownloader.h"
#include "Worker.h"
YtDownloader::YtDownloader(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YtDownloader)
{
    ui->setupUi(this);
    this->youtubeDownloader=YoutubeDownloader::getInstance();

    thread=new QThread();
    worker=new Worker();
    worker->moveToThread(thread);
    connect(worker,SIGNAL(progresBarChanged(int)),ui->progressBar,SLOT(setValue(int)));
    connect(worker,SIGNAL(videosListRequested()),thread,SLOT(start()));
    connect(thread,SIGNAL(started()),worker,SLOT(videosListLoad()));
    connect(worker,SIGNAL(loadFinished()),thread,SLOT(quit()),Qt::DirectConnection);
    connect(worker,SIGNAL(loadFinished()),this,SLOT( onLoadFinshed()));
}


void workFinished();
void videosListRequested();
void dowloadRequest();
void progresBarChanged(const int &val);

YtDownloader::~YtDownloader()
{
    worker->abort();
    thread->wait();
    delete thread;
    delete worker;
    delete ui;
}




void YtDownloader::addVideoComponents(YoutubeVideo vid){
VideoListElement* element=new VideoListElement();
    element->setup(vid);
    QVBoxLayout* layout=qobject_cast<QVBoxLayout*>( ui->VideosListContent->layout());
      layout->insertWidget(layout->count(),element);

}

void YtDownloader::onLoadFinshed()
{
    qDebug()<<"Load finished";;
    std::vector<YoutubeVideo> videos= this->youtubeDownloader->getVideos();
    for (int var = 0; var < videos.size(); ++var) {
      this->addVideoComponents(videos[var]);
    }

}

void YtDownloader::clearLoadedVideos()
{
      QLayoutItem* item;
    QVBoxLayout* layout=qobject_cast<QVBoxLayout*>( ui->VideosListContent->layout());
      while((item=layout->takeAt(0)))
    {
        delete item->widget();
          delete item;
    }
}


void YtDownloader::on_searchButon_clicked()
{
    clearLoadedVideos();
    std::string url=  ui->youtubeVideoInput->toPlainText().toStdString();

 ui->progressBar->setValue(0);
 qDebug()<<"Startign wokrer request";
 this->worker->reuqestVideos(url);
}

