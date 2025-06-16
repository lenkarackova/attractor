#ifndef COLORMODEL_H
#define COLORMODEL_H

#include "Gradient.h"

#include <QObject>
#include <QString>
#include <QColor>
#include <QVector>
#include <QQmlEngine>

class ColorModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QStringList coloringModes READ coloringModes CONSTANT)
    Q_PROPERTY(ColoringMode coloringMode READ coloringMode WRITE setColoringMode NOTIFY modeChanged)
    Q_PROPERTY(QColor backgroundColor MEMBER m_backgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor attractorColor MEMBER m_attractorColor NOTIFY attractorColorChanged)
    Q_PROPERTY(QVector<QVector<QColor>> colorGradients MEMBER m_colorGradients CONSTANT)
    Q_PROPERTY(QVector<QColor> gradientStops READ gradientStops NOTIFY gradientChanged)
    Q_PROPERTY(int gradientIndex READ gradientIndex WRITE setGradientIndex NOTIFY gradientChanged)

public:
    enum ColoringMode
    {
        Single,
        Depth,
        Velocity,
        Angle,
    };
    Q_ENUM(ColoringMode)

    ColorModel(QObject *parent = nullptr);

    Gradient gradient() const;
    ColoringMode coloringMode() const;
    QColor attractorColor() const;
    QStringList coloringModes() const;
    QVector<QColor> gradientStops() const;
    int gradientIndex() const;

public slots:
    void setColoringMode(ColoringMode mode);
    void setGradientIndex(int index);

signals:
    void modeChanged(ColoringMode mode);
    void backgroundColorChanged(QColor color);
    void attractorColorChanged(QColor color);
    void gradientChanged(int index);

private:
    ColoringMode m_coloringMode = ColoringMode::Single;
    QColor m_backgroundColor = Qt::black;
    QColor m_attractorColor = Qt::white;
    int m_gradientIndex = 0;

    const QVector<QVector<QColor>> m_colorGradients = {
        { Qt::red, Qt::yellow, Qt::green, Qt::blue },
        { {217, 231, 252 }, {66, 135, 245} },
        { Qt::yellow, {245, 161, 34}, Qt::red },
        { {4, 201, 97}, {252, 237, 33} },
        { Qt::darkBlue, Qt::darkGreen },
        { {9, 32, 63}, {83, 120, 149} },
        { {113, 78, 156}, Qt::white },
        { {255,0,23}, {255,137,0}, {255,178,0}, {255,255,0}, {148,255,0} },
    };
};

#endif // COLORMODEL_H
