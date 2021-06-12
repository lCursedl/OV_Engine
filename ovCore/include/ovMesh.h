#pragma once
#define NUM_BONES_PERVERTEX 4
#define MAXBONES 200

#include <ovPrerequisitesCore.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <ovVector2.h>
#include <ovVector3.h>
#include <ovVector4.h>
#include <ovMatrix4.h>

namespace ovEngineSDK {
  class Buffer;
  class Texture;
  class SamplerState;
  struct MeshVertex
  {
   public:
    Vector3 Position;
    Vector2 TexCoords;
    Vector3 Normal;
    Vector3 Tangent;
    Vector3 Bitangent;
    uint32 BoneID[4] = {0};
    float Weights[4] = {0.f};
  };

  struct VertexBoneData
  {
    float BoneID[NUM_BONES_PERVERTEX] = {0};
    float Weights[NUM_BONES_PERVERTEX] = {0};
    void addBoneData(uint32 boneID, float weight);
  };

  struct BoneInfo
  {
    Matrix4 BoneOffset;
    Matrix4 FinalTransform;
    BoneInfo() {
      BoneOffset = Matrix4(0.f);
      FinalTransform = Matrix4(0.f);
    }
  };

  struct MeshTexture
  {
   public:
    String Type;
    String Path;
    Texture* TextureMesh = nullptr;
  };

  class OV_CORE_EXPORT Mesh
  {
   public:
    Mesh(Vector<MeshVertex>* vertex,
         Vector<uint32>* index,
         Vector<MeshTexture> texture,
         aiMesh* mesh);
    ~Mesh();
    void setUpMesh();
    void draw(SamplerState* sstate);
   private:
    Vector<MeshVertex>*  m_vertices;
    Vector<uint32>*      m_indices;
    Vector<MeshTexture> m_textures;
    Vector<BoneInfo> m_boneInfo;
    Vector<VertexBoneData> m_bonesPerVertex;
    Map<String, uint32> m_boneMapping;
    uint32 m_numBones;

    Buffer* m_vertexBuffer;
    Buffer* m_indexBuffer;

    friend class Model;
  };
}