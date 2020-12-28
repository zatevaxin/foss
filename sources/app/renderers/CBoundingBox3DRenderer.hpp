#pragma once

#include "app/renderers/C3DRendererBase.hpp"
#include "app/scene/CVertexBufferObject.hpp"
#include "app/scene/CVertexArrayObject.hpp"


struct SPhongMaterial;

class CBoundingBox3DRenderer : public C3DRendererBase
{
public:
    CBoundingBox3DRenderer();
    ~CBoundingBox3DRenderer() = default;

    void draw(SStaticModel3D & model) override;

private:
    CVertexBufferObject mVertices;
    CVertexBufferObject mIndexes;
    CVertexArrayObject mVao;
};
