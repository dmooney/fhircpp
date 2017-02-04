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

class fhircpp_test : public ::testing::Test {};

TEST(fhircpp_test, primitive_boolean)
{
    fhir::boolean b;
    EXPECT_FALSE(b.value());
    EXPECT_TRUE(b.valid());

    fhir::boolean b2(true);
    ASSERT_TRUE(b2.value());
    EXPECT_TRUE(b2.valid());

    fhir::boolean b3(b2);
    EXPECT_TRUE(b3.value());
    EXPECT_TRUE(b3.valid());

    fhir::boolean b4 = b3;
    EXPECT_TRUE(b4.value());
    EXPECT_TRUE(b4.valid());
}

TEST(fhircpp_test, primitive_integer)
{
    fhir::integer i;
    EXPECT_EQ(i.value(), 0);
    EXPECT_TRUE(i.valid());

    fhir::integer i2(1);
    ASSERT_EQ(i2.value(), 1);
    EXPECT_TRUE(i2.valid());

    fhir::integer i3(i2);
    EXPECT_EQ(i3.value(), 1);
    EXPECT_TRUE(i3.valid());

    fhir::integer i4(i3);
    EXPECT_EQ(i4.value(), 1);
    EXPECT_TRUE(i4.valid());
}