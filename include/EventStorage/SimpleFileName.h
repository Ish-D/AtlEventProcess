/**
 \brief an interface for a call back class
 \file EventStorage/FileNameCallback.h

 a class to separate the generation of file names from the DataWriter

 \author Cyril Topfel
 \date December 2009
*/

#ifndef EVENTSTORAGE_SIMPLEFILENAME_H
#define EVENTSTORAGE_SIMPLEFILENAME_H

#include <string>
#include "EventStorage/EventStorageIssues.h"

namespace EventStorage {
  
class SimpleFileName : public FileNameCallback
{
public:
  SimpleFileName(std::string tfn)
  {
    m_filename= tfn;
  }
  
  ~SimpleFileName() {};

  virtual void advance()
  {
    EventStorage::ES_SingleFile ci(ERS_HERE, "DataWriter called with a freename. DataWriter wants to go to next file, but cannot, since indexing is forbidden. Increase the file size limit (or turn it off)");
    throw ci;  
  }
  
  virtual std::string getCurrentFileName(bool writing=false)
  {
    if (writing)
      return m_filename + ".writing";
    else
      return m_filename;

  }
    
  virtual std::string getCoreName()
  {
    return m_filename;
  }
  
/*  virtual std::string getFileNameByIndex(int index);*/
  virtual unsigned int getIndex()
  {
    EventStorage::ES_SingleFile ci(ERS_HERE, "DataWriter called with a freename. DataWriter wants to go to next file, but cannot, since indexing is forbidden. Increase the file size limit (or turn it off)");
    throw ci;    
  
  }
  
  
  virtual void fileAlreadyExists()
  {
    EventStorage::ES_SingleFileAlreadyExists ci(ERS_HERE, "File Already exists, and cannot recover since file name index is forbidden");
    throw ci;    
  
  }
  
private:

  std::string m_filename;

};

}
#endif // EVENTSTORAGE_FILENAMECALLBACK_H




