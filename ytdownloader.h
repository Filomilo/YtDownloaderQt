#pragma once
#ifndef YTDOWNLOADER_H
#define YTDOWNLOADER_H

#include <QMainWindow>
#include "YtDlpWrapper/YoutubeDownloader.h"
#include "Worker.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class YtDownloader;
}
QT_END_NAMESPACE

class YtDownloader : public QMainWindow
{
    Q_OBJECT

public:
    YtDownloader(QWidget *parent = nullptr);
    ~YtDownloader();

private slots:


    void on_searchButon_clicked();
  void onLoadFinshed();
    void on_videoradio_clicked();

  void on_audioRadio_clicked();

    void on_sponsorDropdown_textActivated(const QString &arg1);

  void on_donwladAlButton_clicked();

  private:
    Ui::YtDownloader *ui;
    void addVideoComponents(YoutubeVideo vid);
    YoutubeDownloader* youtubeDownloader;
    void clearLoadedVideos();
    Worker* worker;
    QThread* thread;
    void onDownloadFinshed();
};
#endif // YTDOWNLOADER_H
