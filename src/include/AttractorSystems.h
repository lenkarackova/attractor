#ifndef ATTRACTORSYSTEMS_H
#define ATTRACTORSYSTEMS_H

#include "Vertex.h"
#include "ParameterModel.h"

#include <QString>


class AttractorSystem
{
public:
    virtual void next(Vertex & v) = 0;

    bool setParameters(std::vector<float> parameters);
    QString name() const;
    //QAbstractListModel* parameterModel();
    void reset();
    //void random();

protected:
    AttractorSystem(QString name, const std::vector<Parameter>& parameters, ParameterModel* model);
    AttractorSystem(int count, float min, float max, ParameterModel* model);
    QString m_name;
    ParameterModel* m_p;

private:
    std::vector<float> m_initialParameters;
    //int m_count;
};


class LorenzAttractor : public AttractorSystem
{
public:
    LorenzAttractor(ParameterModel* model);
    virtual void next(Vertex & v) override;
};


class Lorenz84Attractor : public AttractorSystem
{
public:
    Lorenz84Attractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class RosslerAttractor : public AttractorSystem
{
public:
    RosslerAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class PickoverAttractor : public AttractorSystem
{
public:
    PickoverAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class CliffordAttractor : public AttractorSystem
{
public:
    CliffordAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class CliffordRectangleAttractor : public AttractorSystem
{
public:
    CliffordRectangleAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class DeJongAttractor : public AttractorSystem
{
public:
    DeJongAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class DeJong2Attractor : public AttractorSystem
{
public:
    DeJong2Attractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class PolynomialAAttractor : public AttractorSystem
{
public:
    PolynomialAAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class PolynomialBAttractor : public AttractorSystem
{
public:
    PolynomialBAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class PolynomialCAttractor : public AttractorSystem
{
public:
    PolynomialCAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class TinkerbellAttractor : public AttractorSystem
{
public:
    TinkerbellAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class PolynomialAbsAttractor : public AttractorSystem
{
public:
    PolynomialAbsAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class PolynomialPowerAttractor : public AttractorSystem
{
public:
    PolynomialPowerAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


class RabinovichFabrikantAttractor : public AttractorSystem
{
public:
    RabinovichFabrikantAttractor(ParameterModel* model);
    virtual void next(Vertex & v);
};


/*class Hopalong : public AttractorSystem
{
public:
    Hopalong()
    {
        name = "Hopalong";
        parameters = { Parameter("A", 0.0f, 10.0f), Parameter("B", 0.0f, 10.0f), Parameter("C", 0.0f, 10.0f) };

        initial_parameters = { 2.0, 7.0, 4.0 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(v.y() - 1 - sqrt(abs(p.at(1) * v.x() - 1 - p.at(2))) * sgn(v.x() - 1));
            v1.setY(p.at(0) - v.x() - 1);
            v1.setZ(v1.y());

            v = v1;
        }
    }
};


class GumowskiMira : public AttractorSystem
{
public:
    GumowskiMira()
    {
        name = "Gumowski-Mira";
        parameters = { Parameter("A", -1.0f, 1.0f), Parameter("B", -1.0f, 1.0f) };

        initial_parameters = { 0.744, 0.130 };
    }

    double mira(double x, double a)
    {
        return a * x + 2.0 * (1.0 - a) * x * x / (1.0 + x * x);
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(v.y() + p.at(0) * (1 - p.at(1) * v.y() * v.y()) * v.y() + mira(v.x(), p.at(0)));
            //v1.x = p.at(1) * v.y + mira(v.x, p.at(0));
            v1.setY(- v.x() + mira(v1.x(), p.at(0)));
            v1.setZ(v1.y());

            v = v1;
        }
    }
};


class ChenAttractor : public AttractorSystem
{
public:
    ChenAttractor()
    {
        name = "Chen";
        parameters =
            {
                Parameter("A", 0.0f, 35.0f),
                Parameter("B", 0.0f, 3.0f),
                Parameter("C", 0.0f, 28.0f)
            };

        initial_parameters = { 35.0, 3.0, 28.0 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            //journals.tubitak.gov.tr/elektrik/issues/elk-10-18-2/elk-18-2-3-0906-67.pdf
            v1.setX(p.at(0) * (v.y() - v.x()));
            v1.setY(- v.x() * v.z() + p.at(2) * v.y());
            v1.setZ(v.x() * v.y() - p.at(1) * v.z());

            v = v1;
        }
    }
};


class Rampe1 : public AttractorSystem
{
public:
    Rampe1()
    {
        name = "Rampe 1";

        parameters =
            {
                Parameter("A", -2.0f, 2.0f),
                Parameter("B", -2.0f, 2.0f),
                Parameter("C", -2.0f, 2.0f),
                Parameter("D", -2.0f, 2.0f),
                Parameter("E", -2.0f, 2.0f),
                Parameter("F", -2.0f, 2.0f)
            };

        initial_parameters = { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(v.z() * sin(p.at(0) * v.x()) + cos(p.at(1) * v.y()));
            v1.setY(v.x() * sin(p.at(2) * v.y()) + cos(p.at(3) * v.z()));
            v1.setZ(v.y() * sin(p.at(4) * v.z()) + cos(p.at(5) * v.x()));

            v = v1;
        }
    }
};


class Rampe2 : public AttractorSystem
{
public:
    Rampe2()
    {
        name = "Rampe 2";

        parameters =
            {
                Parameter("A", -1.0f, 1.0f),
                Parameter("B", -1.0f, 1.0f),
                Parameter("C", -1.0f, 1.0f),
                Parameter("D", -1.0f, 1.0f),
                Parameter("E", -1.0f, 1.0f),
                Parameter("F", -1.0f, 1.0f)
            };

        initial_parameters = { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(v.z() * sin(p.at(0) * v.x()) + acos(p.at(1) * v.y()));
            v1.setY(v.x() * sin(p.at(2) * v.y()) + acos(p.at(3) * v.z()));
            v1.setZ(v.y() * sin(p.at(4) * v.z()) + acos(p.at(5) * v.x()));

            v = v1;
        }
    }
};


class Rampe3 : public AttractorSystem
{
public:
    Rampe3()
    {
        name = "Rampe 3";

        parameters =
            {
                Parameter("A", -10.0f, 10.0f),
                Parameter("B", -10.0f, 10.0f),
                Parameter("C", -10.0f, 10.0f),
                Parameter("D", -10.0f, 10.0f),
                Parameter("E", -10.0f, 10.0f),
                Parameter("F", -10.0f, 10.0f)
            };

        initial_parameters = { -4.990, 0.155, -0.010, -3.378, 2.484, -4.887 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(v.x() * v.z() * sin(p.at(0) * v.x()) - cos(p.at(1) * v.y()));
            v1.setY(v.y() * v.x() * sin(p.at(2) * v.y()) - cos(p.at(3) * v.z()));
            v1.setZ(v.z() * v.y() * sin(p.at(4) * v.z()) - cos(p.at(5) * v.x()));

            v = v1;
        }
    }
};


class Rampe4 : public AttractorSystem
{
public:
    Rampe4()
    {
        name = "Rampe 4";

        parameters =
            {
                Parameter("A", -20.0f, 20.0f),
                Parameter("B", -20.0f, 20.0f),
                Parameter("C", -20.0f, 20.0f)
            };

        initial_parameters = { 10.421, -15.801, -5.837 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(v.x() * sin(p.at(0) * v.x()) + cos(p.at(0) * v.y()));
            v1.setY(v.y() * sin(p.at(1) * v.y()) + cos(p.at(1) * v.z()));
            v1.setZ(v.z() * sin(p.at(2) * v.z()) + cos(p.at(2) * v.x()));

            v = v1;
        }
    }
};


class Rampe8 : public AttractorSystem
{
public:
    Rampe8()
    {
        name = "Rampe 8";

        parameters =
            {
                Parameter("A", -10.0f, 10.0f),
                Parameter("B", -10.0f, 10.0f),
                Parameter("C", -10.0f, 10.0f)
            };

        initial_parameters = { -4.444, -0.556, 0.549 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(v.z() * sin(p.at(0) * v.x()) - cos(v.y()));
            v1.setY(v.x() * cos(p.at(1) * v.y()) + sin(v.z()));
            v1.setZ(v.y() * sin(p.at(2) * v.z()) - cos(v.x()));

            v = v1;
        }
    }
};


class Ikeda : public AttractorSystem
{
public:
    Ikeda()
    {
        name = "Ikeda";

        parameters =
            {
                Parameter("A", -10.0f, 10.0f),
                Parameter("B", -10.0f, 10.0f),
                Parameter("C", -10.0f, 10.0f),
                Parameter("D", -10.0f, 10.0f)
            };

        initial_parameters = { 2.227, 0.916, 0.786, 1.156 };
    }

    virtual void next(Vertex & v, const std::vector<double> & p)
    {
        if (checkParameters(p))
        {
            Vertex v1;

            v1.setX(p.at(0) + p.at(1) *(v.x()*cos(v.z()) - v.y()*sin(v.z())));
            v1.setY(p.at(1) *(v.x()*sin(v.z()) + v.y()*cos(v.z())));
            v1.setZ(p.at(2) - p.at(3)/(1+v.x()*v.x()+v.y()*v.y()));

            v = v1;
        }
    }
};*/

#endif // ATTRACTORSYSTEMS_H
