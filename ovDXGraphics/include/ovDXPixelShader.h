#pragma once
#include <ovShader.h>
#include <ovPrerequisitesDX.h>

namespace ovEngineSDK {
  /**
  * @class       DXPixelShader
  * @brief       Class which holds info for a D3D11's pixel shader.
   */
  class DXPixelShader final : public PixelShader
  {
   public:

    /**
    * @fn        ~DXPixelShader()
    * @brief     Class destructor.
    *            If m_ps or m_blob was used, release memory before deleting object.
    */
    ~DXPixelShader();

  protected:

    /**
    * @fn        DXPixelShader()
    * @brief     Class constructor.
    *            Sets m_ps & m_blob as nullptr.
    */
    DXPixelShader();

  private:
    ID3D11PixelShader* m_ps;        /**< ID3D11PixelShader pointer */
    ID3DBlob* m_blob;               /**< ID3D11Blob pointer */

    friend class DXGraphicsAPI;
  };
}