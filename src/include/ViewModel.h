#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "Attractor.h"
#include "PointCloud.h"
#include "ColorModel.h"

#include <QObject>
#include <QQmlEngine>

class ViewModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Attractor* attractor MEMBER m_attractor NOTIFY attractorChanged)
    Q_PROPERTY(PointCloud* pointCloud MEMBER m_pointCloud NOTIFY pointCloudChanged)
    Q_PROPERTY(ColorModel* colorModel MEMBER m_colorModel NOTIFY colorsChanged)

    Q_PROPERTY(float opacity MEMBER m_opacity NOTIFY opacityChanged)

public:
    ViewModel();

    Q_INVOKABLE void randomAttractor();

signals:
    void pointCloudChanged();
    void colorsChanged();
    void attractorChanged();
    void backgroundChanged();
    void opacityChanged();

private:
    PointCloud* m_pointCloud;
    ColorModel* m_colorModel;
    Attractor* m_attractor;

    float m_opacity = 0.5;
};

#endif // VIEWMODEL_H
