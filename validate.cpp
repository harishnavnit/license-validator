#include "validate.h"

#include <QDir>
#include <QDate>
#include <QCryptographicHash>
#include <QtNetwork/QNetworkInterface>

Validate::Validate(QObject *parent)
    : QObject(parent), m_licenseFilePath("")
{}

Validate::Validate(QUrl path, QObject *parent)
    : QObject(parent), m_licenseFilePath(path)
{}

bool Validate::isValidLicense(QUrl path) const
{
    const QString interfaceName = "wlo1";
    QNetworkInterface interface = QNetworkInterface::interfaceFromName(interfaceName);
    QString systemMacAddress = interface.hardwareAddress();
    QByteArray systemMacHash = QCryptographicHash::hash(QByteArray::fromStdString(systemMacAddress.toStdString()),
                                                        QCryptographicHash::Sha1);

    QFile licenseFile(path.adjusted(QUrl::RemoveScheme).toString());

    if ( !licenseFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug() << "Failed to open/read license file";
        return false;
    }

    QByteArray macHash = licenseFile.readLine();
    macHash.remove(macHash.size()-1, 1);        // remove the trailing '/n' inserting while appending date

    qDebug() << "System MAC hash = " << systemMacHash;
    qDebug() << "License MAC hash = " << macHash;

    if (macHash == systemMacHash) {
        QByteArray expiryDate = licenseFile.readLine();
        qDebug() << "License expiry date = " << QString::fromStdString(expiryDate.toStdString());

        QDate licenseExpiryDate = QDate::fromString( QString::fromStdString(expiryDate.toStdString()), "dd.MM.yyyy" );
        if (licenseExpiryDate > QDate::currentDate()) {
            qDebug() << "License is beyond the expiry date";
            return false;
        }
    } else {
        qDebug() << "MAC addresses do not match";
        return false;
    }

    licenseFile.close();

    return true;
}

QUrl Validate::getLicenseFilePath() const
{
    return m_licenseFilePath;
}

void Validate::setLicenseFilePath(QUrl path)
{
    m_licenseFilePath = path;
}

void Validate::checkLicenseFile(QUrl path)
{
    isValidLicense(path) ? qDebug() << "Valid license" : qDebug() << "Invalid license";
}
