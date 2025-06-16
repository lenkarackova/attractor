#ifndef PARAMETERMODEL_H
#define PARAMETERMODEL_H

#include <QAbstractListModel>

struct Parameter
{
    QString name;
    float min;
    float max;
    float value;

    Parameter(QString name, float min, float max)
        : Parameter(name, min, max, min)
    {
    }

    Parameter(QString name, float min, float max, float value)
        : name(name), min(min), max(max), value(value)
    {
    }
};

class ParameterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ParameterModelRoles
    {
        NameRole = Qt::UserRole + 1,
        ValueRole,
        MinRole,
        MaxRole,
    };
    Q_ENUM(ParameterModelRoles)

    ParameterModel(QObject* parent = nullptr);

    void setParameters(const std::vector<Parameter>& parameters);
    bool setParameterValues(std::vector<float> values, bool notify = true);

    float value(int index) const;
    float min(int index) const;
    float max(int index) const;
    int parameterCount() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<Parameter> m_parameters;
};

#endif // PARAMETERMODEL_H
