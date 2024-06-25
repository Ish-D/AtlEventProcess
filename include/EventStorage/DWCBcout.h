/**
 \brief example implementation for the DataWriterCallBack interface
 \file EventStorage/DWCBcout.h

 a class implementing this interface can be used to take
 user-defined actions on file open and on file close

 \author Szymon Gadomski
 \date June 2004
*/

#ifndef EVENTSTORAGE_DWCBCOUT_H
#define EVENTSTORAGE_DWCBCOUT_H

#include "EventStorage/DataWriterCallBack.h"

class DWCBcout : public EventStorage::DataWriterCallBack
{
public:
  DWCBcout(std::string appName);
  ~DWCBcout() {};

  void FileWasOpened(std::string logicalfileName,
		     std::string fileName,
		     std::string streamtype,
		     std::string streamname,
		     std::string sfoid,
		     std::string guid,
		     unsigned int runNumber, 
		     unsigned int filenumber,
		     unsigned int lumiblock) override;
  // this will be called after a successful file opening

  void FileWasClosed(std::string logicalfileName,
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
		     uint64_t filesize) override;
  // this will be called after a successful file closing
  
 private:
  std::string m_appName;
  
};
#endif // EVENTSTORAGE_DWCBCOUT_H




