/**
 * @file DetectorMask.h
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief Encode and Interpret the ATLAS detector mask. 
 */

#ifndef EFORMAT_DETECTORMASK_H 
#define EFORMAT_DETECTORMASK_H

#include <string>
#include <vector>
#include <bitset>
#include "eformat/SourceIdentifier.h"

namespace eformat {

  namespace helper {

    class DetectorMask {

      public:
      
      /**
       * Convert the provided integers (interpreted as a bitmask) 
       * into a string representation. 
       * The string format is simply the hex representation of the number
       * without any leading marker. The string will always include 
       * 32 characters. e.g.:
       * 64 --> "00000000000000000000000000000040"
       */

      static std::string to_string(const uint64_t least, const uint64_t most = 0);
      /**
       * Convert the bitmask into a string representation. The 
       * string format is simply the hex representation of the number
       * without any leading marker. The string will always include 
       * 32 characters. e.g.:
       * 64 --> "00000000000000000000000000000040"
       */

      static std::string to_string(const std::bitset<128>&);
     
      /**
       * Convert the provided string into a number. The string must:
       * - contain exactly 32 characters
       * - be the hex represenation of a number without leading markers
       */
      static std::bitset<128> from_string(const std::string&);

      public:

        /**
         * Default constructor, no bits of the mask get set in this way.
         */
        DetectorMask();

        /**
         * Initialize the mask with an already existing mask.
         */
        explicit DetectorMask(const std::bitset<128>& mask);

        /**
	 * Initialize the mask with an already existing mask.
         */
        explicit DetectorMask(const uint64_t least, const uint64_t most = 0);
            
        /**
         * Initialize the mask with an already existing mask.
         */
        explicit DetectorMask(const std::string& mask);
   
        /**
         * Initialize the mask with a list of SubDetector identifiers. This will
         * internally call the convertion routines.
         */
        DetectorMask(const std::vector<eformat::SubDetector>& ids);

        /**
         * A copy constructor.
         */
        DetectorMask(const DetectorMask& other) = default;

        /**
         * Attribution
         */
        DetectorMask& operator= (const DetectorMask& other) = default;

        /**
         * D'tor
         */
        virtual ~DetectorMask();

        /**
         * Decode the current mask in a set of subdetectors 
         */
        void sub_detectors(std::vector<eformat::SubDetector>& ids) const;

        /**
         * Returns the current mask
         */
        std::bitset<128> mask() const;

        /**
         * Adds another SubDetector to the current mask. It is not an error to
         * add twice the same SubDetector.
         */
        void set(eformat::SubDetector id);
        void set(const std::vector<eformat::SubDetector>& ids);
        void unset(eformat::SubDetector id);
        void unset(const std::vector<eformat::SubDetector>& ids);

        /**
         * Completely clear the current mask 
         */
        void reset ();

        /**
         * Checks if a certain SubDetector is present in the current mask
         */
        bool is_set(eformat::SubDetector id) const;

        /**
         * Returns a string representation of the mask 
	 * (see to_string documentation)
         */
        std::string string() const;


	/**
         * Returns a pair of 64 bits numbers representing the mask.
	 * most significant part --> pair.first
	 * least significant part --> pair.second
         */
	std::pair<uint64_t, uint64_t> serialize() const;
      
      private:
      std::bitset<128> m_mask;

    };

  }

}

#endif /* EFORMAT_DETECTORMASK_H */

