#ifndef ERS_LOCAL_STREAM_H
#define ERS_LOCAL_STREAM_H

/*
 *  LocalStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 21.11.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file LocalStream.h This file defines ERS LocalStream class.
  * \author Serguei Kolos
  * \brief ers header and documentation file
  */

#include <condition_variable>
#include <functional>
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>

#include <ers/Issue.h>
#include <ers/IssueCatcherHandler.h>

ERS_DECLARE_ISSUE(  ers,					// namespace
		    IssueCatcherAlreadySet, 			// issue class name
		    "Local error catcher has been already set",	//
		     ERS_EMPTY					// no attributes
		 )
                     
namespace ers
{    
    class Issue;
    template <class > class SingletonCreator;
    
    class IssueCatcherHandler;
    
    /** The \c LocalStream class can be used for passing issues between threads of the same process.
      *
      * \author Serguei Kolos
      * \version 1.2
      */

    class LocalStream
    {
        friend class IssueCatcherHandler;
	template <class > friend class SingletonCreator;
        
      public:
	        
        //! returns the singleton
        static LocalStream & instance();

	//! sets local issue catcher
	IssueCatcherHandler * set_issue_catcher( 
        			const std::function<void ( const ers::Issue & )> & catcher );

	void error( const ers::Issue & issue );
	
        void fatal( const ers::Issue & issue );
	
        void warning( const ers::Issue & issue );

      private:
	LocalStream( );
	~LocalStream( );
        
        void remove_issue_catcher();

	void report_issue( ers::severity type, const ers::Issue & issue );
        
	void thread_wrapper();

      private:
	std::function<void ( const ers::Issue & )>	m_issue_catcher;
	std::unique_ptr<std::thread>			m_issue_catcher_thread;
	std::mutex					m_mutex;
	std::condition_variable			        m_condition;
	bool						m_terminated;
	std::queue<ers::Issue *>			m_issues;
	std::thread::id					m_catcher_thread_id;
    };
}

#endif

