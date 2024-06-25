#ifndef ERS_CONFIGURATION_H
#define ERS_CONFIGURATION_H

/*
 *  Configuration.h
 *  ers
 *
 *  Created by Serguei Kolos on 21.11.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file Configuration.h This file defines ERS Configuration class.
  * \author Serguei Kolos
  * \brief ers header and documentation file
  */

#include <iostream>

namespace ers
{   
    class Issue;
    template <class > class SingletonCreator;
    
    /** The \c Configuration class provides API for configuring ERS output streams.
      * 
      * \author Serguei Kolos
      * \version 1.2
      * \brief Manager of ERS streams configuration. 
      * \see ers::debug
      * \see ers::error
      * \see ers::fatal
      * \see ers::information
      * \see ers::log
      * \see ers::warning
      */
    
    class Configuration
    {	
	friend std::ostream & operator<<( std::ostream &, const ers::Configuration & );
	template <class > friend class SingletonCreator;
        
      public:
	        
  	static Configuration & instance();	/**< \brief return the singleton */
        
        int debug_level() const			/**< \brief returns current debug level */
        { return m_debug_level; }
        
        int verbosity_level() const		/**< \brief returns current verbosity level */
        { return m_verbosity_level; }
        
        void debug_level( int debug_level )	/**< \brief can be used to set the current debug level */
        { m_debug_level = debug_level; }
        
        void verbosity_level( int verbosity_level );	/**< \brief can be used to set the current verbosity level */
        
      private:	
	Configuration( );
                
        int m_debug_level;		/**< \brief current active level for the debug stream */	
    	int m_verbosity_level;		/**< \brief current verbosity level for all streams */
    };
    
    std::ostream & operator<<( std::ostream &, const ers::Configuration & );
}

#endif

