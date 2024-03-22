#include "Worker.h"
#include "YtDlpWrapper/YoutubeDownloader.h"


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

void Worker::videosListLoad(){


    mutex.lock();
    _working = false;
    mutex.unlock();
    YoutubeDownloader::getInstance()->loadFiles(this->url);
    emit progresBarChanged(100);
    emit loadFinished();
    qDebug()<<"Videos loaded";
}
