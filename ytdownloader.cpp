#include "ytdownloader.h"
#include "ui_ytdownloader.h"
#include "videolistelement.h"
#include "YtDlpWrapper/YoutubeVideo.h"
#include "YtDlpWrapper/YoutubeDownloader.h"
#include "Worker.h"
#include <QMovie>
#include <QFileDialog>
// #include "YtDlpWrapper/DownloadRequest.h"
YtDownloader::YtDownloader(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YtDownloader)
{
    ui->setupUi(this);
    this->youtubeDownloader=YoutubeDownloader::getInstance();
    setupWorkerLoadTherad();
    setupWorkerDownloadTherad();
    QMovie *movie = new QMovie(":/gifs/assets/loading.gif");
    ui->loadingCircle->setMovie(movie);
    movie->start();
    ui->loadingCircle->hide();
    // on_searchButon_clicked();
    ui->donwladAlButton->setEnabled(false);
    this->on_videoradio_clicked();
    ui->FormatDropDown->setVisible(false);
    ui->qualityDropDown_2->setVisible(false);
}

void YtDownloader::setupWorkerLoadTherad()
{
    thread=new QThread();
    worker=new Worker();
    worker->moveToThread(thread);
    connect(worker,SIGNAL(progresBarChanged(int)),ui->progressBar,SLOT(setValue(int)));
    connect(worker,SIGNAL(videosListRequested()),thread,SLOT(start()));
    connect(thread,SIGNAL(started()),worker,SLOT(videosListLoad()));
    connect(worker,SIGNAL(loadFinished()),thread,SLOT(quit()),Qt::DirectConnection);
    connect(worker,SIGNAL(loadFinished()),this,SLOT( onLoadFinshed()));


}
void YtDownloader::setupWorkerDownloadTherad()
{
    threadDownload=new QThread();
    workerDownload=new Worker();
    workerDownload->moveToThread(threadDownload);
    connect(workerDownload,SIGNAL(progresBarChanged(int)),ui->progressBar,SLOT(setValue(int)));
    connect(workerDownload,SIGNAL(videosListDownlaodRequest()),threadDownload,SLOT(start()));
    connect(threadDownload,SIGNAL(started()),workerDownload,SLOT(downloadStart()));
    // connect(workerDownload,SIGNAL(downloadFinished()),this,SLOT( onDownloadFinshed()));
    // connect(workerDownload,SIGNAL(downloadFinished()),threadDownload,SLOT(quit()),Qt::DirectConnection);
 connect(workerDownload,SIGNAL(downloadFinished()),this,SLOT( onDownloadFinshed()));
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
        ui->searchButon->setDisabled(false);
     ui->loadingCircle->hide();
        std::string newLabel="Videos: "+ std::to_string(videos.size());
     ui->howManyVideos->setText(QString::fromUtf8(newLabel.data(), int(newLabel.size())));
        if(videos.size()>0)
     {
             ui->donwladAlButton->setEnabled(true);
     }
        else{
              ui->donwladAlButton->setEnabled(false);
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
    ui->searchButon->setDisabled(true);
 ui->progressBar->setValue(0);
 qDebug()<<"Startign wokrer request";
 this->worker->reuqestVideos(url);
 ui->loadingCircle->show();
}


void YtDownloader::on_videoradio_clicked()
{
    ui->FormatDropDown->clear();
    ui->FormatDropDown->addItem("mp4");
    ui->FormatDropDown->addItem("mkv");
    ui->qualityDropDown_2->clear();
     ui->qualityDropDown_2->addItem("360");
      ui->qualityDropDown_2->addItem("480");
      ui->qualityDropDown_2->addItem("720");
           ui->qualityDropDown_2->addItem("1080");
      this->isAudio=false;
}


void YtDownloader::on_audioRadio_clicked()
{
    ui->FormatDropDown->clear();
    ui->FormatDropDown->addItem("mp3");
    ui->FormatDropDown->addItem("wav");
    ui->qualityDropDown_2->clear();
    ui->qualityDropDown_2->addItem("80");
    ui->qualityDropDown_2->addItem("120");
    ui->qualityDropDown_2->addItem("240");
    ui->qualityDropDown_2->addItem("360");
     this->isAudio=true;
}


void YtDownloader::on_sponsorDropdown_textActivated(const QString &arg1)
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


void YtDownloader::on_donwladAlButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("choose directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
       ui->donwladAlButton->setEnabled(true);
    std::string format="."+ui->FormatDropDown->currentText().toStdString();
        qDebug()<<"foramt: "<<format;
    if(dir.length()>0)
    {
           std::vector<YoutubeVideo> videos=YoutubeDownloader::getInstance()->getVideos();
        std::vector<DownloadRequest> requests;
           for(int i=0;i<videos.size();i++)
        {
            DownloadRequest request;
               request.setYtVideo(new YoutubeVideo(videos[i]));
            std::string location=dir.toStdString()+"/"+videos[i].getName()+format;
             qDebug()<<"Locaton: "<<location;
            qDebug()<<"vide url: "<< videos[i].getUrl();

              request.setLocation(dir.toStdString());
             request.setIsAudio(  isAudio);
             // request.setRes(ui->qualityDropDown_2->currentText().toInt());
              // request.setFormat(ui->FormatDropDown->currentText().toStdString());
             int itemCount = ui->sponsorList->count();


             std::vector<std::string> blocks;
             for (int i = 0; i < itemCount; ++i) {
                 QListWidgetItem* item = ui->sponsorList->item(i);
                 qDebug() << item->text();
                 blocks.push_back(item->text().toStdString());
             }
             request.setBlocks(blocks);
             requests.push_back(request);
             // qDebug()<<"request: "<<request.toString();

        }
            ui->loadingCircle->show();
           this->workerDownload->requestDownload(requests);

    }
}

void YtDownloader::onDownloadFinshed()
{
      qDebug()<<"downalod finshed";;
    ui->searchButon->setDisabled(false);
    ui->loadingCircle->hide();



        ui->donwladAlButton->setEnabled(true);

}
