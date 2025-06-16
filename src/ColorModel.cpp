#include "include/ColorModel.h"

#include <QMetaEnum>


ColorModel::ColorModel(QObject *parent) : QObject { parent } { }


ColorModel::ColoringMode ColorModel::coloringMode() const
{
    return m_coloringMode;
}


QStringList ColorModel::coloringModes() const
{
    QMetaEnum metaEnum = QMetaEnum::fromType<ColoringMode>();
    QStringList enumStrings;

    for(int i = 0; i < metaEnum.keyCount(); ++i)
    {
        enumStrings.append(metaEnum.key(i));
    }

    return enumStrings;
}


QVector<QColor> ColorModel::gradientStops() const
{
    return m_colorGradients[m_gradientIndex];
}


int ColorModel::gradientIndex() const
{
    return m_gradientIndex;
}


void ColorModel::setColoringMode(ColoringMode mode)
{
    if (m_coloringMode != mode)
    {
        m_coloringMode = mode;
        emit modeChanged(m_coloringMode);
    }
}


void ColorModel::setGradientIndex(int index)
{
    if (m_gradientIndex != index && index < m_colorGradients.size())
    {
        m_gradientIndex = index;
        emit gradientChanged(index);
    }
}


QColor ColorModel::attractorColor() const
{
    return m_attractorColor;
}


Gradient ColorModel::gradient() const
{
    return Gradient(m_colorGradients[m_gradientIndex]);
}
