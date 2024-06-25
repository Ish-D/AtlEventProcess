//Dear emacs, this is -*- c++ -*-


/** 
    \brief The API for reading of raw data data files 
    written by ATLAS TDAQ applications.
    \author Szymon Gadomski
    \date May 2002 - Feb 2007
    \file EventStorage/DataReader.h
*/

#ifndef EVENTSTORAGE_DATAREADER_H
#define EVENTSTORAGE_DATAREADER_H

#include <vector>
#include <string>
#include <stdint.h>
#include <bitset>
#include "EventStorage/DRError.h"
#include "EventStorage/ESCompression.h"

#include <boost/utility.hpp>

using namespace EventStorage;

namespace EventStorage {  

  class DataReader : boost::noncopyable
    {
    protected:
      DataReader() {};

    public: 
      /** the virual destructor */
      virtual ~DataReader() {};

    public:
      /** 
	  The method to enamble reading of file sequences.
	  You need to call this method if you want to enable reading of 
	  file sequences (*0001.data, *0002.data ...).
	  By default, i.e. unless you call this method, only one file will 
	  be read 
      */ 
      virtual DRError enableSequenceReading() = 0;

      /** Feedback to user. Check if you can still read more data. */ 
      virtual bool good() const = 0;

      /** true if no more events left in the current file */
      virtual bool endOfFile() const = 0;

      /** true if no more events left in the file sequence */
      virtual bool endOfFileSequence() const = 0; 
 
      /** number of the file currently open; make sense only if you are reading a sequence */
      virtual unsigned int currentFileNumber() const = 0; 

      virtual unsigned int latestDataNumber() const = 0;


      /** 
	  read the event data 
	  \param &eventSize the event (or data block) size will be returned here
	  \param **event start of the data block
	  \param pos if you give this parameter, you are trying to get an event from the offset pos
	
	  Possible return codes are decribed in the file EventStorage/DataReader.h
      */
      virtual DRError getData(unsigned int &eventSize, char **event, int64_t pos = -1, bool memAlreadyAlloc = false, int64_t allocSizeInBytes=-1) = 0;
 
      virtual DRError getDataPreAlloced(unsigned int &eventSize, char **event, int64_t allocSizeInBytes) = 0;
 
      virtual DRError getDataPreAllocedWitPos(unsigned int &eventSize, char **event,  int64_t allocSizeInBytes, int64_t pos = -1) = 0; 
 
 
      /** name of the current file */
      virtual std::string fileName() const = 0;
     
      /** get the current offset within the file */
      virtual int64_t getPosition() const = 0;

      /** 
	  The following methogs give access to metadata stored in the files.
	
	  Dates and times are the local time of the PC that was writing tha data file.
	  Human-readable encoding as integers was used. 
	  For instance date 31012007 is 31 Jan 2007.
	  Time 184422 is 18:44:22. 

	  The following information is available without penalty at any stage during reading:
      */
      virtual unsigned int fileStartDate() const = 0; ///< Date when the file writing has started.
      virtual unsigned int fileStartTime() const = 0; ///< Time when the file writing was started.
      virtual unsigned int fileSizeLimitInDataBlocks() const = 0; ///< Maximum number of data blocks that was given when writing.
      virtual unsigned int fileSizeLimitInMB() const = 0; ///< Maximum size in MB given when writing.
      virtual std::string appName() const = 0;       ///< Name of the application that has written the file.
      virtual std::string fileNameCore() const = 0;  ///< File name not including ._<file number>.data

      /** 
	  The following parameters of the run come from the Information System of the DAQ. 
	  The information is also available without penalty at any stage during reading.
      */
      virtual unsigned int runNumber() const = 0;    ///< Run number 
      virtual unsigned int maxEvents() const = 0;    ///< Maximum number of events specified for this run
      virtual unsigned int recEnable() const = 0;    ///< Was recording enabled?     
      virtual unsigned int triggerType() const = 0;  ///< Trigger type
      virtual std::bitset<128> detectorMask() const = 0; ///< Detector mask
      virtual unsigned int beamType() const = 0;     ///< Beam type
      virtual unsigned int beamEnergy() const = 0;   ///< Beam energy
      virtual std::vector<std::string> freeMetaDataStrings() const = 0; ///< Vector of strings containing metadata

      virtual CompressionType compression() const = 0; ///< File compression technology

      /// Unique ID of the file represened as a string on POOL style.
      /// For instance 10605EAF-52B1-DB11-94A4-000347D7BFE1
      virtual std::string GUID() const = 0; 

      /** 
	  The following methods will rewind to the end of file.
	  Reading of data can continue undisturbed. 
      */    
      virtual unsigned int fileEndDate() = 0;            ///< Date when writing has stopped.
      virtual unsigned int fileEndTime() = 0;            ///< Time when writing has stopped.
      virtual unsigned int eventsInFile() = 0;           ///< Number of events in this file.
      virtual unsigned int dataMB_InFile() = 0;          ///< Number of megabytes in this file.
      virtual unsigned int eventsInFileSequence() = 0;   ///< Number of events in this file sequence written so far.
      virtual unsigned int dataMB_InFileSequence() = 0;  ///< Number of MB in this file sequence written so far. 

      virtual uint32_t lumiblockNumber() = 0;
      virtual std::string stream() = 0;
      virtual std::string projectTag() = 0;

    };

}

#endif // EVENTSTORAGE_DATAREADER_H




