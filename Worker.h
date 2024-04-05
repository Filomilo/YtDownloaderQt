#pragma once
#ifndef WORKER_H
#define WORKER_H

#include <QCoreApplication>
#include <QThread>
#include <QDebug>
// #include "YtDlpWrapper/YoutubeVideo.h"
// #include "YtDlpWrapper/YoutubeDownloader.h"
#include <QMutex>
#include <vector>
#include "YtDlpWrapper/DownloadRequest.h"


class Worker: public QObject
{
    Q_OBJECT



    std::string url;

public slots:
    void videosListLoad();
    void downloadStart();
public:
       explicit Worker(QObject *parent = 0);

    void reuqestVideos(std::string url);

       void abort();
  void requestDownload(std::vector<DownloadRequest> requests);
signals:
   void loadFinished();
    void videosListRequested();
   void videosListDownlaodRequest();
   void progresBarChanged(const int &val);
   void downloadFinished();
   private:
   void updateProgresBar(int a, int b);
       std::vector<DownloadRequest> requests;
    QMutex mutex;
    bool _working;
    bool _abort;
};

#endif // WORKER_H
