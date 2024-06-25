/*
 *  Issue.h
 *  ers
 *
 *  Created by Matthias Wiesmann on 08.12.04.
 *  Modified by Serguei Kolos on 02.08.05.
 *  Copyright 2005 CERN. All rights reserved.
 *
 */

#ifndef ERS_ISSUE_H
#define ERS_ISSUE_H

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <chrono>

#include <ers/IssueFactory.h>
#include <ers/LocalContext.h>
#include <ers/Severity.h>

/** \file Issue.h This file defines the ers::Issue class, 
  * which is the base class for any user defined issue.
  * \author Serguei Kolos
  * \brief ers header and documentation file 
  */

using std::chrono::system_clock;

namespace ers
{
    class OutputStream;
        
    typedef std::map<std::string, std::string>	string_map;
    
    template<class T>
    class IssueRegistrator {
    public:
        IssueRegistrator() {
            ers::IssueFactory::instance().register_issue(T::get_uid(), create);
        }

    private:
        static ers::Issue* create(const Context &context) {
            return new T(context);
        }
    };
    
    /** This is a base class for any user define issue.
      *  The class stores all attributes declared in a user define descendant class in a hashmap
      *  as sting key/value pairs. The object defines a number of methods for providing access to this map.
      *  For an example of how to define a custom subclass of the Issue have a look at the SampleIssues.h file.
      *
      *  \see ers::IssueFactory
      *  \see SampleIssues.h
      *  \brief Base class for any user define issue.
      */
    class Issue : public std::exception
    {
	friend class IssueFactory;

      public:        
	Issue(	const Context & context,
		const std::string & message = std::string() ); 
	
	Issue(	const Context & context,
		const std::exception & cause );

	Issue(	const Context & context,
		const std::string & message,
                const std::exception & cause ); 	
	
	Issue( const Issue & other );
	      
	virtual ~Issue() noexcept;
	
	virtual Issue * clone() const = 0;
	
        virtual const char * get_class_name() const = 0;	/**< \brief Get key for class (used for serialisation)*/
       	
        virtual void raise() const = 0;                         /**< \brief throws a copy of this issue preserving the real issue type*/
	
	void add_qualifier( const std::string & qualif );	/**< \brief adds a qualifier to the issue */
	
	const Issue * cause() const				/**< \brief return the cause Issue of this Issue */
	{ return m_cause.get(); }
        
	const Context & context() const				/**< \brief Context of the issue. */
        { return *(m_context.get()); }
        
        const std::string & message() const			/**< \brief General cause of the issue. */
	{ return m_message; }
        
	const std::vector<std::string> & qualifiers() const	/**< \brief return array of qualifiers */
        { return m_qualifiers; }
        
	const string_map & parameters() const                   /**< \brief return array of parameters */
        { return m_values; }
        
        ers::Severity severity() const				/**< \brief severity of the issue */
	{ return m_severity; }
        
	template <class Precision=std::chrono::seconds>
        std::string time(const std::string & format = "%Y-%b-%d %H:%M:%S", bool isUTC = false) const;

	/**< \brief string representation of local time of the issue */
        template <class Precision>
        std::string localtime(const std::string & format = "%Y-%b-%d %H:%M:%S") const
        { return time<Precision>(format, false); }
        
	/**< \brief string representation of UTC time of the issue */
	template <class Precision>
        std::string gmtime(const std::string & format = "%Y-%b-%d %H:%M:%S") const
        { return time<Precision>(format, true); }
        
	std::time_t time_t() const;				/**< \brief seconds since 1 Jan 1970 */
        
	const system_clock::time_point & ptime() const		/**< \brief original time point of the issue */
	{ return m_time; }
        
        const char * what() const noexcept			/**< \brief General cause of the issue. */
	{ return m_message.c_str(); }
        
	ers::Severity set_severity( ers::Severity severity ) const;

	void wrap_message( const std::string & begin, const std::string & end );
        
      protected:
        Issue(	Severity severity,
		const system_clock::time_point & time,
		const ers::Context & context,
		const std::string & message,
		const std::vector<std::string> & qualifiers,
		const std::map<std::string, std::string> & parameters,
		const ers::Issue * cause = 0 );
        
        /**< \brief Gets a value of any type that has an input operator for the standard stream defined */
	template <typename T>
	void get_value( const std::string & key, T & value ) const;
	void get_value( const std::string & key, const char * & value ) const;
	void get_value( const std::string & key, std::string & value ) const;
	
	/**< \brief Sets a value of any type that has an output operator for the standard stream defined */
	template <typename T>
	void set_value( const std::string & key, T value );

	void set_message( const std::string & message )
	{ m_message = message; }
        
	void prepend_message( const std::string & message );
        
      private:        
        Issue & operator=( const Issue & other ) = delete;
					  
	std::unique_ptr<const Issue>	m_cause;		/**< \brief Issue that caused the current issue */
	std::unique_ptr<Context>	m_context;		/**< \brief Context of the current issue */
	std::string			m_message;		/**< \brief Issue's explanation text */
	std::vector<std::string>	m_qualifiers;		/**< \brief List of associated qualifiers */
	mutable Severity		m_severity;		/**< \brief Issue's severity */
	system_clock::time_point	m_time;			/**< \brief Time when issue was thrown */
	string_map			m_values;		/**< \brief List of user defined attributes. */	
    };

    std::ostream & operator<<( std::ostream &, const ers::Issue & );    
} // ers
        
#include <ers/internal/IssueDeclarationMacro.h>

ERS_DECLARE_ISSUE(  ers,
		    NoValue,
		    "value for the \"" << key << "\" key is not set ",
		    ((std::string)key ) )

template <typename T>
void 
ers::Issue::get_value( const std::string & key, T & value ) const
{
    string_map::const_iterator it = m_values.find(key);
    if ( it == m_values.end() )
    {
	throw ers::NoValue( ERS_HERE, key );
    }
    std::istringstream in( it->second );
    in >> value;
}

template <typename T>
void 
ers::Issue::set_value( const std::string & key, T value )
{
    std::ostringstream out;
    out << value;
    m_values[key] = out.str();
}

template <class Precision>
std::string 
ers::Issue::time(const std::string & format, bool isUTC) const
{
    static const int width(::log10(Precision::period::den));
    
    std::time_t t = time_t();
    std::tm tm = isUTC ? *gmtime_r(&t, &tm) : *localtime_r(&t, &tm);

    char buff[128];
    std::strftime(buff, 128 - 16, format.c_str(), &tm);

    auto c = std::chrono::duration_cast<Precision>(
			m_time.time_since_epoch()).count();
    double frac = c - (double)t*Precision::period::den;
    sprintf(buff + strlen(buff), ",%0*.0f", width, frac);

    return buff;
}

#endif

