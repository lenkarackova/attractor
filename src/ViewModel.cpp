#include "include/ViewModel.h"

ViewModel::ViewModel(QObject* parent)
    : QObject(parent)
{
    m_colorModel = std::make_unique<ColorViewModel>(this);
    m_attractor = std::make_unique<Attractor>(Attractor::AttractorType::Rossler, m_colorModel.get(), this);
    m_pointCloud = std::make_unique<PointCloud>(m_attractor.get());

    QObject::connect(m_colorModel.get(), &ColorViewModel::attractorColorChanged, m_pointCloud.get(), &PointCloud::updateCloud);
    QObject::connect(m_colorModel.get(), &ColorViewModel::gradientChanged, m_pointCloud.get(), &PointCloud::updateCloud);
    QObject::connect(m_colorModel.get(), &ColorViewModel::modeChanged, m_pointCloud.get(), &PointCloud::updateCloud);
    QObject::connect(m_attractor.get(), &Attractor::attractorChanged, m_pointCloud.get(), &PointCloud::updateCloud);
}


void ViewModel::randomAttractor()
{
    if (m_attractor)
        m_attractor->random();
}
