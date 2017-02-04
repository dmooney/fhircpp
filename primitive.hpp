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

    template<typename Traits>
    class primitive : public element
    {
    public:
        primitive()
            : value_(typename Traits::value_type())
            , is_valid_(Traits::validate(value_))
        {
        }

        primitive(const typename Traits::value_type& value)
            : value_(value)
            , is_valid_(Traits::validate(value_))
        {
        }

        primitive(const primitive& other)
            : value_(other.value_)
            , is_valid_(other.is_valid_)
        {

        }

        primitive& operator=(const primitive& other)
        {
            if (this != &other) {
                value_ = other.value_;
                is_valid_ = other.is_valid_;
            }
            return *this;
        }

        virtual ~primitive()
        {
        }

        const typename Traits::value_type& value() const
        {
            return value_;
        }

        bool valid() const
        {
            return is_valid_;
        }

    private:
        typename Traits::value_type value_;
        bool is_valid_;
    };

    typedef primitive<default_primitive_traits<bool>> boolean;
    typedef primitive<default_primitive_traits<std::int32_t>> integer;
    typedef primitive<default_primitive_traits<std::wstring>> string;
    typedef primitive<default_primitive_traits<boost::multiprecision::cpp_dec_float_50>> decimal;
    typedef primitive<default_primitive_traits<std::wstring>> uri;
    typedef primitive<default_primitive_traits<std::string>> base64_binary;
    typedef primitive<default_primitive_traits<boost::locale::date_time>> instant;
    typedef primitive<date_traits> date;
    typedef primitive<default_primitive_traits<boost::locale::date_time>> date_time;
    typedef primitive<default_primitive_traits<std::chrono::seconds>> time;

    // Primitive types with simple restrictions
    typedef primitive<regex_primitive_traits<code_regex_traits>> code;
    typedef primitive<regex_primitive_traits<oid_regex_traits>> oid;
    typedef primitive<regex_primitive_traits<id_regex_traits>> id;
    typedef primitive<default_primitive_traits<std::uint32_t>> unsigned_int;
    typedef primitive<positive_int_traits> positive_int;
}
#endif //FHIRCPP_PRIMATIVE_HPP
