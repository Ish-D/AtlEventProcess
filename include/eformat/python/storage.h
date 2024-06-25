/**
 * @file eformat/python/storage.h
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief A few utilities that are specific for python bindings to the
 * EventStorage library. Mostly extensions.
 */

#ifndef EFORMAT_PYTHON_STORAGE_H 
#define EFORMAT_PYTHON_STORAGE_H

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include "eformat/blob.h"
#include "EventStorage/DataReader.h"
#include "EventStorage/DataWriter.h"
#include "eformat/write/node.h"

namespace eformat { namespace python {

  //wrapping function to handle the EventStorage error codes
  eformat::helper::u32list read_u32list(EventStorage::DataReader& dr);

  //wrappers for creating DataReaders
  boost::shared_ptr<EventStorage::DataReader> 
    make_reader_simple(const std::string& s);

  //wrappers for writing data into the writable storage conviniently
  template <class T>
  void write_blob(EventStorage::DataWriter& dw, const T& s);

  template <class T> 
    void write_readonly(EventStorage::DataWriter& dw, const T& e);

  template <class T> 
    void write_readwrite(EventStorage::DataWriter& dw, T& e);

} }

template <class T>
void eformat::python::write_blob(EventStorage::DataWriter& dw, const T& l) {
  void* ptr = reinterpret_cast<void*>(const_cast<uint32_t*>(l.ptr()));
  if (dw.putData(l.length()*sizeof(uint32_t), ptr) != EventStorage::DWOK) { 
    throw std::runtime_error("Could not write data uint32_t blob to file");
  }
}

template <class T>
void eformat::python::write_readonly(EventStorage::DataWriter& dw, const T& e) {
  const uint32_t* ptr = 0;
  e.start(ptr);
  if (dw.putData(e.fragment_size_word()*sizeof(uint32_t), (void*)ptr) 
      != EventStorage::DWOK) {
    throw std::runtime_error("Could not write fragment to file");
  }
}

template <class T> 
void eformat::python::write_readwrite(EventStorage::DataWriter& dw, T& e) {
  const eformat::write::node_t* top = e.bind();
  uint32_t npage = eformat::write::count(*top);
  struct iovec* iov = new struct iovec[npage];
  uint32_t copied = eformat::write::shallow_copy(*top, iov, npage);
  if (!copied) {
    throw std::runtime_error("Could not shallow copy fragment");
  }
  if (dw.putData(copied, iov) != EventStorage::DWOK) {
    throw std::runtime_error("Could not write (iov) fragment to file");
  }
  delete[] iov;
}

#endif /* EFORMAT_PYTHON_STORAGE_H */

