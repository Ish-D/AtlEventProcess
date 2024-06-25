//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/HeaderMarker.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch>André DOS ANJOS</a>
 * $Author$
 * $Revision$
 * $Date$ 
 *
 * @brief Defines the constants used by Event Fragments.
 */

#ifndef EFORMAT_HEADERMARKER_H
#define EFORMAT_HEADERMARKER_H

#include <stdint.h>
#include <string>
#include "eformat/EnumClass.h"

namespace eformat {

  /**
   * The types of header markers available. They are all 32 bit
   * numbers, with 1234 in the middle for the identification of byte
   * ordering (endianness).
   */
  typedef enum HeaderMarker { 
          ROD = 0xee1234ee, ///< The ROD marker
		      ROB = 0xdd1234dd, ///< The ROB marker
		      FULL_EVENT = 0xaa1234aa ///< The event marker
  } HeaderMarker;
  
  namespace helper {

    extern const eformat::helper::EnumClass<HeaderMarker> 
      HeaderMarkerDictionary;

  }
 
  /**
   * Returns the child marker of a given parent marker
   *
   * @param e The marker from which you would like to the get child fragment
   * type from
   */
  HeaderMarker child_marker(HeaderMarker e);

  /**
   * Returns a string that represents the string of the equivalent marker
   *
   * @param e The enumeration value
   */
  std::string marker2string (const eformat::HeaderMarker& e);

  /**
   * Returns a string that represents the string of the equivalent marker
   *
   * @param e The enumeration value
   */
  std::string marker2string (uint32_t e);

}

#endif //EFORMAT_HEADERMARKER_H
