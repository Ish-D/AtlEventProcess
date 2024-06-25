/**
 * @file eformat/index.h 
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief Constructions to build indexes of ROBs and retrieve specific data
 * from events.
 */

#ifndef EFORMAT_INDEX_H 
#define EFORMAT_INDEX_H

#include "eformat/FullEventFragment.h"
#include "eformat/ROBFragment.h"
#include "eformat/SourceIdentifier.h"
#include <map>
#include <vector>

namespace eformat {

  namespace helper {

    /**
     * Fills in the memory address of each of the ROB fragments underneath a
     * Full Event Fragment.
     *
     * @param event The full event fragment you want check
     * @param index The map you want filled with the addresses
     * @param consider_optional If this flag is set to true, we will make the
     * keys of your index taking into consideration also the "optional" part of
     * the SourceIdentifier field. The default is @b not to do this.
     */
    void build_toc (const eformat::read::FullEventFragment& event,
       std::map<uint32_t, const uint32_t*>& index,
       bool consider_optional=false);

    /**
     * Fills in the memory address of each of the ROB fragments underneath a
     * Full Event Fragment.
     *
     * @param event The full event fragment you want check
     * @param index The map you want filled with the addresses per subdetector
     * type.
     */
    void build_toc (const eformat::read::FullEventFragment& event,
       std::map<eformat::SubDetector, std::vector<const uint32_t*> >& index);

    /**
     * Fills in the memory address of each of the ROB fragments underneath a
     * Full Event Fragment.
     *
     * @param event The full event fragment you want check
     * @param index The map you want filled with the addresses per subdetector
     * group.
     */
    void build_toc (const eformat::read::FullEventFragment& event,
     std::map<eformat::SubDetectorGroup, std::vector<const uint32_t*> >& index);

    /**
     * Counts how many ROBs of each detector type there are in an event.
     *
     * @param event The full event fragment you want check
     * @param index The map you want filled with the number of ROBs of each
     * subdetector type
     */
    void count_robs (const eformat::read::FullEventFragment& event,
        std::map<eformat::SubDetector, uint32_t>& index);

    /**
     * Counts how many ROBs of each detector group there are in an event.
     *
     * @param event The full event fragment you want check
     * @param index The map you want filled with the number of ROBs of each
     * subdetector type
     */
    void count_robs (const eformat::read::FullEventFragment& event,
        std::map<eformat::SubDetectorGroup, uint32_t>& index);

    /**
     * Retrieves the first occurence of a specific ROB in the event 
     *
     * @param event The full event fragment you want check
     * @param source_id The source identifier for the ROB you are interested
     * in.
     * @param consider_optional If this flag is set to true, we will conduct
     * the search considering the optional field on the existing
     * SourceIdentifiers. The default is @b not to do this.
     */
    const uint32_t* find_rob 
      (const eformat::read::FullEventFragment& event,
       uint32_t source_id, bool consider_optional=false);

  }

}

#endif /* EFORMAT_INDEX_H */

