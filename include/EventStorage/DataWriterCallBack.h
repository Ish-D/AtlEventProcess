/**
 \brief an interface for a call back class
 \file EventStorage/DataWriterCallBack.h

 a class implementing this interface can be used to take
 user-defined actions on file open and on file close
 need to be registered with the DataWriter

 \author Szymon Gadomski
 \date June 2004
*/

#ifndef EVENTSTORAGE_DATAWRITERCALLBACK_H
#define EVENTSTORAGE_DATAWRITERCALLBACK_H

#include <string>
#include <stdint.h>

namespace EventStorage {
  
class DataWriterCallBack
{
public:
  virtual ~DataWriterCallBack() {};

  /** will be called after a successful file opening */
  virtual void FileWasOpened(std::string logicalfileName,
			     std::string fileName,
			     std::string streamtype,
			     std::string streamname,
			     std::string sfoid,
			     std::string guid,
			     unsigned int runNumber, 
			     unsigned int filenumber,
			     unsigned int lumiblock) = 0;
			     

  /** will be called after a successful file closing */
  virtual void FileWasClosed(std::string logicalfileName,
			     std::string fileName,
			     std::string streamtype,
			     std::string streamname,
			     std::string sfoid,
			     std::string guid,
                             std::string checksum,
			     unsigned int eventsInFile, 
			     unsigned int runNumber, 
			     unsigned int filenumber,
			     unsigned int lumiblock,
			     uint64_t filesize)= 0; 

};

}
#endif // EVENTSTORAGE_DATAWRITERCALLBACK_H




