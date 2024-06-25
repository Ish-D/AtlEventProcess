//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/eformat.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Includes all entities from the Event Format Library (eformat)
 */

#ifndef EFORMAT_EFORMAT_H
#define EFORMAT_EFORMAT_H

//utilities
#include "eformat/util.h"

//core stuff
#include "eformat/ROBFragment.h"
#include "eformat/FullEventFragment.h"

//eformat issues
#include "eformat/Issue.h"
#include "eformat/Problem.h"

//helpers
#include "eformat/SourceIdentifier.h"
#include "eformat/DetectorMask.h"
#include "eformat/Version.h"
#include "eformat/Status.h"
#include "eformat/StreamTag.h"
#include "eformat/RunType.h"
#include "eformat/checksum.h"
#include "eformat/compression.h"

#endif /* EFORMAT_EFORMAT_H */
