//Dear emacs, this is -*- c++ -*-

#ifndef COMPRESSION_DATABUFFER_H
#define COMPRESSION_DATABUFFER_H

#include <string>
#include "boost/utility.hpp"
#include "compression/compression.h"


namespace compression {
  
  class DataBuffer: public CompressionBuffer, public boost::noncopyable {
    
  public:
    DataBuffer();
    DataBuffer(const uint32_t& size);
    virtual ~DataBuffer();
     
    void realloc(const uint32_t& newsize);

    void grow(const uint32_t& newsize);
    
    void* handle();
    
    uint32_t buffersize() const;

  private:
    class implementation;
    implementation * rep;
    
    //DataBuffer(const DataBuffer& aBuf);
    //DataBuffer& operator= (const compression::DataBuffer & aBuf);
  };
}

#endif //COMPRESSION_DATABUFFER_H
