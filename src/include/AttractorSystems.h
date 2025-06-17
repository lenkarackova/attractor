#pragma once

#include "Vertex.h"
#include "ParameterListModel.h"

#include <QString>


class AttractorSystem
{
public:
    virtual void next(Vertex & v) = 0;

    bool setParameters(std::vector<float> parameters);
    QString name() const;
    void reset();

protected:
    AttractorSystem(QString name, const std::vector<Parameter>& parameters, ParameterListModel* model);
    AttractorSystem(int count, float min, float max, ParameterListModel* model);
    QString m_name;
    ParameterListModel* m_p;

private:
    std::vector<float> m_initialParameters;
};


class LorenzAttractor : public AttractorSystem
{
public:
    LorenzAttractor(ParameterListModel* model);
    virtual void next(Vertex & v) override;
};


class Lorenz84Attractor : public AttractorSystem
{
public:
    Lorenz84Attractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class RosslerAttractor : public AttractorSystem
{
public:
    RosslerAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class PickoverAttractor : public AttractorSystem
{
public:
    PickoverAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class CliffordAttractor : public AttractorSystem
{
public:
    CliffordAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class CliffordRectangleAttractor : public AttractorSystem
{
public:
    CliffordRectangleAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class DeJongAttractor : public AttractorSystem
{
public:
    DeJongAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class DeJong2Attractor : public AttractorSystem
{
public:
    DeJong2Attractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class PolynomialAAttractor : public AttractorSystem
{
public:
    PolynomialAAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class PolynomialBAttractor : public AttractorSystem
{
public:
    PolynomialBAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class PolynomialCAttractor : public AttractorSystem
{
public:
    PolynomialCAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class TinkerbellAttractor : public AttractorSystem
{
public:
    TinkerbellAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class PolynomialAbsAttractor : public AttractorSystem
{
public:
    PolynomialAbsAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class PolynomialPowerAttractor : public AttractorSystem
{
public:
    PolynomialPowerAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};


class RabinovichFabrikantAttractor : public AttractorSystem
{
public:
    RabinovichFabrikantAttractor(ParameterListModel* model);
    virtual void next(Vertex & v);
};
