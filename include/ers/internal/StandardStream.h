/*
 *  StandardStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 02.08.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */
 
/** \file StandardStream.h This file defines StandardStream ERS stream.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_STANDARD_STREAM_H
#define ERS_STANDARD_STREAM_H

#include <ers/OutputStream.h>
#include <ers/StandardStreamOutput.h>

namespace ers
{

    /** This class streams an issue into standard C++ output stream.
     *
      * \author Serguei Kolos
      * \brief Single line, human readable format stream.
      */

    template <class Device>
    struct StandardStream : public OutputStream,
    			    public StandardStreamOutput,
    			    public Device
    {
        using Device::device;
        
        StandardStream()
        { ; }
        
        StandardStream( const std::string & file_name )
          : Device ( file_name )
        { ; }
        
        void write( const Issue & issue )
	{
	    println( device().stream(), issue, Configuration::instance().verbosity_level() );
	    chained().write( issue );
	}
    };
}
    
#endif
