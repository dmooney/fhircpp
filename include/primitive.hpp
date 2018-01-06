//    fhircpp - C++ Library for FHIR
//
//    Copyright (C) 2017 David Mooney
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#ifndef FHIRCPP_PRIMITIVE_HPP
#define FHIRCPP_PRIMITIVE_HPP

#include <chrono>
#include <cstdint>
#include <regex>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/locale/date_time.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "element.hpp"

/// Namespace for all fhircpp library code
namespace fhir
{
    namespace internal {
        typedef bool boolean_type;
        typedef std::int32_t integer_type;
        typedef std::string string_type;
        typedef boost::multiprecision::cpp_dec_float_50 decimal_type;
        typedef boost::locale::date_time date_time_type;
        typedef std::chrono::seconds time_type;
        typedef std::uint32_t unsigned_int_type;
    }

    template<typename T>
    struct default_primitive_traits {
        typedef T value_type;

        static bool validate(const value_type&)
        {
            return true;
        }

        static T parse(const std::string& str)
        {
            if (std::is_same<T, std::string>::value) {
                return str;
            }
            else {
                return T(str);
            }
        }
    };

    template<>
    internal::boolean_type default_primitive_traits<internal::boolean_type>::parse(const std::string& str)
    {
        return boost::iequals(str, "true");
    }

    template<>
    internal::integer_type default_primitive_traits<internal::integer_type >::parse(const std::string& str)
    {
        return std::stol(str);
    }

    template<>
    internal::decimal_type default_primitive_traits<internal::decimal_type>::parse(const std::string& str)
    {
        return internal::decimal_type(str.c_str());
    }

    template<typename T>
    struct regex_primitive_traits : private T {
        typedef typename T::value_type value_type;
        static bool validate(const value_type& value)
        {
            return std::regex_match(value, std::basic_regex<typename value_type::value_type>(T::validation_regex));
        }
    };

    struct code_regex_traits {
        typedef internal::string_type value_type;
    protected:
        static const std::string validation_regex;
    };

    struct oid_regex_traits {
        typedef internal::string_type value_type;
    protected:
        static const std::string validation_regex;
    };

    struct id_regex_traits {
        typedef internal::string_type value_type;
    protected:
        static const std::string validation_regex;
    };

    struct positive_int_traits {
        typedef internal::integer_type value_type;
        static bool validate(value_type value)
        {
            return value > 0;
        }
    };

    /// Precision enumeration for partial dates (e.g. just year or year + month)
    enum date_precision {
        year = 0,
        month = 1,
        day = 2
    };

    struct date_traits {
        typedef std::pair<date_precision, internal::date_time_type> value_type;
        static bool validate(const value_type& value)
        {
            return true;
        }
    };

    /// Base template for primitive elements. End user should use provided typedefs.
    /// \tparam Traits provides the value_type and validator method
    template<typename Traits>
    class primitive : public element
    {
    public:
        /// Default constructor for the primitive element, initializes the value using the value_type's default
        /// constructor
        primitive()
            : primitive{typename Traits::value_type()}
        {
        }

        /// Value constructor for the primitive element
        /// \param value Initial value for the primitive element
        primitive(const typename Traits::value_type& value)
            : value_(value)
            , is_valid_(Traits::validate(value_))
        {
        }

        /// Copy constructor for the primitive element
        /// \param other Object to be copied from
        primitive(const primitive& other)
            : value_(other.value_)
            , is_valid_(other.is_valid_)
        {
        }

        /// String constructor which will parse the string value if necessary
        /// \param str String representation of the value
        primitive(const char * str)
                : primitive{Traits::parse(str)}
        {
        }

        /// Assignment operator for the primitive element
        /// \param other Object to be copied from
        /// \return *this
        primitive& operator=(const primitive& other)
        {
            if (this != &other) {
                value_ = other.value_;
                is_valid_ = other.is_valid_;
            }
            return *this;
        }

        /// Assignment operator using value type
        /// \param value Value to be assigned
        /// \return *this
        primitive& operator=(const typename Traits::value_type& value)
        {
            value_ = value;
            is_valid_ = Traits::validate(value_);
            return *this;
        }

        /// Assignment operator using string value
        /// \param value Value to be parsed and assigned
        /// \return *this
        primitive& operator=(const char * value)
        {
            value_ = Traits::parse(value);
            is_valid_ = Traits::validate(value_);
            return *this;
        }

        /// Destructor for the primitive element
        virtual ~primitive()
        {
        }

        /// Retrieve the value of the primitive element
        /// \return the value of the primitive element
        const typename Traits::value_type& value() const
        {
            return value_;
        }

        /// Check whether the primitive element's value complies with the standard
        /// \return whether the primitive element's value complies with the standard
        bool valid() const
        {
            return is_valid_;
        }

    private:
        typename Traits::value_type value_;
        bool is_valid_;
    };

    /// Primitive Boolean type may be true or false
    typedef primitive<default_primitive_traits<internal::boolean_type>> boolean;

    /// Primitive signed 32-bit integer type (for larger values, use decimal)
    typedef primitive<default_primitive_traits<internal::integer_type>> integer;

    /// Primitive sequence of Unicode characters, not to exceed 1MB in size
    typedef primitive<default_primitive_traits<internal::string_type>> string;

    /// Primitive type for rational numbers that have a decimal representation
    typedef primitive<default_primitive_traits<internal::decimal_type>> decimal;

    /// Primitive type for a Uniform Resource Identifier (RFC 3986)
    typedef primitive<default_primitive_traits<internal::string_type>> uri;

    /// Primitive type for a stream of bytes, base64 encoded (RFC 4648)
    typedef primitive<default_primitive_traits<internal::string_type>> base64_binary;

    /// Primitive type for an instant in time known at least to the second and always including a time zone.
    typedef primitive<default_primitive_traits<internal::date_time_type>> instant;

    /// Primitive type for a date or partial date (e.g. just year or year + month) as used in human communication.
    /// There is no time zone. Dates SHALL be valid dates
    typedef primitive<date_traits> date;

    /// A date, date-time or partial date (e.g. just year or year + month) as used in human communication. If hours and
    /// minutes are specified, a time zone SHALL be populated. Seconds must be provided due to schema type constraints
    /// but may be zero-filled and may be ignored. Dates SHALL be valid dates. The time "24:00" is not allowed
    typedef primitive<default_primitive_traits<internal::date_time_type>> date_time;

    /// A time during the day, with no date specified (can be converted to a Duration since midnight). Seconds must be
    /// provided due to schema type constraints but may be zero-filled and may be ignored. The time "24:00" is not
    /// allowed, and neither is a time zone
    typedef primitive<default_primitive_traits<internal::time_type>> time;

    // Primitive types with simple restrictions

    /// Indicates that the value is taken from a set of controlled strings defined elsewhere (see Using codes for
    /// further discussion). Technically, a code is restricted to a string which has at least one character and no
    /// leading or trailing whitespace, and where there is no whitespace other than single spaces in the contents
    typedef primitive<regex_primitive_traits<code_regex_traits>> code;

    /// An OID represented as a URI (RFC 3001 ); e.g. urn:oid:1.2.3.4.5
    typedef primitive<regex_primitive_traits<oid_regex_traits>> oid;

    /// Any combination of upper or lower case ASCII letters ('A'..'Z', and 'a'..'z', numerals ('0'..'9'), '-' and '.',
    /// with a length limit of 64 characters. (This might be an integer, an un-prefixed OID, UUID or any other
    /// identifier pattern that meets these constraints.)
    typedef primitive<regex_primitive_traits<id_regex_traits>> id;

    /// A string that may contain markdown syntax for optional processing by a markdown presentation engine
    typedef primitive<default_primitive_traits<internal::string_type>> markdown;

    /// Any non-negative integer (e.g. >= 0)
    typedef primitive<default_primitive_traits<internal::unsigned_int_type>> unsigned_int;

    /// Any positive integer (e.g. > 0)
    typedef primitive<positive_int_traits> positive_int;

    template<typename Traits>
    std::ostream& operator<<(std::ostream& out, const primitive<Traits>& pr)
    {
        out << pr.value();
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const boolean& b)
    {
        out << std::boolalpha << b.value();
        return out;
    }
}
#endif //FHIRCPP_PRIMITIVE_HPP
