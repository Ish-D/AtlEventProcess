//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/FullEventFragment.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines the Event Fragment entity. The definition is based on the
 * update of ATL-DAQ-98-129, by D.Francis et al.
 */

#ifndef EFORMAT_FULLEVENTFRAGMENT_H
#define EFORMAT_FULLEVENTFRAGMENT_H

#include "eformat/FullEventFragmentNoTemplates.h"

namespace eformat {

  /**
   * Describes how to access the contents of an event fragment, as prescribed
   * by the event format note.
   */
  template <class TPointer> 
  class FullEventFragment : public eformat::read::FullEventFragment {

  public: //interface

   /**
    * Builds an empty, otherwise useless FullEventFragment
    */
   FullEventFragment () : eformat::read::FullEventFragment() {}

   /**
     * To build a fragment given the containing buffer. I need to know
     * where the fragment starts in order to do that.
     *
     * @param it The exact position where this fragment should start.
     */
    FullEventFragment (const TPointer& it)
      : eformat::read::FullEventFragment(it) {}

    /**
     * Copy constructor
     *
     * @param other The fragment to be copied
     */
    FullEventFragment (const FullEventFragment& other) 
      : eformat::read::FullEventFragment(other) {}

    /**
     * Copy constructor
     *
     * @param other The fragment to be copied
     */
    FullEventFragment (const eformat::read::FullEventFragment& other)
      : eformat::read::FullEventFragment(other) {}

    /**
     * Destructor virtualisation
     */
    virtual ~FullEventFragment() {}

    /**
     * Copy operator
     *
     * @param other The fragment to be copied
     */
    FullEventFragment& operator= (const FullEventFragment& other) 
    { eformat::read::FullEventFragment::operator=(other); return *this; }

  };

}

#endif /* EFORMAT_FULLEVENTFRAGMENT_H */
