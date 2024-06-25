//Dear emacs, this is -*- c++ -*-

/**
 * @file Problem.h 
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief Problems that can be seen on eformat fragments
 */

#ifndef EFORMAT_PROBLEM_H 
#define EFORMAT_PROBLEM_H

#include "eformat/EnumClass.h"
#include "eformat/SourceIdentifier.h"

#include <string>

namespace eformat {
  
  //Describes problems the eformat library can detect in ROD fragments. Please
  //note that these are COMPLEMENTARY to the problems that can be described by
  //the ROBIN using the ROBFragment status word.
  typedef enum FragmentProblem { 
    NO_PROBLEM = 0x0, //no problem found
    WRONG_MARKER = 0x1, //wrong marker found on the being of the fragment
    WRONG_ROD_MARKER = 0x2, //wrong ROD start marker
    UNSUPPORTED_VERSION = 0x3, //unsupported eformat version
    WRONG_FRAGMENT_SIZE = 0x4, //wrong fragment size detected
    UNSUPPORTED_ROD_VERSION = 0x5, //unsupported ROD major version
    WRONG_ROD_HEADER_SIZE = 0x6, //wrong header size
    WRONG_ROD_FRAGMENT_SIZE = 0x7 //wrong fragment size
  } FragmentProblem;

  namespace helper {

    extern const eformat::helper::EnumClass<FragmentProblem> 
      FragmentProblemDictionary;

  }
  
  namespace helper {

    class ProblemContainer {

    public:

      /**
       * Constructor.
       *
       * @param source The source identifier
       * @param issues The list of problems associated with the identifier
       */
      ProblemContainer(const uint32_t& source, 
		       const std::vector<eformat::FragmentProblem>& issues)
	: problems(issues), sourceid(source) {}
      
      /**
       * Empty build
       */
      ProblemContainer() {}

      /**
       * Copy
       */
      ProblemContainer(const ProblemContainer& other) = default;
      
      ProblemContainer& operator=(const ProblemContainer& other) = default;
	
      /**
       * Virtualized destructor
       */
      virtual ~ProblemContainer() {}

      /**
       * Returns a string that represents the source identifier in a human
       * readable format
       */
      std::string human_source() 
      {return eformat::helper::SourceIdentifier(sourceid).human();}

    public: //representation
      std::vector<eformat::FragmentProblem> problems; ///< The list of problems
      uint32_t sourceid; ///< The source identifier
    };
  }
}

#endif /* EFORMAT_PROBLEM_H */

