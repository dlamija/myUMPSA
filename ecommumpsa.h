#ifndef ECOMMUMPSA_H
#define ECOMMUMPSA_H

#include <QObject>
#include <QJsonArray>
#include <QSslError>

class QNetworkAccessManager;
class QNetworkCookieJar;
class QNetworkReply;

class EcommUMPSA : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *networkManager;
    QNetworkCookieJar *cookieJar;
    QString user;
    QString pass;
    QString extractUsername(const QString &html);
    QJsonArray extractAttendanceData(const QString &html);
    QString getJnlpPath();
    void getInitialCookies();
    void login(const QString &username, const QString &password);
    void checkAttendance();

private slots:
    void onCookiesSlot();
    void onLoginSlot();
    void onAttedanceSlot();
    void savetofile(QString &responseText);
    void onSslError(QNetworkReply *r, QList<QSslError> l);
    void onImsAcademicSlot(QNetworkReply *reply);

public:
    explicit EcommUMPSA(QString username, QString password, QObject *parent = nullptr);
    void checkInUMPSA();
    void checkOutUMPSA();
    void openPath(QString link);
    void openImsAcademic();

signals:
    void attendantFound(QString time);
    void attendantNotFound();
    void checkInSignal(QNetworkReply *reply);
    void checkOutSignal(QNetworkReply *reply);
    void openImsAcademicSignal(QString username, QString sessionId);
};

#endif // ECOMMUMPSA_H
