/*
 *  AbortStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 02.08.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

/** \file AbortStream.h This file defines AbortStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_ABORT_STREAM_H
#define ERS_ABORT_STREAM_H

#include <ers/OutputStream.h>

namespace ers
{
    class Issue; 

    /** This class implements a stream, which aborts the application whenever it receives an issue.
     * In order to employ this implementation in a stream configuration the name to be used is "abort".
     * E.g. the following configuration will print a first issue that is passed to the FATAL ERS stream
     * to the standard output and then aborts the application:
     *
     *         export TDAQ_ERS_FATAL="stdout,abort"
     *
     * \author Serguei Kolos
     * \brief Aborts the current application
     */
    
    struct AbortStream : public OutputStream
    {
	void write( const Issue & issue ) override;
    };
}

#endif

