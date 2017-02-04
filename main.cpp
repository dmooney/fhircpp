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

#include <iostream>
#include "primitive.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    fhir::boolean b;
    fhir::integer n;
    fhir::string s;
    fhir::decimal d;
    fhir::instant i;
    fhir::date dt;
    fhir::date_time dtm;
    fhir::base64_binary bin;
    fhir::time t;
    fhir::unsigned_int ui;
    fhir::positive_int pi(0);
    fhir::positive_int pi2(1);

    std::cout << std::boolalpha << "pi valid: " << pi.valid() << std::endl;
    std::cout << std::boolalpha << "pi2 valid: " << pi2.valid() << std::endl;

    fhir::code c;
//    fhir::code c2(L"12 3/45");
//    fhir::code c3(L"   12 3 45   ");
    auto v = c.valid();
    std::cout << std::boolalpha << "c valid: " << c.valid() << std::endl;
//    std::cout << std::boolalpha << "c2 valid: " << c2.valid() << std::endl;
//    std::cout << std::boolalpha << "c3 valid: " << c3.valid() << std::endl;
    fhir::oid o;
    fhir::id id;

    return 0;
}