/**
 * @file eformat/blob.h
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief A few common tools for Python <-> C++ conversion and generic
 * handling.
 */

#ifndef EFORMAT_BLOB_H 
#define EFORMAT_BLOB_H

#include <boost/shared_array.hpp>
#include <vector>
#include <string>
#include <stdint.h>
#include <stdexcept>

namespace eformat { 
  namespace helper {

    //Our current storage model is like this: the storage allocates the memory,
    //we have to deallocate it. To achieve this, we create a type that will
    //handle the memory deallocation for us. Besides this requirement, because
    //of the nature of ATLAS events, the data has to be slice-able so we can
    //get just a bit of it. Reference counting should still take place in this
    //case.
    class u32list {
      
      private:
        boost::shared_array<uint32_t> m_data;
        size_t                        m_start;
        size_t                        m_size;
        
      public:
        /**
         * Build from scratch. Can only be used from c++
         */
        u32list(uint32_t* data, size_t start, size_t size);

        /**
         * Build by copying.
         */
        u32list(const u32list& other) = default;

        /**
         * Build by assignment.
         */
        u32list& operator=(const u32list& other) = default;

        /**
         * Decrements the reference count to this guy...
         */
        virtual ~u32list();
        
        /**
         * Gets me the length of this array
         */
        inline size_t length() const { return m_size; }

        /**
         * Sets a certain item in this array. May throw std::range_error
         */
        uint32_t setitem(long pos, uint32_t val);
        
        /**
         * Gets a certain item from this array. This will copy. May throw
         * std::range_error
         */
        uint32_t getitem(long pos) const;

        /**
         * Allows const access to the raw data (on your account)
         */
        inline const uint32_t* ptr() const { return m_data.get(); }

        /**
         * Says at which offset we start
         */
        inline size_t start() const { return m_start; }
    };

    //A slice is about the same as the u32list above, except we don't manage
    //memory, we just point to in and allow the user to manipulate it as a
    //python list.
    class u32slice {
      
      private:
        const uint32_t* m_data;
        size_t          m_size;
        
      public:
        /**
         * Build from scratch. Can only be used from c++
         */
        u32slice(const uint32_t* data, size_t size);

        /**
         * Build by copying.
         */
        u32slice(const u32slice& other) = default;

        /**
         * Build by assignment.
         */
        u32slice& operator=(const u32slice& other) = default;

        /**
         * Build by copying. This is just updating the internal references.
         */
        u32slice(const u32list& other);

        /**
         * Decrements the reference count to this guy...
         */
        virtual ~u32slice();
        
        /**
         * Gets me the length of this array
         */
        inline size_t length() const { return m_size; }

        /**
         * Gets a certain item from this array. This will copy. May throw
         * std::range_error
         */
        uint32_t getitem(long pos) const;

        /**
         * Allows const access to the raw data (on your account)
         */
        inline const uint32_t* ptr() const { return m_data; }
    };

  }
}

#endif /* EFORMAT_PYTHON_UTIL_H */

