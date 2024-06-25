/*
 *  NullStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 02.08.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

/** \file NullStream.h This file defines NullStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file
  */

#ifndef ERS_NULL_STREAM_H
#define ERS_NULL_STREAM_H

#include <ers/OutputStream.h>
#include <ers/InputStream.h>

namespace ers
{
    class Issue;

    /** This stream implementation silently discards any issue that is sent to it.
     * In order to employ this implementation in a stream configuration the name to be used is "null".
     * E.g. the following configuration will result in no output been produced for the ERROR stream:
     *
     *         export TDAQ_ERS_ERROR="null"
     *
     * \author Serguei Kolos
     * \brief Null stream
     */

    struct NullStream : public OutputStream
    {
        void write( const Issue & ) override
        { ; }

        bool isNull() const override
        { return true; }
    };
}

#endif

