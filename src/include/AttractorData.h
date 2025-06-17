#pragma once

#include "Vertex.h"

static const unsigned SETTLE_ITERATIONS = 1000;
static const unsigned CHECK_ITERATIONS = 4000;
static const unsigned INITIALIZE_ITERATIONS = 4000;
static const unsigned RANDOM_TRIES = 10000;

struct AttractorData
{
    Vertex center;
    Vertex max;
    Vertex min;

    QVector3D scale;

    bool drawable;
    bool chaotic;

    double lyapunov;
    double minAngle;
    double maxSpeed;
    double maxAngle;

    int	randoms;
    int	point;
    int	infinite;
    int	stable;
    int	periodic;
};

