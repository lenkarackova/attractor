#include "include/Vertex.h"

#include <cmath>


Vertex::Vertex(){}
Vertex::Vertex(float p) : QVector3D(p, p, p){}
Vertex::Vertex(float x, float y, float z) : QVector3D(x, y, z){}


bool Vertex::isInfinite() const
{
    return (x() < -1e10 || y() < -1e10 || z() < -1e10 || x() > 1e10 || y() > 1e10 || z() > 1e10);
}


double Vertex::angle(const Vertex & a, const Vertex & c) const
{
    double const as = distanceToPoint(c);
    double const bs = a.distanceToPoint(c);
    double const cs = distanceToPoint(a);

    if (as > (bs + cs) || bs > (as + cs) || cs > (as + bs) || 2 * as * cs == 0)
    {
        return 0.0;
    }
    else
    {
        double const angle = acos((as*as+cs*cs-bs*bs)/(2*as*cs));
        return (angle == angle) ? angle : 0.0;
    }
}


void Vertex::delta(const Vertex & a, const Vertex & b)
{
    setX(a.x() - b.x());
    setY(a.y() - b.y());
    setZ(a.z() - b.z());
}


void Vertex::updateMax(const Vertex & v)
{
    if (x() < v.x()) setX(v.x());
    if (y() < v.y()) setY(v.y());
    if (z() < v.z()) setZ(v.z());
}


void Vertex::updateMin(const Vertex & v)
{
    if (x() > v.x()) setX(v.x());
    if (y() > v.y()) setY(v.y());
    if (z() > v.z()) setZ(v.z());
}


QVector3D Vertex::toVector3D() const
{
    return QVector3D(this->x(), this->y(), this->z());
}
