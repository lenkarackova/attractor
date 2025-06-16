#include "include/Gradient.h"


Gradient::Gradient(QVector<QColor> const & colorStops, double min, double max)
    : m_colorStops(colorStops), m_min(min), m_max(max) {}


QColor Gradient::getColor(double value) const
{
    if (m_colorStops.size() < 1 || value != value)
    {
        return QColor(0,0,0);
    }

    // outliers
    if (m_colorStops.size() == 1 || value <= m_min || m_max == m_min)
    {
        return m_colorStops.front();
    }

    if (value >= m_max)
    {
        return m_colorStops.back();
    }

    // find the "bin" that value falls in
    const double range = m_max - m_min;
    const double v = value - m_min;
    const double step = range / (static_cast<double>(m_colorStops.size()-1));
    const int bin = static_cast<int>(v / step);

    // normalize value in the interval (0,1]
    const double normalized = (v - bin*step) / step;

    return interpolate(m_colorStops.at(bin), m_colorStops.at(bin+1), normalized);
}


void Gradient::setMin(double min)
{
    m_min = min;
}


void Gradient::setMax(double max)
{
    m_max = max;
}


void Gradient::setColorStops(const QVector<QColor> & colorStops)
{
    m_colorStops = colorStops;
}


QStringList Gradient::stopsList() const
{
    QStringList list;

    for(QColor const &color: m_colorStops)
    {
        list.append(color.name());
    }

    return list;
}


QColor Gradient::interpolate(const QColor & c1, const QColor & c2, double v) const
{
    if (v <= 0.0) return c1;
    if (v >= 1.0) return c2;

    const double r = (1.0 - v) * c1.red() + v * c2.red();
    const double g = (1.0 - v) * c1.green() + v * c2.green();
    const double b = (1.0 - v) * c1.blue() + v * c2.blue();

    return QColor(r,g,b);
}
