//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/Version.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines a helper class to encode and decode version numbers.
 */

#ifndef EFORMAT_VERSION_H
#define EFORMAT_VERSION_H

#include <stdint.h>
#include <string>

namespace eformat {

  /**
   * The default eformat version to use
   */
  const uint32_t DEFAULT_VERSION = 0x05000000;
  
  /**
   * The default eformat version to use for ROD fragments
   */
  const uint32_t DEFAULT_ROD_VERSION = 0x03010000;
  
  /**
   * The major default eformat version to use
   */
  const uint16_t MAJOR_DEFAULT_VERSION = 0x0500;

  /**
   * The major default eformat version to use
   */
  const uint16_t MAJOR_V40_VERSION = 0x0400;

  /**
   * The major default eformat version to use
   */
  const uint16_t MAJOR_V31_VERSION = 0x0301;

  /**
   * The major default eformat version to use
   */
  const uint16_t MAJOR_V30_VERSION = 0x0300;

  /**
   * The major default eformat version to use
   */
  const uint16_t MAJOR_V24_VERSION = 0x0204;

  namespace helper {

    /**
     * Defines converters between version numbers and its components
     */
    class Version {

    public:
      /**
       * Constructor. Takes the components to form a version
       *
       * @param minor The minor version
       * @param major The major version
       */
      Version (uint16_t minor, uint16_t major=MAJOR_DEFAULT_VERSION)
	: m_minor(minor), m_major(major) {}

      /**
       * Constructor. Takes the version to understand the components from.
       *
       * @param v The version number, fully built.
       * @warning This version number <b>has</b> to conform to the current
       * version of the library or unpredictable results might occur.
       */
      Version (uint32_t v=DEFAULT_VERSION);

      /**
       * Virtualized destructor
       */
      virtual ~Version() {}

      /**
       * Extracts the major version part of this version
       */
      inline uint16_t major_version (void) const { return m_major; }

      /**
       * Extracts the minor version part of this version
       */
      inline uint16_t minor_version (void) const { return m_minor; }

      /**
       * Gets the full 32-bit number made by assembling the 2 numbers
       * above.
       */
      uint32_t code (void) const;

      /**
       * Returns a string representation of the major version number
       */
      std::string human_major (void) const;

      /**
       * Returns a string representation of the minor version number
       */
      std::string human_minor (void) const;

      /**
       * Returns a string representation of the version number
       */
      std::string human (void) const;

    private: //representation

      uint16_t m_minor; ///< The minor part of the version number
      uint16_t m_major; ///< The major part of the version number

    };

  }

}

#endif /* EFORMAT_VERSION_H */
