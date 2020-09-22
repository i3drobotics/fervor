#include "qtdownload.h"
#include <QCoreApplication>
#include <QUrl>
#include <QNetworkRequest>
#include <QFile>
#include <QDebug>
#include <QProcess>

QtDownload::QtDownload() : QObject(0) {
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinished(QNetworkReply*)));
}

QtDownload::~QtDownload() {

}


void QtDownload::setTarget(const QString &t, const QString &fp) {
    this->target = QUrl::fromEncoded(t.toLocal8Bit());
    this->filepath = fp;
}

void QtDownload::setTarget(const QUrl &t, const QString &fp) {
    this->target = t;
    this->filepath = fp;
}

void QtDownload::downloadFinished(QNetworkReply *data) {
    QFile localFile(filepath);
    if (!localFile.open(QIODevice::WriteOnly))
        return;
    const QByteArray sdata = data->readAll();
    qDebug() << "Writing data to file...";
    localFile.write(sdata);
    //qDebug() << sdata;
    localFile.close();

    qDebug() << "Download complete.";

    emit done();
}

void QtDownload::runFile(){
    QProcess::startDetached(filepath);
}

void QtDownload::download() {
    QNetworkRequest request(this->target);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    QObject::connect(manager.get(request), SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
}

void QtDownload::downloadProgress(qint64 recieved, qint64 total) {
    float progress_val = (float)recieved/(float)total;
    emit progress(progress_val*100);
    qDebug() << recieved << total;
}
