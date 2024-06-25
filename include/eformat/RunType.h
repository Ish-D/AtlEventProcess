//Dear emacs, this is -*- c++ -*-

/**
 * @file RunType.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre Anjos</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines possible run type values
 */

#ifndef EFORMAT_RUNTYPE_H
#define EFORMAT_RUNTYPE_H

#include <string>
#include <stdint.h>
#include "eformat/EnumClass.h"

namespace eformat {

  /**
   * The types of run available. They are all 32 bit numbers.
   */
  typedef enum RunType { 
    PHYSICS = 0x00000000,
		CALIBRATION = 0x00000001,
		COSMICS = 0x00000002,
    SIMULATION = 0x80000000,
		TEST = 0x0000000f
  } RunType;

  namespace helper {

    extern const eformat::helper::EnumClass<RunType> RunTypeDictionary;

  }

  /**
   * Returns a string that represents the run type
   *
   * @param e The enumeration value
   */
  std::string run_type2string (const eformat::RunType& e);

  /**
   * Returns a string that represents the run type
   *
   * @param e The enumeration value
   */
  std::string run_type2string (uint32_t e);

}

#endif /* EFORMAT_RUNTYPE_H */
