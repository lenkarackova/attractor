#include "include/ColorViewModel.h"

#include <QMetaEnum>


ColorViewModel::ColorViewModel(QObject *parent) : QObject { parent } { }


ColorViewModel::ColoringMode ColorViewModel::coloringMode() const
{
    return m_coloringMode;
}


QStringList ColorViewModel::coloringModes() const
{
    QMetaEnum metaEnum = QMetaEnum::fromType<ColoringMode>();
    QStringList enumStrings;

    for(int i = 0; i < metaEnum.keyCount(); ++i)
    {
        enumStrings.append(metaEnum.key(i));
    }

    return enumStrings;
}


QVector<QColor> ColorViewModel::gradientStops() const
{
    return m_colorGradients[m_gradientIndex];
}


int ColorViewModel::gradientIndex() const
{
    return m_gradientIndex;
}


void ColorViewModel::setColoringMode(ColoringMode mode)
{
    if (m_coloringMode != mode)
    {
        m_coloringMode = mode;
        emit modeChanged(m_coloringMode);
    }
}


void ColorViewModel::setGradientIndex(int index)
{
    if (m_gradientIndex != index && index < m_colorGradients.size())
    {
        m_gradientIndex = index;
        emit gradientChanged(index);
    }
}


QColor ColorViewModel::attractorColor() const
{
    return m_attractorColor;
}


Gradient ColorViewModel::gradient() const
{
    return Gradient(m_colorGradients[m_gradientIndex]);
}
