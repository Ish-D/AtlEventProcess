/*
 *  ExitStream.h
 *  ers
 *
 *  Created by Serguei Kolos on 02.08.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

/** \file ExitStream.h This file defines ExitStream ERS stream.
 * \author Serguei Kolos
 * \brief ers header file
 */

#ifndef ERS_EXIT_STREAM_H
#define ERS_EXIT_STREAM_H

#include <ers/OutputStream.h>

namespace ers {

    class Issue;

    /** This class implements a stream, which exits the application whenever it receives an issue.
     * In order to employ this implementation in a stream configuration the name to be used is "exit".
     * E.g. the following configuration will print a first issue that is passed to the FATAL ERS stream
     * to the standard output and then terminates the application:
     *
     *         export TDAQ_ERS_FATAL="stdout,exit"
     *
     * \author Serguei Kolos
     * \version 1.0
     * \brief Terminates the current application
     */

    struct ExitStream: public OutputStream
    {
        /**
         * Creates a new instance of Exit stream.
         *
         * @param exit_code This sting shall contain a number that will be used as the application exit status.
         */
        explicit ExitStream(const std::string &exit_code = "1");

        void write(const Issue &issue) override;

    private:
        int m_exit_code;
    };
}

#endif

