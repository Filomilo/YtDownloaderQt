#include "ytdownloader.h"
#include "ui_ytdownloader.h"
#include "ui_VideoElement.h"
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

    QVBoxLayout* layout=qobject_cast<QVBoxLayout*>( ui->VideosListContent->layout());
    layout->insertWidget(layout->count(),button);
}
