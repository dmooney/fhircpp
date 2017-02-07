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

#include "primitive.hpp"

namespace fhir {
    const std::wstring code_regex_traits::validation_regex = L"[^\\s]+([\\s]+[^\\s]+)*";
    const std::wstring oid_regex_traits::validation_regex = L"urn:oid:[0-2](\\.[1-9]\\d*)+";
    const std::string id_regex_traits::validation_regex = "[A-Za-z0-9\\-\\.]{1,64}";
}