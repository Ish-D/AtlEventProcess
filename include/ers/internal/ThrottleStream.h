/*
 *  ThrottleStream.h
 *  ers
 *
 *  Created by Gordon Crone on 02.08.05.
 *  Copyright 2004 CERN. All rights reserved.
 *
 */

#ifndef ERS_THROTTLE_STREAM_H
#define ERS_THROTTLE_STREAM_H

#include <map>
#include <mutex>

#include <ers/OutputStream.h>

namespace ers
{
    /** This class implements a stream that swallows identical issues if they are sent to the given stream too often.
     * In order to employ this implementation in a stream configuration the name to be used is "throttle".
     * E.g. the following configuration will suppress identical issues from been printed to the standard output:
     *
     *         export TDAQ_ERS_FATAL="throttle(10, 20),stdout"
     *
     * This stream has two configuration parameters:
     *   - first parameter defines an initial number of identical messages after which the throttling shall be started
     *   - second parameter defines a timeout in seconds after which the throttling is reset to its initial state if no
     *          issues of a given type have been reported in this period
     *
     * \author Serguei Kolos
     * \brief Throws issues as exceptions
     */
    class ThrottleStream: public ers::OutputStream {
    public:
        explicit ThrottleStream(const std::string &criteria);

        void write(const ers::Issue &issue) override;

    private:
        class IssueRecord {
        public:
            IssueRecord();
            void reset();

            std::time_t m_lastOccurance;
            std::time_t m_lastReport;
            std::string m_lastOccuranceFormatted;
            int m_initialCounter;
            int m_threshold;
            int m_suppressedCounter;
        };

    private:
        void throttle(IssueRecord &record, const ers::Issue &issue);

        void reportSuppression(IssueRecord &record, const ers::Issue &issue);

        typedef std::map<std::string, IssueRecord> IssueMap;
        IssueMap m_issueMap;

        int m_initialThreshold;
        int m_timeLimit;
        std::mutex m_mutex;
    };
}

#endif
