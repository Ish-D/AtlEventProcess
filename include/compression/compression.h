//Dear emacs, this is -*- c++ -*-

#ifndef COMPRESSION_COMPRESSION_H
#define COMPRESSION_COMPRESSION_H

#include <sys/uio.h>
#include "ers/ers.h"
#include <string>

ERS_DECLARE_ISSUE(compression,             
		  CompressionIssue,
		  ERS_EMPTY, ERS_EMPTY)

ERS_DECLARE_ISSUE_BASE(compression,             
		       ZlibFailed, 
		       compression::CompressionIssue,
		       "" << message << " - Zlib return code: " 
		       << return_code << " Zlib message: " << zlib_message,
		       ERS_EMPTY,
		       ((const char *) message )
		       ((int)return_code)
		       ((std::string) zlib_message)
		       )


namespace compression {
      
  /**
   *  Abstract interface of a *CONTIGUOUS* buffer used for
   *  event compression and uncompression
   */
  class CompressionBuffer{
    
  public:
    virtual ~CompressionBuffer() {};

    /**
     *  Returns a pointer to the underlying buffer
     *
     *  @return Pointer to the buffer
     */
    virtual void * handle() = 0;
    
    /**
     *  Resizes the underlying buffer without preserving the 
     *  existing content.
     *
     *  @param newsize The expected updated buffer size in 
     *                 bytes
     */
    virtual void realloc(const uint32_t& newsize) = 0;

    /**
     * Resize the underlying buffer *preserving*
     * the existing content.
     *
     * @param newsize The expected updated buffer size in 
     *                 bytes
     */
    virtual void grow(const uint32_t& newsize) = 0;

    /**
     * Returns size (in byte) of the underlying buffer
     *
     * @return Buffer size in bytes
     */
    virtual uint32_t buffersize() const = 0;
  };
  

  /**
   * @brief Compress a block of data
   *
   * @param compressed A CompressionBuffer object that
   *                   will be used to store the compressed
   *                   data
   * @param compressedsize Will be updated with the compressed
   *                       data size (in bytes)
   * @param entries Input io vector length
   * @param iov Input io vector
   * @param totalsize Total size of data in the io vector (in bytes)
   * @param level Compression level (1<-->9)
   *
   * @throws CompressionIssue In case of failure an exception of type 
   * CompressionIssue (or subclass) is thrown
   */

  void zlibcompress(CompressionBuffer& compressed,
		    uint32_t& compressedsize,
		    const uint32_t& entries, 
		    const struct iovec* iov,
		    const uint32_t& totalsize,
		    const uint32_t& level);
  

  /**
   * Decompress a zlib compressed block of data
   *
   * @param uncompressed A CompressionBuffer object that
   *                     will be used to store the uncompressed
   *                     data
   * @param uncompressedsize Will be updated with the uncompressed
   *                         data size (in bytes)
   * @param compressed Pointer to the compressed data block
   * @param compsize Size of the compressed data block (in bytes)
   *
   * @throws CompressionIssue In case of failure an exception of type 
   * CompressionIssue (or subclass) is thrown. In this case the 
   * compressed data block is simply copied into the uncompressed buffer.
   *
   */
  void zlibuncompress(CompressionBuffer& uncompressed,
		      uint32_t& uncompressedsize,
		      const void * compressed,
		      const uint32_t& compsize);

}

#endif //COMPRESSION_COMPRESSION_H
