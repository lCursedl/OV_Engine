#pragma once
#include <ovPrerequisitesOGL.h>
#include <ovShaderProgram.h>

namespace ovEngineSDK {
  /**
  * @class       OGLShaderProgram
  * @brief       Class which holds info for an OpenGL shader program.
  *              The concept of ShaderProgram exists only on OGl, therefore the functionality
  *              of the base class is expanded here.
  */
  class OGLShaderProgram :
    public ShaderProgram
  {
   protected:

    /** 
    * @fn        OGLShaderProgram()
    * @brief     Class constructor.
    */
    OGLShaderProgram() = default;

   public:
    /**
    * @fn       ~OGLShaderProgram()
    * @brief    Class destructor.
    *           If m_program was used, release memory before deleting object.
    */
    ~OGLShaderProgram();

    void setVertexShader(SPtr<VertexShader> vertexShader)             override;

    void setPixelShader(SPtr<PixelShader> pixelShader)                override;

    void linkProgram()                                               override;

   private:
    
    uint32 m_program = 0; /**< unsigned int for OpenGL shader program index. */

    friend class OGLGraphicsAPI;
  };
}