#include "videolistelement.h"
#include "ui_videolistelement.h"

VideoListElement::VideoListElement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoListElement)
{
    ui->setupUi(this);
}

VideoListElement::~VideoListElement()
{
    delete ui;
}

void VideoListElement::on_pushButton_5_clicked()
{

}

