#ifndef ERS_SAMPLE_ISSUES_H
#define ERS_SAMPLE_ISSUES_H

/*
 *  SampleIssues.h
 *  ers
 *
 *  Created by Matthias Wiesmann on 24.01.05.
 *  Modified by Serguei Kolos on 24.08.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

#include <ers/Issue.h>


/** \file SampleIssues.h Defines examples of user issues. 
  * \brief Sample ERS issues
  * \author Serguei Kolos
  * \version 1.0 
  */

/** \def ers::File This is the base class for all file related issues. 
 */
ERS_DECLARE_ISSUE_HPP( 	ers, 			// namespace
			File, 			// issue class name
			ERS_EMPTY, 		// no message
                        ((const char *)file_name ) // single attribute 
                 )

/** \def ers::CantOpenFile This issue is reported when a certain file can 
 * not be opened by any reason. 
 */
ERS_DECLARE_ISSUE_BASE_HPP( 	ers, 			// namespace
				CantOpenFile, 		// issue class name
                                ers::File, 		// base class name
				"Can not open \"" << file_name << "\" file", // message
                                ((const char *)file_name ), // base class attributes
                        	ERS_EMPTY 		// no attributes in this class
                 	)

/** \def ers::FileDoesNotExist This issue is reported when a certain file does not exist. 
 */
ERS_DECLARE_ISSUE_BASE_HPP( 	ers, 			// namespace
				FileDoesNotExist, 	// issue class name
				ers::File, 		// base class name
				"File \"" << file_name << "\" does not exist", // message
                        	(( const char * )file_name ), // base class attributes
				ERS_EMPTY 		// no attributes in this class
                 	)

/** \def ers::PermissionDenied This issue is reported when a certain file exists but
 * but not accessible for the current user. 
 */
ERS_DECLARE_ISSUE_BASE_HPP( 	ers, 					// namespace
				PermissionDenied, 			// issue class name
				ers::File, 				// base class name
				"You are not allowed to open \"" 
                        	<< file_name << "\" file, which has " 
                        	<< mode << " access mode",		// message
                        	((const char *)file_name ),		// base class attributes
				((int)mode )				// attribute of this class
                 	)

#endif

