/*
 *  RFilterStream.h
 *  ERS
 *
 *  Created by Andrea Negri on 13.11.06.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file RFilterStream.h This file defines RFilterStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_STREAM_RFILTER_H 
#define ERS_STREAM_RFILTER_H

#include <ers/OutputStream.h>
#include <boost/regex.hpp>

namespace ers
{    
    /** This stream offers basic filtering capability.
      * It hooks up in front of another stream and filters the messages that are passed to it
      * with respect to the given configuration.
      * Filtering is based on using matching of the issue's function name and qualifiers with
      * the given regular expressions. A stream configuration is composed of the stream name,
      * that is "rfilter", followed by brackets with a comma separated list
      * of regular expressions, where any expression can be preceded by an exclamation mark.
      * For example:
      *  \li rfilter(create.*,new.*) - this stream will pass messages that have originated
      *         from a function that starts with either "create" or "new" string.
      *  \li rfilter(!create.*,!new.*) - this stream will pass messages that have originated
      *         from a function that starts with neither "create" nor "new" string.
      *
      * \brief Filtering stream implementation.
      */
    
    class RFilterStream : public OutputStream
    {
      public:
	RFilterStream( const std::string & format ); 
	
        void write( const Issue & issue ) override;
        
      private:	    
        bool is_accepted( const ers::Issue & issue );

        std::vector<boost::regex> m_regInclude;         /**< \brief include list */
        std::vector<boost::regex> m_regExclude;         /**< \brief exclude list */
    };
}

#endif
