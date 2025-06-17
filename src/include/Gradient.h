#pragma once

#include <QColor>
#include <QStringList>
#include <QVector>

class Gradient
{

public:
    Gradient(QVector<QColor> const & colorStops, double min = 0.0, double max = 1.0);

    QColor getColor(double value) const;
    void setMin(double min);
    void setMax(double max);
    void setColorStops(QVector<QColor> const & colorStops);

    QStringList stopsList() const;
    QVector<QColor> stops() const;

private:
    double m_min, m_max;
    QVector<QColor> m_colorStops;

    QColor interpolate(const QColor & c1, const QColor & c2, double v) const;
};

