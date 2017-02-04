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
#include <boost/locale/date_time.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "element.hpp"

/// Namespace for all fhircpp library code
namespace fhir
{
    template<typename T>
    struct default_primitive_traits {
        typedef T value_type;
        static bool validate(const value_type&)
        {
            return true;
        }
    };

    template<typename T>
    struct regex_primitive_traits : private T {
        typedef typename T::value_type value_type;
        static bool validate(const value_type& value)
        {
            return std::regex_match(value, std::basic_regex<typename value_type::value_type>(T::validation_regex));
        }
    };

    struct code_regex_traits {
        typedef std::wstring value_type;
    protected:
        static const wchar_t * validation_regex;
    };
    const wchar_t * code_regex_traits::validation_regex = L"[^\\s]+([\\s]+[^\\s]+)*";

    struct oid_regex_traits {
        typedef std::wstring value_type;
    protected:
        static const wchar_t * validation_regex;
    };
    const wchar_t * oid_regex_traits::validation_regex = L"urn:oid:[0-2](\\.[1-9]\\d*)+";

    struct id_regex_traits {
        typedef std::string value_type;
    protected:
        static const char * validation_regex;
    };
    const char * id_regex_traits::validation_regex = "[A-Za-z0-9\\-\\.]{1,64}";

    struct positive_int_traits {
        typedef std::uint32_t value_type;
        static bool validate(value_type value)
        {
            return value > 0;
        }
    };

    /// Precision enumerator for partial dates (e.g. just year or year + month)
    enum date_precision {
        year = 0,
        month = 1,
        day = 2
    };

    struct date_traits {
        typedef std::pair<date_precision, boost::locale::date_time> value_type;
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
        /// constuctor
        primitive()
            : value_(typename Traits::value_type())
            , is_valid_(Traits::validate(value_))
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
    typedef primitive<default_primitive_traits<bool>> boolean;

    /// Primitive signed 32-bit integer type (for larger values, use decimal)
    typedef primitive<default_primitive_traits<std::int32_t>> integer;

    /// Primitive sequence of Unicode characters, not to exceed 1MB in size
    typedef primitive<default_primitive_traits<std::wstring>> string;

    /// Primitive type for rational numbers that have a decimal representation
    typedef primitive<default_primitive_traits<boost::multiprecision::cpp_dec_float_50>> decimal;

    /// Priitive type for a Uniform Resource Identifier (RFC 3986)
    typedef primitive<default_primitive_traits<std::wstring>> uri;

    /// Primitive type for a stream of bytes, base64 encoded (RFC 4648)
    typedef primitive<default_primitive_traits<std::string>> base64_binary;

    /// Primitive type for an instant in time known at least to the second and always including a time zone.
    typedef primitive<default_primitive_traits<boost::locale::date_time>> instant;

    /// Primitive type for a date or partial date (e.g. just year or year + month) as used in human communication.
    /// There is no time zone. Dates SHALL be valid dates
    typedef primitive<date_traits> date;

    /// A date, date-time or partial date (e.g. just year or year + month) as used in human communication. If hours and
    /// minutes are specified, a time zone SHALL be populated. Seconds must be provided due to schema type constraints
    /// but may be zero-filled and may be ignored. Dates SHALL be valid dates. The time "24:00" is not allowed
    typedef primitive<default_primitive_traits<boost::locale::date_time>> date_time;

    /// A time during the day, with no date specified (can be converted to a Duration since midnight). Seconds must be
    /// provided due to schema type constraints but may be zero-filled and may be ignored. The time "24:00" is not
    /// allowed, and neither is a time zone
    typedef primitive<default_primitive_traits<std::chrono::seconds>> time;

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
    typedef primitive<default_primitive_traits<std::wstring>> markdown;

    /// Any non-negative integer (e.g. >= 0)
    typedef primitive<default_primitive_traits<std::uint32_t>> unsigned_int;

    /// Any positive integer (e.g. > 0)
    typedef primitive<positive_int_traits> positive_int;
}
#endif //FHIRCPP_PRIMATIVE_HPP
