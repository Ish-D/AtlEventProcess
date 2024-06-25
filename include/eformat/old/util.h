//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/old/util.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch>André Rabello dos
 * ANJOS</a>
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines a set of utilities for format conversion
 */

#ifndef EFORMAT_OLD_UTIL_H
#define EFORMAT_OLD_UTIL_H

#include <stdint.h>
#include "eformat/checksum.h"

namespace eformat {

  namespace old {

    /**
     * Converts a full event fragment or a ROS fragment, from @b any old to the
     * new format, using the space of contiguous memory storage area given. If
     * the event given is already on the current format, no conversion takes
     * place.
     *
     * @param src A pointer to the first word of the event, lying in a @b
     * contiguous area of memory.
     * @param dest The destination area of memory, preallocated
     * @param max The maximum number of words that fit in the preallocated
     * memory area "dest".
     * @param event_checksum What type of checksum to deploy for full events
     * @param rob_checksum What type of checksum to deploy for rob fragments
     *
     * @return A counter, for the number of words copied from the source to the
     * destination. If that number is zero, something wrong happened.
     */
    uint32_t convert(const uint32_t* src, uint32_t* dest, uint32_t max,
        const eformat::CheckSum& event_checksum=eformat::NO_CHECKSUM,
        const eformat::CheckSum& rob_checksum=eformat::NO_CHECKSUM);

  }

}

#endif //EFORMAT_OLD_UTIL_H
