#pragma once

#include <QVector3D>

class Vertex : public QVector3D
{
public:
    Vertex();
    Vertex(float p);
    Vertex(float x, float y, float z);

    bool isInfinite() const;
    double angle(const Vertex & a, const Vertex & c) const;
    void delta(const Vertex & a, const Vertex & b);
    void updateMax(const Vertex & v);
    void updateMin(const Vertex & v);

    QVector3D toVector3D() const;
};

