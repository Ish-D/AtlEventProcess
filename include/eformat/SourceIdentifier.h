//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/SourceIdentifier.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch>André dos ANJOS</a>
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Declares a type that can perform the conversion between source
 * identifier components and the its 32-bit version.
 */

#ifndef EFORMAT_HELPER_SOURCEIDENTIFIER_H
#define EFORMAT_HELPER_SOURCEIDENTIFIER_H

#include <stdint.h>
#include <string>
#include "eformat/EnumClass.h"

namespace eformat {

  typedef enum SubDetectorGroup { 
    ANY_DETECTOR = 0x0,
    PIXEL = 0x1,
    SCT = 0x2,
    TRT = 0x3,
    LAR = 0x4,
    TILECAL = 0x5,
    MUON = 0x6,
    TDAQ = 0x7,
    FORWARD = 0x8,
    OTHER_DETECTORS = 0xf
  } SubDetectorGroup;

  namespace helper {

    extern const eformat::helper::EnumClass<SubDetectorGroup> 
      SubDetectorGroupDictionary;

  }

  /**
   * Sub-detector ID
   */
  typedef enum SubDetector { 
         FULL_SD_EVENT = 0x00,
	 OFFLINE = 0x01,
         PIXEL_BARREL = 0x11,
         PIXEL_DISK = 0x12,
         PIXEL_B_LAYER = 0x13,
	 PIXEL_IBL = 0x14,
	 PIXEL_DBM = 0x15,
         SCT_BARREL_A_SIDE = 0x21,
         SCT_BARREL_C_SIDE = 0x22,
         SCT_ENDCAP_A_SIDE = 0x23,
         SCT_ENDCAP_C_SIDE = 0x24,
         TRT_ANCILLARY_CRATE = 0x30,
         TRT_BARREL_A_SIDE = 0x31,
         TRT_BARREL_C_SIDE = 0x32,
         TRT_ENDCAP_A_SIDE = 0x33,
         TRT_ENDCAP_C_SIDE = 0x34,
         LAR_EM_BARREL_A_SIDE = 0x41,
         LAR_EM_BARREL_C_SIDE = 0x42,
         LAR_EM_ENDCAP_A_SIDE = 0x43,
         LAR_EM_ENDCAP_C_SIDE = 0x44,
         LAR_HAD_ENDCAP_A_SIDE = 0x45,
         LAR_HAD_ENDCAP_C_SIDE = 0x46,
         LAR_FCAL_A_SIDE = 0x47,
         LAR_FCAL_C_SIDE = 0x48,
         LAR_EM_BARREL_ENDCAP_A_SIDE = 0x49,
         LAR_EM_BARREL_ENDCAP_C_SIDE = 0x4a,
         LAR_EM_HAD_ENDCAP_A_SIDE = 0x4b,
         LAR_EM_HAD_ENDCAP_C_SIDE = 0x4c,
         TILECAL_LASER_CRATE = 0x50,
         TILECAL_BARREL_A_SIDE = 0x51,
         TILECAL_BARREL_C_SIDE = 0x52,
         TILECAL_EXT_A_SIDE = 0x53,
         TILECAL_EXT_C_SIDE = 0x54,
         MUON_ANCILLARY_CRATE = 0x60,
         MUON_MDT_BARREL_A_SIDE = 0x61,
         MUON_MDT_BARREL_C_SIDE = 0x62,
         MUON_MDT_ENDCAP_A_SIDE = 0x63,
         MUON_MDT_ENDCAP_C_SIDE = 0x64,
         MUON_RPC_BARREL_A_SIDE = 0x65,
         MUON_RPC_BARREL_C_SIDE = 0x66,
         MUON_TGC_ENDCAP_A_SIDE = 0x67,
         MUON_TGC_ENDCAP_C_SIDE = 0x68,
         MUON_CSC_ENDCAP_A_SIDE = 0x69,
         MUON_CSC_ENDCAP_C_SIDE = 0x6A,
	 MUON_MMEGA_ENDCAP_A_SIDE = 0x6B,
         MUON_MMEGA_ENDCAP_C_SIDE = 0x6C,
         MUON_STGC_ENDCAP_A_SIDE = 0x6D,
         MUON_STGC_ENDCAP_C_SIDE = 0x6E,
         TDAQ_BEAM_CRATE = 0x70,
         TDAQ_CALO_PREPROC = 0x71,
         TDAQ_CALO_CLUSTER_PROC_DAQ = 0x72,
         TDAQ_CALO_CLUSTER_PROC_ROI = 0x73,
         TDAQ_CALO_JET_PROC_DAQ = 0x74,
         TDAQ_CALO_JET_PROC_ROI = 0x75,
         TDAQ_MUON_CTP_INTERFACE = 0x76,
         TDAQ_CTP = 0x77,
         TDAQ_L2SV = 0x78,
         TDAQ_SFI = 0x79,
         TDAQ_SFO = 0x7a,
         TDAQ_LVL2 = 0x7b,
	 TDAQ_EVENT_FILTER = 0x7c,
	 TDAQ_HLT = 0x7c,
	 TDAQ_LAR_MET = 0x7d,
	 TDAQ_TILE_MET = 0x7e,
	 TDAQ_FTK = 0x7f,
         FORWARD_BCM = 0x81,
         FORWARD_LUCID = 0x82,
         FORWARD_ZDC = 0x83,
         FORWARD_ALPHA = 0x84,
         FORWARD_AFP = 0x85,
	 TDAQ_CALO_TOPO_PROC = 0x91,
	 TDAQ_CALO_DIGITAL_PROC = 0x92,
	 TDAQ_CALO_FEAT_EXTRACT_DAQ = 0x93,
	 TDAQ_CALO_FEAT_EXTRACT_ROI = 0x94,
         OTHER = 0xff
  } SubDetector;

  namespace helper {

    extern const eformat::helper::EnumClass<SubDetector> 
      SubDetectorDictionary;

  }

  namespace helper {

    /**
     * Defines converters between source identifiers and its components.
     */
    class SourceIdentifier {

    public:
      /**
       * Constructor. Takes the components to form a source identifier.
       *
       * @param subdet The subdetector for this source
       * @param id The module identifier
       * @param optional This is the optional field (MSB). Defaults to zero, as
       * stated at the Event Format document.
       */
      SourceIdentifier (const eformat::SubDetector subdet,
                        const uint16_t id,
                        const uint8_t optional = 0);

      /**
       * Constructor. Takes the source identifier to understand the components
       * from.
       *
       * @param sid The source identifier, fully built.
       * @warning This source identifier <b>has</b> to conform to the current
       * version of the library or unpredictable results might occur.
       */
      SourceIdentifier (const uint32_t sid);

      /**
       * Empty build
       */
      SourceIdentifier () : SourceIdentifier(OTHER, 0) {};

      /**
       * Copy
       */
      SourceIdentifier (const SourceIdentifier& other) = default;
          
      SourceIdentifier& operator=(const SourceIdentifier& other) = default;
      
      /**
       * Virtualized destructor
       */
      virtual ~SourceIdentifier() {}

      /**
       * Extracts the SubDetector component of the identifier.
       */
      inline eformat::SubDetector subdetector_id (void) const { return m_sd; }

      /**
       * Extracts the SubDetectorGroup component of the identifier.
       */
      inline eformat::SubDetectorGroup subdetector_group (void) const
      { return (eformat::SubDetectorGroup)(m_sd>>4); }

      /**
       * Returns the value of the optional field in the Source Identifier
       * value. This corresponds to the most significative byte.
       */
      inline uint8_t optional_field (void) const { return m_opt; }
      
      /**
       * Extracts the Module identifier from the source identifier.
       */
      inline uint16_t module_id (void) const { return m_id; }

      /**
       * Gets the full 32-bit number made by assembling the 3 numbers
       * above.
       */
      uint32_t code (void) const;

      /**
       * Gets the full 32-bit number made by assembling only 2 of the numbers
       * above (subdetector_id and module_id)
       */
      uint32_t simple_code (void) const;

      /**
       * Returns a string that represents the source identifier in a human
       * readable format
       */
      std::string human (void) const;

      /**
       * Returns a string that represents the subdetector identifier in a human
       * readable format
       */
      std::string human_detector (void) const;

      /**
       * Returns a string that represents the subdetector identifier in a human
       * readable format
       */
      std::string human_group (void) const;

      /**
       * To use this class as keys in maps
       */
      inline bool operator< (const SourceIdentifier& other) const
      { return (this->code() < other.code()); }

      /**
       * To use this class as keys in maps
       */
      inline bool operator== (const SourceIdentifier& other) const
      { return (this->code() == other.code()); }

    private: //representation

      eformat::SubDetector m_sd; ///< The subdetector component
      uint16_t m_id; ///< The module identifier
      uint8_t m_opt; ///< The optional field

    };

  }

}

#endif //EVENTFORMAT_HELPER_SOURCEID_H
