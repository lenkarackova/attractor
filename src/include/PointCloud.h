#pragma once

#include "Attractor.h"

#include <QQuick3DGeometry>

class PointCloud : public QQuick3DGeometry
{
    Q_OBJECT

    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    PointCloud(Attractor* attractor);

    int count() const;

public slots:
    void updateCloud();
    void setCount(int value);
    void setAttractor(Attractor* attractor);

signals:
    void countChanged(int count);
    void attractorChanged();

private:
    void updateGeometry();

    int m_pointCount = 800000;
    Attractor* m_attractor;
};

