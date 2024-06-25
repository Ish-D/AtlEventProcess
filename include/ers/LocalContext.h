/*
 *  LocalContext.h
 *  ers
 *
 *  Created by Serguei Kolos on 26.11.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

#ifndef ERS_LOCAL_CONTEXT_H
#define ERS_LOCAL_CONTEXT_H

/** \file LocalContext.h
  * This file defines the ers::LocalContext class,
  * which implements the ers::Context interface.
  */ 

#include <sys/types.h>
#include <unistd.h>

#include <ers/Context.h>

#ifdef  TDAQ_PACKAGE_NAME
#define ERS_PACKAGE TDAQ_PACKAGE_NAME
#else
#define ERS_PACKAGE "unknown"
#endif

namespace ers
{   
    struct LocalProcessContext
    {
	LocalProcessContext(	const char * const host_name,
				const char * const cwd,
				int uid,
				const char * const uname )
	  : m_host_name( host_name ),
            m_cwd( cwd ),
            m_uid( uid ),
            m_uname( uname )
        { ; }
        
	const char * const	m_host_name;	/**< host name */
	const char * const	m_cwd;		/**< process cwd */
	const int		m_uid;		/**< user id */
	const char * const	m_uname;	/**< user name */
    };
    
    class LocalContext : public Context
    {
      public:

	/** creates a new instance of a local context for an issue.
	  * This constructor should not be called directly, instead one should use the \c ERS_HERE macro.
	  * \param package_name name of the current sw package
          * \param filename name of the source code file
	  * \param line_number line_number in the source code
	  * \param function_name name of the current function
	  */
	LocalContext(	const char * package_name,
        		const char * filename,
                        int line_number,
                        const char * function_name,
                        bool debug = false);

        virtual ~LocalContext()
        { ; }

        virtual Context * clone() const			/**< \return copy of the current context */
        { return new LocalContext( *this ); }
        
        const char * cwd() const			/**< \return current working directory of the process */
        { return c_process.m_cwd; }
        
        const char * file_name() const			/**< \return name of the file which created the issue */
        { return m_file_name; }
        
        const char * function_name() const		/**< \return name of the function which created the issue */
        { return m_function_name; }
        
        const char * host_name() const			/**< \return host where the process is running */
        { return c_process.m_host_name; }
        
        int line_number() const				/**< \return line number, in which the issue has been created */
        { return m_line_number; }
        
        const char * package_name() const		/**< \return CMT package name */
        { return m_package_name; }
        
        pid_t process_id() const			/**< \return process id */
        { return ::getpid(); }
        
        pid_t thread_id() const				/**< \return thread id */
        { return m_thread_id; }
        
        void * const * stack_symbols() const		/**< \return stack frames */
        { return m_stack; }
        
        int stack_size() const				/**< \return number of frames in stack */
        { return m_stack_size; }
        
        int user_id() const				/**< \return user id */
        { return c_process.m_uid; }
        
        const char * user_name() const			/**< \return user name */
        { return c_process.m_uname; }

        const char * application_name() const;		/**< \return application name */

        static void resetProcessContext();

      private:
        static const LocalProcessContext	c_process;

	const char * const			m_package_name; /**< source package name */
        const char * const			m_file_name;	/**< source file-name */
	const char * const			m_function_name;/**< source function name */
	const int				m_line_number;	/**< source line-number */
	const pid_t				m_thread_id;	/**< thread id */	
        void *					m_stack[64];	/**< stack frames */
	const int				m_stack_size;	/**< stack frames number */
    };
}

/** \def ERS_HERE This macro constructs a context object with all the current values 
  */
#define ERS_HERE_DEBUG ers::LocalContext( ERS_PACKAGE, __FILE__, __LINE__, __PRETTY_FUNCTION__, true )

#ifndef ERS_NO_DEBUG
#define ERS_HERE ERS_HERE_DEBUG
#else
#define ERS_HERE ers::LocalContext( ERS_PACKAGE, __FILE__, __LINE__, __PRETTY_FUNCTION__, false)
#endif

#endif

