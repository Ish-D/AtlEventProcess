//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/write/FullEventFragment.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Helps the user to define and build a FullEvent fragment.
 */

#ifndef EFORMAT_WRITE_FULLEVENTFRAGMENT_H
#define EFORMAT_WRITE_FULLEVENTFRAGMENT_H

#include "eformat/write/ROBFragment.h"
#include "compression/compression.h"
#include <cstring>

namespace eformat {

  namespace write {

    /**
     * Defines a helper class to aid the creation of FullEvent fragments.
     */
    class FullEventFragment {

    public:

      /**
       * Builds a new FullEvent fragment from scratch, using the current time
       * as the time label.
       *
       * @param source_id The source identifier to be using for this
       * FullEvent 
       * @param bc_time_secs The bunch crossing time in seconds, since the
       * (unix) orgin
       * @param bc_time_nsec The additional amount of nanoseconds since the
       * @param global_id The global identifier for this fragment
       * @param run_type The run type for this fragment
       * @param run_no The run number for this fragment
       * @param lumi_block The luminosity block number (16-bits)
       * @param lvl1_id The LVL1 trigger identifier for this fragment
       * @param bc_id The bunch crossing identifier (12-bits)
       * @param lvl1_type The LVL1 trigger type for this fragment (8-bits)
       */
      FullEventFragment (uint32_t source_id, uint32_t bc_time_secs,
			 uint32_t bc_time_nsec, uint64_t global_id, uint32_t run_type,
			 uint32_t run_no, uint16_t lumi_block,
			 uint32_t lvl1_id, uint16_t bc_id, uint8_t lvl1_type);

      /**
       * Builds a new FullEvent fragment from an existing FullEvent fragment in
       * contiguous memory.
       *
       * @param fe The existing FullEvent fragment
       */
      FullEventFragment (const uint32_t* fe);

      /**
       * Builds a new empty FullEventFragment, otherwise invalid. This is
       * useful for array builds and standard containers.
       */
      FullEventFragment ();

      /**
       * Copy constructor. This will only copy the meta data, not the fragment
       * relationships and block-data (children and status block) contained in
       * the to-be-copied fragment. If you wish this fragment to have the same
       * children of the copied fragment, you have to do this operation
       * manually, after copying. If you wish to make a copy of the status as
       * well, do it manually and then assign it to this fragment using the
       * status() method.
       *
       * @param other The other fragment to take the meta data from.
       */
      FullEventFragment (const FullEventFragment& other);

      /**
       * Base destructor
       */
      virtual ~FullEventFragment ();

      /**
       * Assigment operator. This will only copy the meta data, not the
       * fragment relationships and block-data (children and parent and status
       * block) contained in the to-be-copied fragment. If you wish this
       * fragment has the same parents, and children of the copied fragment,
       * you have to do this operation manually, after copying. If you wish to
       * make a copy of the status as well, do it manually and then assign it
       * to this fragment using the status() method.
       *
       * @param other The other fragment to take the meta data from.
       */
      FullEventFragment& operator= (const FullEventFragment& other);

      /**
       * Copies the header (meta data information) from another existing
       * FullEvent Fragment. Please note that this will not copy any specificy
       * payload related information belonging to the other fragment. 
       *
       * Also note that the variable length data (status, info words, stream
       * tags) is copied in a shallow way, by pointing to the existing blocks
       * of the copied fragment. This way, you either must reset or guarantee
       * this data will be available during the lifetime of this fragment.
       *
       * @param other The other FullEventFragment from which I should copy the
       * metadata from
       */
      void copy_header(const uint32_t* other);
      void copy_header(const FullEventFragment& other);

      /**
       * Changes the number of status words and the status words themselves
       * from the fragment
       *
       * @param n How many status words the underlying FullEventFragment
       * fragment supposed to have.
       * @param status A pointer to <tt>n</tt> pre-allocated words
       */
      void status (uint32_t n, const uint32_t* status);

      /**
       * Returns the number of status wors in this fragment
       */
      inline uint32_t nstatus (void) const { return m_node[0].base[5]; }

      /**
       * Returns a pointer to the first status word to be used by this fragment
       */
      inline const uint32_t* status (void) const { return m_node[1].base; }

      /**
       * Changes the minor version number of the fragment
       *
       * @param v The new minor version for this header
       */
      inline void minor_version (uint16_t v) 
      { m_node[0].base[3] = eformat::DEFAULT_VERSION | v; }

      /**
       * Returns the minor version number of the fragment
       */
      inline uint16_t minor_version (void) const 
      { return 0xffff & m_node[0].base[3]; }

      /**
       * Changes the source identifier for this fragment
       *
       * @param s The new value to set
       */
      inline void source_id (uint32_t s) 
      { m_node[0].base[4] = s; }

      /**
       * Returns the source identifier of this fragment
       */
      inline uint32_t source_id (void) const 
      { return m_node[0].base[4]; }

      /**
       * Changes the check-sum type for this fragment. This will actually @b
       * not calculate the checksum for this fragment. You will have to call
       * bind() in order to do that. If you change anything within the fragment
       * after calling bind(), a re-bind() is required.
       *
       * @param s The new value to set
       */
      void checksum_type (uint32_t s);

      /**
       * Returns the check sum type of this fragment
       */
      inline uint32_t checksum_type (void) const { return m_node[2].base[0]; }

      /**
       * Changes the compression for this fragment. The actual compression will
       * be performed during the bind() call. In case you modify the fragment, 
       * re-bind() in needed.
       *
       * @param s The new value to set
       */
      void compression_type (const uint32_t s);
      

      /**
       * Returns the compression type of this fragment
       */
      inline uint32_t compression_type (void) const 
      { return m_node[2].base[11]; }

      /**
       * Sets the compression level of this fragment
       */
      inline void compression_level (unsigned int level)
      { m_compression_level = level; }
      
      /**
       * Returns the compression level of this fragment
       */
      inline unsigned int compression_level (void) const 
      { return m_compression_level; }

      /**
       * Changes the bunch crossing time (seconds) this fragment was produced
       * at.
       *
       * @param s The new value to set
       */
      inline void bc_time_seconds (uint32_t s) 
      { m_node[2].base[1] = s; }

      /**
       * Changes the bunch crossing time (the nanoseconds part) this fragment
       * was produced at.
       *
       * @param s The new value to set
       */
      inline void bc_time_nanoseconds (uint32_t s) 
      { m_node[2].base[2] = s; }

      /**
       * Returns the time since the (unix) origin, in seconds, for this
       * fragment
       */
      inline uint32_t bc_time_seconds (void) const 
      { return m_node[2].base[1]; }

      /**
       * Returns the additional amount of nanoseconds, for this fragment's
       * bunch crossing time.
       */
      inline uint32_t bc_time_nanoseconds (void) const 
      { return m_node[2].base[2]; }

      /**
       * Changes the global identifier for this event
       *
       * @param s The new value to set
       */
      inline void global_id (const uint64_t s) 
      { 
	m_node[2].base[3] = s; 
	m_node[2].base[4] = (s >> 32); 
      }

      /**
       * Returns the global identifier for this event
       */
      inline uint64_t global_id (void) const
      { 
	uint64_t gid = m_node[2].base[4]; 	  
	gid <<= 32;
	gid |= m_node[2].base[3];
	return gid; 
      }

      /**
       * Changes the run type
       *
       * @param s The new value to set
       */
      inline void run_type (const uint32_t s) 
      { m_node[2].base[5] = s; }

      /**
       * Returns the run type for this fragment
       */
      inline uint32_t run_type (void) const 
      { return m_node[2].base[5]; }

      /**
       * Changes the run number
       *
       * @param s The new value to set
       */
      inline void run_no (const uint32_t s) 
      { m_node[2].base[6] = s; }

      /**
       * Returns the run number for this fragment
       */
      inline uint32_t run_no (void) const 
      { return m_node[2].base[6]; }

      /**
       * Changes the luminosity block number
       *
       * @param s The new value to set
       */
      inline void lumi_block (const uint16_t s) 
      { m_node[2].base[7] = s; }

      /**
       * Returns the luminosity block number for this fragment
       */
      inline uint16_t lumi_block (void) const 
      { return m_node[2].base[7]; }

      /**
       * Changes the lvl1 identifier in this fragment
       *
       * @param s The new value to set
       */
      inline void lvl1_id (const uint32_t s) 
      { m_node[2].base[8] = s; }

      /**
       * Returns the lvl1 identifier for this fragment
       */
      inline uint32_t lvl1_id (void) const 
      { return m_node[2].base[8]; }

      /**
       * Changes the bunch crossing identifier in this fragment
       *
       * @param s The new value to set
       */
      inline void bc_id (const uint16_t s) 
      { m_node[2].base[9] = s; }

      /**
       * Returns the bunch crossing identifier for this fragment
       */
      inline uint16_t bc_id (void) const 
      { return m_node[2].base[9]; }

      /**
       * Changes the lvl1 trigger type in this fragment
       *
       * @param s The new value to set
       */
      inline void lvl1_trigger_type (const uint8_t s) 
      { m_node[2].base[10] = s; }

      /**
       * Returns the lvl1 trigger type for this fragment
       */
      inline uint8_t lvl1_trigger_type (void) const 
      { return m_node[2].base[10]; }

      /**
       * Changes the LVL1 trigger info words from the fragment
       *
       * @param n How many LVL1 info words the underlying FullEventFragment
       * fragment supposed to have.
       * @param data A pointer to <tt>n</tt> pre-allocated words
       */
      void lvl1_trigger_info (uint32_t n, const uint32_t* data);

      /**
       * Returns the number of status wors in this fragment
       */
      inline uint32_t nlvl1_trigger_info (void) const 
      { return m_node[2].base[13]; }

      /**
       * Returns a pointer to the first LVL1 trigger info to be used by this
       * fragment
       */
      inline const uint32_t* lvl1_trigger_info (void) const 
      { return m_node[3].base; }

      /**
       * Changes the LVL2 trigger info words from the fragment
       *
       * @param n How many LVL2 info words the underlying FullEventFragment
       * fragment supposed to have.
       * @param data A pointer to <tt>n</tt> pre-allocated words
       */
      void lvl2_trigger_info (uint32_t n, const uint32_t* data);

      /**
       * Returns the number of status wors in this fragment
       */
      inline uint32_t nlvl2_trigger_info (void) const 
      { return m_node[4].base[0]; }

      /**
       * Returns a pointer to the first LVL2 trigger info to be used by this
       * fragment
       */
      inline const uint32_t* lvl2_trigger_info (void) const 
      { return m_node[5].base; }

      /**
       * Changes the EF trigger info words from the fragment
       *
       * @param n How many EF info words the underlying FullEventFragment
       * fragment supposed to have.
       * @param data A pointer to <tt>n</tt> pre-allocated words
       */
      void event_filter_info (uint32_t n, const uint32_t* data)
      { this->hlt_info(n,data); }

      /**
       * Returns the number of status wors in this fragment
       */
      inline uint32_t nevent_filter_info (void) const 
      { return this->nhlt_info(); }

      /**
       * Returns a pointer to the first EF trigger info to be used by this
       * fragment
       */
      inline const uint32_t* event_filter_info (void) const 
      { return this->hlt_info(); }

       /**
       * Changes the HLT trigger info words from the fragment
       *
       * @param n How many HLT info words the underlying FullEventFragment
       * fragment supposed to have.
       * @param data A pointer to <tt>n</tt> pre-allocated words
       */
      void hlt_info (uint32_t n, const uint32_t* data);

      /**
       * Returns the number of status wors in this fragment
       */
      inline uint32_t nhlt_info (void) const 
      { return m_node[6].base[0]; }

      /**
       * Returns a pointer to the first HLT trigger info to be used by this
       * fragment
       */
      inline const uint32_t* hlt_info (void) const 
      { return m_node[7].base; }
      
      /**
       * Returns the number of stream tag words in this fragment. At this
       * level of the API, a stream tag is defined to be a 32-bit null padded
       * (standard) C string.
       */
      inline uint32_t nstream_tag (void) const 
      { return m_node[8].base[0]; }

      /**
       * Changes the stream tag words from the fragment. At this level of the
       * API, a stream tag is defined to be a 32-bit null padded (standard) C
       * string.
       *
       * @param n How many stream tag words the underlying FullEventFragment
       * fragment supposed to have.
       * @param data A pointer to <tt>n</tt> pre-allocated words
       */
      void stream_tag (uint32_t n, const uint32_t* data);

      /**
       * Returns a pointer to the first stream tag word to be used by this
       * fragment. At this level of the API, a stream tag is defined to be a
       * 32-bit null padded (standard) C string.
       */
      inline const uint32_t* stream_tag (void) const { return m_node[9].base; }

      /**
       * Returns the size of this fragments header
       */
      inline uint32_t meta_size_word (void) const
      { return m_node[0].base[2] + (checksum_type()?1:0); }

      /**
       * Returns the total size for this fragment, in words
       */
      inline uint32_t size_word (void) const
      { return m_node[0].base[1]; }
      
      /**
       * Appends a new ROB fragment to this FullEvent fragment.
       *
       * @warning This will change the page structure of the last ROS fragment
       * inserted here, in order to concatenate the ROS fragments
       * together. Please note that this operation is not compatible with
       * multiple threads of operation, if you would like to share
       * eformat::write::Fragment's between threads. A better strategy would
       * be create, for every thread of operation, a proper ROSFragment
       * instead.
       *
       * @param rob The ROB fragment to be appended to myself
       */
      void append (eformat::write::ROBFragment* rob);

      /**
       * Appends an unchecked (read-only) ROB fragment to the current
       * FullEvent. The fragment will be appended after the writable ROB
       * fragments inserted with append().
       *
       * Unchecked fragments are appended to the end of the fragment stream, in
       * the order they are received. This is done so we make sure that damaged
       * fragments would only happen in the end of the stream and not on its
       * begin - which could cause good fragments to be skipped.
       *
       * Despite being unchecked the ROB fragment still has to fullfill two
       * constraints: 
       * 1. It has to start with the proper ROB fragment header marker
       * 2. The second word from the top should indicate its correct size in
       * words
       *
       * @param rob_fragment A pointer to the unchecked ROB fragment will be
       * inserted as part of the current fragment. This ROB fragment must still
       * fullfill the two requirements above.
       */
      void append_unchecked (const uint32_t* rob);

      /**
       * Returns the number of unchecked ROBs there are
       */
      inline uint32_t nunchecked_fragments (void) const
      { return m_n_unchecked; }

      /**
       * Returns a particular unchecked ROB fragment. Please not that this
       * method will not perform bound-checking. You are supposed to make sure
       * the existing range is not exceeded.
       * 
       * @param n The index of the unchecked fragment you want to retrieve.
       */
      const uint32_t* unchecked_fragment (uint32_t n) const;
      
      /**
       * This returns the first child of this fragment. The system operates as
       * a concatenated list of fragments. From this child you can get to the
       * next.
       */
      inline const ROBFragment* first_child (void) const 
      { return m_child; }

      /**
       * This method is used by children of this fragment to notify fragment
       * size changes.
       *
       * @param o The old size, in 32-bit words
       * @param n The new size, in 32-bit words
       */
      inline void size_change (uint32_t o, uint32_t n)
      { m_node[0].base[1] -= o; m_node[0].base[1] += n; }


      /**
       * Returns the first node of a list of nodes that represent the fragment
       * you have constructed. To make use of it, just browse the list as
       * defined in node.h
       */
      const eformat::write::node_t* bind (void);

    private: //to make the code simpler

      /**
       * Initializes the internal fields of this ROB fragment with the standard
       * values.
       */
      void initialize(void);


    private: //representation

      uint32_t m_header[23]; ///< The FullEvent Header
      eformat::write::node_t m_node[12]; ///< Node representation
      eformat::write::ROBFragment* m_child; ///< my children
      eformat::write::ROBFragment* m_last; ///< my last child
      uint32_t m_checksum; ///< My payload's checksum, if asked
      uint32_t m_n_unchecked; ///< The number of unchecked nodes attached
      uint32_t m_unchecked_size; ///< The size of unchecked node array 
      eformat::write::node_t * m_unchecked; ///< Unchecked nodes
      eformat::write::node_t m_compressed_node; ///< Compressed node
      std::unique_ptr<compression::CompressionBuffer> m_compressed; ///< Compressed event
      unsigned int m_compression_level; ///< Compression level

    };

  }
  
}

#endif /* EFORMAT_WRITE_FULLEVENTFRAGMENT_H */
