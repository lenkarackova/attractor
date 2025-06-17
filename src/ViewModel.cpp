#include "include/ViewModel.h"

ViewModel::ViewModel()
    : m_colorModel()
    , m_attractor(Attractor::AttractorType::Rossler, &m_colorModel)
    , m_pointCloud(&m_attractor)
{
    connect(&m_colorModel, &ColorViewModel::attractorColorChanged, &m_pointCloud, &PointCloud::updateCloud);
    connect(&m_colorModel, &ColorViewModel::gradientChanged,& m_pointCloud, &PointCloud::updateCloud);
    connect(&m_colorModel, &ColorViewModel::modeChanged, &m_pointCloud, &PointCloud::updateCloud);
    connect(&m_attractor, &Attractor::attractorChanged, &m_pointCloud, &PointCloud::updateCloud);
}


void ViewModel::randomAttractor()
{
    m_attractor.random();
}
