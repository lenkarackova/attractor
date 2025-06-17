#pragma once

#include "Attractor.h"
#include "PointCloud.h"
#include "ColorViewModel.h"

#include <QObject>
#include <QQmlEngine>

class ViewModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Attractor* attractor READ attractor CONSTANT)
    Q_PROPERTY(PointCloud* pointCloud READ pointCloud CONSTANT)
    Q_PROPERTY(ColorViewModel* colorModel READ colorModel CONSTANT)

    Q_PROPERTY(float opacity MEMBER m_opacity NOTIFY opacityChanged)

public:
    ViewModel();

    Q_INVOKABLE void randomAttractor();

signals:
    void opacityChanged();

private:
    Attractor* attractor() { return &m_attractor; }
    PointCloud* pointCloud() { return &m_pointCloud; }
    ColorViewModel* colorModel() { return &m_colorModel; }

    ColorViewModel m_colorModel;
    Attractor m_attractor;
    PointCloud m_pointCloud;

    float m_opacity = 0.1;
};

