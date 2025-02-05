#include "ovMesh.h"
#include <ovGraphicsAPI.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ovEngineSDK {

  Mesh::Mesh(const Vector<MeshVertex> vertex,
             const Vector<uint32> index,
             const Vector<MeshTexture> texture,
             aiMesh* mesh) {
    m_vertices = vertex;
    m_indices = index;
    m_textures = texture;
    m_numBones = 0;
    mesh;
    /*uint32 boneIndex;
    String boneName;

    for (uint32 i = 0; i < mesh->mNumBones; ++i) {
      boneIndex = 0;
      boneName = (mesh->mBones[i]->mName.data);

      if (m_boneMapping.find(boneName) == m_boneMapping.end()) {
        boneIndex = m_numBones;
        ++m_numBones;
        m_boneInfo.emplace_back();
      }
      else {
        boneIndex = m_boneMapping[boneName];
      }

      m_boneMapping[boneName] = boneIndex;
      memcpy(&m_boneInfo[boneIndex].BoneOffset,
             &mesh->mBones[i]->mOffsetMatrix,
             sizeof(Matrix4));

      for (uint32 j = 0; j < mesh->mBones[i]->mNumWeights; ++j) {
        uint32 vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
        float weigth = mesh->mBones[i]->mWeights[j].mWeight;

        for (int32 k = 0; k < NUM_BONES_PERVERTEX; ++k) {
          auto& currVertex = m_vertices->at(vertexID);

          if (currVertex.Weights[k] == 0.f) {
            currVertex.BoneID[k] = boneIndex;
            currVertex.Weights[k] = weigth;
            break;
          }
        }
      }
    }*/
    setUpMesh();
  }

  Mesh::~Mesh() {
    if (!m_vertices.empty()) {
      m_vertices.clear();
    }
    if (!m_indices.empty()) {
      m_indices.clear();
    }
    if (!m_textures.empty()) {
      m_textures.clear();
    }
  }

  void Mesh::setUpMesh() {
    auto graphicAPI = &g_graphicsAPI();
    m_vertexBuffer = graphicAPI->createBuffer(m_vertices.data(),
                                              static_cast<int32>(sizeof(MeshVertex) * 
                                              m_vertices.size()),
                                              BUFFER_TYPE::kVERTEX_BUFFER);
    m_indexBuffer = graphicAPI->createBuffer(m_indices.data(),
                                             static_cast<int32>(sizeof(uint32) * 
                                             m_indices.size()),
                                             BUFFER_TYPE::kINDEX_BUFFER);
  }

  void Mesh::draw(SPtr<SamplerState> sstate) {
    auto graphicAPI = &g_graphicsAPI();

    graphicAPI->setVertexBuffer(m_vertexBuffer, static_cast<int32>(sizeof(MeshVertex)), 0);
    graphicAPI->setIndexBuffer(m_indexBuffer, FORMATS::kR32_UINT);

    SIZE_T numTextures = m_textures.size();

    for (uint32 i = 0; i < numTextures; ++i) {
      graphicAPI->setSamplerState(0, m_textures[i].TextureMesh,
                                  sstate,
                                  SHADER_TYPE::PIXEL_SHADER);
      graphicAPI->setTexture(i, m_textures[i].TextureMesh);
    }
    
    graphicAPI->drawIndexed(static_cast<int32>(m_indices.size()), 0, 0);

    for (uint32 i = 0; i < numTextures; ++i) {
      graphicAPI->setTexture(i, nullptr);
    }
  }

  void
  Mesh::getMeshInfo(Vector<Vector3>& vertices,
                    Vector<uint32>& indices,
                    Vector<Vector3>& normals,
                    Vector<Vector2>& uvs) {
    for (auto& vertex : m_vertices) {
      vertices.push_back(vertex.Position);
      normals.push_back(vertex.Normal);
      uvs.push_back(vertex.TexCoords);
    }

    for (auto& index : m_indices) {
      indices.push_back(index);
    }
  }

  void VertexBoneData::addBoneData(uint32 boneID, float weight) {
    for (uint32 i = 0; i < NUM_BONES_PERVERTEX; ++i) {
      if (0.f == Weights[i]) {
        BoneID[i] = boneID;
        Weights[i] = weight;
        return;
      }
    }
  }
}
