#include "include/AttractorSystems.h"

#include <QRandomGenerator>


AttractorSystem::AttractorSystem(QString name, const std::vector<Parameter>& parameters, ParameterModel* model)
    : m_name(name)
    , m_p(model)
{
    for (int i = 0; i < parameters.size(); ++i)
    {
        m_initialParameters.push_back(parameters[i].value);
    }

    m_p->setParameters(parameters);
};


AttractorSystem::AttractorSystem(int count, float min, float max, ParameterModel* model)
    : m_p(model)
{
    std::vector<Parameter> p;

    for (int i = 0; i < count; i++)
    {
        QString name = "P" + QString::number(i + 1);
        p.push_back(Parameter(name, min, max, min));
    }

    m_p->setParameters(p);
}


bool AttractorSystem::setParameters(std::vector<float> p)
{
    return m_p->setParameterValues(p);
}


QString AttractorSystem::name() const
{
    return m_name;
}


void AttractorSystem::reset()
{
    m_p->setParameterValues(m_initialParameters);
}


LorenzAttractor::LorenzAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Lorenz",
        {
            { "A", -3.0f, 20.0f, 11.821 },
            { "B",  0.0f, 20.0f, 17.450 },
            { "C",  0.0f, 20.0f,  2.496 },
            { "dT", 0.0f,  0.5f,  0.036 }
        },
        model
    )
{}


void LorenzAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(v.x() + m_p->value(3) * m_p->value(0) * (v.y() - v.x()));
    v1.setY(v.y() + m_p->value(3) * (v.x() * (m_p->value(1) - v.z()) - v.y()));
    v1.setZ(v.z() + m_p->value(3) * (v.x() * v.y() - m_p->value(2) * v.z()));

    v = v1;
}


Lorenz84Attractor::Lorenz84Attractor(ParameterModel* model)
    : AttractorSystem
    (
        "Lorenz84",
        {
            { "A",  0.0f, 20.0f, 10.0 },
            { "B",  0.0f, 20.0f, 0.004 },
            { "F",  0.0f, 20.0f, 10.0 },
            { "G",  0.0f, 20.0f, 6.230 },
            { "dT", 0.0f,  0.5f, 0.099 },
        },
        model
    ) {}


void Lorenz84Attractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(v.x() + m_p->value(4) * (-m_p->value(0) * v.x() - v.y() * v.y() - v.z() * v.z() + m_p->value(0) * m_p->value(2)));
    v1.setY(v.y() + m_p->value(4) * (-v.y() + v.x() * v.y() -  m_p->value(1) * v.x() * v.z() + m_p->value(3)));
    v1.setZ(v.z() + m_p->value(4) * (-v.z() + m_p->value(1) * v.x() * v.y() + v.x() * v.z()));

    v = v1;
}


RosslerAttractor::RosslerAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Rossler",
        {
            Parameter("A", -2.0f, 2.0f, 0.373),
            Parameter("B", -2.0f, 2.0f, -0.828),
            Parameter("C", -2.0f, 2.0f, 0.989),
        },
        model
    ) {}


void RosslerAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(-v.y() - v.z());
    v1.setY(v.x() + m_p->value(0) * v.y());
    v1.setZ(m_p->value(1) - m_p->value(2) * v.z() + v.x() * v.z());

    v = v1;
}


PickoverAttractor::PickoverAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Clifford Pickover",
        {
            Parameter("A", -3.0f, 3.0f, 2.227),
            Parameter("B", 0.0f, 3.0f, 0.916),
            Parameter("C", -3.0f, 3.0f, 0.786),
            Parameter("D", 0.0f, 3.0f, 1.156)
        },
          model
    ) {}


void PickoverAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(sin(m_p->value(0)*v.y()) - v.z()*cos(m_p->value(1)*v.x()));
    v1.setY(v.z()*sin(m_p->value(2)*v.x()) - cos(m_p->value(3)*v.y()));
    v1.setZ(sin(v.x()));

    v = v1;
}


CliffordAttractor::CliffordAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Clifford Pickover 2",
        {
            Parameter("A", -2.0f, 2.0f, 1.5),
            Parameter("B", -2.0f, 2.0f, -1.8),
            Parameter("C", -2.0f, 2.0f, 1.6),
            Parameter("D",  0.0f, 2.0f, 0.9)
        },
          model
    )
{}


void CliffordAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(sin(m_p->value(0)*v.y()) + m_p->value(2)*cos(m_p->value(0)*v.x()));
    v1.setY(sin(m_p->value(1)*v.x()) + m_p->value(3)*cos(m_p->value(1)*v.y()));
    v1.setZ(sin(m_p->value(2)*v.x()) + m_p->value(0)*cos(m_p->value(2)*v.z()));

    v = v1;
}


CliffordRectangleAttractor::CliffordRectangleAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Clifford Pickover Rectangle",
        {
            Parameter("A", -2.0f, 2.0f, 2.0),
            Parameter("B", -2.0f, 2.0f, 2.0),
            Parameter("C", -2.0f, 2.0f, 2.0),
            Parameter("D",  0.0f, 2.0f, 2.0)
        },
          model
    )
{}


void CliffordRectangleAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX((m_p->value(3) * sin(m_p->value(0) * v.y()) - sin(m_p->value(1) * v.x())) - m_p->value(0) * cos(v.x() - m_p->value(2)));
    v1.setY((m_p->value(2) * cos(m_p->value(0) * v.x()) + cos(m_p->value(1) * v.y())) - m_p->value(1) * sin(v.y() - m_p->value(3)));
    v1.setZ(v.y());

    v = v1;
}


DeJongAttractor::DeJongAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Peter de Jong",
        {
            Parameter("A", -3.0f, 3.0f, 1.4),
            Parameter("B", -3.0f, 3.0f, -2.3),
            Parameter("C", -3.0f, 3.0f, 2.4),
            Parameter("D", -3.0f, 3.0f, -2.1)
        },
          model
    )
{}


void DeJongAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(sin(m_p->value(0)*v.y()) - cos(m_p->value(1)*v.x()));
    v1.setY(sin(m_p->value(2)*v.x()) + cos(m_p->value(3)*v.y()));
    v1.setZ(sin(v.x()));

    v = v1;
}


DeJong2Attractor::DeJong2Attractor(ParameterModel* model)
    : AttractorSystem
    (
        "Svensson",
        {
            Parameter("A", -3.0f, 3.0f),
            Parameter("B", -3.0f, 3.0f),
            Parameter("C", -3.0f, 3.0f),
            Parameter("D",-10.0f, 3.0f)
        },
          model
    )
{}


void DeJong2Attractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(m_p->value(3) * sin(m_p->value(0)*v.y()) - sin(m_p->value(1)*v.x()));
    v1.setY(m_p->value(2) * cos(m_p->value(0)*v.x()) - cos(m_p->value(1)*v.y()));
    v1.setZ(sin(v.x()));

    v = v1;
}


PolynomialAAttractor::PolynomialAAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Polynomial A",
        {
            Parameter("P1", 0.0f, 2.0f),
            Parameter("P2", 0.0f, 2.0f),
            Parameter("P3", 0.0f, 2.0f)
        },
          model
    )
{}


void PolynomialAAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(m_p->value(0) + v.y() - v.z()*v.y());
    v1.setY(m_p->value(1) + v.z() - v.x()*v.z());
    v1.setZ(m_p->value(2) + v.x() - v.y()*v.x());

    v = v1;
}


PolynomialBAttractor::PolynomialBAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Polynomial B",
        {
            Parameter("P1", -1.2f, 1.2f, 0.698),
            Parameter("P2", -1.2f, 1.2f, 0.280),
            Parameter("P3", -1.2f, 1.2f, 0.212),
            Parameter("P4", -1.2f, 1.2f, -0.196),
            Parameter("P5", -1.2f, 1.2f, 0.808),
            Parameter("P6", -1.2f, 1.2f, 1.142)
        },
          model
    )
{}


void PolynomialBAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(m_p->value(0) + v.y() - v.z() * (m_p->value(1) + v.y()));
    v1.setY(m_p->value(2) + v.z() - v.x() * (m_p->value(3) + v.z()));
    v1.setZ(m_p->value(4) + v.x() - v.y() * (m_p->value(5) + v.x()));

    v = v1;
}


PolynomialCAttractor::PolynomialCAttractor(ParameterModel* model)
    : AttractorSystem(18, -1.5f, 1.5f, model)
{
    m_name = "Polynomial C";
}


void PolynomialCAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(m_p->value(0) + v.x() * (m_p->value(1) + m_p->value(2) *v.x() + m_p->value(3) * v.y()) + v.y() * (m_p->value(4) + m_p->value(5) * v.y()));
    v1.setY(m_p->value(6) + v.y() * (m_p->value(7) + m_p->value(8) * v.y() + m_p->value(9) *v.z()) + v.z() * (m_p->value(10) + m_p->value(11) * v.z()));
    v1.setZ(m_p->value(12) + v.z() * (m_p->value(13) + m_p->value(14) * v.z() + m_p->value(15) * v.x()) + v.x() * (m_p->value(16) + m_p->value(17) * v.x()));

    v = v1;
}


TinkerbellAttractor::TinkerbellAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Tinkerbell",
        {
            Parameter("A", -10.0f, 10.0f, -4.444),
            Parameter("B", -10.0f, 10.0f, -0.556),
            Parameter("C", -10.0f, 10.0f, 0.549),
            Parameter("D", -10.0f, 10.0f, 0.549)
        },
          model
    )
{}


void TinkerbellAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(v.x() * v.x() - v.y() * v.y() + (m_p->value(0) * v.x()) + (m_p->value(1) * v.y()));
    v1.setY(2 * v.x() * v.y() + (m_p->value(2) * v.x()) + (m_p->value(3) * v.y()));
    v1.setZ(v1.y());

    v = v1;
}


PolynomialAbsAttractor::PolynomialAbsAttractor(ParameterModel* model)
    : AttractorSystem(21, -1.5f, 1.5f, model)
{
    m_name = "Polynomial Function: Abs";
}


void PolynomialAbsAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(m_p->value(0) + m_p->value(1) * v.x() + m_p->value(2) * v.y() + m_p->value(3) * v.z() + m_p->value(4) * abs(v.x()) + m_p->value(5) * abs(v.y()) + m_p->value(6) * abs(v.z()));
    v1.setY(m_p->value(7) + m_p->value(8) * v.x() + m_p->value(9) * v.y() + m_p->value(10) * v.z() + m_p->value(11) * abs(v.x()) + m_p->value(12) * abs(v.y()) + m_p->value(13) * abs(v.z()));
    v1.setZ(m_p->value(14) + m_p->value(15) * v.x() + m_p->value(16) * v.y() + m_p->value(17) * v.z() + m_p->value(18) * abs(v.x()) + m_p->value(19) * abs(v.y()) + m_p->value(20) * abs(v.z()));

    v = v1;
}


PolynomialPowerAttractor::PolynomialPowerAttractor(ParameterModel* model)
    : AttractorSystem(24, -1.5f, 1.5f, model)
{
    m_name = "Polynomial Function: Power";
}


void PolynomialPowerAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(m_p->value(0) + m_p->value(1) * v.x() + m_p->value(2) * v.y() + m_p->value(3) * v.z() + m_p->value(4) * abs(v.x()) + m_p->value(5) * abs(v.y()) + m_p->value(6) * pow(abs(v.z()), m_p->value(7)));
    v1.setY(m_p->value(8) + m_p->value(9) * v.x() + m_p->value(10) * v.y() + m_p->value(11) * v.z() + m_p->value(12) * abs(v.x()) + m_p->value(13) * abs(v.y()) + m_p->value(14) * pow(abs(v.z()), m_p->value(15)));
    v1.setZ(m_p->value(16) + m_p->value(17) * v.x() + m_p->value(18) * v.y() + m_p->value(19) * v.z() + m_p->value(20) * abs(v.x()) + m_p->value(21) * abs(v.y()) + m_p->value(22) * pow(abs(v.z()), m_p->value(23)));

    v = v1;
}


RabinovichFabrikantAttractor::RabinovichFabrikantAttractor(ParameterModel* model)
    : AttractorSystem
    (
        "Rabinovich-Fabrikant",
        { Parameter("A", 0.4f, 0.6f, 0.510), Parameter("B", -1.0f, 0.5f, -0.351) },
        model
    )
{}


void RabinovichFabrikantAttractor::next(Vertex & v)
{
    Vertex v1;

    v1.setX(v.y() * (v.z() - 1 + v.x() * v.x()) + m_p->value(1) * v.x());
    v1.setY(v.x() * (3 * v.z() + 1 - v.x() * v.x()) + m_p->value(1) * v.y());
    v1.setZ(-2 * v.z() * (m_p->value(0) + v.x() * v.y()));

    v = v1;
}
