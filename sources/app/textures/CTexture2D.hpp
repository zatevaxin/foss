#pragma once

#include "ITexture.hpp"
#include "auxiliary.hpp"

#include "app/auxiliary/glm.hpp"
#include "app/auxiliary/sdl.hpp"


using namespace textures;


class CTexture2D :
    public ITexture
{
public:
    CTexture2D();
    ~CTexture2D() override;

    CTexture2D(const CTexture2D&) = delete;

    glm::ivec2 size() const;
    bool isAlpha() const;

    void bind() const override;
    static void unbind();

    void setSurface(const SDL_Surface& surface);
    void setWrapMode(ETextureWrapMode s, ETextureWrapMode t);

    inline unsigned int id()
    {
        return mTextureId;
    }

private:
    unsigned int mTextureId;
    glm::ivec2 mSize;
    bool mHasAlpha;
};
