/**
 * @file eformat/python/util.h
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief A few common tools for Python <-> C++ conversion and generic
 * handling.
 */

#ifndef EFORMAT_PYTHON_UTIL_H 
#define EFORMAT_PYTHON_UTIL_H

#include <boost/python.hpp>
#include <boost/python/slice.hpp>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include "eformat/eformat.h" 
#include "eformat/write/eformat.h" 

namespace eformat { namespace python {

  /**
   * lvalue converter for string vectors into python lists. This will allow you
   * to do this:
   * l = list(std_string_vector_object)
   */
  struct string_vector_to_list {
    static PyObject* convert (const std::vector<std::string>& v);
  };

  /**
   * Exception translators
   */
  void translate_ers_issue(ers::Issue const& e);
  void translate_range_error(std::range_error const& e); 

  /**
   * A helper to encode stream tags in pythonic way
   */
  eformat::helper::u32list stream_tag_encode
    (const std::vector<eformat::helper::StreamTag>& v);

  /**
   * A helper to decode stream tags in pythonic way
   */
  void stream_tag_decode
    (std::vector<eformat::helper::StreamTag>& v, 
     const eformat::helper::u32list& blob);

  /**
   * Builds eformat::helper::u32lists from actual python lists of integers and
   * longs.
   */
  boost::shared_ptr<eformat::helper::u32list> from_py_list
    (const boost::python::list& l); 

  /**
   * Returns me a slice from this array. Make sure to tie the life times of the
   * return value and the first parameter. 
   */
  eformat::helper::u32slice getslice(const eformat::helper::u32list& l,
      const boost::python::slice& pos);

  /**
   * Gets a copy of a certain slice.
   */
  boost::python::list copy(const eformat::helper::u32list& orig, 
      const boost::python::slice& pos); 

  /**
   * Returns me a slice from this array. Make sure to tie the life time of the
   * return value and the first parameter.
   */
  eformat::helper::u32slice getslice
    (const eformat::helper::u32slice& s, const boost::python::slice& pos); 

  /**
   * Gets a copy of a certain slice.
   */
  boost::python::list copy(const eformat::helper::u32slice& s,
      const boost::python::slice& pos);

   //This one we cannot make work as an injected constructor, since the
   //custodian_and_ward policies seem to give problems
   //boost::shared_ptr<eformat::read::FullEventFragment > 
   //  make_event(const u32list& blob) {
   //  return boost::shared_ptr<eformat::read::FullEventFragment >
   //    (new eformat::read::FullEventFragment(blob.ptr()));
   //}

  eformat::helper::u32slice get_blob(const eformat::Header& f);

  //A set of helper function to retrieve blobs of data inside the fragment
  eformat::helper::u32slice get_status
    (const eformat::Header& f);

  eformat::helper::u32slice get_specific_header
  (const eformat::Header& f);

  eformat::helper::u32slice get_payload
  (const eformat::Header& f); 

  eformat::helper::u32slice get_header
  (const eformat::Header& f);

  eformat::helper::SourceIdentifier get_source_id
  (const eformat::Header& f);

  eformat::helper::Version get_version
  (const eformat::Header& f);

  uint16_t get_minor_version (const eformat::Header& f);

  template <typename T, typename R> 
  void write_copy_header(T& f, const R& other);
  template <typename T>
  void write_copy_header(T& f, const eformat::helper::u32slice& other);
  template <typename T>
  void write_copy_header(T& f, const eformat::helper::u32list& other);
  
  eformat::helper::u32slice get_readable_payload
  (const eformat::read::FullEventFragment& f); 

  eformat::helper::u32slice get_lvl1_trigger_info
  (const eformat::read::FullEventFragment& f); 

  eformat::helper::u32slice get_lvl2_trigger_info
  (const eformat::read::FullEventFragment& f); 

  eformat::helper::u32slice get_event_filter_info
  (const eformat::read::FullEventFragment& f); 

  eformat::helper::u32slice get_raw_stream_tag
  (const eformat::read::FullEventFragment& f); 

  std::vector<eformat::helper::StreamTag> get_stream_tag
  (const eformat::read::FullEventFragment& f); 

  eformat::RunType get_run_type
  (const eformat::read::FullEventFragment& f); 

  eformat::helper::SourceIdentifier get_rod_source_id
  (const eformat::read::ROBFragment& f);

  eformat::helper::Version get_rod_version
  (const eformat::read::ROBFragment& f);

  uint16_t get_rod_minor_version 
    (const eformat::read::ROBFragment& f);
  
  eformat::helper::u32slice get_rod_status
  (const eformat::read::ROBFragment& f); 

  eformat::helper::u32slice get_rod_data
  (const eformat::read::ROBFragment& f); 

  eformat::helper::u32slice get_rod_header
  (const eformat::read::ROBFragment& f); 

  eformat::helper::u32slice get_rod
  (const eformat::read::ROBFragment& f);

  //Converts from old format, using a pythonic-able blob
  eformat::helper::u32list convert_old(const eformat::helper::u32list& old,
        const eformat::CheckSum& event_checksum=eformat::NO_CHECKSUM,
        const eformat::CheckSum& rob_checksum=eformat::NO_CHECKSUM);

  //Returns a specific subfragment from another fragment 
  template <class U, class T> U get_child(const T& f, size_t i);

  template <class T> 
    eformat::helper::u32slice write_get_status (const T& fragment);

  template <class T>
    void write_set_status (T& fragment, eformat::helper::u32slice& s);
  
  template <class T>
    void write_set_status (T& fragment, eformat::helper::u32list& l);

  template <class T>
    void write_set_source (T& fragment, eformat::helper::SourceIdentifier& s);
  
  template <class T>
    eformat::helper::SourceIdentifier write_get_source (const T& fragment);

  eformat::helper::u32slice write_get_lvl1_trigger_info 
    (const eformat::write::FullEventFragment& fragment);

  void write_set_lvl1_trigger_info 
    (eformat::write::FullEventFragment& fragment, eformat::helper::u32slice& s);

  void write_set_lvl1_trigger_info 
    (eformat::write::FullEventFragment& fragment, eformat::helper::u32list& l);

  eformat::helper::u32slice write_get_lvl2_trigger_info 
    (const eformat::write::FullEventFragment& fragment);

  void write_set_lvl2_trigger_info 
    (eformat::write::FullEventFragment& fragment, eformat::helper::u32slice& s);

  void write_set_lvl2_trigger_info 
    (eformat::write::FullEventFragment& fragment, eformat::helper::u32list& l);

  eformat::helper::u32slice write_get_event_filter_info 
    (const eformat::write::FullEventFragment& fragment);

  void write_set_event_filter_info 
    (eformat::write::FullEventFragment& fragment, eformat::helper::u32slice& s);

  void write_set_event_filter_info 
    (eformat::write::FullEventFragment& fragment, eformat::helper::u32list& l);

  eformat::helper::u32slice write_get_raw_stream_tag 
    (const eformat::write::FullEventFragment& fragment);

  std::vector<eformat::helper::StreamTag> 
    write_get_stream_tag (const eformat::write::FullEventFragment& f);

  void write_set_stream_tag (eformat::write::FullEventFragment& fragment, 
      eformat::helper::u32slice& s);

  void write_set_stream_tag 
    (eformat::write::FullEventFragment& fragment, eformat::helper::u32list& l); 

  void write_append_unchecked (eformat::write::FullEventFragment& event, 
      eformat::helper::u32list& s);

  void write_append_unchecked (eformat::write::FullEventFragment& event, 
      eformat::helper::u32slice& s);

  void write_append_unchecked (eformat::write::FullEventFragment& event, 
      eformat::read::ROBFragment& f);

  eformat::read::ROBFragment unchecked_fragment
    (eformat::write::FullEventFragment& event,  uint32_t n);

  // builds the fragment into a contiguous memory object
  template <class T> eformat::helper::u32list build (T& fragment);
  
  eformat::helper::u32slice write_get_rod_status 
    (const eformat::write::ROBFragment& fragment);

  void write_set_rod_status (eformat::write::ROBFragment& fragment,
      eformat::helper::u32slice& s);
  
  void write_set_rod_status (eformat::write::ROBFragment& fragment, 
      eformat::helper::u32list& s);
  
  eformat::helper::u32slice write_get_rod_data 
    (const eformat::write::ROBFragment& fragment); 

  void write_set_rod_data (eformat::write::ROBFragment& fragment,
      eformat::helper::u32slice& s);
  
  void write_set_rod_data (eformat::write::ROBFragment& fragment, 
      eformat::helper::u32list& s);
  
  void write_set_rod_source (eformat::write::ROBFragment& fragment,
    eformat::helper::SourceIdentifier& s);
  
  eformat::helper::SourceIdentifier write_get_rod_source 
    (const eformat::write::ROBFragment& fragment);

  uint32_t checksum(const eformat::CheckSum& type, 
      const eformat::helper::u32list& s);
  
  uint32_t checksum(const eformat::CheckSum& type, 
      const eformat::helper::u32slice& s);

  uint32_t checksum(const eformat::CheckSum& type, 
      const boost::python::list& l);

  std::map<eformat::helper::SourceIdentifier, 
    eformat::read::ROBFragment>*
    build_toc (const eformat::read::FullEventFragment& event);

  std::map<eformat::helper::SourceIdentifier, 
    eformat::read::ROBFragment>*
    build_toc_opt (const eformat::read::FullEventFragment& event,
        bool consider_optional);

  eformat::read::ROBFragment 
    find_rob (const eformat::read::FullEventFragment& event,
     const eformat::helper::SourceIdentifier& source_id);

  eformat::read::ROBFragment 
    find_rob_opt (const eformat::read::FullEventFragment& event,
     const eformat::helper::SourceIdentifier& source_id,
     bool consider_optional);

  boost::shared_ptr<eformat::helper::DetectorMask> detmask_from_list(const boost::python::list& ids);

  void detmask_set_list(eformat::helper::DetectorMask& mask,
      const boost::python::list& ids);

  void detmask_unset_list(eformat::helper::DetectorMask& mask, 
      const boost::python::list& ids);

  boost::python::list detmask_decode(eformat::helper::DetectorMask& mask);
  
  boost::python::list get_fe_problems
    (const eformat::read::FullEventFragment& event);

  boost::python::list get_all_problems (const eformat::read::ROBFragment& rob);
  boost::python::list get_rob_problems (const eformat::read::ROBFragment& rob);
  boost::python::list get_rod_problems (const eformat::read::ROBFragment& rob);


  template <typename ElementType>
    struct set_wrapper
    {
      typedef std::set<ElementType> w_t;
      typedef ElementType e_t;
      
      static void
      insert_element(w_t& self, e_t const& x) { self.insert(x); }
      
      static void
      insert_set(w_t& self, w_t const& other)
      {
	self.insert(other.begin(), other.end());
      }
      
      static bool
      contains(w_t const& self, e_t const& x)
      {
	return self.find(x) != self.end();
      }
      
      static e_t
      getitem(w_t const& self, std::size_t i)
      {
	if (i >= self.size()){
	  PyErr_SetString(PyExc_IndexError, "Index out of range.");
	  boost::python::throw_error_already_set();
	}
	typename w_t::const_iterator p = self.begin();
	while (i > 0) { p++; i--; }
	return *p;
      }
            
      static void
      wrap(std::string const& python_name)
      {
	namespace bp = boost::python;
        boost::python::class_<w_t, std::shared_ptr<w_t> >(python_name.c_str())
	  .def( boost::python::init<w_t const&>())
	  .def("size", &w_t::size)
	  .def("__len__", &w_t::size)
	  .def("insert", insert_element)
	  .def("append", insert_element)
	  .def("insert", insert_set)
	  .def("extend", insert_set)
	  .def("erase", (std::size_t(w_t::*)(e_t const&)) &w_t::erase)
	  .def("clear", &w_t::clear)
	  .def("__contains__", contains)
	  .def("__getitem__", getitem)
	   ;
	
      }
    };
  
}}

template <class U, class T> U eformat::python::get_child(const T& f, size_t i)
{
  const uint32_t* p = 0;
  if (i >= f.nchildren()) throw std::range_error("Index is out of range");
  f.child(p, i);
  return p;
}

template <class T> 
eformat::helper::u32slice eformat::python::write_get_status (const T& fragment) 
{
  return eformat::helper::u32slice(fragment.status(), fragment.nstatus());
}

template <class T>
void eformat::python::write_set_status (T& fragment, eformat::helper::u32slice& s) 
{
    fragment.status(s.length(), s.ptr());
}

template <class T>
void eformat::python::write_set_status (T& fragment, eformat::helper::u32list& l)
{
    fragment.status(l.length(), l.ptr());
}

template <class T>
void eformat::python::write_set_source (T& fragment, eformat::helper::SourceIdentifier& s) 
{
    fragment.source_id(s.code());
}

template <class T>
eformat::helper::SourceIdentifier eformat::python::write_get_source (const T& fragment) 
{
    return fragment.source_id();
}

template <class T> eformat::helper::u32list eformat::python::build (T& fragment)
{
    const eformat::write::node_t* top = fragment.bind();
    uint32_t size = eformat::write::count_words(*top);
    uint32_t* data = new uint32_t[size];
    eformat::write::copy(*top, data, size);
    return eformat::helper::u32list(data, 0, size);
}

template <typename T, typename R> void eformat::python::write_copy_header
(T& f, const R& other) 
{
  const uint32_t* start = 0;
  other.start(start);
  f.copy_header(start);
}

template <typename T> void eformat::python::write_copy_header
(T& f, const eformat::helper::u32slice& other) 
{
  f.copy_header(other.ptr());
}

template <typename T> void eformat::python::write_copy_header
(T& f, const eformat::helper::u32list& other) 
{
  f.copy_header(other.ptr()+other.start());
}
  
#endif /* EFORMAT_PYTHON_UTIL_H */

