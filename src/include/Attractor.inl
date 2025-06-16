template <typename OutputIterator>
void Attractor::getPoints(unsigned long int iterations,
                          OutputIterator out)
{
    Vertex v0(0.001);
    Vertex v1(0.0);
    Vertex v2(0.0);

    double minColor, maxColor;
    double value;

    ColorModel::ColoringMode mode = ColorModel::ColoringMode::Single;
    QColor color = Qt::white;
    Gradient gradient = Gradient({ Qt::red, Qt::yellow, Qt::green, Qt::blue });

    if (m_colorModel != nullptr)
    {
        mode = m_colorModel->coloringMode();
        color = m_colorModel->attractorColor();
        gradient = m_colorModel->gradient();
    }

    switch (mode)
    {
    case ColorModel::ColoringMode::Single:
        minColor = 0.0;
        maxColor = 0.0;
        break;
    case ColorModel::ColoringMode::Depth:
        minColor = m_data.min.z();
        maxColor = m_data.max.z();
        break;
    case ColorModel::ColoringMode::Velocity:
        minColor = 0.1;
        maxColor = m_data.maxSpeed;
        break;
    case ColorModel::ColoringMode::Angle:
        minColor = m_data.minAngle;
        maxColor = m_data.maxAngle;
        break;
    default:
        minColor = 0.0;
        maxColor = 1.0;
    }

    gradient.setMin(minColor);
    gradient.setMax(maxColor);

    for (unsigned i = 0; i < iterations + SETTLE_ITERATIONS; i++)
    {
        // save coordinates computed in previous iteration
        v2 = v1;
        v1 = v0;

        // get new coordinates
        m_system->next(v0);

        if (i >= SETTLE_ITERATIONS)
        {
            // get color from gradient
            if (mode != ColorModel::ColoringMode::Single)
            {
                switch (mode)
                {
                case ColorModel::ColoringMode::Depth:
                    value = v0.z();
                    break;
                case ColorModel::ColoringMode::Velocity:
                    value = v1.distanceToPoint(v0);
                    break;
                case ColorModel::ColoringMode::Angle:
                    value = v1.angle(v2, v0);
                    break;
                default:
                    value = 0.5;
                }

                color = gradient.getColor(value);
            }

            out(v0.toVector3D(), color);
        }
    }
}
