//Dear emacs, this is -*- c++ -*-

/**
 * @file StreamTag.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre Anjos</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Describes stream tags in a FullEvent header
 */

#ifndef EFORMAT_STREAMTAG_H
#define EFORMAT_STREAMTAG_H

#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <map>
#include <sstream>
#include "eformat/EnumClass.h"
#include "eformat/SourceIdentifier.h"

namespace eformat {

  /**
   * Defines the allowed tag types from the event format perspective.
   */
  typedef enum TagType {
    PHYSICS_TAG = 0x1,
    CALIBRATION_TAG = 0x2,
    RESERVED_TAG = 0x4,
    DEBUG_TAG = 0x8,
    UNKNOWN_TAG = 0x10,
    EXPRESS_TAG = 0x20,
    MONITORING_TAG = 0x40
  } TagType;

  namespace helper {

    extern const eformat::helper::EnumClass<TagType> TagTypeDictionary;

  }

  namespace helper {

    /**
     * Defines the base type that contains the raw elements in every
     * stream tag.
     */
    class StreamTag {

      public: //users can directly access and change properties
        
        std::string name; ///< The name tag for this stream
        std::string type; ///< The type tag for this stream
        bool obeys_lumiblock; ///< If the event obeys the luminosity boundary condition
        std::set<uint32_t> robs; ///< Optional list of ROBIDs for PEB
        std::set<eformat::SubDetector> dets; ///< Optional list of DETIDs for PEB
      
      public:

        /**
         * Ctor
         */
        StreamTag(const std::string& n, const eformat::TagType& t, bool ol, 
		  const std::set<uint32_t>& r = std::set<uint32_t>(),
		  const std::set<eformat::SubDetector>& d = 
		  std::set<eformat::SubDetector>());

        /**
         * Ctor
         */
        StreamTag(const std::string& n, const std::string& t, bool ol,
		  const std::set<uint32_t>& r = std::set<uint32_t>(),
		  const std::set<eformat::SubDetector>& d = 
		  std::set<eformat::SubDetector>());
      
        /**
         * Emtpy builds (for std containers)
         */
        StreamTag(): 
	  name(""), type("physics"), obeys_lumiblock(false), 
	  robs(std::set<uint32_t>()), dets(std::set<eformat::SubDetector>()) {}

        /**
         * Dtor
         */
        virtual ~StreamTag() {}

        /**
         * Compares two stream tags for equality
         *
         * @param other The tag to compare myself to
         */
        bool operator== (const StreamTag& other) const;

        /**
         * Compares two stream tags for inequality
         *
         * @param other The tag to compare myself to
         */
        bool operator!= (const StreamTag& other) const;

        /**
         * Compares two stream tags for greateness
         *
         * @param other The tag to compare myself to
         */
        bool operator< (const StreamTag& other) const;
      
    };

    /**
     * Defines how to decode the information on the event. Multiple StreamTags
     * can exist in a event. They are separated by null characters ('\0'). The
     * total amount of tags is calculated on-the-fly by taking into
     * consideration the total stream tag size. In order to be 32-bit padded, it
     * is possible that the last few bytes are all null.
     *
     * @param szword The size, in 32-bit words, of the encoded stream tag vector
     * @param encoded A bytestream of stream tags encoded in 32-bit words
     * @param decoded A vector of StreamTag objets, decoded
     */
    void decode (const uint32_t& szword, const uint32_t* encoded,
		 std::vector<StreamTag>& decoded);

    /**
     * Defines how to encode the information on the event. Multiple StreamTags
     * can exist in a event. Each StreamTag is terminated by one or more 
     * null characters ('\0'), up to a 32-bit boundary.
     *
     * @param decoded A vector of StreamTag objets, in decoded form
     * @param szword The size, in 32-bit words, of the encoded stream tag
     * vector. The "encoded" variable following this one should have at least
     * that size available so I can transplant the data into it.
     * @param encoded A bytestream of stream tags encoded in 32-bit words
     */
    void encode (const std::vector<StreamTag>& decoded,
		 uint32_t& szword, uint32_t* encoded);

    /**
     * Determines the number of words which are necessary for a stream tag
     * vector to be encoded.
     *
     * @param decoded A vector of StreamTag objets, in decoded form
     */
    uint32_t size_word (const std::vector<StreamTag>& decoded);

    /**
     * Determines, from a set of StreamTags, if a certain combination of types
     * is present
     *
     * @param v The input vector of StreamTags to be analyzed.
     * @param type The types t check for
     *
     * @return The number of stream tags that have the predefined type.
     */
    uint32_t contains_type (const std::vector<StreamTag>& v, uint32_t type);

    /**
     * Converts the enumeration TagType passed to a string representation.
     *
     * @param t The TagType variable you want converted into string
     * representation.
     */
    std::string tagtype_to_string(const eformat::TagType& t);

    /**
     * Checks the tag type on the string passed as input. If the tag type is
     * invalid, convert the tag type to "unknown"
     *
     * @param t The TagType variable you want to convert.
     */
    eformat::TagType string_to_tagtype(const std::string& t);

  }

}

#endif /* EFORMAT_STREAMTAG_H */
