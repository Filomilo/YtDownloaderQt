QT       += core gui
QT += quickcontrols2
# QT += webenginewidgets
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -stdlib=libc++

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Worker.cpp \
    main.cpp \
    videolistelement.cpp \
    ytdownloader.cpp \
    YtDlpWrapper/YoutubeDownloader.cpp \
    YtDlpWrapper/Executor.cpp \
    YtDlpWrapper/Logger.cpp \
    YtDlpWrapper/YoutubeDownloader.cpp \
    YtDlpWrapper/DownloadRequest.cpp

HEADERS += \
    Worker.h \
    videolistelement.h \
    ytdownloader.h \
    # YtDlpWrapper/YoutubeDownloader.h \
    # YtDlpWrapper/Executor.h \
    # YtDlpWrapper/Logger.h \
    # YtDlpWrapper/YoutubeDownloader.h \
    # YtDlpWrapper/DownloadRequest.h

FORMS += \
    videolistelement.ui \
    ytdownloader.ui

TRANSLATIONS += \
    YtDownloader_en_001.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /YtDlpWrapper

RESOURCES += \
    loadingIndicator.qrc
RC_ICONS = ytDownalder.ico
