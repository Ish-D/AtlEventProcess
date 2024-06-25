/*
 *  ers.h
 *  ers
 *
 *  Created by Matthias Wiesmann on 26.01.05.
 *  Modified by Serguei Kolos on 26.08.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file ers.h This file defines the basic ERS API.
  * \author Serguei Kolos
  * \version 1.1
  * \brief ers main header and documentation file
  */

#ifndef ERS_ERS_H
#define ERS_ERS_H

#include <sys/resource.h>
#include <functional>
#include <sstream>
#include <ers/StreamManager.h>
#include <ers/Configuration.h>
#include <ers/Issue.h>
#include <ers/Assertion.h>
#include <ers/Severity.h>
#include <ers/LocalStream.h>

#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

/*! \namespace ers
 *  This is a wrapping namespace for all ERS classes and global functions.
 */

namespace ers
{
    typedef Issue Exception;
    
    /*! \namespace thread
     *	This is a wrapping namespace for ERS classes and global functions
     *  which can be used for the local inter-thread error reporting.
     */

    /*!
     *	This function sets up the local issue handler function. This function will be executed in the context
     *	of dedicated thread which will be created as a result of this call. All the issues which are reported
     *	via the ers::error, ers::fatal and ers::warning functions will be forwarded to this thread.
     *	\param issue the issue to be reported
     *	\return pointer to the handler object, which allows to remove the catcher by just destroying this object.
     *			If an applications ignores this return value there will no way of de installing the issue catcher.
     *	\throw ers::IssueCatcherAlreadySet for safety reasons local issue handler can be set only once
     *	\see ers::error()
     *	\see ers::fatal()
     *	\see ers::warning()
     */
    inline IssueCatcherHandler * 
    	set_issue_catcher( const std::function<void ( const ers::Issue & )> & catcher )
    { return LocalStream::instance().set_issue_catcher( catcher ); }
    
    /*! 
     *  This function returns the current debug level for ERS.
     */
    inline int debug_level( )
    { return Configuration::instance().debug_level( ); }
    
    /*! 
     *  This function sends the issue to the ERS DEBUG stream which corresponds to the given debug level.
     *  \param issue the issue to be reported
     *  \level debug level which will be associated with the reported issue
     */
    inline void debug( const Issue & issue, int level = debug_level() )
    { StreamManager::instance().debug( issue, level ); }
    
    /*! 
     *  This function sends the issue to the ERS ERROR stream.
     *  \param issue the issue to be reported
     */
    inline void error( const Issue & issue )
    { LocalStream::instance().error( issue ); }
    
    /*! 
     *  This function sends the issue to the ERS FATAL stream.
     *  \param issue the issue to be reported
     */
    inline void fatal( const Issue & issue )
    { LocalStream::instance().fatal( issue ); }
    
    /*! 
     *  This function sends the issue to the ERS INFO stream.
     *  \param issue the issue to be reported
     */
    inline void info( const Issue & issue )
    { StreamManager::instance().information( issue ); }
    
    /*! 
     *  This function sends the issue to the ERS LOG stream.
     *  \param issue the issue to be reported
     */
    inline void log( const Issue & issue )
    { StreamManager::instance().log( issue ); }
    
    /*! 
     *  This function returns the current verbosity level for ERS.
     */
    inline int verbosity_level( )
    { return Configuration::instance().verbosity_level( ); }

    /*! 
     *  This function sends the issue to the ERS WARNING stream.
     *  \param issue the issue to be reported
     */
    inline void warning( const Issue & issue )
    { LocalStream::instance().warning( issue ); }

    inline int enable_core_dump() {
        rlimit core_limit = { RLIM_INFINITY, RLIM_INFINITY };
        return setrlimit( RLIMIT_CORE, &core_limit );
    }
}

ERS_DECLARE_ISSUE( ers, Message, ERS_EMPTY, ERS_EMPTY )

#define ERS_REPORT_IMPL( stream, issue, message, level ) \
{ \
    std::ostringstream ers_report_impl_out_buffer; \
    ers_report_impl_out_buffer << message; \
    stream( issue( ERS_HERE, ers_report_impl_out_buffer.str() ) \
	    BOOST_PP_COMMA_IF( BOOST_PP_NOT( ERS_IS_EMPTY( ERS_EMPTY level ) ) ) level ); \
}

#ifndef ERS_NO_DEBUG
/** \def ERS_DEBUG( level, message) This macro sends the message to the ers::debug stream
 * if level is less or equal to the TDAQ_ERS_DEBUG_LEVEL, which is equal to 0 by default.
 * \note This macro is defined to empty statement if the \c ERS_NO_DEBUG macro is defined
 */
#define ERS_DEBUG( level, message ) do { \
if ( ers::debug_level() >= level ) \
{ \
    ERS_REPORT_IMPL( ers::debug, ers::Message, message, level ); \
} } while(0)
#else
#define ERS_DEBUG( level, message ) do { } while(0)
#endif

/** \def ERS_INFO( message ) This macro sends the message to the ers::info stream.
 */
#define ERS_INFO( message ) do { \
{ \
    ERS_REPORT_IMPL( ers::info, ers::Message, message, ERS_EMPTY ); \
} } while(0)

/** \def ERS_LOG( message ) This macro sends the message to the ers::log stream.
 */
#define ERS_LOG( message ) do { \
{ \
    ERS_REPORT_IMPL( ers::log, ers::Message, message, ERS_EMPTY ); \
} } while(0)

#endif // ERS_ERS_H

