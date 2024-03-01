#ifndef YTDOWNLOADER_H
#define YTDOWNLOADER_H

#include <QMainWindow>

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

private:
    Ui::YtDownloader *ui;
};
#endif // YTDOWNLOADER_H
