#include "Model.h"
#include "Vertex.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

void Model::createModel(std::filesystem::path& path, const Mesh& mesh) {
    Assimp::Exporter exporter;
    const aiScene scene = generateScene(mesh);

    exporter.Export(&scene, "fbx", path);
}

void Model::loadModel(const std::filesystem::path& path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        BOOST_LOG_TRIVIAL(error) << "Failed to load model at: " << path << " - " << import.GetErrorString();
        return;
    }

    directory = path.parent_path();
    processNode(scene, scene->mRootNode);
}

void Model::processNode(const aiScene* scene, const aiNode* node) {
    /*for (size_t i = 0; i< node->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(scene, processMesh(scene, mesh));
    }

    for (size_t i = 0; i< node->mNumChildren; i++) {
        processNode(scene, node->mChildren[i]);
    }*/
}

void Model::processMesh(const aiScene* scene, const aiMesh* mesh) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for (size_t i = 0; i< mesh->mNumVertices; i++) {
        vertices.emplace_back(
            glm::vec3_cast(mesh->mVertices[i]),
            glm::vec3_cast(mesh->mNormals[i]),
            mesh->HasTextureCoords(0) ? glm::vec2_cast(mesh->mTextureCoords[0][i]) : vec2::zero
        );
    }

    for (size_t i = 0; i< mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        const aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

        auto material = loadMaterial(mat);

        auto diffuseMaps = loadMaterials(mat, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        /*auto specularMaps = loadMaterials(mat, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        auto normalMaps = loadMaterials(mat, aiTextureType_HEIGHT);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        auto heightMaps = loadMaterials(mat, aiTextureType_AMBIENT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        if (textures.empty()) {
            auto r = static_cast<unsigned char>(material.diffuse[0] * 255);
            auto g = static_cast<unsigned char>(material.diffuse[1] * 255);
            auto b = static_cast<unsigned char>(material.diffuse[2] * 255);
            textures.push_back(std::make_shared<Texture>(r, g, b));
        }*/
    }
}

std::vector<std::shared_ptr<Texture>> Model::loadMaterials(const aiMaterial* material, aiTextureType type) {
    std::vector<std::shared_ptr<Texture>> textures;
    for (size_t i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        if (material->GetTexture(type, i, &str) == AI_SUCCESS) {
            std::filesystem::path path = directory;
            directory /= str.C_Str();

            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (const auto& texture : texturesLoaded) {
                if (texture->path() == path) {
                    textures.push_back(texture);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }

            // if texture hasn't been loaded already, load it
            if (!skip) {
                auto texture = std::make_shared<Texture>(path, true, false);
                textures.push_back(texture);
                texturesLoaded.push_back(texture); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        } else {
            BOOST_LOG_TRIVIAL(error) << "Could not get texture from material";
        }
    }



    return textures;
}

Material Model::loadMaterial(const aiMaterial* material)
{
    Material mat;
    aiColor3D color;
    float shininess;

    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    mat.diffuse = glm::vec3_cast(color);

    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    mat.ambient = glm::vec3_cast(color);

    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    mat.specular = glm::vec3_cast(color);

    material->Get(AI_MATKEY_SHININESS, shininess);
    mat.shininess = shininess;

    return mat;
}

aiScene Model::generateScene(const Mesh& mesh) {
    aiScene scene;
    scene.mRootNode = new aiNode();

    scene.mMaterials = new aiMaterial*[1];
    scene.mNumMaterials = 1;
    scene.mMaterials[0] = new aiMaterial();

    scene.mMeshes = new aiMesh*[1];
    scene.mNumMeshes = 1;
    scene.mMeshes[0] = new aiMesh();
    scene.mMeshes[0]->mMaterialIndex = 0;

    scene.mRootNode->mMeshes = new unsigned int[1];
    scene.mRootNode->mNumMeshes = 1;
    scene.mRootNode->mMeshes[0] = 0;

    auto pMesh = scene.mMeshes[0];

    const auto& vertices = mesh.vertices;
    size_t numVertices = vertices.size();

    pMesh->mVertices = new aiVector3D[numVertices];
    pMesh->mNumVertices = numVertices;

    pMesh->mNormals = new aiVector3D[numVertices];

    pMesh->mTextureCoords[0] = new aiVector3D[numVertices];
    pMesh->mNumUVComponents[0] = numVertices;

    for (size_t i = 0; i < numVertices; i++) {
        const auto& v = vertices[i];
        pMesh->mVertices[i] = aiVector3D(v.position.x, v.position.y, v.position.z);
        pMesh->mNormals[i] = aiVector3D(v.normal.x, v.normal.y, v.normal.z);
        pMesh->mTextureCoords[0][i] = aiVector3D(v.uv.x, v.uv.y, 0);
    }

    const auto& indices = mesh.indices;
    size_t numFaces = indices.size() / 3;

    pMesh->mFaces = new aiFace[numFaces];
    pMesh->mNumFaces = numFaces;

    for (size_t i = 0, j = 0; i < numFaces; i++, j += 3) {
        aiFace& face = pMesh->mFaces[i];
        face.mIndices = new unsigned int[3];
        face.mNumIndices = 3;
        face.mIndices[0] = indices[j+0];
        face.mIndices[1] = indices[j+1];
        face.mIndices[2] = indices[j+2];
    }

    return scene;
}
