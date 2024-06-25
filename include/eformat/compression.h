/**
 * @file eformat/compression.h
 * @author <a href="mailto:wainer.vandelli@cern.ch">Wainer Vandelli</a> 
 *
 * @brief Defines compression facilities
 */

#ifndef EFORMAT_COMPRESSION_H 
#define EFORMAT_COMPRESSION_H

namespace eformat { 

  /**
   * The compression enumeration defines all possible options for event data
   * compression.
   */
  typedef enum Compression {
    UNCOMPRESSED = 0x0,
    ZLIB         = 0x1,
    RESERVED     = 0xff
  } Compression;
}



#endif //EFORMAT_COMPRESSION_H
