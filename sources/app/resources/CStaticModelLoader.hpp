#pragma once

#include <assimp/scene.h>
#include <filesystem>
#include <glm/matrix.hpp>
#include <unordered_map>
#include <vector>

#include "IModelLoader.hpp"
#include "app/scene/Mesh.hpp"


enum class EImportQuality
{
    FAST,
    HIGH,
    MAX
};


class CStaticModelLoader : public IModelLoader
{

private:
    std::unordered_map<unsigned, glm::mat4> mMeshTransforms;
    TMeshesList mMeshes;
    TMaterialList mMaterials;
    aiScene* mScene;
    const std::filesystem::path mModelDirectory;
    EImportQuality mQuality;

public:
    CStaticModelLoader(const std::filesystem::path& path, EImportQuality quality);

    TModelPtr getModel() override;

private:
    void loadMaterials();

    void visitNodeTree();

    void visitNode(const aiNode& node, const glm::mat4& parentTransform);

    void add(const aiMesh& mesh, TMaterialToMeshMap& mat2mesh);

    void copyIndices(const aiMesh& mesh, TIndiceList& indices) const;
    void copyVertices(const aiMesh& mesh, TVerticeList& vertices) const;
};
