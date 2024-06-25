/*
 *  IssueFactory.h
 *  ers
 *
 *  Created by Matthias Wiesmann on 30.11.04.
 *  Modified by Serguei Kolos on 10.08.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

#ifndef ERS_ISSUE_FACTORY
#define ERS_ISSUE_FACTORY

#include <chrono>
#include <string>
#include <vector>
#include <map>

#include <ers/Severity.h>

/** \file IssueFactory.h This file defines the IssueFactory class, 
  * which is responsible for registration and creation of user defined issues.
  * \author Serguei Kolos
  * \brief ers header and documentation file 
  */

using std::chrono::system_clock;
  
namespace ers
{
    class Issue; 
    class Context;
    template <class > class SingletonCreator;
    
    /** This class implements factory pattern for Issues.
      * The main responsibility of this class is to keep track of the existing types of Issues
      * Each user defined issue class should register one factory method for creating instances of this class.
      * This is required for reconstructing issues produced in the context of a different process.
      * 
      * \author Serguei Kolos
      * \brief Implements factory pattern for user defined Issues.
      */
    
    class IssueFactory
    {
	template <class > friend class SingletonCreator;
        
	typedef Issue * (*IssueCreator)( const ers::Context & );
	typedef std::map<std::string,IssueCreator> FunctionMap;

      public:
	static IssueFactory & instance();					/**< \brief method to access singleton */

	Issue * create( const std::string & name,
        		const Context & context ) const ;			/**< \brief build an empty issue for a given name */
	
        Issue * create( const std::string & name,
        		const Context & context,
                        Severity severity,
                        const system_clock::time_point & time,
                        const std::string & message,
                        const std::vector<std::string> & qualifiers,
                        const std::map<std::string, std::string> & parameters,
                        const Issue * cause = 0 ) const ;			/**< \brief build issue out of all the given parameters */
	
        void register_issue( const std::string & name, IssueCreator creator );	/**< \brief register an issue factory */
      
      private:
	IssueFactory()
        { ; }
        
	FunctionMap m_creators;     
    };

    std::ostream& operator<<(std::ostream&, const IssueFactory& factory);         /**< \brief streaming operator */
}

#endif

