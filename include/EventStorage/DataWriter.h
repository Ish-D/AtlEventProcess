/** 
    \brief The API for writing of event data in ATLAS TDAQ applications.
    \author Szymon Gadomski
    \date May 2002 - Feb 2007
    \file EventStorage/EnhancedDataWriter.h

    The data is stored in a sequence of disk files.
    A maximal size of a single file can be given either in number of events
    or in MB. 
*/


#ifndef EVENTSTORAGE_DATAWRITER_H
#define EVENTSTORAGE_DATAWRITER_H

#include <string>
#include <fstream>
#include <sys/uio.h>
#include <stdint.h>
#include <zlib.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include "EventStorage/DWError.h"
#include "EventStorage/EventStorageRecords.h"
#include "EventStorage/RawFileName.h"
#include "EventStorage/ESCompression.h"
#include "EventStorage/Adler32MTDefaults.h"

namespace compression {
  class DataBuffer;
}

namespace EventStorage {
  
  class DataWriterCallBack;
  class FileNameCallback;

  enum FileStatus { FINISHED, UNFINISHED };

class DataWriter : boost::noncopyable
{
public:
 
  /** 
      constructor with metadata strings 
      \param writingPath directory where to write data  
      \param fileNameCore file name not including the ending "._NNNN.data"
      \param run_parameters_record rPar other parameters from IS including the run number 
      \param fmdStrings optional vector of strings containing metadata 
      \param startIndex initial file sequence index
      \param compression Compression type
      \param compLevel   Compression level
   */
  DataWriter(const std::string writingPath,     
	     const std::string fileNameCore,    
	     const run_parameters_record rPar, 
	     const std::vector<std::string> fmdStrings, 
	     const unsigned int startIndex = 1,
	     const CompressionType compression = NONE,
	     const unsigned int compLevel = 1,
	     const int adler32mt_nb_threads = Adler32MTDefaults::NB_THREADS,
	     const uint32_t adler32mt_threshold = Adler32MTDefaults::THRESHOLD);

  DataWriter(const std::string writingPath,   
	     boost::shared_ptr<FileNameCallback> theFNCB,   
	     const run_parameters_record rPar, 
	     const std::string project,
	     const std::string streamType,
	     const std::string streamName,
	     const std::string stream,
	     const unsigned int lumiBlockNumber,
	     const std::string applicationName,
	     const std::vector<std::string> fmdStrings,
	     const CompressionType compression = NONE,
	     const unsigned int compLevel = 1,
	     const int adler32mt_nb_threads = Adler32MTDefaults::NB_THREADS,
	     const uint32_t adler32mt_threshold = Adler32MTDefaults::THRESHOLD);

  DataWriter(const std::string writingPath,   
	     const std::string fileNameCore,     
	     const run_parameters_record rPar, 
	     const std::string project,
	     const std::string streamType,
	     const std::string streamName,
	     const std::string stream,
	     const unsigned int lumiBlockNumber,
	     const std::string applicationName,
	     const std::vector<std::string> fmdStrings,
	     const CompressionType compression = NONE,
	     const unsigned int compLevel = 1,
	     const int adler32mt_nb_threads = Adler32MTDefaults::NB_THREADS,
	     const uint32_t adler32mt_threshold = Adler32MTDefaults::THRESHOLD);


private:
  DataWriter();
  
public:
  /** destructor,
      the way to close the sequence of files
  */
  ~DataWriter();
        
  /**
     max size of 1 file in number of data blocks (or events)
     1 putData call is one block
  */
  DWError setMaxFileNE(const unsigned int& maxFileNE);    

  /**
     max size of 1 file in MB. The file is closed before this limit is overrun.
  */ 
  DWError setMaxFileMB(const unsigned int& maxFileMB);    

  /**
     feedback to user
  */
  bool good() const; // check if open and last write went OK

  /** 
      set another writing path
  */
  void cd(const std::string& writingPath);

  /** 
      The file currently open is not closed immediately after cd()
      this method will return true if we are in transition phase,
      i.e. the file has not yet been closed after a cd()
  */
  bool inTransition() const;

  /** 
      Write a single block of data.
      If one of the size limits would be exceeded, the current file
      will be closed and another one will be opened automatically.
      \param dataSize size of the event in bytes
      \param *event start of the event data in memory
  */
  DWError putData(const unsigned int& dataSize, const void *event);


  /** 
      Write a single block of data already compressed. 
      *WARNING* the library has now way to check if the compression
      algorithm matches the declared file type. The data is 
      directly written to the file without check, completely trusting
      the caller. Use with care!
      If one of the size limits would be exceeded, the current file
      will be closed and another one will be opened automatically.
      \param dataSize size of the eveny in bytes
      \param *event start of the event data in memory
  */
  DWError putPrecompressedData(const unsigned int& dataSize, 
			       const void *event);

 /** 
      Write a single block of data already compressed. 
      *WARNING* the library has now way to check if the compression
      algorithm matches the declared file type. The data is 
      directly written to the file without check, completely trusting
      the caller. Use with care!
      If one of the size limits would be exceeded, the current file
      will be closed and another one will be opened automatically.
      \param number of the data chunks
      \param locations of the data chunks
  */
  DWError putPrecompressedData(const unsigned int& entries, 
			       const struct iovec* my_iovec);


  /** 
      Write data when you have one event scattered in many blocks, 
      in memory, like in the SFI application.
      If one of the size limits would be exceeded, the current file
      will be closed and another one will be opened automatically.
      \param number of the data chunks
      \param locations of the data chunks
  */
  DWError putData(const unsigned int& entries, const struct iovec* my_iovec);


    /** 
      Write a single block of data.
      If one of the size limits would be exceeded, the current file
      will be closed and another one will be opened automatically.
      \param dataSize size of the eveny in bytes
      \param *event start of the event data in memory
      \param &sizeToDisk will be update with the actual chunck size on disk
  */
  DWError putData(const unsigned int& dataSize, const void *event, uint32_t& sizeToDisk);

  /** 
      Write data when you have one event scattered in many blocks, 
      in memory, like in the SFI application.
      If one of the size limits would be exceeded, the current file
      will be closed and another one will be opened automatically.
      \param entries number of the data chunks
      \param my_iovec locations of the data chunks
      \param &sizeToDisk will be update with the actual chunck size on disk
  */
  DWError putData(const unsigned int& entries, const struct iovec* my_iovec, 
		  uint32_t& sizeToDisk);


  /**
     Close the currently open file. 
     Next file will be open anyway if you try to write again afterwards.
  */
  DWError closeFile();

  /** 
      close the file and open next one immediately
  */
  DWError nextFile();

  /**
     get the name of the current file
  */
  std::string nameFile(const FileStatus& fs) const;

  /** 
      get the offset of the latest written event;
      one should call it AFTER putData(...)
  */
  int64_t getPosition() const;

  /** number of events written to the currently open file */
  unsigned int eventsInFile() const; 

  /** number of events written to the file sequence */
  unsigned int eventsInFileSequence() const;
 
  /** number of mega bytes written to the current file */
  unsigned int dataMB_InFile() const; 

  /** number of mega bytes written to the file sequence */
  unsigned int dataMB_InFileSequence() const; 
 
  /** If you want to define actions to be taken when a file is 
      open or closed register your call-back objects here with this
      method.
      For version strictly greater than tdaq-common-02-02-00:
      Several callbacks can now be registered. Every call to this
      function with a non-null pointer will add a new callback.
      To unregister do not call register with a NULL pointer: call
      unregisterCallback instead. */
  void registerCallBack(DataWriterCallBack *pUserCBclass);

  /** New in versions strictly greater than tdaq-common-02-02-00
   * Unregister an already registered callback object to stop
   * receiving information about file opening/closing.
   */
  void unregisterCallBack(DataWriterCallBack *pUserCBclass);

  /** Returns the compression type for this file
   */
  EventStorage::CompressionType getCompression() const;

  /** Externally set the GUID for the _next_ file in this sequence
   */
  void setGuid(const std::string& Guid);
 
 private:
  class impl;
  std::unique_ptr<impl> pimpl;
};

}
#endif // EVENTSTORAGE_DATAWRITER_H




