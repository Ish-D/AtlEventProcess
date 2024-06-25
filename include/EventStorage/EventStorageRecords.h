/**
   \brief metadata records for EventStorage library
   \author Szymon Gadomski
   \date January 2004
*/

#ifndef EVENTSTORAGE_RECORDS_H
#define EVENTSTORAGE_RECORDS_H

#include <string>
#include <vector>
#include <stdint.h>

// version of file format
#define FILE_FORMAT_VERSION 0x00000006

// markers as in DAQ-1
#define FILE_START_MARKER 0x1234aaaa
#define RUN_PARAMETERS_MARKER 0x1234bbbb

#define EVENT_RECORD_MARKER 0x1234cccc

#define STRING_SECTION_MARKER 0x1234aabb
#define FREE_STRINGS_MARKER 0x1234aabc

#define FILE_END_MARKER 0x1234dddd
#define FILE_END_MARKER_LAST 0x1234eeee

namespace EventStorage {
    
  struct  file_start_record 
  {
    uint32_t marker;         /* Start of record marker          */
    uint32_t record_size;    /* Total record size               */
    uint32_t version;        /* Format version number           */
    uint32_t file_number;    /* File number in the sequence     */
    uint32_t date;           /* Date of run start               */
    uint32_t time;           /* Time of run start               */
    uint32_t sizeLimit_dataBlocks;  /* Max number of data blocks in the file */
    uint32_t sizeLimit_MB;   /* Max number of data blocks in the file */
  };

  struct file_name_strings {
    std::string appName;     
    std::string fileNameCore; 
  };

  typedef std::vector<std::string> freeMetaDataStrings;

  struct run_parameters_record {
    uint32_t marker;         /* Start of record marker          */
    uint32_t record_size;    /* Total record size               */
    uint32_t run_number;     /* From IS                         */
    uint32_t max_events;     /* From IS                         */
    uint32_t rec_enable;     /* From IS                         */
    uint32_t trigger_type;   /* From IS                         */
    uint64_t detector_mask_LS;  /* From IS                      */
    uint64_t detector_mask_MS;    /* From IS                      */
    uint32_t beam_type;      /* From IS                         */
    uint32_t beam_energy;    /* From IS                         */
  };

  struct data_separator_record {
    uint32_t marker; 	     /* Start of record marker          */
    uint32_t record_size;    /* Total record size               */
    uint32_t data_block_number;  /* Index in the file sequence      */  
    uint32_t data_block_size;    /* Size of the following block of data */
  };

  struct file_end_record {
    uint32_t marker;         /* Start of record marker          */
    uint32_t record_size;    /* Total record size               */
    uint32_t date;           /* Date of run end                 */
    uint32_t time;           /* Time of run end                 */
    uint32_t events_in_file; /* Number of events recorded       */
    uint32_t data_in_file;   /* Volume of data recorded         */
    uint32_t events_in_run;  /* Number of events recorded       */
    uint32_t data_in_run;    /* Volume of data recorded         */
    uint32_t status;         /* Used to mark the last file. Other use possible in the future.*/
    uint32_t end_marker;     /* End of RUNEND marker            */
  };

  // implement patterns
  const uint32_t file_name_strings_marker = STRING_SECTION_MARKER;
  const uint32_t free_strings_marker = FREE_STRINGS_MARKER;

  const file_start_record file_start_pattern = {
    FILE_START_MARKER,                  
    sizeof(file_start_record)/sizeof(uint32_t),     
    FILE_FORMAT_VERSION,                
    0,                                  
    0,                                  
    0,
    0,
    0
  };

  const data_separator_record data_separator_pattern = {
    EVENT_RECORD_MARKER, 	       
    sizeof(data_separator_record)/sizeof(uint32_t),           
    0,    
    0     
  };

  const file_end_record file_end_pattern = {
    FILE_END_MARKER,         
    sizeof(file_end_record)/sizeof(uint32_t),          
    0,          
    0,          
    0, 
    0,   
    0,  
    0,    
    0,    
    FILE_END_MARKER_LAST    
  };

  std::string string_record(void *ri, const void *pi);
  std::string string_record(file_name_strings nst);
  void reset_record(void *ri, const void *pi);

} // for namespace

#endif // EVENTSTORAGE_RECORDS_H


