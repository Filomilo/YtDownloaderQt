#include "ytdownloader.h"
#include "ui_ytdownloader.h"

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
