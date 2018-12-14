#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QDebug>

class Organization final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Organization)

public:
    static Organization& getInstance();

    QString id = "1";
    QString deviceName = "nayttolaite";
    QString apiKey = "null";

private:
    Organization() = default;
    ~Organization() = default;
};

#endif // ORGANIZATION_H