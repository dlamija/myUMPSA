#ifndef STAFF_H
#define STAFF_H

#include <QObject>
#include <QTime>

/**
 * @brief The Staff class represents a staff member with their authentication and status information
 */
class Staff : public QObject
{
    Q_OBJECT

public:
    explicit Staff(QObject *parent = nullptr);

    // Getters
    QString username() const;
    QString password() const;
    bool isInUMPSA() const;
    bool autoCheckIn() const;
    bool disableCheckOut() const;
    bool disableOutside() const;
    bool isCheckedIn() const;
    QTime checkInTime() const;

    // Setters
    void setUsername(const QString &newUsername);
    void setPassword(const QString &newPassword);
    void setIsInUMPSA(bool newIsInUMPSA);
    void setAutoCheckIn(bool newAutoCheckIn);
    void setDisableCheckOut(bool newDisableCheckOut);
    void setDisableOutside(bool newDisableOutside);
    void setIsCheckedIn(bool newIsCheckedIn);
    void setCheckInTime(const QTime &newCheckInTime);

    QString sessionId() const;
    void setSessionId(const QString &newSessionId);

signals:

private:
    // Authentication
    QString m_username;
    QString m_password;
    QString m_sessionId;

    // Status flags
    bool m_isInUMPSA = false;
    bool m_isCheckedIn = false;
    bool m_isCheckedOut = false;
    bool m_settingSaved = false;
    bool m_autoCheckIn = false;
    bool m_disableCheckOut = false;
    bool m_disableOutside = true;

    // Time tracking
    QTime m_checkInTime;
};

#endif // STAFF_H
