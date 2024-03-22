#ifndef WORKER_H
#define WORKER_H
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include "YtDlpWrapper/YoutubeVideo.h"
#include "YtDlpWrapper/YoutubeDownloader.h"
#include <QMutex>
class Worker: public QObject
{
    Q_OBJECT



    std::string url;

public slots:
    void videosListLoad();

public:
       explicit Worker(QObject *parent = 0);

    void reuqestVideos(std::string url);

       void abort();

signals:
   void loadFinished();
    void videosListRequested();
   void dowloadRequest();
   void progresBarChanged(const int &val);
   private:
    QMutex mutex;
    bool _working;
    bool _abort;
};

#endif // WORKER_H
