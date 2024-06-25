/*
 *  FormattedStandardStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 02.08.07.
 *  Copyright 2007 CERN. All rights reserved.
 *
 */
 
/** \file FormattedStandardStream.h This file defines FormattedStandardStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_FORMATTED_STANDARD_STREAM_H
#define ERS_FORMATTED_STANDARD_STREAM_H

#include <map>

#include <ers/OutputStream.h>

namespace ers
{

    /** This is a helper class that provides implementation of an output stream that can be used to
     * customise the output format of the streamed issues.
     * \author Serguei Kolos
     */
    namespace format
    {
        enum Token {
            Severity, Time, Position, Context, Host, PID, TID, User, CWD,
            Function, Line, Text, Stack, Cause, Parameters, Qualifiers
        };
    }
    
    template <class Device>
    struct FormattedStandardStream : public OutputStream,
				     public Device
    {
        using Device::device;
        
        FormattedStandardStream( ) =  default;
        
        /**
         * This constructor creates a new formatted output stream. The format parameter is a comma separated
         * list of tokens that defines the which attributes of the issues will be printed as well as their order.
         * Here is the list of supported tokens:
         *  "severity, time, position, context, pid, tid, cwd, function, line, cause, stack, parameters, qualifiers, user"
         * @param format a list of issue attributes that have to be printed for each issue
         */
        explicit FormattedStandardStream( const std::string & format );
        
        void write( const Issue & issue ) override;
        
      private:
	void report( std::ostream & out, const Issue & issue );
        
	struct Fields : public std::map< std::string, format::Token >
        {
            Fields();
        };
        
        static std::string get_file_name( const std::string & param );
	static std::string get_format( const std::string & param );
                
        static Fields			s_supported_fields;
        std::vector<format::Token>	m_tokens;
    };
}

#include <ers/internal/FormattedStandardStream.inc>
    
#endif
