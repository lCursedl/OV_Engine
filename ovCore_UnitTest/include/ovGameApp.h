#pragma once
#include <ovBaseApp.h>
#include <ovMatrix4.h>

using namespace ovEngineSDK;

class GameApp : public BaseApp
{
 public:
  GameApp() = default;
  ~GameApp() = default;

  void
  onCreate() override;

  void
  onUpdate(float delta) override;

  void
  onRender() override;

  void
  onClear() override;

 private:
  Color m_color;
  SPtr<Texture> m_pBack;
  SPtr<Texture> m_finalTexture;
  Vector<SPtr<Texture>> m_vTextures;
  bool m_showDemo = true;

  /*struct Bones {
    Matrix4 bones[MAXBONES];
  };*/
};