#pragma once

namespace ovEngineSDK {
  /**
  * @enum        BUFFER_TYPE
  * @brief       Enum which contains definitions for buffer types.
  */
  namespace BUFFER_TYPE {
    enum E {
      kVERTEX_BUFFER = 0x1L,	/**< Vertex buffer enum value (1)*/
      kINDEX_BUFFER = 0x2L,	/**< Index buffer enum value (2)*/
      kCONST_BUFFER = 0x4L,		/**< Constant buffer enum value (4)*/
      kSHADER_BUFFER = 0x08L, /**< Shader resource buffer enum value (8)*/
      kUNORDERED_BUFER = 0x80L /**<Unordered Access buffer enum value (128)*/
    };
  }

  /**
  * @class       CBuffer
  *	@brief       Class which serves as an interface for both CDXBuffer and COGLBuffer.
  *
  *	             Contains only a constructor and virtual destructor.
  */
  class Buffer
  {
   public:
    Buffer() = default;
    virtual ~Buffer() = default;
  };
}