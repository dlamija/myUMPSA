#ifndef MYUMPSA_H
#define MYUMPSA_H

#include <QDialog>
#include "staff.h"
#include "ecommumpsa.h"

class QSystemTrayIcon;
class QMenu;
class QTimer;
class QDnsLookup;
class QNetworkReply;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class myUMPSA;
}
QT_END_NAMESPACE

/**
 * @brief The myUMPSA class represents the main application window and system tray functionality
 */
class myUMPSA : public QDialog
{
    Q_OBJECT

public:
    explicit myUMPSA(QWidget *parent = nullptr);
    ~myUMPSA();

private:
    // UI Components
    Ui::myUMPSA *ui;
    Staff *staff;
    QTimer *timer;
    QDnsLookup *dns;
    EcommUMPSA *ecomm;
    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;

    // Actions
    QAction *login_action;
    QAction *checkmemo_action;
    QAction *checkin_action;
    QAction *checkout_action;
    QAction *configure_action;
    QAction *quitAction;
    QAction *testAction;
    QAction *ims_action;

    // Constants
    static const QRegularExpression re;

    // Initialization methods
    void readSettings();
    void createActions();
    void createTrayIcon();
    void setIcon();
    void writeSettings(bool save_delete);

    // Network and DNS methods
    bool lookupUMPDNS();
    void dnsResolver(const QString &domain);
    void testFunc();

private slots:
    // E-Comm related slots
    void loginEcommBrowser();
    void checkMemo();
    void checkInUMPSA();
    void checkOutUMPSA();
    void imsAcademic();
    void on_pushButtonSave_clicked();

    // Network response slots
    void checkInSlot(QNetworkReply *reply);
    void checkOutSlot(QNetworkReply *reply);
    void checkIPChanged();
    void dnsResults();
    void getCookiesSlot(QNetworkReply *reply);
    void checkedInSlot(QString time);
    void imsAcademicSlot(QString username, QString sessionId);

    // Attendant related slots
    void attendantSlot(QString time, QString ip, QString location);
    void attendantNotFoundSlot();
};

#endif // MYUMPSA_H
