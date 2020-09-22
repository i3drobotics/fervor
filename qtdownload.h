#ifndef QTDOWNLOAD_H
#define QTDOWNLOAD_H

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


class QtDownload : public QObject {
    Q_OBJECT
public:
    explicit QtDownload();
    ~QtDownload();

    void setTarget(const QString& t, const QString& fp);
    void setTarget(const QUrl& t, const QString& fp);

private:
    QNetworkAccessManager manager;
    QUrl target;
    QString filepath;

signals:
    void done();
    void progress(float val);

public slots:
    void download();
    void runFile();
    void downloadFinished(QNetworkReply* data);
    void downloadProgress(qint64 recieved, qint64 total);
};

#endif // QTDOWNLOAD_H
