/** 
    \brief Class describing filenames of raw data in a format agreed for ATLAS; contruct, interpret and modify such file-names.
    \author Kostas Kordas
    \date Oct 2008
    \file EventStorage/RawFileName.h
*/

#ifndef EVENTSTORAGE_ONLINEFILENAME_H
#define EVENTSTORAGE_ONLINEFILENAME_H

#include "EventStorage/EventStorageIssues.h"
#include "EventStorage/FileNameCallback.h"
//-----------------
// includes for ers
#include "ers/ers.h"
//-----------------

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>



namespace daq 
{

  /**
   *  Constants associated with the RAW file name convention
   * --------------------------------------------------------
   */
  // extenstions of files and delimiter between fields:
  static const std::string  RAWFILENAME_EXTENSION_UNFINISHED    = ".writing";
  static const std::string  RAWFILENAME_EXTENSION_FINISHED      = ".data";
  static const std::string  RAWFILENAME_DELIMITER               = ".";
  // defaults:
  static const unsigned int RAWFILENAME_DEFAULT_UINT            = 0;
  static const std::string  RAWFILENAME_DEFAULT_STRING          = ""; 
  //  width of some file name fields, for proper padding:
  static const unsigned int RAWFILENAME_RUN_NUMBER_LENGTH       = 8;
  static const unsigned int RAWFILENAME_LB_NUMBER_LENGTH        = 4;
  static const unsigned int RAWFILENAME_FILE_NUMBER_LENGTH      = 4;
  static const unsigned int RAWFILENAME_RUN_NUMBER_LENGTH_OLD   = 7;
  static const unsigned int RAWFILENAME_FILE_NUMBER_LENGTH_OLD  = 2;


  /**
   * Helper class for exceptions
   */
  class BadConversion : public std::runtime_error {
  public:
    BadConversion(const std::string& s) : std::runtime_error(s) { }
  };

  /**
   * The class implementing the online filename convention
   */
  class RawFileName : public EventStorage::FileNameCallback {
  public:
    /**
     * Contructor with all ingredients given
     * Note: Extension will be made to start with '.' (e.g., "data" -> ".data")
     */
    RawFileName(std::string ProjectTag,
		unsigned int RunNumber,
		std::string StreamType,
		std::string StreamName,
		unsigned int LumiBlockNumber,
		std::string ApplicationName,
		std::string ProductionStep="daq",
		std::string DataType="RAW",
		unsigned int FileSequenceNumber=1,
		std::string Extension="");
		


    void advance();
    std::string getCurrentFileName(bool writing);
  /*  virtual std::string getFileNameByIndex(int index);*/

    std::string getCoreName();


    unsigned int getIndex();
    void fileAlreadyExists();


		
    /**
     * Constructor with the FileNameCore, a FileSequenceNumber and 
     * the Extension only - 
     *  Does not alter the FileNameCore, just attaches trailer fields 
     *  to the fileNameCore; also, tries to interpret the resulting filename
     *  Note: Extension will be made to start with '.' (e.g., "data" -> ".data")
     */
    RawFileName(std::string FileNameCore,
		unsigned int FileSequenceNumber,
		std::string Extension="");

    /**
     * Contructor with just the filename given: for interpretation
     */   
    RawFileName(std::string FileName);
     
    /**
     * Destructor
     */
    ~RawFileName();

    /**
     * given the ingedients, contruct the fileName
     */
    void buildFileName(std::string ProjectTag,
		       unsigned int RunNumber,
		       std::string StreamType,
		       std::string StreamName,
		       unsigned int LumiBlockNumber,
		       std::string ApplicationName,
		       std::string ProductionStep,
		       std::string DataType,
		       unsigned int FileSequenceNumber,
		       std::string Extension);
    
    /**
     * given the ingedients, contruct the fileNameCore 
     * and set m_core_known = true
     */
    void buildFileNameCore(std::string ProjectTag,
			   unsigned int RunNumber,
			   std::string StreamType,
			   std::string StreamName,
			   unsigned int LumiBlockNumber,
			   std::string ApplicationName,
			   std::string ProductionStep,
			   std::string DataType);

    /**
     * Complete the FileName, 
     * by appending a FileSequenceNumber and an Extension to the FileNameCore
     * and set m_trailers_known = true
     * Note: Extension will be made to start with '.' (e.g., "data" -> ".data")
     */
    void buildFileNameTrailers(std::string FileNameCore, 
			       unsigned int FileSequenceNumber,
			       std::string Extension);

    /**
     * given the fileName, reconstruct the ingredients
     */
    bool interpretFileName(std::string FileName); 

    /**
     * contruct the complain
     */
    std::string complain();
 
    /**
     * print the content of this object
     */
    void print();

    /**
     * Get methods:
     * ------------
     */
    std::string project();
    unsigned int runNumber();
    std::string streamType();
    std::string streamName();
    std::string stream();
    unsigned int lumiBlockNumber();
    std::string applicationName();
    std::string productionStep();
    std::string dataType();
    unsigned int fileSequenceNumber();
    std::string extension();

    std::string fileNameCore() { return m_fileNameCore; }
    std::string fileName() { return m_fileName; }

    bool hasValidCore() { return m_core_known; }
    bool hasValidTrailer() { return m_trailer_known; }

    std::string datasetName();

    /**
     * Set methods:
     * ------------
     */

    /**
     * Default values for the filename fields 
     * If filename is valid, the correct values will be returned when asked.
     */
    void setDefaults();

    /**
     * Modify the File Trailer fileds (FileSequence Number and  Extension)
     */
    void setTailers(unsigned int fsn_i, std::string extension_s); 

    /**
     * Modify the FileSequenceNumber at the file trailer fields
     */
    void setFileSequenceNumber( unsigned int fsn_i );

    /**
     * Modify the File Extension at the file trailer fields
     */
    void setExtension( std::string extension_s );
    

  public: 
    /** 
     *  Helper methods: made static for use even without an object
     * ------------------------------------------------------------
     */

    /**
     * given a string and a delimeter, split it in fields and return them in 
     * a vector of strings
     */
    static std::vector<std::string> split(std::string const & s, 
					  char delimiter);

    /**
     * string to integer conversion
     */ 
    static unsigned int convertToUINT(const std::string & s);


  private:
    /**
     * Member data:
     * ------------
     */
    std::string m_project;
    unsigned int m_runNumber;
    std::string m_streamType;
    std::string m_streamName;
    std::string m_stream;
    unsigned int m_lumiBlockNumber;
    std::string m_applicationName;
    std::string m_productionStep;
    std::string m_dataType;
    std::string m_fileNameCore;

    unsigned int m_fileSequenceNumber;
    std::string m_extension;
    std::string m_fileName;

    std::string m_datasetName;

    bool m_core_known;
    bool m_trailer_known;
    
  }; // end RawFileName class declaration

} // end "daq" namespace

#endif // EVENTSTORAGE_ONLINEFILENAME_H
