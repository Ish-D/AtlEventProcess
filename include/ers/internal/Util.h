/*
 *  Util.h
 *  ers
 *
 *  Created by Serguei Kolos on 26.08.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file Util.h This file defines some common utility functions for ERS.
  * \author Serguei Kolos
  * \brief ers header file 
  */

#ifndef ERS_UTIL_H
#define ERS_UTIL_H

#include <string>
#include <vector>

namespace ers
{    
    void tokenize(	const std::string & text,
    			const std::string & separators,
                        std::vector<std::string> & tokens );
    
    int read_from_environment( const char * name, int default_value );
    
    const char * read_from_environment( const char * name, const char * default_value );
}

#endif
