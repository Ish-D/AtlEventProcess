//Dear emacs, this is -*- c++ -*-

/**
 * @file eformat/Issue.h
 * @author <a href="mailto:Andre.dos.Anjos@cern.ch">Andre DOS ANJOS</a> 
 * $Author$
 * $Revision$
 * $Date$
 *
 * @brief Defines the base eformat Issue
 */

#ifndef EFORMAT_ISSUE_H
#define EFORMAT_ISSUE_H

#include <stdint.h>
#include <string>

#include "ers/Issue.h"
#include "eformat/HeaderMarker.h"

/**
 * Macro to facilitate hexadecimal conversion
 *
 * @param x The number that will be printed out as hexdecimal
 */
#define EFORMAT_HEX(x) std::hex << "0x" << x << std::dec

/**
 * Declares the base eformat Issue
 */
ERS_DECLARE_ISSUE(eformat, Issue, ERS_EMPTY, ERS_EMPTY)

/**
 * Simplifies the use of this Issue
 */
#define EFORMAT_ISSUE eformat::Issue(ERS_HERE)

/**
 * This exception is supposed to be thrown when version problems are found
 */
ERS_DECLARE_ISSUE_BASE(eformat, BadVersionIssue, eformat::Issue, 
  "This version of the library only supports (Full Event or ROB) format " 
  << EFORMAT_HEX(supported) << ", not " 
  << EFORMAT_HEX(current), 
  ERS_EMPTY, ((uint32_t)current) ((uint32_t)supported))

/**
 * Simplifies the use of this Issue
 *
 * @param current The current version you are trying to read
 * @param supported The supported version by this library
 */
#define EFORMAT_BAD_VERSION(current, supported) \
  eformat::BadVersionIssue(ERS_HERE, current, supported)

/**
 * This exception is supposed to be thrown when version problems are found at
 * the ROD fragment level
 */
ERS_DECLARE_ISSUE_BASE(eformat, BadRodVersionIssue, eformat::Issue, 
  "This version of the library only supports ROD format " 
  << EFORMAT_HEX(supported) << ", not "
  << EFORMAT_HEX(current), 
  ERS_EMPTY, ((uint32_t)current) ((uint32_t)supported))

/**
 * Simplifies the use of this Issue
 *
 * @param current The current version you are trying to read
 * @param supported The supported version by this library
 */
#define EFORMAT_BAD_ROD_VERSION(current, supported) \
  eformat::BadRodVersionIssue(ERS_HERE, current, supported)

/**
 * This exception is supposed to be thrown when the user is looking for a
 * child fragment that doesn't exist.
 */
ERS_DECLARE_ISSUE_BASE(eformat, NoSuchChildIssue, eformat::Issue,
		       "This fragment has only " << total 
		       << " fragment(s), but you have request fragment " 
		       << req, ERS_EMPTY,((size_t) req) ((size_t) total))

/**
 * Simplifies the use of this Issue
 *
 * @param req The request child
 * @param total The total child number available
 */
#define EFORMAT_NO_SUCH_CHILD(req, total) \
  eformat::NoSuchChildIssue(ERS_HERE, req, total)

/**
 * This exception is supposed to be thrown when the user is looking for a
 * region of memory not covered inside the buffer area.
 */
ERS_DECLARE_ISSUE_BASE(eformat, OutOfBoundsIssue, eformat::Issue,
		       "This buffer size is " << size 
		       << ", but you requested position " << pos, ERS_EMPTY,
		       ((size_t) size) ((size_t) pos))

/**
 * Simplifies the use of this Issue
 *
 * @param size The current buffer size
 * @param pos The requested position
 */
#define EFORMAT_OUT_OF_BOUNDS(size, pos) \
  eformat::OutOfBoundsIssue(ERS_HERE, size, pos)

/**
 * This exception is supposed to be thrown when the user is looking for a
 * region of memory not covered inside the buffer area.
 */
ERS_DECLARE_ISSUE_BASE(eformat, SizeCheckIssue, eformat::Issue,
		       "The fragment has informed its size to be " << informed 
		       << ", but it seems to be " << actual, ERS_EMPTY,
		       ((uint32_t) actual) ((uint32_t) informed))

/**
 * Simplifies the use of this Issue
 *
 * @param actual The actual value for the fragment size added up
 * @param informed The informed value for the fragment size
 */
#define EFORMAT_SIZE_CHECK(actual, informed) \
  eformat::SizeCheckIssue(ERS_HERE, actual, informed)

/**
 * This exception is supposed to be thrown when the reported ROD fragment size 
 * (from the trailer) does not match the expected fragment size (from the ROB)
 */
ERS_DECLARE_ISSUE_BASE(eformat, RODSizeCheckIssue, eformat::Issue,
		       "The fragment has informed its size to be " << informed 
		       << ", when corresponding ROB header reported " 
		       << actual, ERS_EMPTY,
		       ((uint32_t) actual) ((uint32_t) informed))

/**
 * Simplifies the use of this Issue
 *
 * @param actual The actual value for the fragment size added up
 * @param informed The informed value for the fragment size
 */
#define EFORMAT_ROD_SIZE_CHECK(actual, informed) \
  eformat::RODSizeCheckIssue(ERS_HERE, actual, informed)


/**
 * This exception is supposed to be thrown when the wrong marker is found on
 * the stream
 */
ERS_DECLARE_ISSUE_BASE(eformat, WrongMarkerIssue, eformat::Issue,
		       "Read (what is supposed to be a) marker 0x" 
		       << std::hex << current << ", but I was expecting"
		       << " marker 0x" << expected, ERS_EMPTY,
		       ((uint32_t) current) ((uint32_t) expected))

/**
 * Simplifies the use of this Issue
 *
 * @param current The current marker on the stream
 * @param expected The expected marker on the stream
 */
#define EFORMAT_WRONG_MARKER(current, expected)	\
  eformat::WrongMarkerIssue(ERS_HERE, current, expected)

/**
 * This exception is supposed to be thrown when the user is looking for a
 * region of memory not covered inside the buffer area.
 */
ERS_DECLARE_ISSUE_BASE(eformat, WrongSizeIssue, eformat::Issue,
		       "The informed fragment size of " << size 
		       << " words, is wrong.", ERS_EMPTY, ((uint32_t) size))

/**
 * Simplifies the use of this Issue
 *
 * @param size The wrong size informed
 */
#define EFORMAT_WRONG_SIZE(size) eformat::WrongSizeIssue(ERS_HERE, size)

/**
 * Exception that is supposed to be thrown in the case the block of data is
 * misaligned on a 32-bit boundary
 */
ERS_DECLARE_ISSUE_BASE(eformat, NotAlignedIssue, eformat::Issue,
		       "The current block of data is misaligned address = 0x" 
		       << EFORMAT_HEX(base) << " block size = " 
		       << size, ERS_EMPTY, 
                       ((unsigned long int) base) ((size_t) size))

/**
 * Simplifies the use of this Issue
 *
 * @param req The request child
 * @param total The total child number available
 */
#define EFORMAT_NOT_ALIGNED(base, size) \
  eformat::NotAlignedIssue(ERS_HERE, (unsigned long int)base, size)

/**
 * This exception is supposed to be thrown when the user is trying to add
 * more blocks than the number of blocks I can handle.
 */
ERS_DECLARE_ISSUE_BASE(eformat, TooBigCountIssue, eformat::Issue,
		       "I cannot handle " << count << " blocks of data, only "
		       << maxcount, ERS_EMPTY, 
                       ((size_t) count) ((size_t) maxcount))

/**
 * Simplifies the use of this Issue
 *
 * @param count The number of blocks I was asked to deal with
 * @param maxcount The maximum number of blocks I can deal with
 */
#define EFORMAT_TOO_BIG_COUNT(count, maxcount) \
  eformat::TooBigCountIssue(ERS_HERE, count, maxcount)

/**
 * This exception is supposed to be thrown when the user is trying give to the
 * writing part a node pointing to block of memory with insufficient size.
 */
ERS_DECLARE_ISSUE_BASE(eformat, BlockSizeTooSmallIssue, eformat::Issue,
		       "I need " << headersize << " words to serialzed my header, "
		       "but you only gave me " << nodesize, ERS_EMPTY, 
		       ((size_t) headersize) ((size_t) nodesize))

/**
 * Simplifies the use of this Issue
 *
 * @param count The number of blocks I was asked to deal with
 * @param maxcount The maximum number of blocks I can deal with
 */
#define EFORMAT_BLOCK_SIZE_TOO_SMALL(headersize, nodesize) \
  eformat::BlockSizeTooSmallIssue(ERS_HERE, headersize, nodesize)

/**
 * This exception is supposed to be thrown when the user wants to convert data
 * which is neither a full event fragment nor a ros fragment.
 */
ERS_DECLARE_ISSUE_BASE(eformat, UnsupportedOperationIssue, eformat::Issue,
		       "I cannot " << operation << " fragments of type "
		       << eformat::marker2string(marker), ERS_EMPTY, 
		       ((std::string) operation) ((uint32_t) marker))

/**
 * Simplifies the use of this Issue
 *
 */
#define EFORMAT_UNSUPPORTED_OPERATION(operation, marker) \
  eformat::UnsupportedOperationIssue(ERS_HERE, operation, marker)

/**
 * Exception that is supposed to be thrown in the case we cannot allocate
 * enough memory
 */
ERS_DECLARE_ISSUE_BASE(eformat, OutOfMemory, eformat::Issue,
		       "Could not allocate " << size << " bytes.", ERS_EMPTY, 
                       ((size_t) size))

/**
 * Simplifies the use of this Issue
 */
#define EFORMAT_OUT_OF_MEMORY(size) eformat::OutOfMemory(ERS_HERE, size)
  
/**
 * Exception that is supposed to be thrown in the case the previous eformat
 * fragment had the wrong fragment size
 */
ERS_DECLARE_ISSUE_BASE(eformat, MisalignedFragment, eformat::Issue,
		       reason, ERS_EMPTY, ((std::string) reason))

/**
 * Simplifies the use of this Issue
 */
#define EFORMAT_MISALIGNED_FRAGMENT(x) eformat::MisalignedFragment(ERS_HERE, x)

/**
 * Exception that is supposed to be thrown in the case the user wants to attach
 * more unchecked fragments in a writable FullEventFragment than the maximum
 * currently allowed. 
 */
ERS_DECLARE_ISSUE_BASE(eformat, TooManyUncheckedFragments, eformat::Issue,
		       "Cannot insert more than " << max << " unchecked ROB fragments in a writeable FullEventFragment.", ERS_EMPTY, ((uint32_t) max))

/**
 * Simplifies the use of this Issue
 */
#define EFORMAT_TOO_MANY_UNCHECKED(x) eformat::TooManyUncheckedFragments(ERS_HERE, x)

/**
 * This exception is supposed to be thrown when an unknown subdetector
 * identifier is found
 */
ERS_DECLARE_ISSUE_BASE(eformat, UnknownSubdetectorIdentifierIssue, eformat::Issue, 
  "Subdetector identifier " << EFORMAT_HEX(value) 
  << " is not known to this version of eformat", ERS_EMPTY, ((uint32_t)value))

/**
 * Simplifies the use of this Issue
 *
 * @param value The unknown subdetector identifier value 
 */
#define EFORMAT_UNKNOWN_SUBDETECTOR(value) \
  eformat::UnknownSubdetectorIdentifierIssue(ERS_HERE, value)

/**
 * This exception is supposed to be thrown when an known subdetector
 * identifier is found and not supported by the detector mask
 */
ERS_DECLARE_ISSUE_BASE(eformat, UnsupportedSubdetectorIdentifierIssue, eformat::Issue, 
  "Subdetector identifier " << EFORMAT_HEX(value) 
  << " is not supported in the DetectorMask for this version of eformat" , 
  ERS_EMPTY, ((uint32_t)value))

/**
 * Simplifies the use of this Issue
 *
 * @param value The unknown subdetector identifier value 
 */
#define EFORMAT_UNSUPPORTED_SUBDETECTOR(value) \
  eformat::UnsupportedSubdetectorIdentifierIssue(ERS_HERE, value)


/**
 * This exception is supposed to be thrown when an compression/uncompression 
 * issues take place
 */
ERS_DECLARE_ISSUE_BASE(eformat, CompressionIssue, eformat::Issue, 
		       "Compression/Decompression problem detected.",
		       ERS_EMPTY, ERS_EMPTY)

/**
 * Simplifies the use of this Issue
 *
 */
#define EFORMAT_COMPRESSION() \
  eformat::CompressionIssue(ERS_HERE)


/**
 * This exception is supposed to be thrown when an uncompression size
 * does not match
 */
ERS_DECLARE_ISSUE_BASE(eformat, WrongUncompressedSizeIssue, 
		       eformat::CompressionIssue, 
		       "Size after uncompression does not match. Expected value " << exp << ", actual value " << value,
		       ERS_EMPTY, ((uint32_t)exp) ((uint32_t)value))

/**
 * Simplifies the use of this Issue
 *
 */
#define EFORMAT_WRONG_UNCOMPRESSED_SIZE(exp, value)			\
  eformat::WrongUncompressedSizeIssue(ERS_HERE,exp,value)


/**
 * This exception is supposed to be thrown when an uncompression size
 * does not match
 */
ERS_DECLARE_ISSUE_BASE(eformat, UnknownCompressionTypeIssue, 
		       eformat::CompressionIssue, 
		       "Unknown compression type: " << value,
		       ERS_EMPTY, ((uint32_t)value))

/**
 * Simplifies the use of this Issue
 *
 */
#define EFORMAT_UNKNOWN_COMPRESSION_TYPE(value)			\
  eformat::UnknownCompressionTypeIssue(ERS_HERE,value)


/**
 * This exception is supposed to be thrown in case of detector mask issues
 * 
 */
ERS_DECLARE_ISSUE_BASE(eformat, DetectorMaskIssue, eformat::Issue, 
		       "Compression/Decompression problem detected.",
		       ERS_EMPTY, ERS_EMPTY)

/**
 * This exception is supposed to be thrown when DetectorMask 
 * string decoding fails
 */
ERS_DECLARE_ISSUE_BASE(eformat, CannotDecodeMaskIssue, 
		       eformat::DetectorMaskIssue, 
		       "Cannot decode DetectorMask string '" << mask << "' because: " << reason,
		       ERS_EMPTY, ((std::string)mask) ((std::string)reason))



#endif /* EFORMAT_ISSUE_H */
