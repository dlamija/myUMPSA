#include "myumpsa.h"
#include "ui_myumpsa.h"

#include <QDebug>
#include <QSettings>
#include <QByteArray>
#include <QAction>
#include <QThread>
#include <QUrl>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QRegularExpression>
#include <QHostInfo>
#include <QTimer>
#include <QDnsLookup>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QTemporaryDir>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QTime>

#ifdef Q_OS_MAC
    // macOS bundle structure: myUMPSA.app/Contents/Resources/frmservlet.jnlp
#else
    // Other platforms: executable_dir/Resources/frmservlet.jnlp
#endif

myUMPSA::myUMPSA(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::myUMPSA)
{
    ui->setupUi(this);
    this->readSettings();
    this->createActions();
    this->createTrayIcon();
    this->setIcon();
    trayIcon->show();

    staff = new Staff();
    staff->setIsInUMPSA(this->lookupUMPDNS());
    dns = new QDnsLookup(this);

    //Periodic DNS check
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &myUMPSA::checkIPChanged);
    timer->start(2 * 60000); // 2 minutes

    //get user info if not prev data saved
    if (staff->username().isEmpty()){
        this->show();
    } else {
        ecomm = new EcommUMPSA(staff->username(), staff->password());
        connect(ecomm, &EcommUMPSA::attendantFound, this, &myUMPSA::attendantSlot);
        connect(ecomm, &EcommUMPSA::attendantNotFound, this, &myUMPSA::attendantNotFoundSlot);
        connect(ecomm, &EcommUMPSA::checkInSignal, this, &myUMPSA::checkInSlot);
        connect(ecomm, &EcommUMPSA::checkOutSignal, this, &myUMPSA::checkOutSlot);
        connect(ecomm, &EcommUMPSA::openImsAcademicSignal, this, &myUMPSA::imsAcademicSlot);
    }
}

myUMPSA::~myUMPSA()
{
    delete ui;
}

void myUMPSA::readSettings()
{
    qDebug() << Q_FUNC_INFO << "Read Saved Setting";
    QSettings settings;
    QString username;
    QString password;
    bool autoCheckIn;
    bool disableCheckOut;
    bool disableOutside;


    settings.beginGroup("Login");
    username = *new QString(QByteArray::fromBase64(settings.value("username").toString().toUtf8()));
    password = *new QString(QByteArray::fromBase64(settings.value("password").toString().toUtf8()));
    settings.endGroup();

    settings.beginGroup("Date");
    autoCheckIn = settings.value("day").toBool();
    disableCheckOut = settings.value("month").toBool();
    disableOutside = settings.value("week").toBool();
    settings.endGroup();

    staff->setUsername(username);
    staff->setPassword(password);
    staff->setAutoCheckIn(autoCheckIn);
    staff->setDisableCheckOut(disableCheckOut);
    staff->setDisableOutside(disableOutside);

    ui->username->setText(username);
    ui->password->setText(password);
    if(autoCheckIn){
        ui->checkBoxCheckINAuto->setCheckState(Qt::Checked);
    }
    if(disableCheckOut){
        ui->checkBoxCheckOutBefore4pm->setCheckState(Qt::Checked);
    }
    if(disableOutside){
        ui->checkBoxDisableOutside->setCheckState(Qt::Checked);
    }
}

void myUMPSA::createActions()
{
    login_action = new QAction(tr("Log in &eComm WEB"), this);
    connect(login_action, &QAction::triggered, this, &myUMPSA::loginEcommBrowser);

    checkmemo_action = new QAction(tr("Check &Memo"), this);
    connect(checkmemo_action, &QAction::triggered, this, &myUMPSA::checkMemo);

    ims_action = new QAction(tr("&IMS Academic"),this);
    connect(ims_action, &QAction::triggered, this, &myUMPSA::imsAcademic);

    checkin_action = new QAction(tr("Check &In"), this);
    connect(checkin_action, &QAction::triggered, this, &myUMPSA::checkInUMPSA);

    checkout_action = new QAction(tr("Check &Out"), this);
    connect(checkout_action, &QAction::triggered, this, &myUMPSA::checkOutUMPSA);

    configure_action = new QAction(tr("&Configure"),this);
    connect(configure_action, &QAction::triggered, this, &myUMPSA::show);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    testAction = new QAction(tr("&Test"),this);
    connect(testAction, &QAction::triggered, this, &myUMPSA::testFunc);
}

void myUMPSA::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(login_action);
    trayIconMenu->addAction(checkmemo_action);
    trayIconMenu->addAction(ims_action);

    trayIconMenu->addSeparator();
    trayIconMenu->addAction(checkin_action);
    trayIconMenu->addAction(checkout_action);


    trayIconMenu->addSeparator();
    trayIconMenu->addAction(configure_action);
    trayIconMenu->addAction(testAction);

    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void myUMPSA::setIcon()
{
    QIcon icon = QIcon(":/images/new.png");
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("eComm"));
}

void myUMPSA::writeSettings(bool save_delete)
{
    QSettings settings;
    qDebug() << "save or delete" << save_delete << Qt::endl;
    if (save_delete) {
        settings.beginGroup("Login");
        settings.setValue("username", staff->username().toUtf8().toBase64());
        settings.setValue("password", staff->password().toUtf8().toBase64());
        settings.endGroup();
        settings.beginGroup("Date");
        settings.setValue("day", staff->autoCheckIn());
        settings.setValue("month", staff->disableCheckOut());
        settings.setValue("week", staff->disableOutside());
        settings.endGroup();
    } else {
        settings.beginGroup("Login");
        settings.remove("");
        settings.endGroup();
        settings.beginGroup("Date");
        settings.remove("");
        settings.endGroup();
    }
    settings.sync();
}

bool myUMPSA::lookupUMPDNS()
{
    QString umpHostUrl = "umpsa.edu.my";
    //Work differently with Apple Private Relay
    QHostInfo umpHost = QHostInfo::fromName(umpHostUrl);    //QString("umpsa.edu.my");

    if(umpHost.addresses().isEmpty()){ // No Network
        qDebug() <<  Q_FUNC_INFO << "No Network!";
        return false;
    }

    QHostAddress getHost = umpHost.addresses().first();
    qDebug() <<  Q_FUNC_INFO << getHost.toString();
    return(getHost.isInSubnet(QHostAddress::parseSubnet("172.16.0.0/16")));
}

void myUMPSA::checkInUMPSA()
{
    if (!ecomm) {
        qWarning() << "eComm not initialized";
        return;
    }
    ecomm->checkInUMPSA();
}

void myUMPSA::checkOutUMPSA()
{
    if (!ecomm) {
        qWarning() << "eComm not initialized";
        return;
    }
    ecomm->checkOutUMPSA();
}

void myUMPSA::dnsResolver(const QString &domain)
{
    dns->setType(QDnsLookup::A);
    dns->setName(domain);
    connect(dns, &QDnsLookup::finished, this, &myUMPSA::dnsResults);
    dns->lookup();
}

// void myUMPSA::loginToEcomm()
// {
//     eCOMM->loginUMPSA(umpsaLogin, staff->getUsername(), staff->getPassword());
// }

void myUMPSA::testFunc()
{
    ecomm->openPath("https://www.google.com");
}

// void myUMPSA::printCookies()
// {
//     qDebug() << Q_FUNC_INFO << "After login ecom";
//     QList<QNetworkCookie> cookies = cookieJar->cookiesForUrl(umpsaLink);
//     qDebug() << Q_FUNC_INFO << "\tCookies:";
//     for (const QNetworkCookie &cookie : cookies) {
//         qDebug() << "\t" << cookie.name() << "=" << cookie.value();
//     }
// }

void myUMPSA::loginEcommBrowser()
{
    QTemporaryDir dir;
    QString path = dir.path() +"/";
    QFile file("out.html");
    if (dir.isValid()) {
        if(QDir::setCurrent(dir.path())){
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << "<html>" << Qt::endl;
            out << "<body >" << Qt::endl;
            out << "    <form id=\"auto\" method=\"post\" ";
            out << "        action=\"https://ecomm.ump.edu.my/Login\">" << Qt::endl;
            out << "        <input name=\"userName\" type=\"hidden\" value=\"" << staff->username() << "\"/>" << Qt::endl;
            out << "        <input name=\"password\" type=\"hidden\" value=\"" << staff->password() << "\"/>" << Qt::endl;
            out << "        <input name=\"level\" type=\"hidden\" value=\"Staff\"/>" << Qt::endl;
            out << "    </form>" << Qt::endl;
            out << "    <script type=\"text/javascript\">" << Qt::endl;
            out << "        function myfunc(){" << Qt::endl;
            out << "            var frm=document.getElementById(\"auto\");" << Qt::endl;
            out << "            frm.submit();" << Qt::endl;
            out << "        }" << Qt::endl;
            out << "        window.onload=myfunc;" << Qt::endl;
            out << "    </script>" << Qt::endl;
            out << "</body>" << Qt::endl;
            out << "</html>" << Qt::endl;

            file.close();
            QString link = "file://" + path + "out.html";
            QUrl url(link);
            QDesktopServices::openUrl(url);
            QThread::sleep(1);
        }
    }
}

void myUMPSA::checkMemo()
{
    const QString linkMemo = "https://ecomm.ump.edu.my/memo.jsp?action=folders&type=Y&folderID=1";
    if (ecomm) {
        ecomm->openPath(linkMemo);
    } else {
        qWarning() << "eComm not initialized";
    }
}

void myUMPSA::on_pushButtonSave_clicked()
{

    staff->setUsername(ui->username->text());
    staff->setPassword(ui->password->text());
    staff->setAutoCheckIn(ui->checkBoxCheckINAuto->checkState());
    staff->setDisableCheckOut(ui->checkBoxCheckOutBefore4pm->checkState());
    staff->setDisableOutside(ui->checkBoxDisableOutside->checkState());

    this->writeSettings(true);
    myUMPSA::hide();

    ecomm = new EcommUMPSA(staff->username(), staff->password());
    connect(ecomm, &EcommUMPSA::attendantFound, this, &myUMPSA::attendantSlot);

}

void myUMPSA::checkInSlot(QNetworkReply *reply)
{
    QRegularExpression re("[\n\t\r]");

    qDebug() << Q_FUNC_INFO  << "In finish "<< Qt::endl;
    if(reply->error())
    {
        qDebug() << Q_FUNC_INFO  << "ERROR!";
        qDebug() << Q_FUNC_INFO  << reply->errorString();

    }
    else
    {
        QString strdata = reply->readAll();
        QTextDocument doc;
        doc.setHtml(strdata);
        strdata = doc.toPlainText().remove(re).trimmed();
        if (strdata.mid(1,1) == ' '){
            strdata = strdata.mid(2,strdata.length());
        }

        QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(1);

        if ( strdata.contains("Check in failed!") ){
            //Wrong username or password
            qDebug() << strdata;
            trayIcon->showMessage(QCoreApplication::applicationName() + ": Dear " + staff->username().toUpper(),
                                 strdata, msgIcon, 5 * 1000);
        } else if (strdata.contains("Check-in failed.")) {
            // Failed! already check in today
            int indexN = strdata.indexOf("Check-in failed.",0,Qt::CaseSensitive);
            QString name = strdata.mid(0,indexN-1).trimmed();
            strdata = strdata.mid(indexN, strdata.length());
            qDebug() << "Check-in failed. : " +strdata;

            trayIcon->showMessage(name, strdata, msgIcon, 5 * 1000);
            staff->setIsCheckedIn(true);
            checkin_action->setEnabled(true);
            checkout_action->setEnabled(false);
        } else {
            // Success!
            QString mark = "Selamat datang ";
            int indexN = strdata.indexOf(mark,0,Qt::CaseSensitive) + mark.length();
            int endN = strdata.indexOf(')',0,Qt::CaseSensitive) +1;
            QString name = strdata.mid(indexN,endN-indexN).trimmed().toUpper();
            strdata = strdata.mid(endN+1, strdata.length());
            qDebug() << "Check-in successful : " +strdata;

            trayIcon->showMessage(name, strdata, msgIcon, 5 * 1000);
            staff->setIsCheckedIn(true);
            checkin_action->setEnabled(false);
            checkout_action->setEnabled(true);

        }
        reply->deleteLater();
    }
}

void myUMPSA::checkOutSlot(QNetworkReply *reply)
{
    QRegularExpression re("[\n\t\r]");

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        QString strdata = reply->readAll();
        QTextDocument doc;
        doc.setHtml(strdata);
        strdata = doc.toPlainText().remove(re).trimmed();
        if (strdata.mid(1,1) == ' '){
            strdata = strdata.mid(2,strdata.length());
        }

        QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(1);
        if (strdata == "Check out failed!.") {
            // Check out failed!
            qDebug() << strdata;
            trayIcon->showMessage(QCoreApplication::applicationName() + ": Check Out",
                                  "Dear " + staff->username() + ", " + strdata,
                                  msgIcon, 5 * 1000);
        } else if (strdata.contains("Check-out failed.")) {
            // Check out failed not check in
            QString checkOutFailed = "Check-out failed.";
            strdata = strdata.mid(checkOutFailed.length(), strdata.length()).trimmed();
            qDebug() << checkOutFailed +": "+ strdata;

            trayIcon->showMessage(checkOutFailed, strdata, msgIcon, 5 * 1000);
        } else {
            // Check out success
            int indexN = strdata.indexOf("Check-out successful",0,Qt::CaseSensitive);
            QString name = strdata.mid(1,indexN-1).trimmed();
            strdata = strdata.mid(indexN, strdata.length());

            qDebug() << strdata;
            trayIcon->showMessage(name, strdata, msgIcon, 5 * 1000);
            checkout_action->setEnabled(false);
        }
    }
    reply->deleteLater();
}

void myUMPSA::checkIPChanged()
{
    QString umpHostUrl = "www.umpsa.edu.my";
    qDebug() << Q_FUNC_INFO <<": timer call" << QTime::currentTime();
    this->dnsResolver(umpHostUrl);
}

void myUMPSA::dnsResults()
{
    if (dns->error() != QDnsLookup::NoError ) {
        qWarning() << "DNS lookup failed:" << dns->errorString();
        staff->setIsInUMPSA(false);
        return;
    }

    const auto records = dns->hostAddressRecords();
    for (const QDnsHostAddressRecord &record : records) {
        qDebug() << "Found address:" << record.value().toString();
        staff->setIsInUMPSA(
            record.value().isInSubnet(QHostAddress::parseSubnet("172.16.0.0/16"))
            );
    }

    if (staff->isInUMPSA() && !staff->isCheckedIn()) {
        this->checkInUMPSA();
        //timer needed back when date changes
        delete timer;
    }
}

void myUMPSA::getCookiesSlot(QNetworkReply *reply)
{
    QRegularExpression re("[\n\t\r]");
    if(reply->error())
    {
        qDebug() << Q_FUNC_INFO << "\n\t :ERROR!" << reply->errorString();

    }
    else
    {
        qDebug() << Q_FUNC_INFO << "\n\t:NO error";
        QString strdata = reply->readAll();
        QTextDocument doc;
        doc.setHtml(strdata);
        strdata = doc.toPlainText().remove(re).trimmed();
        qDebug() << Q_FUNC_INFO << strdata << Qt::endl;
    }
    reply->deleteLater();

}

void myUMPSA::checkedInSlot(QString time)
{
    QTime checkInTime;
    checkInTime = QTime::fromString(time, "hh:mm");
    staff->setCheckInTime(checkInTime);
}

void myUMPSA::attendantSlot(QString time)
{
    qDebug() << Q_FUNC_INFO;
    QTime checkInTime = QTime::fromString(time, "hh:mm");
    qDebug() <<"\t" << checkInTime;
    staff->setCheckInTime(checkInTime);
}

void myUMPSA::attendantNotFoundSlot()
{
    //check in
    qDebug() << "Not Check in yet";
    if (staff->isInUMPSA() && staff->autoCheckIn()) {
        qDebug() << Q_FUNC_INFO << "in umpsa and autocheck in";
    } else {
        qDebug() << Q_FUNC_INFO << "not in umpsa";
    }
}

void myUMPSA::imsAcademic()
{
    qDebug() << Q_FUNC_INFO;
    ecomm->openImsAcademic();
}

void myUMPSA::imsAcademicSlot(QString username, QString sessionId)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Username:" << username;
    qDebug() << "Session ID:" << sessionId;
    QString jnlpPath = QCoreApplication::applicationDirPath() + "/../Resources/frmservlet.jnlp";
    QString jnlpPathSource = QCoreApplication::applicationDirPath() + "/../Resources/source.jnlp";

    QFile jnlpFile(jnlpPath);
    QFile jnlpFileSource(jnlpPathSource);
    if (!jnlpFileSource.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open JNLP file:" << jnlpPathSource;
        return;
    }

    QString jnlpContent = jnlpFileSource.readAll();
    jnlpFileSource.close();

    // Replace placeholders with actual username and session ID
    jnlpContent.replace("XxXxXxX", username);
    jnlpContent.replace("HHHHHHHHHH-HHHHH", sessionId);

    // Write modified content back to temporary file
    
    if (!jnlpFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open JNLP file for writing:" << jnlpPath;
        return;
    }
    QTextStream out(&jnlpFile);
    out << jnlpContent;
    jnlpFile.close();
    // Open the JNLP file with the system's default handler
    #ifdef Q_OS_WIN
        QProcess::startDetached("javaws", QStringList() << jnlpPath);
    #else
        QDesktopServices::openUrl(QUrl::fromLocalFile(jnlpPath));
    #endif
}
