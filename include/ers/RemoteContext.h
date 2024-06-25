/*
 *  RemoteContext.h
 *  ers
 *
 *  Created by Serguei Kolos on 26.11.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

#ifndef ERS_REMOTE_CONTEXT_H
#define ERS_REMOTE_CONTEXT_H

/** \file RemoteContext.h
  * This file defines the ers::RemoteContext class,
  * which implements the ers::Context interface.
  */ 

#include <ers/Context.h>

namespace ers
{   
    struct RemoteProcessContext
    {
	RemoteProcessContext(	const std::string & host_name,
				int pid,
				int tid,
				const std::string & cwd,
				int uid,
				const std::string & uname,
                                const std::string & app_name )
	  : m_host_name( host_name ),
            m_pid( pid ),
            m_tid( tid ),
            m_cwd( cwd ),
            m_uid( uid ),
            m_uname( uname ),
            m_app_name( app_name )
        { ; }
        
	const std::string	m_host_name;	/**< host name */
	const pid_t 		m_pid;		/**< process id */
	const pid_t 		m_tid;		/**< thread id */
	const std::string	m_cwd;		/**< process cwd */
	const int		m_uid;		/**< user id */
	const std::string	m_uname;	/**< user name */
	const std::string	m_app_name;	/**< application name */
    };
    
    class RemoteContext : public Context
    {
      public:

	/** creates a new instance of a context for an Issue that has been originated from another process.
	  * \param package_name name of the sw package
          * \param filename name of the source code file
	  * \param line_number line_number in the source code
	  * \param function_name name of the function
	  */
	RemoteContext(	const std::string & package,
        		const std::string & filename,
        		int line_number,
                        const std::string & function_name,
                        const RemoteProcessContext & pc )
	  : m_process( pc ),
	    m_package_name( package ),
            m_file_name( filename ),
	    m_function_name( function_name ),
	    m_line_number( line_number )
	{ ; }

        virtual ~RemoteContext()
        { ; }

        virtual Context * clone() const			/**< \return copy of the current context */
        { return new RemoteContext( *this ); }
        
        const char * cwd() const			/**< \return current working directory of the process */
        { return m_process.m_cwd.c_str(); }
        
        const char * file_name() const			/**< \return name of the file which created the issue */
        { return m_file_name.c_str(); }
        
        const char * function_name() const		/**< \return name of the function which created the issue */
        { return m_function_name.c_str(); }
        
        const char * host_name() const			/**< \return host where the process is running */
        { return m_process.m_host_name.c_str(); }
        
        int line_number() const				/**< \return line number, in which the issue has been created */
        { return m_line_number; }
        
        const char * package_name() const		/**< \return CMT package name */
        { return m_package_name.c_str(); }
        
        pid_t process_id() const			/**< \return process id */
        { return m_process.m_pid; }
        
        pid_t thread_id() const				/**< \return thread id */
        { return m_process.m_tid; }
        
        void * const * stack_symbols() const		/**< \return stack frames */
        { return 0; }
        
        int stack_size() const				/**< \return number of frames in stack */
        { return 0; }
        
        int user_id() const				/**< \return user id */
        { return m_process.m_uid; }
        
        const char * user_name() const			/**< \return user name */
        { return m_process.m_uname.c_str(); }

        const char * application_name() const		/**< \return application name */
        { return m_process.m_app_name.c_str(); }

      private:
        const RemoteProcessContext	m_process;		/**< process information */
        const std::string		m_package_name;		/**< source package name */
        const std::string		m_file_name;		/**< source file name */
	const std::string		m_function_name;	/**< source function name */
	const int			m_line_number;		/**< source line number */	
    };
}

#endif

