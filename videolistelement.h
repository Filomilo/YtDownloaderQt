#pragma once
#ifndef VIDEOLISTELEMENT_H
#define VIDEOLISTELEMENT_H
#include <QNetworkReply>
#include <QWidget>
#include "YtDlpWrapper/YoutubeVideo.h"
#include <cstdio>
#include "Worker.h"

namespace Ui {
class VideoListElement;
}

class VideoListElement : public QWidget
{
    Q_OBJECT

public:
    explicit VideoListElement(QWidget *parent = nullptr);
    void setup(YoutubeVideo data);
    ~VideoListElement();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();
   void downloadThumbnailFinished(QNetworkReply *reply);
    void on_timeEnd_userTimeChanged(const QTime &time);

   void on_audioRadio_clicked();

    void on_videoradio_clicked();

   void on_sponsorDropdown_textActivated(const QString &arg1);

    void on_sliderStart_sliderMoved(int position);

   void on_sliderEnd_valueChanged(int value);

    void on_timeEnd_timeChanged(const QTime &time);

   void on_timeStart_userTimeChanged(const QTime &time);
  void onDownloadFinshed();
     void on_downloadButton_clicked();

 private:
    Ui::VideoListElement *ui;

    void setTitle(std::string title);
    void setThumbnail(std::string url);
    void setAudio();
    void setVideo();
    void addOrRemoveSponsorBlockElemnt(std::string element);
    void setLength(std::string length);
    void resolveStartTime();
    void resolveEndTime();
      bool isAudio=false;
    Worker* worker;
    QThread* thread;
    Worker* workerDownload;
    QThread* threadDownload;
    YoutubeVideo loaded;
    void setupWorkerDownloadTherad();
};





#endif // VIDEOLISTELEMENT_H
