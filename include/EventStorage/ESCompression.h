//Dear emacs, this is -*- c++ -*-

#ifndef EVENTSTORAGE_ESCOMPRESSION_H
#define EVENTSTORAGE_ESCOMPRESSION_H

#include <string>
#include "ers/ers.h"

namespace EventStorage {
      
  enum CompressionType { NONE, RESERVED, UNKNOWN, ZLIB};

  static const std::string compressiontag("Compression");
  
  CompressionType string_to_type(const std::string& type);
  std::string type_to_string(const CompressionType& type);

}

#endif
