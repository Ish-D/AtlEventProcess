/*
 *  PluginManager.h
 *  ers
 *
 *  Created by Serguei Kolos on 21.11.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file PluginManager.h This file defines PluginManager ERS class.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_PLUGIN_MANAGER_H
#define ERS_PLUGIN_MANAGER_H

#include <string>
#include <map>

namespace ers
{
    class PluginException
    {
      public:
	PluginException( const std::string & reason)
	  : reason_( reason )
	{ ; }

	const std::string & reason() const
	{ return reason_; }

      private:
	const std::string reason_;
    };

    class PluginManager
    {
	class SharedLibrary
	{
	  public:
	    /**	 Loads a shared library and locates the create function.
	    Stores a pointer to the create function in the map indexed by
	    the library name.
	    @param name Name of the class to be loaded (library name excluding
	    lib prefix and .so suffix).
	    */
	    SharedLibrary( const std::string & name );

	    /** Unloads dynamic library and removes it from the map.  */
	    ~SharedLibrary();

	  private:
	    void *	handle_;
	};

	typedef std::map< std::string, SharedLibrary* > LibMap;

	LibMap	    libraries_;

      public:
	/** Constructor loads the plugins.
	 */
	PluginManager();

	/** Destructor unloads the plugins.
	 */
	~PluginManager();
    };
}

#endif
