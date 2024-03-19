#ifndef VIDEOLISTELEMENT_H
#define VIDEOLISTELEMENT_H

#include <QWidget>

namespace Ui {
class VideoListElement;
}

class VideoListElement : public QWidget
{
    Q_OBJECT

public:
    explicit VideoListElement(QWidget *parent = nullptr);
    ~VideoListElement();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::VideoListElement *ui;
};

#endif // VIDEOLISTELEMENT_H
