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
#include "gtest/gtest.h"

TEST(fhircpp_test, primitive_boolean) {
    fhir::boolean b;
    ASSERT_FALSE(b.value());
    ASSERT_TRUE(b.valid());

    fhir::boolean b2(true);
    ASSERT_TRUE(b2.value());
    ASSERT_TRUE(b2.valid());

    fhir::boolean b3(b2);
    ASSERT_TRUE(b3.value());
    ASSERT_TRUE(b3.valid());
}
