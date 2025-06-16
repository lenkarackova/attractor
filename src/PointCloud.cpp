#include "include/PointCloud.h"

#include <QVector3D>


PointCloud::PointCloud(Attractor* attractor)
    : m_attractor(attractor)
{
    updateCloud();
}


void PointCloud::setAttractor(Attractor* attractor)
{
    m_attractor = attractor;

    updateGeometry();
    update();

    emit attractorChanged();
}

void PointCloud::updateCloud()
{
    updateGeometry();
    update();
}


int PointCloud::count() const
{
    return m_pointCount;
}


void PointCloud::setCount(int value)
{
    m_pointCount = value;

    updateGeometry();
    update();

    emit countChanged(m_pointCount);
}


void PointCloud::updateGeometry()
{
    clear();

    int stride = 7 * sizeof(float);
    QByteArray vertexData(m_pointCount * stride, Qt::Initialization::Uninitialized);

    float *p = reinterpret_cast<float *>(vertexData.data());
    m_attractor->getPoints(m_pointCount, [&](QVector3D const& v, QColor const& c) {
        *p++ = v.x();
        *p++ = v.y();
        *p++ = v.z();

        *p++ = c.redF();
        *p++ = c.greenF();
        *p++ = c.blueF();
        *p++ = 1.0f;
    });

    setVertexData(vertexData);
    setStride(stride);

    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Points);

    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic,
                 0,
                 QQuick3DGeometry::Attribute::F32Type);

    addAttribute(QQuick3DGeometry::Attribute::ColorSemantic,
                 3 * sizeof(float),
                 QQuick3DGeometry::Attribute::F32Type);

    setBounds(m_attractor->min(), m_attractor->max());
}
