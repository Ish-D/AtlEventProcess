/**
 * @file eformat/EnumClass.h 
 * @author <a href="mailto:andre.dos.anjos@cern.ch">Andre Anjos</a> 
 *
 * @brief Defines a class that knows about enumerations and can help the user
 * iteratate and find string equivalents for printouts.
 */

#ifndef EFORMAT_ENUMCLASS_H 
#define EFORMAT_ENUMCLASS_H

#include <map>
#include <string>
#include <vector>

namespace eformat { namespace helper {

  //Makes enumerations easier to iterate and string'ify
  template <typename T> class EnumClass {

  public:

    //Simplify type definition throughout this class
    typedef typename std::map<T, std::string> dict_type;
    typedef typename dict_type::const_iterator iterator_type;

    //Allows const iteration over enumerations
    class const_iterator {

      public:

        const_iterator(const const_iterator& other) 
          : m_current(other.m_current) { }

        const_iterator(const iterator_type& c)
          : m_current(c) {}

        const_iterator& operator= (const const_iterator& other) {
          m_current = other.m_current;
          return *this;
        }

        const_iterator() {}

        virtual ~const_iterator() {}

        //prefix
        const_iterator& operator++() {
          ++m_current;
          return *this;
        }

        const_iterator& operator--() {
          --m_current;
          return *this;
        }

        //postfix
        const_iterator operator++(int) {
          const_iterator retval(m_current);
          ++m_current;
          return retval;
        }

        const_iterator operator--(int) {
          const_iterator retval(m_current);
          --m_current;
          return retval;
        }

        //dereference
        const std::pair<const T, std::string>& operator*() const 
        { return *m_current; }
        const std::pair<const T, std::string>* operator->() const 
        { return &(*m_current); }

        T enumeration() const { return m_current->first; }
        const std::string& string() const { return m_current->second; }

        //comparison
        bool operator== (const const_iterator& other) const {
          return this->m_current == other.m_current;
        }

        bool operator!= (const const_iterator& other) const {
          return this->m_current != other.m_current;
        }

      private:
        iterator_type m_current; //@

    };

  public:

    /**
     * Constructor, always empty.
     */
    EnumClass(int free, const std::string& unknown)
      : m_free(free), m_unknown(unknown) {}

    /**
     * Virtual destructor
     */
    virtual ~EnumClass() {}

    /**
     * Add an entry to this class
     */
    void add(T key, const std::string& value) {
      m_entry[key] = value;
    }

    /**
     * Provides an iterator to the values
     */
    const_iterator begin() const {
      return m_entry.begin();
    }

    const_iterator end() const {
      return m_entry.end();
    }

    /**
     * Returns a human-readable form of this value
     */
    const std::string& string(T value) const {
      iterator_type t = m_entry.find(value);
      if (t == m_entry.end()) return m_unknown; 
      return t->second;
    }
    const std::string& operator[](T value) const {
      return string(value);
    }

    /**
     * Returns the machine code for this string 
     */
    T enumeration(const std::string& str) const {
      for (iterator_type t=m_entry.begin(); t!= m_entry.end(); ++t) {
        if (t->second == str) return t->first;
      }
      return (T)m_free;
    }
    T enumeration(const char* str) const {
      return enumeration(std::string(str));
    }
    T operator[](const std::string& str) const {
      return enumeration(str);
    }
    T operator[](const char* str) const {
      return enumeration(str);
    }

    /**
     * Entries, as a set
     */
    size_t size() const {
      return m_entry.size();
    }

    void enumerations(std::vector<T>& v) const {
      for (const_iterator it=begin(); it!=end(); ++it) 
        v.push_back(it.enumeration());
    }

    void strings(std::vector<std::string>& v) const {
      for (const_iterator it=begin(); it!=end(); ++it) v.push_back(it.string());
    }

    T unknown() const { return (T)m_free; }
    const::std::string& unknown_string() const { return m_unknown; }

  private:
    int m_free; //an unocuppied number in the enumeration to serve as unknown
    std::string m_unknown; //the "unknown" string
    dict_type m_entry; //all my entries

  };

}}

#endif /* EFORMAT_ENUMCLASS_H */
