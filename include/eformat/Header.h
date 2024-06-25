//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/Header.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch>André Rabello dos
 * ANJOS</a>
 * $Author$
 * $Revision$
 * $Date$ 
 *
 * @brief Defines the Header entity. The definition is based on the
 * update of the "ATLAS Raw Event Format", v4.0, by A.dos Anjos et al. 
 */

#ifndef EFORMAT_HEADER_H
#define EFORMAT_HEADER_H

#include <stdint.h>

namespace eformat {

  /**
   * Contains the information on the Header of a fragment as described
   * by the original note. The header is a composite entity, build from
   * two parts:
   *
   * -# The generic part, containing the header type, size and version
   * information;
   * -# The specific part, containing data that is specific for a
   * particular fragment.
   */
  class Header {

  public:
   
   /**
     * To build a header given the containing buffer. I need to know
     * where the header starts in order to do that.
     *
     * @param it The exact position where this header should start.
     */
    Header (const uint32_t* it);

    /**
     * Builds an empty, otherwise useless Header
     */
    Header ();

    /**
     * Copy constructor
     *
     * @param other The other header to construct from
     */
    Header (const Header& other) = default;

    /**
     * Destructor virtualisation
     */
    virtual ~Header();

    /**
     * Assigment operator
     *
     * @param other The other header to assign from
     */
    Header& operator= (const Header& other) = default;

    /**
     * If you set this parameter, objects of this type will throw exceptions.
     * The default behavior is to throw.
     */
    void throws (bool b);

    /**
     * Says if we are supposed to throw exceptions or not.
     */
    bool throws () const;

    /**
     * Reassign this header
     *
     * @param it The exact position where this header should start.
     */
    Header& assign (const uint32_t* it);

    /**
     * Returns the fragment type.
     */
    uint32_t marker() const;

    /**
     * Returns the size, in words, of the current fragment.
     */
    uint32_t fragment_size_word() const;

    /**
     * Returns the size, in words, of the current header. That does include
     * the specific part of the header.
     */
    uint32_t header_size_word() const;

    /**
     * Returns the formatting version.
     */
    uint32_t version() const;

    /**
     * Returns the full source identifier.
     */
    uint32_t source_id() const;

    /**
     * Returns the number of status words available
     */
    uint32_t nstatus () const;

    /**
     * Sets the pointer to my start
     *
     * @param it The pointer to set
     */
    const uint32_t* start() const;
    inline void start (const uint32_t*& it) const { it = start(); } //legacy

    /**
     * Sets the pointer to where the payload starts
     *
     * @param it The pointer to set
     */
    const uint32_t* payload() const;
    inline void payload (const uint32_t*& it) const { it = payload(); } //legacy

    /**
     * Sets the pointer to one-past my end position
     *
     * @param it The pointer to set
     */
    const uint32_t* end() const;
    inline void end (const uint32_t*& it) const { it = end(); } //legacy

    /**
     * Returns the payload size
     */
    uint32_t payload_size_word (void) const;

    /**
     * Returns the status words, as an iterator to the status words available.
     *
     * @param it An <em>updateable</em> iterator you should provide.
     */
    const uint32_t* status() const;
    inline void status (const uint32_t*& it) const { it = status(); } //legacy

    /**
     * Returns the check-sum type entry 
     */
    uint32_t checksum_type () const; 

    /**
     * Returns the number of specific words available in the specific header
     * part 
     */
    uint32_t nspecific () const; 
    
    /**
     * Returns an iterator to the start of the specific header part 
     *
     * @param it An <em>updateable</em> iterator you should provide.
     */
    const uint32_t* specific_header() const;
    inline void specific_header (const uint32_t*& it) const //legacy
    { it = specific_header(); }

    /**
     * Access the check sum value of this fragment, if any. Understand that if,
     * checksum_type() resolves to eformat::NO_CHECKSUM, the returned value
     * will have no meaning.
     */
    uint32_t checksum_value (void) const; 
    
    /**
     * Evaluates the current (supposed) checksum for this fragment, taking
     * into consideration the current setting for the checksum type. Please
     * note this value may be different from the actual checksum_value() if for
     * any reason the fragment is corrupted.
     */
    uint32_t eval_checksum (void) const;

    /**
     * This will actually re-calculate the checksum and verify that the payload
		 * of the current fragment matches that. Only works with contiguous memory
		 * templates.
     */
    bool checksum (void) const;
    
  private: ///< representation

    const uint32_t* m_top; ///< my start word

  };

}

#endif //EFORMAT_HEADER_H
