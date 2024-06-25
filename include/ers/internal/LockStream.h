/*
 *  LockStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 12.04.06.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */
 
/** \file LockStream.h This file defines LockStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_LOCK_STREAM_H
#define ERS_LOCK_STREAM_H

#include <ers/OutputStream.h>
#include <mutex>

namespace ers
{

    /** This class can be used to lock a particular ERS output streams to prevent 
      * output to this stream produced by concurrent threads from been mixed up.
     * In order to employ this implementation in a stream configuration the name to be used is "lock".
     * E.g. the following configuration will assure that the output sent to the LOG stream by
     * concurrent threads is never mixed up:
     *
     *         export TDAQ_ERS_LOG="lock,stdout"
      *
      * \author Serguei Kolos
      * \brief Lock implementation for an ERS stream.
      */

    struct LockStream : public OutputStream
    {
	void write( const Issue & issue ) override;
        
      private:
	std::mutex m_mutex;
    };
}

#endif
