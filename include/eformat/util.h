//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/util.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch>André Rabello dos
 * ANJOS</a>
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines a set of utilities common to many event operations.
 */

#ifndef EFORMAT_UTIL_H
#define EFORMAT_UTIL_H

#include <fstream>
#include <stdint.h>
#include <cstdlib>
#include "eformat/HeaderMarker.h"
#include "eformat/Issue.h"

namespace eformat {

  /**
   * This function will read the next fragment in a normal, already opened,
   * std::fstream. The space for the fragment will be allocated dynamically and
   * the user should free it. Otherwise, if the user wants to re-use a
   * pre-allocated memory space, the second and third arguments can be given,
   * in which case the function will check if the space is enough. If the space
   * is not enough, NULL is returned.
   *
   * @param fs The input filestream
   * @param addr The optional user allocated space
   * @param size The optional size, in bytes, of the allocated space
   */
  uint32_t* next_fragment (std::fstream& fs, uint32_t* addr=0, size_t size=0);

  /**
   * Returns pointers (to words) to the start of each ROD fragment block in a
   * piece of memory. This is primarily intended for LVL2 supervisor usage.
   *
   * @warning This will invert the data order, meaning the last ROD will be the
   * first in the vector to appear, due to the way the ROD readout has to
   * happen (back to front of the stream). If that is not satisfactory, you
   * have to sort back the vector yourself.
   *
   * @warning this does not work if the area of memory is a compressed
   * full event.
   *
   * @param block_start The start address of the data block you want to dig the
   * ROD pointers from
   * @param block_size The size of the block, in 32-bit words 
   * @param rod A (optional) pointer to set of pre-allocated pointers
   * @param rod_size A (optional) pointer to set of pre-allocated size_t's,
   * where the size of each ROD, in words, will be stored.
   * @param max_count The maximum number of blocks to dig out from
   * <tt>block_start</tt>, if rod is not NULL. If rod is NULL, this is
   * meaningless. If the value is set to zero, all RODs are returned.
   *
   * @return The number of ROD fragments the function actually found on the
   * block, irrespective of max_count.
   */
  size_t find_rods (const uint32_t* block_start, size_t block_size,
		    const uint32_t** rod=0, uint32_t* rod_size=0,
		    size_t max_count=0);

  /**
   * A generic method to find all fragments in a contiguous area of
   * memory. These fragments cannot be RODFragments. For that, use the
   * eformat::find_rods().
   * @warning this does not work if the area of memory is a compressed
   * full event.
   *
   * @param marker The marker you are searching for (as a 32-bit word)
   * @param block_start A pointer to the block start
   * @param block_size The overall size of this block, in 32-bit words
   * @param frag A (optional) preallocated set of pointers to hold the found
   * fragments. If frag is NULL, only counts the number of children.
   * @param max_count The maximum number of fragments I'll search for, if frag
   * is not NULL. If frag is NULL, this flag has no meaning. If the value is
   * zero, return all fragments available
   *
   * @return The number of fragments the function actually found, irrespective
   * of max_count.
   */
  size_t find_fragments (uint32_t marker,
      const uint32_t* block_start, size_t block_size, 
      const uint32_t** frag=0, size_t max_count=0);
  size_t find_fragments (uint32_t marker,
      uint32_t* block_start, size_t block_size, 
      uint32_t** frag=0, size_t max_count=0);
  
  /**
   * A generic method to find all fragments in a contiguous area of
   * memory. These fragments cannot be RODFragments. For that, use the
   * eformat::find_rods().
   * @warning this does not work if the area of memory is a compressed
   * full event.
   *
   * @param marker The marker you are searching for.
   * @param block_start A pointer to the block start
   * @param block_size The overall size of this block, in 32-bit words
   * @param frag A (optional) preallocated set of pointers to hold the found
   * fragments. If frag is NULL, only counts the number of children.
   * @param max_count The maximum number of fragments I'll search for, if frag
   * is not NULL. If frag is NULL, this flag has no meaning. If the value is
   * zero, return all fragments available
   *
   * @return The number of fragments the function actually found, irrespective
   * of max_count.
   */
  size_t find_fragments (eformat::HeaderMarker marker, 
			 const uint32_t* block_start, size_t block_size,
			 const uint32_t** frag=0, size_t max_count=0);
  size_t find_fragments (eformat::HeaderMarker marker,
      uint32_t* block_start, size_t block_size, 
      uint32_t** frag=0, size_t max_count=0);

  /**
   * Gets pointers to all ROB fragments from a fragment of a type which is not
   * known in advance.
   * @warning Does not work with compressed full events.
   *
   * @param fragment The top level fragment to extract the other ROBFragment's
   * from.
   * @param rod A pointer to set of pre-allocated pointers
   * @param max_count The maximum number of blocks to dig out from
   * <tt>block_start</tt>.
   *
   * @return The number of ROBFragments the function actually found
   */
  size_t get_robs (const uint32_t* fragment, const uint32_t** rob,
                   size_t max_count) __attribute__ ((deprecated));
  
  /**
   * Gets pointers to all ROB fragments from a fragment of a type which is not
   * known in advance.
   *
   * @param fragment The top level fragment to extract the other ROBFragment's
   * from.
   * @param rob A vector that will be filled with the discovered ROB pointers.
   * The pointers may refer to the provided memory buffer or to dynamically 
   * allocated memory (in case of e.g. compressed event). The shared pointers
   * implicitly know what delete strategy to use
   */
  void get_robs (const uint32_t* fragment,
		 std::vector<std::shared_ptr<const uint32_t>>& robs);

  /**
   * This function can peek the type of fragment you are dealing with,
   * returning a HeaderMarker entity.
   *
   * @param fragment The input fragment to check
   */
  inline eformat::HeaderMarker peek_type (const uint32_t* fragment) {
    return (eformat::HeaderMarker)fragment[0];
  }

  /**
   * This function can peek the type of fragment you are dealing with,
   * returning an integer entity representing it.
   *
   * @param fragment The input fragment to check
   */
  inline uint32_t peek_marker (const uint32_t* fragment) {
    return fragment[0];
  }
  
  /**
   * This function can peek the major version number of any fragment type.
   *
   * @param fragment The input fragment to check
   */
  uint16_t peek_major_version (const uint32_t* fragment);

}

#endif //EFORMAT_UTIL_H
