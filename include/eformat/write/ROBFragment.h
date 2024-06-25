//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/write/ROBFragment.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Helps the user to define and build a ROB fragment.
 */

#ifndef EFORMAT_WRITE_ROBFRAGMENT_H
#define EFORMAT_WRITE_ROBFRAGMENT_H

#include "eformat/write/node.h"
#include "eformat/Version.h"

namespace eformat {

  namespace write {

    class FullEventFragment; //forward

    /**
     * Defines a helper class to aid the creation of ROB fragments.
     */
    class ROBFragment {

    public:

      /**
       * Builds a new ROB fragment from scratch
       *
       * @param source_id The source identifier to be using for this ROB and
       * ROD
       * @param run_no The run number for this ROB/ROD
       * @param lvl1_id The LVL1 identifier for this ROB/ROD
       * @param bc_id The bunch crossing identifier for this ROB/ROD
       * @param lvl1_type The LVL1 trigger type identifier for this ROB/ROD
       * @param detev_type The detector event type for this ROB/ROD
       * @param ndata The number of 32-bits pointed by "data" bellow
       * @param data A set of 32-bit words that consist the data block of
       * this ROB fragment
       * @param status_position The status block position you want to have on
       * the ROD format. Use the definitions available in Status.h to
       * get generic identifiers for the possibilities.
       */
      ROBFragment (uint32_t source_id,
		   uint32_t run_no,
		   uint32_t lvl1_id,
		   uint32_t bc_id,
		   uint32_t lvl1_type,
		   uint32_t detev_type,
		   uint32_t ndata,
		   const uint32_t* data,
		   uint32_t status_position);

      /**
       * Builds a new ROB fragment from scratch
       *
       * @param rob_source_id The source identifier to be using for this ROB 
       * @param rod_source_id The source identifier to be using for the
       * internal ROD
       * @param run_no The run number for this ROB/ROD
       * @param lvl1_id The LVL1 identifier for this ROB/ROD
       * @param bc_id The bunch crossing identifier for this ROB/ROD
       * @param lvl1_type The LVL1 trigger type identifier for this ROB/ROD
       * @param detev_type The detector event type for this ROB/ROD
       * @param ndata The number of 32-bits pointed by "data" bellow
       * @param data A set of 32-bit words that consist the data block of
       * this ROB fragment
       * @param status_position The status block position you want to have on
       * the ROD format. Use the definitions available in Status.h to
       * get generic identifiers for the possibilities.
       */
      ROBFragment (uint32_t rob_source_id,
		   uint32_t rod_source_id,
		   uint32_t run_no,
		   uint32_t lvl1_id,
		   uint32_t bc_id,
		   uint32_t lvl1_type,
		   uint32_t detev_type,
		   uint32_t ndata,
		   const uint32_t* data,
		   uint32_t status_position);

      /**
       * Builds a new "empty" ROB fragment, otherwise invalid. Use the methods
       * bellow to set its fields. This is useful to pre-allocate objects of
       * this class in the stack and later use them by assigment. Another
       * option are standard containers, that demand the contained classes to
       * have this method.
       */
      ROBFragment ();

      /**
       * Copy constructor. This will perform a shallow copy of the fragment. In
       * this case, the data and status blocks are not copied, only the meta
       * information, i.e., @b all but the payload of the underlying ROD
       * fragment and non-variable data blocks are copied. If you wish to have
       * the data/status copied, you have to copy it manually yourself and set
       * the data pointer with the rod_data() and status() and rod_status()
       * methods. The parent fragment remains unset, and you have to append
       * this fragment manually after creation. Binding also doesn't take
       * place.
       *
       * BROKEN FRAGMENTS ACCEPTED
       *
       * @param other The other fragment to copy the meta data from.
       */
      ROBFragment (const ROBFragment& other);

      /**
       * Builds a new ROB fragment from scratch, starting from an existing ROD
       * fragment as basis.
       *
       * @param rod The rod fragment you want to start with, in a contiguous
       * block of memory
       * @param size_word The size of the ROD fragment, in words
       */
      ROBFragment (const uint32_t* rod, uint32_t size_word);

      /**
       * Builds a new ROB fragment from an existing ROB fragment in contiguous
       * memory
       *
       * @warning You cannot build from non-contiguous memory. If you have that
       * requirement, please post it to the eformat developers.
       *
       * @param rob The ROB fragment you want to start with, in a contiguous
       * block of memory
       *
       * BROKEN FRAGMENTS ACCEPTED
       */
      ROBFragment (const uint32_t* rob);

      /**
       * Base destructor
       */
      virtual ~ROBFragment ();

      /**
       * Assignment operator. This will perform a shallow copy of the
       * fragment. In this case, the data and status blocks are not copied,
       * only the meta information, i.e., @b all but the payload of the
       * underlying ROD fragment and non-variable data blocks are copied. If
       * you wish to have the data/status copied, you have to copy it manually
       * yourself and set the data pointer with the rod_data() and status() and
       * rod_status() methods. The parent fragment is @b not changed in this
       * operation. Previous binding operations remain valid after assignment.
       *
       * @param other The other fragment to copy the meta data from.
       *
       * BROKEN FRAGMENTS ACCEPTED
       */
      ROBFragment& operator= (const ROBFragment& other);

      /**
       * Copies the header (meta data information) from another
       * ROBFragment. Please note that this will not copy any specificy
       * payload related information belonging to the other fragment.
       *
       * Also note that the status of the other fragment is copied in a shallow
       * way, by pointing to the existing block of the copied fragment. This
       * way, you either must reset or guarantee this data will be available
       * during the lifetime of this fragment.
       *
       * @param other The other ROBFragment from which I should copy the
       * metadata from
       *
       * BROKEN FRAGMENTS ACCEPTED
       */
      void copy_header(const uint32_t* other);
      void copy_header(const ROBFragment& other);

      /**
       * Changes the number of status words and the status words themselves
       * from the fragment
       *
       * @param n How many status words the underlying ROD fragment supposed
       * to have.
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
      { m_node[0].base[3] &= 0xffff0000;
	m_node[0].base[3] |= v; }

      /**
       * Returns the minor version number of the fragment
       */
      inline uint16_t minor_version (void) const 
      { return 0xffff & m_node[0].base[3]; }

      /**
       * Changes the number of status words and the status words themselves
       * from the ROD fragment
       *
       * @param n How many status words the underlying ROD fragment supposed to
       * have 
       * @param status A pointer to <tt>n</tt> pre-allocated words
       */
      void rod_status (uint32_t n, const uint32_t* status);

      /**
       * Returns the number of status wors in this fragment
       */
      inline uint32_t rod_nstatus (void) const { return m_node[6].base[0]; }

      /**
       * Returns a pointer to the first ROD status word to be used by this
       * fragment 
       */
      inline const uint32_t* rod_status (void) const { return m_node[4].base; }

      /**
       * Changes the order of the status and data blocks in the ROD fragment
       *
       * @param s The new value. If v is zero, the status will preceed the
       * data, while the contrary will happen if v equals 1.
       */
      void status_position (uint32_t v);

      /**
       * Returns the current status position
       */
      inline uint32_t status_position (void) const 
      { return m_node[6].base[2]; }

      /**
       * Changes the minor version number of the underlying ROD fragment
       *
       * @param v The new minor version for this header
       */
      inline void rod_minor_version (uint16_t v)
      { m_node[3].base[2] = eformat::DEFAULT_ROD_VERSION | v; }
      
      /**
       * Gets the minor version number of the underlying ROD fragment
       */
      inline uint16_t rod_minor_version (void) const 
      { return 0xffff & m_node[3].base[2]; }

      /**
       * Changes the number of data words and the data words themselves
       * from the ROD fragment
       *
       * @param n How many data words the underlying ROD fragment supposed to
       * have 
       * @param status A pointer to <tt>n</tt> pre-allocated words
       */
      void rod_data (uint32_t n, const uint32_t* data);

      /**
       * Returns the number of data words at the ROD fragment
       */
      inline uint32_t rod_ndata (void) const { return m_node[6].base[1]; }

      /**
       * Returns a pointer to the first of the data words at the ROD fragment
       */
      inline const uint32_t* rod_data (void) const { return m_node[5].base; }

      /**
       * Changes the source identifier for both the ROB and the ROD
       * fragments. You may use individual setting methods for the ROB and the
       * ROD identifiers if you look at rob_source_id() or rob_source_id().
       *
       * @param s The new value to set
       */
      inline void source_id (uint32_t s) 
      { m_node[0].base[4] = m_node[3].base[3] = s; }

      /**
       * Changes the source identifier for @b only the ROD fragment
       *
       * @param s The new value to set
       */
      inline void rod_source_id (uint32_t s) { m_node[3].base[3] = s; }

      /**
       * Changes the source identifier for @b only the ROB fragment
       *
       * @param s The new value to set
       */
      inline void rob_source_id (uint32_t s) { m_node[0].base[4] = s; }

      /**
       * Returns the source identifier of the ROB fragment. This functionality
       * is here to make the API backwards compatible. If you read this, please
       * use either rob_source_id() or rod_source_id() bellow.
       */
      inline uint32_t source_id (void) const { return m_node[0].base[4]; }

      /**
       * Returns the source identifier of the ROB fragment
       */
      inline uint32_t rob_source_id (void) const { return source_id(); }

      /**
       * Returns the source identifier of the ROD fragment
       */
      inline uint32_t rod_source_id (void) const { return m_node[3].base[3]; }

      /**
       * Changes the check sum type for this fragment.
       *
       * @warning This will @b not calculate the checksum of the fragment until
       * you call bind(). From this point on, you should not change anymore the
       * fragment, or a re-bind() is needed.
       *
       * @param s The new value to set
       */
      void checksum_type (uint32_t s);

      /**
       * Returns the check sum type for this fragment
       */
      inline uint32_t checksum_type (void) const { return m_node[2].base[0]; }
      
      /**
       * Changes the run number for the ROD fragment
       *
       * @param s The new value to set
       */
      inline void rod_run_no (uint32_t s) 
      { m_node[3].base[4] = (s & 0x7fffffff); }

      /**
       * Returns the run number for the ROD fragment
       */
      inline uint32_t rod_run_no (void) const 
      { return m_node[3].base[4]; }

      /**
       * Changes the lvl1 identifier in the ROD fragment
       *
       * @param s The new value to set
       */
      inline void rod_lvl1_id (uint32_t s) 
      { m_node[3].base[5] = s; }

      /**
       * Returns the lvl1 identifier for the ROD fragment
       */
      inline uint32_t rod_lvl1_id (void) const 
      { return m_node[3].base[5]; }

      /**
       * Changes the bunch crossing identifier in the ROD fragment
       *
       * @param s The new value to set
       */
      inline void rod_bc_id (uint32_t s) 
      { m_node[3].base[6] = s; }

      /**
       * Returns the bunch crossing identifier for the ROD fragment
       */
      inline uint32_t rod_bc_id (void) const 
      { return m_node[3].base[6]; }

      /**
       * Changes the lvl1 trigger type in the ROD fragment
       *
       * @param s The new value to set
       */
      inline void rod_lvl1_type (uint32_t s) 
      { m_node[3].base[7] = s; }

      /**
       * Returns the lvl1 event type identifier for the ROD fragment
       */
      inline uint32_t rod_lvl1_type (void) const 
      { return m_node[3].base[7]; }

      /**
       * Changes the detector event type in the ROD fragment
       *
       * @param s The new value to set
       */
      inline void rod_detev_type (uint32_t s) 
      { m_node[3].base[8] = s; }

      /**
       * Returns the detector event type identifier for the ROD fragment
       */
      inline uint32_t rod_detev_type (void) const 
      { return m_node[3].base[8]; }

      /**
       * Returns the total size for the meta data (everything that does @b not
       * encompass the contents of the m_data pointer in the private
       * representation of this class) in the fragment, in words
       */
      inline uint32_t meta_size_word (void) const
      { return rob_header_size_word() + rod_header_size_word() + 
               rod_trailer_size_word() + rod_nstatus() + 
               rob_trailer_size_word(); }

      /**
       * Returns the total size for this fragment, in words
       */
      inline uint32_t size_word (void) const
      { return meta_size_word() + rod_ndata(); }

      /**
       * Returns the total size of the ROB header.
       */
      inline uint32_t rob_header_size_word (void) const 
      { return 7 + m_node[0].base[5]; }

      /**
       * Returns the total size of the ROB header.
       */
      inline uint32_t rob_trailer_size_word (void) const 
      { return (checksum_type()?1:0); }

      /**
       * Returns a pointer to the ROD header
       */
      inline const uint32_t* rod_header (void) const 
      { return m_node[3].base; }

      /**
       * Returns the size of a ROD header
       */
      inline uint32_t rod_header_size_word (void) const 
      { return m_node[3].size_word; }

      /**
       * Returns a pointer to the ROD trailer
       */
      inline const uint32_t* rod_trailer (void) const 
      { return m_node[6].base; }

      /**
       * Returns the size of a ROD header
       */
      inline uint32_t rod_trailer_size_word (void) const 
      { return m_node[6].size_word; }

      /**
       * Outputs a concatenation of eformat::write::node making up a list with
       * the contents of this ROB fragment.
       */
      const eformat::write::node_t* bind (void);

      /**
       * Outputs a concatenation of eformat::write::node making up a list with
       * the contents of the underlying ROD fragment.
       */
      const eformat::write::node_t* rod_bind (void);

      /**
       * This sets the parent fragment
       *
       * @param ros The ROS parent fragment of this ROB/ROD
       */
      inline void parent (eformat::write::FullEventFragment* ros) 
      { m_parent = ros; }

      /**
       * This returns the parent fragment
       */
      inline const FullEventFragment* parent (void) const { return m_parent; }

      /**
       * Sets the next sibling
       *
       * @param n The sibling following this fragment
       */
      inline void next (const ROBFragment* n) { m_next = n; }

      /**
       * Returns the next sibling
       */
      inline const ROBFragment* next (void) const { return m_next; }

    private: //to make the code simpler

      /**
       * Initializes the internal fields of this ROB fragment with the standard
       * values.
       */
      void initialize(void);

    private: //representation

      uint32_t m_header[7]; ///< The ROB Header
      uint32_t m_rod_header[9]; ///< The ROD Header
      uint32_t m_rod_trailer[3]; ///< The ROD trailer
      uint32_t m_checksum; ///< The ROB trailer
      eformat::write::node_t m_node[8]; ///< Node representation
      eformat::write::FullEventFragment* m_parent; ///< My parent
      const eformat::write::ROBFragment* m_next; ///< Next sibling

    };

  }

}

#endif /* EFORMAT_WRITE_ROBFRAGMENT_H */
