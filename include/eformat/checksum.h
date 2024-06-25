/**
 * @file eformat/checksum.h 
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief Contains constructions to allow you to calculate the check-sum of
 * fragments in an easy and uniform way.
 */

#ifndef EFORMAT_CHECKSUM_H 
#define EFORMAT_CHECKSUM_H

#include <stdint.h>
#include "eformat/EnumClass.h"

namespace eformat { 

  /**
   * The checksum enumeration defines all possible options for event format
   * check-summing.
   */
  typedef enum CheckSum {
    NO_CHECKSUM = 0x0,
    CRC16_CCITT = 0x1,
    ADLER32     = 0x2
  } CheckSum;


  namespace helper {

    extern const eformat::helper::EnumClass<CheckSum> CheckSumDictionary;

  }
  
  namespace helper {

    /**
     * Updates the Adler-32 check-sum for the data block given as parameter.
     *
     * @param current This is the initial value of the check-sum you want this
     * update routine to take into consideration. This call is normally
     * deployed if you know the check-sum of a block and you want to just to
     * append things to it. In this mode, you don't have to re-calculate the
     * whole check-sum, but to use this update version of the algorithm.
     * @param data This is a pointer to the 32-bit data block of which you
     * would like to calculate the check-sum
     * @param size This is the size, in 32-bit words, of the data block
     *
     * @return The check-sum for the whole of the data considered (this
     * includes the part of which the init value was good for)
     */
    uint32_t adler32(uint32_t init, const uint32_t* data, uint32_t size);

    /**
     * Calculates the Adler-32 check-sum for the data block given as parameter.
     *
     * @param data This is a pointer to the 32-bit data block of which you
     * would like to calculate the check-sum
     * @param size This is the size, in 32-bit words, of the data block
     *
     * @return The check-sum for the whole of the data considered
     */
    uint32_t adler32(const uint32_t* data, uint32_t size);
      
    /**
     * Calculates the CRC16-CCITT check-sum for the data block given as
     * parameter.
     *
     * @warning This algorithm is optimized for hardware execution. Make sure
     * you understand its performance before applying it randomly on your code.
     * If you want faster checksumming, consider using eformat::adler32
     *
     * @param data This is a pointer to the 32-bit data block of which you
     * would like to calculate the check-sum
     * @param size This is the size, in 32-bit words, of the data block
     *
     * @return The check-sum for the whole of the data considered
     */
    uint32_t crc16_ccitt(const uint32_t* data, uint32_t size);

    /**
     * Updates the CRC-CCITT check-sum for the data block given as parameter.
     *
     * @warning This algorithm is optimized for hardware execution. Make sure
     * you understand its performance before applying it randomly on your code.
     * If you want faster checksumming, consider using eformat::adler32
     *
     * @param current This is the initial value of the check-sum you want this
     * update routine to take into consideration. This call is normally
     * deployed if you know the check-sum of a block and you want to just to
     * append things to it. In this mode, you don't have to re-calculate the
     * whole check-sum, but to use this update version of the algorithm.
     * @param data This is a pointer to the 32-bit data block of which you
     * would like to calculate the check-sum
     * @param size This is the size, in 32-bit words, of the data block
     *
     * @return The check-sum for the whole of the data considered (this
     * includes the part of which the init value was good for)
     */
    uint32_t crc16_ccitt(uint32_t init, const uint32_t* data, uint32_t size);

    /**
     * Calculates the check-sum for the data block given as parameter.
     *
     * @warning This algorithm is optimized for hardware execution. Make sure
     * you understand its performance before applying it randomly on your code.
     * If you want faster checksumming, consider using eformat::adler32
     *
     * @param type This is one of the types value for event format check sums
     * @param data This is a pointer to the 32-bit data block of which you
     * would like to calculate the check-sum
     * @param size This is the size, in 32-bit words, of the data block
     *
     * @return The check-sum for the whole of the data considered (this
     * includes the part of which the init value was good for)
     */
    uint32_t checksum(uint32_t type, const uint32_t* data, uint32_t size);

    //this variant is for convinience
    inline uint32_t checksum(const eformat::CheckSum& type,
        const uint32_t* data, uint32_t size)
    { return checksum((uint32_t)type, data, size); }

    /**
     * Updates the check-sum for the data block given as parameter.
     *
     * @warning This algorithm is optimized for hardware execution. Make sure
     * you understand its performance before applying it randomly on your code.
     * If you want faster checksumming, consider using eformat::adler32
     *
     * @param type This is one of the types value for event format check sums
     * @param init This is the initial value of the check-sum you want this
     * update routine to take into consideration. This call is normally
     * deployed if you know the check-sum of a block and you want to just to
     * append things to it. In this mode, you don't have to re-calculate the
     * whole check-sum, but to use this update version of the algorithm.
     * @param data This is a pointer to the 32-bit data block of which you
     * would like to calculate the check-sum
     * @param size This is the size, in 32-bit words, of the data block
     *
     * @return The check-sum for the whole of the data considered (this
     * includes the part of which the init value was good for)
     */
    uint32_t checksum(uint32_t type, uint32_t init, 
        const uint32_t* data, uint32_t size);

    //this variant is for convinience
    inline uint32_t checksum(const eformat::CheckSum& type, uint32_t init, 
        const uint32_t* data, uint32_t size) 
    { return checksum((uint32_t)type, init, data, size); }
    
  } 
}

#endif /* EFORMAT_CHECKSUM_H */

