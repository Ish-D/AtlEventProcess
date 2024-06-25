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

#ifndef ERS_GLOBAL_LOCK_STREAM_H
#define ERS_GLOBAL_LOCK_STREAM_H

#include <mutex>

#include <ers/OutputStream.h>

namespace ers
{

    /** This class can be used to protect output produced by distinct ERS streams, e.g. INFO and LOG,
      * from been mixed up when originated from concurrent threads. The name to be used for this stream
      * in stream configurations is "glock".
      * \author Serguei Kolos
      * \brief Lock for ERS streams.
      */

    struct GlobalLockStream : public OutputStream
    {
	void write( const Issue & issue ) override;
        
      private:
	static std::mutex mutex_;
    };
}

#endif
