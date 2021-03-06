#pragma once

#include <cstdint>
#include <cstdlib>
#include <glm/fwd.hpp>


class CShaderProgram;


class CVertexAttribute
{
public:
    explicit CVertexAttribute(int location);

    bool isValid() const;

    void enablePointer();
    void disablePointer();

    void setDivisor(unsigned divisor);
    void setVec3Offset(size_t offset, size_t stride, bool needClamp);
    void setVec2Offset(size_t offset, size_t stride);
    void setFloatsOffset(size_t offset, size_t stride, unsigned numComponents, bool needClamp);
    void setUint8Offset(size_t offset, size_t stride, unsigned numComponents);

private:
    static constexpr int UNDEFINED = -1;

    int mLocation = UNDEFINED;
};
