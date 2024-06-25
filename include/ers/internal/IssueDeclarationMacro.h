#ifndef ERS_ISSUE_DECLARATION_MACRO_H
#define ERS_ISSUE_DECLARATION_MACRO_H

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/tuple.hpp>
#include <boost/preprocessor/logical.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/comparison.hpp>

#define ERS_EMPTY

#define ERS_IS_EMPTY(x) 				ERS_IS_EMPTY_I(ERS_IS_EMPTY_HELPER x)
#define ERS_IS_EMPTY_I(contents) 			ERS_IS_EMPTY_II( contents() )
#define ERS_IS_EMPTY_II(contents) 			ERS_IS_EMPTY_III( contents )
#define ERS_IS_EMPTY_III(contents) 			BOOST_PP_TUPLE_ELEM( 2, 0, ( ERS_IS_EMPTY_DEF_ ## contents ) )
#define ERS_IS_EMPTY_HELPER() 				ERS_IS_EMPTY_TRUE
#define ERS_IS_EMPTY_DEF_ERS_IS_EMPTY_TRUE		1 ,
#define ERS_IS_EMPTY_DEF_ERS_IS_EMPTY_HELPER		0 ,

#define ERS_TYPE( tuple )				BOOST_PP_SEQ_HEAD(tuple)
#define ERS_NAME( tuple )				BOOST_PP_SEQ_TAIL(tuple)

#define ERS_ATTRIBUTE_NAME( _, __, tuple ) \
	, ERS_NAME(tuple)

#define ERS_ATTRIBUTE_NAME_TYPE( _, __, tuple ) \
	, ERS_TYPE(tuple) \
	ERS_NAME(tuple)

#define ERS_ATTRIBUTE_SERIALIZATION( _, __, tuple ) \
	set_value( BOOST_PP_STRINGIZE(ERS_NAME(tuple)), \
	ERS_NAME(tuple) );

#define ERS_ATTRIBUTE_ACCESSORS( _, __, tuple ) \
	ERS_TYPE(tuple) \
	BOOST_PP_CAT( get_, ERS_NAME(tuple) ) () { \
		ERS_TYPE(tuple) val; \
		ers::Issue::get_value( BOOST_PP_STRINGIZE(ERS_NAME(tuple)), val ); \
		return val; \
	}
                                                                
#define ERS_SET_MESSAGE( message ) \
	std::ostringstream out;\
	out << message;\
	prepend_message( out.str() );

#define	ERS_PRINT_LIST( decl, attributes ) \
	BOOST_PP_SEQ_FOR_EACH( decl, _, attributes )

#define __ERS_DECLARE_ISSUE_BASE__( namespace_name, class_name, base_class_name, message, base_attributes, attributes ) \
namespace namespace_name { \
    class class_name : public base_class_name { \
      template <class> friend class ers::IssueRegistrator;\
      protected: \
	BOOST_PP_EXPR_IF( BOOST_PP_NOT_EQUAL( BOOST_PP_SEQ_SIZE( base_attributes attributes ), 0 ), \
        	class_name( const ers::Context & context ) : base_class_name( context ) { ; } )\
      public: \
	static const char * get_uid() { return BOOST_PP_STRINGIZE( namespace_name::class_name ); } \
	class_name( const ers::Context & context \
        	    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
                    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ) ); \
	class_name( const ers::Context & context, \
        	    const std::string & msg \
        	    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
                    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ) ); \
	class_name( const ers::Context & context, \
        	    const std::string & msg \
        	    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
                    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ), \
                    const std::exception & cause ); \
	class_name( const ers::Context & context \
        	    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
                    ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ), \
                    const std::exception & cause ); \
	void raise() const { throw class_name(*this); } \
	const char * get_class_name() const { return get_uid(); } \
	base_class_name * clone() const { return new namespace_name::class_name( *this ); } \
	ERS_PRINT_LIST( ERS_ATTRIBUTE_ACCESSORS, ERS_EMPTY attributes ) \
    }; \
}

#define __ERS_DEFINE_ISSUE_BASE__( INLINE, namespace_name, class_name, base_class_name, message, base_attributes, attributes ) \
namespace namespace_name { \
    INLINE class_name::class_name( const ers::Context & context \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ) ) \
      : base_class_name( context ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME, ERS_EMPTY base_attributes ) ) \
    { \
      ERS_PRINT_LIST( ERS_ATTRIBUTE_SERIALIZATION, ERS_EMPTY attributes ) \
      BOOST_PP_EXPR_IF( BOOST_PP_NOT( ERS_IS_EMPTY( ERS_EMPTY message ) ), ERS_SET_MESSAGE( ERS_EMPTY message ) )\
    } \
    \
    INLINE class_name::class_name( const ers::Context & context, \
		const std::string & msg \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ) ) \
      : base_class_name( context, msg ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME, ERS_EMPTY base_attributes ) ) \
    { \
      ERS_PRINT_LIST( ERS_ATTRIBUTE_SERIALIZATION, ERS_EMPTY attributes ) \
    } \
    \
    INLINE class_name::class_name( const ers::Context & context, \
		const std::string & msg \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ), \
		const std::exception & cause ) \
      : base_class_name( context, msg ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME, ERS_EMPTY base_attributes ), cause ) \
    { \
      ERS_PRINT_LIST( ERS_ATTRIBUTE_SERIALIZATION, ERS_EMPTY attributes ) \
    } \
    INLINE class_name::class_name( const ers::Context & context \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY base_attributes ) \
		ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME_TYPE, ERS_EMPTY attributes ), \
		const std::exception & cause ) \
      : base_class_name( context ERS_PRINT_LIST( ERS_ATTRIBUTE_NAME, ERS_EMPTY base_attributes ), cause ) \
    { \
      ERS_PRINT_LIST( ERS_ATTRIBUTE_SERIALIZATION, ERS_EMPTY attributes ) \
      BOOST_PP_EXPR_IF( BOOST_PP_NOT( ERS_IS_EMPTY( ERS_EMPTY message ) ), ERS_SET_MESSAGE( ERS_EMPTY message ) )\
    } \
} \
namespace { \
    ers::IssueRegistrator<namespace_name::class_name> namespace_name##_##class_name##_instance; \
}

#define ERS_DECLARE_ISSUE_BASE_HPP( namespace_name, class_name, base_class_name, message, base_attributes, attributes ) \
	__ERS_DECLARE_ISSUE_BASE__( namespace_name, class_name, base_class_name, ERS_EMPTY message, ERS_EMPTY base_attributes, ERS_EMPTY attributes )

#define ERS_DEFINE_ISSUE_BASE_CXX( namespace_name, class_name, base_class_name, message, base_attributes, attributes ) \
	__ERS_DEFINE_ISSUE_BASE__( ERS_EMPTY, namespace_name, class_name, base_class_name, ERS_EMPTY message, ERS_EMPTY base_attributes, ERS_EMPTY attributes )

#define ERS_DECLARE_ISSUE_HPP( namespace_name, class_name, message, attributes ) \
	ERS_DECLARE_ISSUE_BASE_HPP( namespace_name, class_name, ers::Issue, ERS_EMPTY message, ERS_EMPTY, ERS_EMPTY attributes )

#define ERS_DEFINE_ISSUE_CXX( namespace_name, class_name, message, attributes ) \
	ERS_DEFINE_ISSUE_BASE_CXX( namespace_name, class_name, ers::Issue, ERS_EMPTY message, ERS_EMPTY, ERS_EMPTY attributes )

#define ERS_DECLARE_ISSUE_BASE( namespace_name, class_name, base_class_name, message, base_attributes, attributes ) \
	__ERS_DECLARE_ISSUE_BASE__( namespace_name, class_name, base_class_name, message, base_attributes, attributes ) \
        __ERS_DEFINE_ISSUE_BASE__( inline, namespace_name, class_name, base_class_name, message, base_attributes, attributes )

#define ERS_DECLARE_ISSUE( namespace_name, class_name, message, attributes ) \
	__ERS_DECLARE_ISSUE_BASE__( namespace_name, class_name, ers::Issue, ERS_EMPTY message, ERS_EMPTY, attributes ) \
        __ERS_DEFINE_ISSUE_BASE__( inline, namespace_name, class_name, ers::Issue, ERS_EMPTY message, ERS_EMPTY, attributes )

#endif
