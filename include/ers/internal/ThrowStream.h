/*
 *  ThrowStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 02.08.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

/** \file ThrowStream.h This file defines ThrowStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_THROW_STREAM_H
#define ERS_THROW_STREAM_H

#include <ers/OutputStream.h>

namespace ers
{
    class Issue; 

    /** This class implements a stream, which throws the issue written to it as a normal C++ exception.
     * In order to employ this implementation in a stream configuration the name to be used is "throw".
     * E.g. the following configuration will print a first issue that is passed to the FATAL ERS stream
     * to the standard output and then throws this issue as a C++ exception:
     *
     *         export TDAQ_ERS_FATAL="stdout,throw"
     *
     * \author Serguei Kolos
     * \brief Throws issues as exceptions
     */
    
    struct ThrowStream : public OutputStream
    {
	void write( const Issue & issue ) override;
    };
}

#endif

