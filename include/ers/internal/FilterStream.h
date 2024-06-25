/*
 *  FilterStream.h
 *  ERS
 *
 *  Created by Matthias Wiesmann on 31.03.05.
 *  Modified by Serguei Kolos on 11.08.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file FilterStream.h This file defines FilterStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_STREAM_FILTER_H 
#define ERS_STREAM_FILTER_H

#include <ers/OutputStream.h>

namespace ers
{    
    /** This stream offers basic filtering capability.
      * It hooks up in front of another stream and filters the messages that are passed to it
      * with respect to the given configuration.
      * Filtering is based on using plain string comparison of the issue's qualifiers with
      * the given configuration tokens. A stream configuration is composed of the stream name,
      * that is "filter", followed by brackets with a comma separated list
      * of string tokens, where any token can be preceded by an exclamation mark. For example:
      *  \li filter(internal,test) - this stream will pass messages that have either
      *         "internal" or "test" qualifier.
      *  \li filter(!internal,!test) this stream will pass messages that have neither
      *         "internal" nor "test" qualifier.
      * 
      * \brief Filtering stream implementation.
      */
    
    class FilterStream : public OutputStream
    {
      public:
	explicit FilterStream( const std::string & format );
	
        void write( const Issue & issue ) override;
        
      private:	
        bool is_accepted( const ers::Issue & issue );
        
	std::vector<std::string> m_include;		/**< \brief include list */
	std::vector<std::string> m_exclude;		/**< \brief exclude list */
    };
}

#endif
