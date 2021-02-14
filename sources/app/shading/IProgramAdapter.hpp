#pragma once

#include "IShaderProgram.hpp"
#include "app/scene/PhongMaterial.hpp"

#include <glm/matrix.hpp>


class IProgramAdapter
{
public:
    virtual void setMaterial(TPhongMaterialPtr material) = 0;
    virtual void setProjection(glm::mat4 projection) = 0;
    virtual void setView(glm::mat4 view) = 0;

    virtual ~IProgramAdapter(){};
};

using TProgramAdapterPtr = std::shared_ptr<IProgramAdapter>;