#include "ytdownloader.h"
#include "ui_ytdownloader.h"
#include "videolistelement.h"
YtDownloader::YtDownloader(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YtDownloader)
{
    ui->setupUi(this);
}

YtDownloader::~YtDownloader()
{
    delete ui;
}

void YtDownloader::on_searcg_clicked()
{
    addVideoComponents();
}


void YtDownloader::addVideoComponents(){
    QPushButton* button=new QPushButton("test");
VideoListElement* element=new VideoListElement();
    QVBoxLayout* layout=qobject_cast<QVBoxLayout*>( ui->VideosListContent->layout());
    layout->insertWidget(layout->count(),button);
       layout->insertWidget(layout->count(),element);
}
