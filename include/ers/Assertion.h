/*
 *  Assertion.h
 *  ers
 *
 *  Created by Matthias Wiesmann on 26.11.04.
 *  Modified by Serguei Kolos on 02.08.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

/** \file Assertion.h
  * This file defines the assertion class and the associated macros. 
  */

#ifndef ERS_ASSERTION_H
#define ERS_ASSERTION_H

#include <ers/Issue.h>
#include <ers/Severity.h>
#include <ers/StreamManager.h>

/** This class represents an assertion in the code, it is an issue with two fields:
  * \li A condition
  * \li A reason
  *
  * If the condition is not verified, an Issue is trown.
  * \author Serguei Kolos
  * \version 1.0
  */

ERS_DECLARE_ISSUE(	ers,					
			Assertion,				
			"Assertion (" << condition 
                        << ") failed because " << reason,	
			((const char *)condition )		
			((const char *)reason ) )		
#ifdef __rtems__
#include <assert.h>
#define ERS_INTERNAL_ABORT(m)	__assert_func (__FILE__, __LINE__, __ASSERT_FUNC, m)
#else
#define ERS_INTERNAL_ABORT(_)	::abort()
#endif

/** \hideinitializer
*/
#define ERS_ASSERT_MSG( expression, message ) { \
if( !(expression) ) \
{ \
    std::ostringstream ers_report_impl_out_buffer; \
    ers_report_impl_out_buffer << BOOST_PP_IF( ERS_IS_EMPTY( message ), "of unknown reason", message ); \
    std::string reason = ers_report_impl_out_buffer.str(); \
    ers::Assertion __issue__( ERS_HERE, #expression, reason.c_str() ); \
    ers::StreamManager::instance().report_issue( ers::Fatal, __issue__ ); \
    ERS_INTERNAL_ABORT(#expression); \
}}

/** \def ERS_ASSERT(expression) This macro inserts an assertion than checks condition expression.
 * If expression is not true, then an issue of type ers::Asertion is thrown. It should be used
 * to check the internal attributes. 
 * \note This macro is defined to empty statement if the \c ERS_NO_DEBUG macro is defined
 */
#define ERS_ASSERT( expression )	ERS_ASSERT_MSG( expression, "of bad internal state" )

/** \def ERS_PRECONDITION(expression) This macro inserts an assertion than checks condition expression. 
 * If expression is not true, then an issue of type ers::Asertion is thrown. It should be used
 * to check the parameters, which are passed to functions. 
 * \note This macro is defined to empty statement  if the \c ERS_NO_DEBUG macro is defined 
 */
#define ERS_PRECONDITION( expression )	ERS_ASSERT_MSG( expression, "of bad external parameter" )

/** \def ERS_RANGE_CHECK( min, val, max ) This macro inserts an assertion than checks 
 * the following condition \code ( min <= val ) && ( val <= max ) \endcode
 * If this expression is not true, then an issue of type ers::Asertion is thrown.
 * \note This macro is defined to empty statement if the \c ERS_NO_DEBUG macro is defined 
 */
#define ERS_RANGE_CHECK( min, val, max )		\
	ERS_ASSERT_MSG( (min) <= (val) && (val) <= (max), \
        			val << " is not in [" << min << "," << max << "] range" )
        
/** \def ERS_STRICT_RANGE_CHECK( min, val, max ) This macro inserts an assertion than checks 
 * the following condition \code ( min < val ) && ( val < max ) \endcode
 * If this expression is not true, then an issue of type ers::Asertion is thrown.
 * \note This macro is disabled if the \c ERS_NO_DEBUG macro is defined 
 */
#define ERS_STRICT_RANGE_CHECK( min, val, max )	\
	ERS_ASSERT_MSG( (min) < (val) && (val) < (max), \
        			val << " is not in (" << min << "," << max << ") range" )

#endif

