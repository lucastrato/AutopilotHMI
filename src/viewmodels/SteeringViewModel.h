
#pragma once

#include <QObject>
#include <QTimer>

class SteeringViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int heading
               READ heading
               WRITE setHeading
               NOTIFY headingChanged)

public:
    explicit SteeringViewModel(QObject *parent = nullptr);

    int heading() const;

    void setHeading(const int &heading);

signals:
    void headingChanged();

private:
    int m_heading = 127;

    QTimer m_timer;
};
