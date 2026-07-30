
#pragma once

#include <QObject>
#include <QTimer>

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

private slots:
    void updateHeading();


private:
    QString m_heading = "127";

    QTimer m_timer;
};
