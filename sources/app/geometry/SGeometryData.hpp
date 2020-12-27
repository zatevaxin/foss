#pragma once

#include "CBoundingBox.hpp"

#include <vector>


namespace geometry
{

template <class TV, class TI>
struct SGeometryData
{
    std::vector<TV> mVerticies;
    std::vector<TI> mIndexes;
    CBoundingBox    mBBox;

    SGeometryData() = default;

    SGeometryData(const std::vector<TV> &verticies, const std::vector<TI> &indexes)
        : mVerticies(verticies), mIndexes(indexes)
    {
    }
};

}
