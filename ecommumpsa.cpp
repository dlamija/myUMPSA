#include "ecommumpsa.h"
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QUrlQuery>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QJsonObject>
#include <QFile>
#include <QDate>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QDir>



EcommUMPSA::EcommUMPSA(QString username, QString password, QObject *parent)
    : QObject{parent}
{
    this->user = username;
    this->pass = password;
    cookieJar = new QNetworkCookieJar(this);
    networkManager = new QNetworkAccessManager(this);
    networkManager->setCookieJar(cookieJar);

    this->getInitialCookies();  // Step 1: Fetch cookies from base URL
}

void EcommUMPSA::checkInUMPSA()
{
    qDebug() << Q_FUNC_INFO;
    //QString link = "https://community.ump.edu.my/ecommstaff/cms/StaffAttendance/checkatt2.jsp";
    QString link = "https://ecomm.ump.edu.my/cms/StaffAttendance/checkatt2.jsp";
    float lat = 3.5467049889754816;
    float lon = 103.4277851570105;

    QUrlQuery urlQuery;
    //QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    urlQuery.addQueryItem("action", "checkin");
    urlQuery.addQueryItem("username", user);
    urlQuery.addQueryItem("password", pass.toLatin1().toPercentEncoding());
    urlQuery.addQueryItem("lat", QString::number(lat) );
    urlQuery.addQueryItem("lon", QString::number(lon) );

    QUrl url = QUrl(link);
    QNetworkRequest networkRequest(url);

    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(onSslError(QNetworkReply*, QList<QSslError>)));

    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SIGNAL(checkInSignal(QNetworkReply*)));

    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkManager->post(networkRequest, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
}

void EcommUMPSA::checkOutUMPSA()
{
    qDebug() << Q_FUNC_INFO;
    //QString link = "https://community.ump.edu.my/ecommstaff/cms/StaffAttendance/checkatt2.jsp";
    QString link = "https://ecomm.ump.edu.my/cms/StaffAttendance/checkatt2.jsp";
    float lat = 3.5467049889754816;
    float lon = 103.4277851570105;

    QUrlQuery urlQuery;
    //QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    urlQuery.addQueryItem("action", "checkout");
    urlQuery.addQueryItem("username", user);
    urlQuery.addQueryItem("password", pass.toLatin1().toPercentEncoding());
    urlQuery.addQueryItem("lat", QString::number(lat) );
    urlQuery.addQueryItem("lon", QString::number(lon) );

    QUrl url = QUrl(link);
    QNetworkRequest networkRequest(url);

    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(onSslError(QNetworkReply*, QList<QSslError>)));

    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SIGNAL(checkOutSignal(QNetworkReply*)));

    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkManager->post(networkRequest, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
}

void EcommUMPSA::openPath(QString link)
{
    QWebEngineView *webView = new QWebEngineView;
    QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
    QWebEngineCookieStore *cookieStore = profile->cookieStore();

    // Assuming you have cookies in `QNetworkCookieJar`
    QList<QNetworkCookie> cookies = cookieJar->cookiesForUrl(QUrl("https://ecomm.ump.edu.my"));
    for (const QNetworkCookie &cookie : cookies) {
        QNetworkCookie newCookie = cookie;
        cookieStore->setCookie(newCookie, QUrl("https://ecomm.ump.edu.my"));
    }

    webView->load(QUrl(link));
    webView->show();
}


QString EcommUMPSA::extractUsername(const QString &html)
{
    QRegularExpression re(R"(<h4 class="mb-0 text-white">([^<]+)</h4>)");
    QRegularExpressionMatch match = re.match(html);

    if (match.hasMatch()) {
        return match.captured(1).trimmed();
    }

    return QString(); // Return empty if not found
}

void EcommUMPSA::onCookiesSlot()
{
    qDebug() << Q_FUNC_INFO;
    QList<QNetworkCookie> cookies = cookieJar->cookiesForUrl(QUrl("https://ecomm.ump.edu.my"));
    for (const QNetworkCookie &cookie : cookies) {
        qDebug() <<"\t" << cookie.toRawForm();
    }

    // Proceed to login
    login(user, pass);  // Step 2: Replace with actual credentials

    sender()->deleteLater();
}

void EcommUMPSA::onLoginSlot()
{
    qDebug() << Q_FUNC_INFO;
    QRegularExpression re("[\n\t\r]");

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        QString responseText = reply->readAll();
        QString user = this->extractUsername(responseText.remove(re));
        qDebug() <<"\t" << "Login successful:" << user;

    } else {
        qDebug() <<"\t" << "Login failed:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    // Step 3: Check attendance page
    this->checkAttendance();

    reply->deleteLater();
}

void EcommUMPSA::onAttedanceSlot()
{
    qDebug() << Q_FUNC_INFO;
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        QString responseText = reply->readAll();
        QJsonArray attendance = this->extractAttendanceData(responseText);
        QJsonDocument doc(attendance);
        if (!attendance.isEmpty()) {
            QJsonObject obj = attendance.first().toObject();
            QString time = obj["time"].toString();
            QString ip = obj["ip"].toString();
            QString location = obj["location"].toString();

            qDebug() <<"\t" << "Check-in Info:";
            qDebug() <<"\t" << "Time:\t" << time;
            qDebug() <<"\t" << "IP:\t" << ip;
            qDebug() <<"\t" << "Location:" << location;
        }else {
            qDebug() <<"\t" << "Not Check in yet";
            //this->attendantFound(time);
        }
    } else {
        qDebug() << "Failed to retrieve attendance page:" << reply->errorString();
    }

    reply->deleteLater();

}

void EcommUMPSA::savetofile(QString &responseText)
{
    QFile file("saved.html");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << responseText;
        file.close();
        qDebug() << "HTML written to attendance.html";
    } else {
        qDebug() << "Failed to write file!";
    }
}

void EcommUMPSA::onSslError(QNetworkReply *r, QList<QSslError> l)
{
    l.size();
    r->ignoreSslErrors();
}

QJsonArray EcommUMPSA::extractAttendanceData(const QString &html)
{
    QJsonArray records;

    // Match rows with time, IP and location in the expected format
    QRegularExpression re(R"(<td[^>]*>\s*<span[^>]*>(\d{2}:\d{2})<\/span>\s*<\/td>\s*<td[^>]*>\s*<span[^>]*>([\d\.]+)<br\s*\/?>\(([^<]+)\)<\/span>)",
                          QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption);

    QRegularExpressionMatchIterator it = re.globalMatch(html);

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if (match.hasMatch()) {
            QJsonObject record;
            record["time"] = match.captured(1);
            record["ip"] = match.captured(2);
            record["location"] = match.captured(3);
            records.append(record);
        }
    }

    return records;
}

void EcommUMPSA::checkAttendance()
{
    QUrl url("https://ecomm.ump.edu.my/staffAttendance.jsp");
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, &EcommUMPSA::onAttedanceSlot);

}

void EcommUMPSA::getInitialCookies()
{
    QUrl url("https://ecomm.ump.edu.my");
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, &EcommUMPSA::onCookiesSlot);

}

void EcommUMPSA::login(const QString &username, const QString &password)
{
    QUrl url("https://ecomm.ump.edu.my");
    url.setPath("/Login");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QDate yesterday = QDate::currentDate().addDays(-1);
    QString dateBefore = yesterday.toString("dd/MM/yyyy");
    float lat = 3.5467049889754816;
    float lon = 103.4277851570105;

    QUrlQuery params;
    params.addQueryItem("userName", username);
    params.addQueryItem("password", password);
    params.addQueryItem("level", "Staff");
    params.addQueryItem("datebefore", dateBefore);
    params.addQueryItem("lat", QString::number(lat) );
    params.addQueryItem("lon", QString::number(lon) );

    QNetworkReply *reply = networkManager->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, this, &EcommUMPSA::onLoginSlot);
}

void EcommUMPSA::openImsAcademic()
{
    qDebug() << Q_FUNC_INFO;

    // Relogin before request ims
    this->login(user, pass);


    const QString link = "https://ecomm.ump.edu.my/cmsformlink.jsp";
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("form", "IMS_ACADSYS_LOGON");
    
    QUrl url = QUrl(link);
    QNetworkRequest networkRequest(url);

    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(onSslError(QNetworkReply*, QList<QSslError>)));

    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onImsAcademicSlot(QNetworkReply*)));

    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkManager->post(networkRequest, urlQuery.toString(QUrl::FullyEncoded).toUtf8());

}

QString EcommUMPSA::getJnlpPath()
{
    // Get the application directory path
    QString appPath = QCoreApplication::applicationDirPath();
    
    #ifdef Q_OS_MAC
        // On macOS, we need to go up to Contents and then to Resources
        // From: myUMPSA.app/Contents/MacOS/
        // To:   myUMPSA.app/Contents/Resources/
        QDir dir(appPath);
        dir.cdUp(); // go up from MacOS to Contents
        dir.cd("Resources"); // go into Resources
        return dir.filePath("frmservlet.jnlp");
    #else
        // For other platforms, Resources is directly in the executable directory
        return appPath + "/Resources/frmservlet.jnlp";
    #endif
}

void EcommUMPSA::onImsAcademicSlot(QNetworkReply *reply)
{
    qDebug() << Q_FUNC_INFO;
    if (reply->error() == QNetworkReply::NoError) {
        QString responseText = reply->readAll();
        
        // Extract the URL using regex
        QRegularExpression re("window\\.open\\(\"(https://student\\.ump\\.edu\\.my/forms/frmservlet\\?[^\"]+)\"");
        QRegularExpressionMatch match = re.match(responseText);
        
        if (match.hasMatch()) {
            QString extractedUrl = match.captured(1);
            qDebug() << "\t" << "Extracted URL:" << extractedUrl;
            
            // Extract username and session ID using regex
            QRegularExpression paramsRe("cms_username=([^+]+)\\+cms_sessid=(\\d+-\\d+)");
            QRegularExpressionMatch paramsMatch = paramsRe.match(extractedUrl);
            
            if (paramsMatch.hasMatch()) {
                QString username = paramsMatch.captured(1);
                QString sessionId = paramsMatch.captured(2);
                qDebug() << "\t" << "Username:" << username;
                qDebug() << "\t" << "Session ID:" << sessionId;
                
                // Get the JNLP file path
                QString jnlpPath = getJnlpPath();
                qDebug() << "\t" << "JNLP Path:" << jnlpPath;
                
                // Here you can use the jnlpPath to read and process the JNLP file
                emit openImsAcademicSignal(username, sessionId);
                
            } else {
                qDebug() << "\t" << "Failed to extract username and session ID from URL";
            }
        } else {
            qDebug() << "Failed to extract URL from response";
        }
    } else {
        qDebug() << "Initial request failed:" << reply->errorString();
    }
    reply->deleteLater();
}
