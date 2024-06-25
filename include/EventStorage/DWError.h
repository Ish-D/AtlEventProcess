#ifndef _ERROR_ESTORE_W_
#define _ERROR_ESTORE_W_

/** 
    \brief Return codes of the DataWriter interface.
    \file EventStorage/DWError.h
*/

namespace EventStorage {

  enum DWError { DWOK = 0, /**< All OK. */
		 DWNOOK    /**< There was a problem. */
  };

}        

#endif //_ERROR_ESTORE_W_
 



