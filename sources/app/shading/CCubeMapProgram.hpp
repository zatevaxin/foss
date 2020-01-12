
#ifndef FOSS_CCUBEMAPPROGRAM_HPP
#define FOSS_CCUBEMAPPROGRAM_HPP

#include "base/shading/CShaderProgram.hpp"


class CCubeMapProgram : public CShaderProgram
{
public:
    CCubeMapProgram();
    ~CCubeMapProgram() override = default;
};

#endif //FOSS_CCUBEMAPPROGRAM_HPP
