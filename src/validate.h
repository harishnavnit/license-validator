#ifndef VALIDATE_H
#define VALIDATE_H

#include <QUrl>
#include <QFile>
#include <QObject>

class Validate : public QObject
{
    Q_OBJECT

public:
    // Constructor
    explicit Validate(QObject *parent=0);
    Validate(QUrl path, QObject *parent=0);

    // Getter methods
    QUrl getLicenseFilePath() const;
    bool isValidLicense(QUrl path) const;

    // Setter method
    void setLicenseFilePath(QUrl path);

public slots:
    void checkLicenseFile(QUrl path);

private:
    QUrl m_licenseFilePath;
};

#endif // VALIDATE_H
