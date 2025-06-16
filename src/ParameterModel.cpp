#include "include/ParameterModel.h"


ParameterModel::ParameterModel(QObject *parent) {}


int ParameterModel::rowCount(const QModelIndex &parent) const
{
    return m_parameters.size();
}


void ParameterModel::setParameters(const std::vector<Parameter>& parameters)
{
    beginResetModel();
    m_parameters = parameters;
    endResetModel();

    emit dataChanged(index(0), index(rowCount() - 1));
}


bool ParameterModel::setParameterValues(std::vector<float> values, bool notify)
{
    if (values.size() != rowCount())
        return false;

    for (int i = 0; i < values.size(); ++i)
    {
        m_parameters[i].value = values[i];
    }

    if (notify)
        emit dataChanged(index(0), index(rowCount() - 1), { ValueRole });

    return true;
}


int ParameterModel::parameterCount() const
{
    return m_parameters.size();
}


float ParameterModel::value(int index) const
{
    if (index < m_parameters.size())
        return m_parameters[index].value;
    else
        return 0.0;
}


float ParameterModel::min(int index) const
{
    if (index < m_parameters.size())
        return m_parameters[index].min;
    else
        return 0.0;
}


float ParameterModel::max(int index) const
{
    if (index < m_parameters.size())
        return m_parameters[index].max;
    else
        return 0.0;
}


QVariant ParameterModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < m_parameters.size())
    {
        if (role == ValueRole)
            return QVariant(m_parameters[index.row()].value);
        else if (role == NameRole)
            return QVariant(m_parameters[index.row()].name);
        else if (role == MinRole)
            return QVariant(m_parameters[index.row()].min);
        else if (role == MaxRole)
            return QVariant(m_parameters[index.row()].max);
    }

    return QVariant();
}


bool ParameterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;

    if (role == ValueRole)
    {
        m_parameters[index.row()].value = value.toFloat();
        emit dataChanged(index, index, { role } );
        return true;
    }

    return false;
}


QHash<int, QByteArray> ParameterModel::roleNames() const
{
    return
    {
        { NameRole, "name" },
        { MinRole, "min" },
        { MaxRole, "max" },
        { ValueRole, "value" },
    };
}
