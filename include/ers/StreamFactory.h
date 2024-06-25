/*
 *  StreamFactory.h
 *  ers
 *
 *  Created by Matthias Wiesmann on 21.01.05.
 *  Modified by Serguei Kolos on 21.11.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

#ifndef ERS_STREAM_FACTORY_H
#define ERS_STREAM_FACTORY_H

#include <ers/Severity.h>
#include <ers/Context.h>
#include <ers/Issue.h>

#include <map>

/** \file StreamFactory.h This file defines the StreamFactory class, 
  * which is responsible for registration and creation of ERS streams.
  * \author Serguei Kolos
  * \brief ers header and documentation file 
  */

ERS_DECLARE_ISSUE(  ers,
		    InvalidFormat,
		    "Creator for the \"" << key << "\" stream is not found",
		    ((std::string)key ) )

namespace ers
{
    class InputStream; 
    class OutputStream; 
    template <class > class SingletonCreator;
    
    /** The \c StreamFactory class is responsible for creating a new instance of a known stream implementation.
      * This class uses singleton pattern.
      * Users should not use this class directly but use the \c ERS_REGISTER_OUTPUT_STREAM macro instead.
      * 
      * \author Serguei Kolos
      * \brief Factory for ERS stream implementations.
      * \see ers::StreamManager
      */
    
    class StreamFactory
    {	
	friend std::ostream & operator<<( std::ostream &, const ers::StreamFactory & );
	template <class > friend class SingletonCreator;
        
        typedef ers::InputStream * (*InputStreamCreator) ( const std::initializer_list<std::string> & params );
        typedef ers::OutputStream * (*OutputStreamCreator)( const std::string & format );
              
      public:
	        
  	static StreamFactory & instance();					/**< \brief return the singleton */

	void register_in_stream( const std::string & name,
        			 InputStreamCreator callback );			/**< \brief register a stream creator */
	
	void register_out_stream( const std::string & name,
        			  OutputStreamCreator callback );		/**< \brief register a stream creator */
	
        InputStream * create_in_stream( const std::string & stream, 
        				const std::string & filter ) const;	/**< \brief create new stream */
	
        InputStream * create_in_stream( const std::string & stream, 
		const std::initializer_list<std::string> & params ) const;	/**< \brief create new stream */
	
        OutputStream * create_out_stream( const std::string & format ) const;	/**< \brief create new stream */
	
      private:	
	StreamFactory( )
        { ; }

	typedef std::map<std::string, InputStreamCreator>	InFunctionMap;
	typedef std::map<std::string, OutputStreamCreator>	OutFunctionMap;
        
	InFunctionMap	m_in_factories;		/**< \brief collection of factories to build input streams */	
	OutFunctionMap	m_out_factories;	/**< \brief collection of factories to build output streams */	
    };
    
    std::ostream & operator<<( std::ostream &, const ers::StreamFactory & );
}

#endif

