#include "include/ParameterListModel.h"


ParameterListModel::ParameterListModel(QObject *parent) {}


int ParameterListModel::rowCount(const QModelIndex &parent) const
{
    return m_parameters.size();
}


void ParameterListModel::setParameters(const std::vector<Parameter>& parameters)
{
    beginResetModel();
    m_parameters = parameters;
    endResetModel();

    emit dataChanged(index(0), index(rowCount() - 1));
}


bool ParameterListModel::setParameterValues(std::vector<float> values, bool notify)
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


int ParameterListModel::parameterCount() const
{
    return m_parameters.size();
}


float ParameterListModel::value(int index) const
{
    if (index < m_parameters.size())
        return m_parameters[index].value;
    else
        return 0.0;
}


float ParameterListModel::min(int index) const
{
    if (index < m_parameters.size())
        return m_parameters[index].min;
    else
        return 0.0;
}


float ParameterListModel::max(int index) const
{
    if (index < m_parameters.size())
        return m_parameters[index].max;
    else
        return 0.0;
}


QVariant ParameterListModel::data(const QModelIndex &index, int role) const
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


bool ParameterListModel::setData(const QModelIndex &index, const QVariant &value, int role)
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


QHash<int, QByteArray> ParameterListModel::roleNames() const
{
    return
    {
        { NameRole, "name" },
        { MinRole, "min" },
        { MaxRole, "max" },
        { ValueRole, "value" },
    };
}
