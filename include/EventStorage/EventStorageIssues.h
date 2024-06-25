#ifndef EVENTSTORAGEISSUES_H
#define EVENTSTORAGEISSUES_H

#include "ers/ers.h"


/**
   To report problems with configuration data base
*/



ERS_DECLARE_ISSUE(EventStorage,
		  WritingIssue,
		  "EventStorage writing problem" << ": " << reason,
		  ((const char*) reason)
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_SingleFile,
		  EventStorage::WritingIssue,
		  "ES_SingleFile" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_SingleFileAlreadyExists,
		  EventStorage::WritingIssue,
		  "ES_SingleFileAlreadyExists" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)




ERS_DECLARE_ISSUE(EventStorage,
		  ReadingIssue,
		  "EventStorage reading problem" << ": " << reason,
		  ((const char*) reason)
		)

ERS_DECLARE_ISSUE(EventStorage,
		  RawFileNameIssue,
		  "EventStorage problem with RawFileName" << ": " << reason,
		  ((const char*) reason)
		)


ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_InternalError,
		  EventStorage::ReadingIssue,
		  "ES_InternalError" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)


ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_WrongFileFormat,
		  EventStorage::ReadingIssue,
		  "ES_WrongFileFormat" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_OutOfFileBoundary,
		  EventStorage::ReadingIssue,
		  "ES_OutOfFileBoundary" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_NoEventFound,
		  EventStorage::ReadingIssue,
		  "ES_NoEventFound" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_WrongEventSize,
		  EventStorage::ReadingIssue,
		  "ES_WrongEventSize" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_NoEndOfFileRecord,
		  EventStorage::ReadingIssue,
		  "ES_NoEndOfFileRecord" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_AllocatedMemoryTooLittle,
		  EventStorage::ReadingIssue,
		  "ES_AllocatedMemoryTooLittle" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)

ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_AllocatingMemoryFailed,
		  EventStorage::ReadingIssue,
		  "ES_AllocatingMemoryFailed" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)



ERS_DECLARE_ISSUE_BASE(EventStorage,
		  ES_SquenceNextFileMissing,
		  EventStorage::ReadingIssue,
		  "ES_SquenceNextFileMissing" << ": " << reason  ,
		  ((const char*) reason), ERS_EMPTY
		)



/*
ES_InternalError

ES_WrongFileFormat

ES_OutOfFileBoundary
ES_NoEventFound
ES_WrongEventSize


ES_NoEndOfFileRecord
ES_AllocatedMemoryTooLittle



*/

#endif
