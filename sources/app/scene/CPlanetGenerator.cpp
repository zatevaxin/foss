
#include "CPlanetGenerator.hpp"
#include "CAsteroidGenerator.hpp"
#include "CTerrainFace.hpp"

#include "Mesh.hpp"
#include "app/auxiliary/trace.hpp"


CPlanetGenerator::CPlanetGenerator(IProceduralSettings& settings)
    : mSettings(static_cast<TPlanetSettings&>(settings))
{
    mNoise.randomize(mSettings.mSeed);
}


void CPlanetGenerator::setSettings(IProceduralSettings& settings)
{
    auto t = static_cast<TPlanetSettings&>(settings);

    if (t.mSeed != mSettings.mSeed)
    {
        mNoise.randomize(mSettings.mSeed);
    }

    mSettings = t;
}

const TPlanetSettings& CPlanetGenerator::getSettings() const
{
    return mSettings;
}

void CPlanetGenerator::generate()
{
    std::function<glm::vec3(glm::vec3)> filter = [this](glm::vec3 point) -> glm::vec3 {
        auto& settings = mSettings.mNoiseSettings;

        auto noiseValue = mNoise.evaluate(point * settings.roughness + settings.center);
        noiseValue = (noiseValue + 1.f) * 0.5f;
        noiseValue = noiseValue * settings.strength;

        return point * glm::vec3(mSettings.mRadius) * (1 + noiseValue);
    };

    auto material = TPhongMaterialPtr(new SMaterialPhong());
    material->mDiffuseColor = glm::vec4(0.f, 0.f, 0.f, 1.f);
    material->mEmissiveColor = glm::vec4(0.f, 0.f, 0.f, 1.f);
    material->mSpecularColor = glm::vec4(0.f, 0.f, 0.f, 1.f);

    std::for_each(CUBE_FACES_DIRECTIONS.begin(), CUBE_FACES_DIRECTIONS.end(),
                  [this, &filter, &material](auto& direction) {
                      CTerrainFace face(mSettings.mResolution, direction);

                      TVerticeList vertices;
                      TIndiceList indices;
                      face.buildMesh(filter, vertices, indices);

                      mMeshes.emplace_back(new Mesh(vertices, indices, material));
                  });

    mProceduralModel.reset(new CStaticModel(mMeshes));
    mMeshes.clear();
}

TModelPtr CPlanetGenerator::get() const
{
    return mProceduralModel;
}