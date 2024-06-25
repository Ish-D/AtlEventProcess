//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/ROBFragment.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines the ROB fragment entity as described in the Event Format
 * note.
 */

#ifndef EFORMAT_ROBFRAGMENT_H
#define EFORMAT_ROBFRAGMENT_H

#include "eformat/ROBFragmentNoTemplates.h"

namespace eformat {

  /**
   * Describes how to access the contents of a subdetector fragment, as
   * prescribed by the event format note.
   */
  template <class TPointer>
  class ROBFragment : public eformat::read::ROBFragment {

  public: //interface

   /**
     * To build a fragment given the containing buffer. I need to know
     * where the fragment starts in order to do that.
     *
     * @param it The exact position where this fragment should start.
     */
    ROBFragment (const TPointer& it) : eformat::read::ROBFragment(it) {}

    /**
     * Copy constructor
     *
     * @param other The fragment to be copied
     */
    ROBFragment (const ROBFragment& other) 
      : eformat::read::ROBFragment(other) {} 

    /**
     * Builds an empty, otherwise useless ROBFragment
     */
    ROBFragment () : eformat::read::ROBFragment() {}

    /**
     * Copy constructor
     *
     * @param other The fragment to be copied
     */
    ROBFragment (const eformat::read::ROBFragment& other)
      : eformat::read::ROBFragment(other) {}

    /**
     * Destructor virtualisation
     */
    virtual ~ROBFragment() {}

    /**
     * Assignment
     *
     * @param other The fragment to be copied
     */
    ROBFragment& operator= (const ROBFragment& other)
    { eformat::read::ROBFragment::operator=(other); return *this; }

  };

}

#endif /* EFORMAT_ROBFRAGMENT_H */
