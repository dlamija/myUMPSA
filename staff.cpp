#include "staff.h"

Staff::Staff(QObject *parent)
    : QObject{parent}
{
    //username = "";
}

QString Staff::username() const
{
    return m_username;
}

void Staff::setUsername(const QString &newUsername)
{
    m_username = newUsername;
}

QString Staff::password() const
{
    return m_password;
}

void Staff::setPassword(const QString &newPassword)
{
    m_password = newPassword;
}

bool Staff::isInUMPSA() const
{
    return m_isInUMPSA;
}

void Staff::setIsInUMPSA(bool newIsInUMPSA)
{
    m_isInUMPSA = newIsInUMPSA;
}

bool Staff::autoCheckIn() const
{
    return m_autoCheckIn;
}

void Staff::setAutoCheckIn(bool newAutoCheckIn)
{
    m_autoCheckIn = newAutoCheckIn;
}

bool Staff::disableCheckOut() const
{
    return m_disableCheckOut;
}

void Staff::setDisableCheckOut(bool newDisableCheckOut)
{
    m_disableCheckOut = newDisableCheckOut;
}

bool Staff::disableOutside() const
{
    return m_disableOutside;
}

void Staff::setDisableOutside(bool newDisableOutside)
{
    m_disableOutside = newDisableOutside;
}

bool Staff::isCheckedIn() const
{
    return m_isCheckedIn;
}

void Staff::setIsCheckedIn(bool newIsCheckedIn)
{
    m_isCheckedIn = newIsCheckedIn;
}

QTime Staff::checkInTime() const
{
    return m_checkInTime;
}

void Staff::setCheckInTime(const QTime &newCheckInTime)
{
    m_checkInTime = newCheckInTime;
}
