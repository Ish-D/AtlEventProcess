//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/Status.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief A helper class to help the user to interpret the status information
 * in the first status word and to code it properly.
 */

#ifndef EFORMAT_STATUS_H
#define EFORMAT_STATUS_H

#include <stdint.h>
#include "eformat/EnumClass.h"

namespace eformat {

  /**
   * Defines possible generic errors for the status words
   */
  typedef enum GenericStatus {
    UNCLASSIFIED = 0x0,
    BCID_CHECK_FAIL = 0x1,
    LVL1ID_CHECK_FAIL = 0x2,
    TIMEOUT = 0x4,
    DATA_CORRUPTION = 0x8,
    INTERNAL_OVERFLOW = 0x10,
    DUMMY_FRAGMENT = 0x20
  } GenericStatus;

  namespace helper {

    extern const eformat::helper::EnumClass<GenericStatus> 
      GenericStatusDictionary;

  }

  /**
   * Defines the 16 specific bits of the ROBIN status word
   */
  typedef enum RobinStatus {
    /**
     * Trigger-Type Sync Error: A „SYNC“ trigger type fragment was received
     * with a mismatch of the lower 3 bits of the event ID and the trigger type
     * field
     */
    TRIGGER_TYPE_SYNC_ERROR = 0x1,

    /**
     * This is an exception of the ROBIN status and is "abused" to also denote
     * a dummy dataflow result in L2/EF ROB fragments.
     */
    DATAFLOW_DUMMY = 0x1,

    /**
     * Actual number of words does not match header + trailer + number of data
     * words + number of status words (indicated in trailer) 
     */
    FRAGMENT_SIZE_ERROR = 0x2, 

    // S-LINK transmission error on data block 
    DATABLOCK_ERROR = 0x4,
    
    // S-LINK transmission error on control word (EOF or BOF) 
    CTRL_WORD_ERROR = 0x8,
    
    /**
     * New fragment started without BOF (after preceding one terminated with
     * EOF)
     */
    MISSING_BOF = 0x10, 

    /**
     * New fragment started with BOF, without the preceding one terminated by
     * EOF
     */   
    MISSING_EOF = 0x20, 
    
    // The header marker of the ROD fragment is invalid 
    INVALID_HEADER_MARKER = 0x40,
    
    /**
     * The major format version (upper 16 bits) doesn't match the expected
     * format
     */
    FORMAT_ERROR = 0x80,
    
    /**
     * Duplicate event: when this fragment was received the ROBIN still had a
     * fragment with the same L1ID in memory. The new fragment has replaced the
     * older one.
     */
    DUPLICATE_EVENT = 0x100,


    /**
     * The L1ID of this ROD fragment was not in sequence with the L1ID of the
     * fragment previously received (L1ID_new not_equal L1ID_old + 1)
     */
    SEQUENCE_ERROR = 0x200,
   
    /** 
     * General flag for a S-Link transmission or formatting error. See bits 16
     * through 23
     */
    TRANSMISSION_ERROR = 0x400,
   
    /**
     * The amount of data sent across S-Link for this fragment was larger than
     * the maximum fragment size the ROBIN was configured to handle. Therefore
     * this fragment has been truncated
     */
    TRUNCATION = 0x800,

    /**
     * The amount of data between the S-Link control words (BOF and EOF) was
     * less than the size of an empty ROD fragment (ROD header + ROD trailer)
     */
    SHORT_FRAGMENT = 0x1000, 
    
    /**
     * The ROBIN did not have a fragment for the requested L1ID. It therefore
     * generated an empty fragment
     */
    FRAGMENT_LOST = 0x2000, 
    
    /**
     * The ROBIN did not have a fragment for the requested L1ID but this
     * fragment may still arrive. It therefore generated an empty fragment.
     * (Used by TDAQ applications)
     */
    FRAGMENT_PENDING = 0x4000,
 
    /**
     * Discard: the ROBIN did not have a fragment for the requested L1ID?
     * because it is in "discard" mode. It therefore generated an empty
     * fragment.
     */
    ROBIN_DISCARD_MODE = 0x8000
  } RobinStatus;

  namespace helper {

    extern const eformat::helper::EnumClass<RobinStatus> RobinStatusDictionary;

  }

  /**
   * Defines the 16 specific bits of the dummy ROB status word
   */
  typedef enum DummyROBStatus {
    /**
     * The RoI did contain all the expected RoI fragments
     */
    INCOMPLETE_ROI = 0x1,
    
    /**
     * The fragment was generated because the collection of the real data failed
     */
    COLLECTION_TIMEOUT = 0x2

  } DummyROBStatus;

  namespace helper {
    
    extern const eformat::helper::EnumClass<DummyROBStatus> DummyROBStatusDictionary;

  }

  /**
   * Defines the 16 specific bits of the Full Event status word
   */
  typedef enum FullEventStatus {
    L2_PROCESSING_TIMEOUT = 0x1,
    L2PU_PROCESSING_TIMEOUT = 0x2,
    SFI_DUPLICATION_WARNING = 0x4,
    DFM_DUPLICATION_WARNING = 0x8,
    HLTSV_DUPLICATION_WARNING = 0x8,
    L2PSC_PROBLEM = 0x10,
    //bit 21 is reserved, 0x20
    //bit 22 is reserved, 0x40
    //bit 23 is reserved, 0x80
    EF_PROCESSING_TIMEOUT = 0x100,
    DCM_PROCESSING_TIMEOUT = 0x100,
    PT_PROCESSING_TIMEOUT = 0x200,
    HLTPU_PROCESSING_TIMEOUT = 0x200,
    SFO_DUPLICATION_WARNING = 0x400,
    DCM_DUPLICATION_WARNING = 0x400,
    EFD_RECOVERED_EVENT = 0x800,
    DCM_RECOVERED_EVENT = 0x800,
    EFPSC_PROBLEM = 0x1000,
    PSC_PROBLEM = 0x1000,
    EFD_FORCED_ACCEPT = 0x2000,
    DCM_FORCED_ACCEPT = 0x2000,
    //bit 30 is reserved, 0x4000
    PARTIAL_EVENT = 0x8000
  } FullEventStatus;


    /**
   * Defines the 16 specific bits of the Full Event status word
   */
  /*namespace pippo {
    typedef enum FullEventStatusNew {
      PARTIAL_EVENT = 0x8000
    } FullEventStatusNew;
    }*/

  namespace helper {

    extern const eformat::helper::EnumClass<FullEventStatus> 
    FullEventStatusDictionaryV40;

    extern const eformat::helper::EnumClass<FullEventStatus> 
    FullEventStatusDictionary;
  }

  const uint32_t STATUS_FRONT = 0; ///< status goes in front of data block
  const uint32_t STATUS_BACK = 1; ///< status goes after data block 

  /**
   * The default status to use
   */
  const uint32_t DEFAULT_STATUS = UNCLASSIFIED;

  namespace helper {

    /**
     * Defines converters between version numbers and its components
     */
    class Status {

    public:

      /**
       * Constructor. Takes the components to form a status
       *
       * @param gen The generic component
       * @param spec The specific component
       */
      Status (eformat::GenericStatus gen, uint16_t spec)
	: m_gen(gen), m_spec(spec) {}

      /**
       * Constructor. Takes the components to form a status
       *
       * @param gen The generic component
       * @param spec_msb The specific MSB component
       * @param spec_lsb The specific LSB component
       */
      Status (eformat::GenericStatus gen, uint8_t spec_msb, uint8_t spec_lsb)
	: m_gen(gen), m_spec(spec_msb) { m_spec <<= 8; m_spec |= spec_lsb; }

      /**
       * Constructor. Takes the status to understand the components from.
       *
       * @param s The status number, fully built.
       * @warning This status value <b>has</b> to conform to the current
       * version of the library or unpredictable results might occur.
       */
      Status (uint32_t v);

      /**
       * Virtualized destructor
       */
      virtual ~Status () {}

      /**
       * Extracts the generic part of this status word
       */
      inline eformat::GenericStatus generic (void) const { return m_gen; }

      /**
       * Extracts the specific part of this status word
       */
      inline uint16_t specific (void) const { return m_spec; }

      /**
       * Extracts the MSB of the specific part of this status word
       */
      inline uint8_t specific_msb (void) const { return (m_spec >> 8) & 0xff; }

      /**
       * Extracts the LSB of the specific part of this status word
       */
      inline uint8_t specific_lsb (void) const { return m_spec & 0xff; }

      /**
       * Gets the full 32-bit number made by assembling the 2 numbers
       * above.
       */
      uint32_t code (void) const;

    private: //representation

      eformat::GenericStatus m_gen; ///< The generic part
      uint16_t m_spec; ///< The specific part

    };

  }

}

#endif /* EFORMAT_STATUS_H */
