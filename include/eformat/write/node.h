//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat_write/node.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines what are eformat::write::node's and their functionality.
 */

#ifndef EFORMAT_WRITE_NODE_H
#define EFORMAT_WRITE_NODE_H

#include <stdint.h>
#include <sys/uio.h>

namespace eformat {

  namespace write {

    /**
     * Defines what is a valid "I/O vector" (a.k.a. iov) node list for eformat
     */
    struct node_t {
      uint32_t* base; ///< The base address for this page
      size_t size_word; ///< The size, in 4-byte words for this page
      node_t* next; ///< The next node
    };

    /**
     * Sets an IOV base values
     *
     * @param i the node to be set
     * @param b the base address to be used by this IOV
     * @param l the size of the page, <b>in words</b>
     * @param n the next node this node should point to
     */
    void set (node_t& i, const uint32_t* b, size_t l, node_t* n=0);

    /**
     * Sets an IOV base values
     *
     * @param i the node to be set
     * @param v the I/O vector node to use as basis
     * @param n the next node this node should point to
     */
    void set (node_t& i, const struct iovec& v, node_t* n=0);

    /**
     * Concatenates a set of IOV's to make up a list as required by some
     * eformat::write functionality.
     *
     * @param n the first node_t of a vector of node_t's. The C array pointed
     * by n should have at least "count" available positions
     * @param v the first IOV node of a vector
     * @param count the number of IOV nodes pointed by "v"
     */
    void cat (node_t* n, const struct iovec* v, uint32_t count);

    /**
     * Concatenates an already set vector of eformat::write::node_t to make up
     * a valid list.
     *
     * @param n the first node_t of a vector of node_t's. The C array pointed
     * by n should have, exactly, "count" available positions
     * @param count the number of IOV nodes pointed by "v"
     */
    void cat (node_t* n, uint32_t count);

    /**
     * Counts how many pages I'm made of
     *
     * @param list The top of the list
     */
    uint32_t count (const node_t& list);

    /**
     * Count how many words I'm made of
     *
     * @param list The top of the list
     */
    uint32_t count_words (const node_t& list);

    /**
     * Performs a memcpy like operation, concatenating the list given as
     * parameter to a block of memory, as fast as possible.
     *
     * @param list The top of the list
     * @param dest The destination block of memory
     * @param max The number of 32-bit words allocated in "dest"
     *
     * @return The number of words copied, in total. If the return value was
     * zero, a problem with the total destination size length was detected and
     * the copy operation may have undergone in an incomplete way
     */
    uint32_t copy (const node_t& list, uint32_t* dest, size_t max);

    /**
     * Performs a shallow copy like operation, concatenating the list given as
     * parameter to a vector of iovec nodes. This will only copy pointers and
     * sizes, but @b not real data. Blank pages (with either zero count or
     * with the data pointer pointing to null) are @b not accounted by this
     * function.
     *
     * @param list The top of the list
     * @param dest The destination vector of iovec nodes
     * @param max The number of iovec nodes I can use there
     *
     * @return The number of non-empty pages used, in total. If the return 
     * value was zero, a problem with the total destination size length was
     * detected and the copy operation may have undergone in an incomplete way.
     */
    uint32_t shallow_copy 
    (const node_t& list, struct iovec* dest, uint32_t max);

    /**
     * Updates the checksum of a block according to the eformat enumeration
     * type you chose.
     */
    uint32_t checksum(uint32_t type, uint32_t init, const node_t* list);

    /**
     * Calculates the checksum of a block according to the eformat enumeration
     * type you chose.
     */
    uint32_t checksum(uint32_t type, const node_t* list);

  }

}

#endif /* EFORMAT_WRITE_NODE_H */
