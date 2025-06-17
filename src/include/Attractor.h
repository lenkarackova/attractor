#pragma once

#include "AttractorSystems.h"
#include "ColorViewModel.h"
#include "ParameterListModel.h"
#include "AttractorData.h"

#include <QObject>

class Attractor : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QStringList attractorTypes READ attractorTypes CONSTANT)
    Q_PROPERTY(QAbstractListModel* parameterModel READ parameterModel NOTIFY attractorChanged)
    Q_PROPERTY(AttractorType type READ type WRITE setType NOTIFY attractorChanged)
    Q_PROPERTY(QVector3D center READ center NOTIFY attractorChanged)
    Q_PROPERTY(QVector3D scale READ scale NOTIFY attractorChanged)

public:
    enum class AttractorType
    {
        Lorenz,
        Lorenz84,
        Rossler,
        Pickover,
        Clifford,
        CliffordRectangle,
        DeJong,
        DeJong2,
        PolynomialA,
        PolynomialB,
        PolynomialC,
        PolynomialAbs,
        PolynomialPower,
        RabinovichFabrikant,
    };
    Q_ENUM(AttractorType)

    Attractor(AttractorType type = AttractorType::Lorenz, ColorViewModel* colorModel = nullptr, QObject* parent = nullptr);
    Attractor(AttractorType type, std::vector<float> parameters, ColorViewModel* colorModel = nullptr, QObject* parent = nullptr);

    Q_INVOKABLE void exportOBJ(QString filename, int count);

    QStringList attractorTypes();
    QAbstractListModel* parameterModel();
    QVector3D min() const;
    QVector3D max() const;
    QVector3D center() const;
    QVector3D scale() const;
    AttractorType type() const;

    template <typename OutputIterator>
    void getPoints(unsigned long int iterations,
                   OutputIterator out);

public slots:
    bool random();    
    void setType(AttractorType type);
    void setParameters(std::vector<float> parameters);
    void setColorModel(ColorViewModel* colorModel);

signals:
    void typeChanged(AttractorType type);
    void parametersChanged();
    void centerChanged();
    void scaleChanged();
    void attractorChanged();

private slots:
    void onParametersChanged();

private:
    void initialize(bool tests = true);

    AttractorType m_type = AttractorType::Clifford;
    AttractorData m_data;
    std::unique_ptr<AttractorSystem> m_system;
    ColorViewModel* m_colorModel = nullptr;
    ParameterListModel* m_parameterModel = nullptr;
};

#include "Attractor.inl"
