
#pragma once

#include <QObject>

class SteeringViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString heading
               READ heading
               WRITE setHeading
               NOTIFY headingChanged)

public:
    explicit SteeringViewModel(QObject *parent = nullptr);

    QString heading() const;

    void setHeading(const QString &heading);

signals:
    void headingChanged();

private:
    QString m_heading = "127";
};
