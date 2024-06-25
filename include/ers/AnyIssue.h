/*
 *  AnyIssue.h
 *  ers
 *
 *  Created by Serguei Kolos on 26.06.10.
 *  Copyright 2010 CERN. All rights reserved.
 *
 */

#ifndef ERS_ANY_ISSUE_H
#define ERS_ANY_ISSUE_H

/** \file AnyIssue.h
  * This file defines the ers::AnyIssue class
  */ 

#include <ers/Issue.h>

namespace ers
{   
    class AnyIssue : public ers::Issue
    {
      public:
        AnyIssue( const std::string & type,
                  const ers::Context & context,
		  const std::string & message = "" )
          : ers::Issue( context, message ),
            m_type( type )
        { ; }
        
        AnyIssue( const std::string & type,
        	  Severity severity,
                  const ers::Context & context,
		  const system_clock::time_point & time,
		  const std::string & message,
		  const std::vector<std::string> & qualifiers,
		  const std::map<std::string, std::string> & parameters,
                  const ers::Issue * cause = 0 )
          : ers::Issue( severity, time, context, message, qualifiers, parameters, cause ),
            m_type( type ) 
	{ ; }
        
        ~AnyIssue() noexcept { ; }
        
        virtual ers::Issue * clone() const
        { return new AnyIssue( *this ); }
	
        virtual const char * get_class_name() const
        { return m_type.c_str(); }
       	
        virtual void raise() const
        { throw AnyIssue(*this); }
        
      private:
      	std::string m_type;
    };
}

#endif

