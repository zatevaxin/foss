
#ifndef FOSS_CGEOMETRYOBJECT_HPP
#define FOSS_CGEOMETRYOBJECT_HPP

#include "core/scene/CBufferObject.hpp"
#include "core/scene/CArrayObject.hpp"
#include "core/geometry/auxiliary.hpp"

#include "SGeometryData.hpp"
#include "CBoundingBox.hpp"
#include "core/auxiliary/glm.hpp"

#include <boost/noncopyable.hpp>
#include <memory>
#include <vector>


namespace geometry
{

class CGeometry : private boost::noncopyable
{
public:
    CGeometry();
    ~CGeometry() = default;

    template<class TV, class TI>
    void copy(const SGeometryData<TV, TI> & data)
    {
        mVao.bind();
        mVerticies.copy(data.mVerticies);
        mIndexes.copy(data.mIndexes);
        mBBox = data.mBBox;
        mVao.unbind();
    }

    const CBoundingBox & getBoundingBox() const;

    void bind();
    void unbind();

private:
    CBufferObject mVerticies;
    CBufferObject mIndexes;
    CBoundingBox  mBBox;
    CArrayObject  mVao;

};

using CGeometrySharedPtr = std::shared_ptr<CGeometry>;

} // geometry

#endif //FOSS_CGEOMETRYOBJECT_HPP
