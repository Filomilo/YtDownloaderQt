#include "Worker.h"
#include "YtDlpWrapper/YoutubeDownloader.h"
#include "YtDlpWrapper/DownloadRequest.h"



Worker::Worker(QObject *parent ):   QObject(parent)
{
    _working =false;
    _abort = false;
}

void Worker::reuqestVideos(std::string url)
{
    mutex.lock();
    this->url=url;
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit videosListRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void Worker::updateProgresBar(int a, int b)
{
    qDebug()<<"update progrs bar "<<a<<" "<<b;
    float prct=((float)a/(float)b) *100;
 qDebug()<<"update progrs bar "<<a<<" "<<b<<" "<<prct;
    emit progresBarChanged((int)prct);
}


void Worker::videosListLoad(){


    mutex.lock();
    _working = false;
    mutex.unlock();
    YoutubeDownloader::getInstance()->loadFilesWithCallBack(this->url,[this](int a, int b) {updateProgresBar(a ,b); });
    emit progresBarChanged(100);
    emit loadFinished();
    qDebug()<<"Videos loaded";
}
void Worker::requestDownload(std::vector<DownloadRequest> requests)
{
      updateProgresBar(0,requests.size()+1);
      for (int var = 0; var < requests.size(); ++var) {
        updateProgresBar(var+1,requests.size()+1);
          qDebug()<<requests.at(var).toString();
        qDebug()<<"Commad: "<<requests.at(var).getCommand().getCommand();
          requests.at(var).execute();
      }
          emit progresBarChanged(100);
    emit downloadFinished();

}
