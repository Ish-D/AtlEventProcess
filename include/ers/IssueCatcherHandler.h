#ifndef ERS_ISSUE_CATCHER_HANDLER_H
#define ERS_ISSUE_CATCHER_HANDLER_H

/*
 *  IssueCatcherHandler.h
 *  ers
 *
 *  Created by Serguei Kolos on 21.11.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

/** \file IssueCatcherHandler.h This file declares utility class which is used to unregister IssueCatcher.
  * \author Serguei Kolos
  * \brief ers header and documentation file
  */
namespace ers
{
    class LocalStream;
    
    /**
     * This is a helper class that is used to support issue catcher management. An instance of this class
     * holds a reference to the last successfully registered issue catcher. When this instance is destroyed
     * the issue catcher is unregistered.
     *
     * \author Serguei Kolos
     * \brief Implements issue catcher lifetime management.
     */
    class IssueCatcherHandler
    {
	friend class LocalStream;
        
      public:	
	~IssueCatcherHandler();
        
      private:
	IssueCatcherHandler() = default;

	IssueCatcherHandler (const IssueCatcherHandler &) = delete;
	IssueCatcherHandler & operator = (const IssueCatcherHandler &) = delete;
    };
}

#endif
