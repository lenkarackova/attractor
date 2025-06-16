#include "include/ViewModel.h"

ViewModel::ViewModel()
{
    m_colorModel = new ColorModel();
    m_attractor = new Attractor(Attractor::Lorenz, m_colorModel);
    m_pointCloud = new PointCloud(m_attractor);

    connect(m_colorModel, &ColorModel::attractorColorChanged, m_pointCloud, &PointCloud::updateCloud);
    connect(m_colorModel, &ColorModel::gradientChanged, m_pointCloud, &PointCloud::updateCloud);
    connect(m_colorModel, &ColorModel::modeChanged, m_pointCloud, &PointCloud::updateCloud);
    connect(m_attractor, &Attractor::attractorChanged, m_pointCloud, &PointCloud::updateCloud);
}


void ViewModel::randomAttractor()
{
    m_attractor->random();
}
