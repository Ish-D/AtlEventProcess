/*
 *  Severity.h
 *  ers
 *
 *  Created by Serguei Kolos on 26.08.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file Severity.h This file defines Severity type for ERS.
  * \author Serguei Kolos
  * \brief ers header and documentation file 
  */

#ifndef ERS_SEVERITY_H
#define ERS_SEVERITY_H

#include <string>
#include <vector>
#include <iostream>

namespace ers
{
    class BadSeverity;
    
    enum severity { Debug, Log, Information, Warning, Error, Fatal };
    
    struct Severity
    {
    	Severity( ers::severity severity, int level = 0 )
          : type( severity ),
            rank( level )
        { ; }
        
        operator ers::severity()
        { return type; }
        
        enum severity	type;
        int		rank;
    };
        
    severity 	parse( const std::string & s, severity & );
    Severity 	parse( const std::string & s, Severity & );
    std::string	to_string( severity s );
    std::string	to_string( Severity s );

    inline std::ostream & operator<<( std::ostream & out, ers::severity severity )
    {
	out << to_string( severity );
	return out;
    }

    inline std::ostream & operator<<( std::ostream & out, const ers::Severity & severity )
    {
	out << to_string( severity );
	return out;
    }

    inline std::istream & operator>>( std::istream & in, ers::severity & severity )
    {
	std::string string;
	in >> string;
	parse( string, severity );
	return in;
    }

    inline std::istream & operator>>( std::istream & in, ers::Severity & severity )
    {
	std::string string;
	in >> string;
	parse( string, severity );
	return in;
    }
}

#endif
