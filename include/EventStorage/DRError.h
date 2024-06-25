#ifndef _ERROR_ESTORE_R_
#define _ERROR_ESTORE_R_

/** 
    \brief Return codes of the DataReader interface.
    \file EventStorage/DRError.h
*/

namespace EventStorage {

  enum DRError { DROK = 0, /**< All OK */
		 DRNOOK,   /**< an error, no way to read more data */
                 DRWAIT,   /**< No way to read more data now, but there is a new file to which another process is writing. */
		 DRNOSEQ,  /**< Not possible to make a file sequence. File name does not end with <number>.data */ 
		 DRWOFF    /**< Wrong offset was given. No event data was found. You can still try another offset. */
  };

}        

#endif //_ERROR_ESTORE_R_
 
