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
    explicit ViewModel(QObject* parent = nullptr);

    Q_INVOKABLE void randomAttractor();

signals:
    void opacityChanged();

private:
    Attractor* attractor() { return m_attractor.get(); }
    PointCloud* pointCloud() { return m_pointCloud.get(); }
    ColorViewModel* colorModel() { return m_colorModel.get(); }

    std::unique_ptr<ColorViewModel> m_colorModel;
    std::unique_ptr<Attractor> m_attractor;
    std::unique_ptr<PointCloud> m_pointCloud;

    float m_opacity = 0.1f;
};

