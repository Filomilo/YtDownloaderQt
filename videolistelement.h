#ifndef VIDEOLISTELEMENT_H
#define VIDEOLISTELEMENT_H
#include <QNetworkReply>
#include <QWidget>
#include "YtDlpWrapper/YoutubeVideo.h"
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

private:
    Ui::VideoListElement *ui;

    void setTitle(std::string title);
    void setThumbnail(std::string url);
    void setAudio();
    void setVideo();
    void addOrRemoveSponsorBlockElemnt(std::string element);
    void setLength(std::string length);
};

#endif // VIDEOLISTELEMENT_H
