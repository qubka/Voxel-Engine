#ifndef VOX_MODEL_H
#define VOX_MODEL_H

class Vertex;
class Texture;
class Material;
class Mesh;

class aiScene;
class aiNode;
class aiMesh;
class aiMaterial;

#include <assimp/material.h>

class Model {
    std::filesystem::path directory;
    std::vector<std::shared_ptr<Texture>> texturesLoaded;
    //std::vector<std::shared_ptr<Mesh<

    void processNode(const aiScene* scene, const aiNode* node);
    void processMesh(const aiScene* scene, const aiMesh* mesh);
    std::vector<std::shared_ptr<Texture>> loadMaterials(const aiMaterial* material, aiTextureType type);
    Material loadMaterial(const aiMaterial* material);

    aiScene generateScene(const Mesh& mesh);
public:
    Model() = default;
    ~Model() = default;

    void loadModel(const std::filesystem::path& path);
    void createModel(std::filesystem::path& path, const Mesh& mesh);
};

#endif //VOX_MODEL_H
