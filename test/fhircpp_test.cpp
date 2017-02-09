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

    fhir::boolean b5("false");
    EXPECT_FALSE(b5.value());
    EXPECT_TRUE(b5.valid());

    fhir::boolean b6("true");
    EXPECT_TRUE(b6.value());
    EXPECT_TRUE(b6.valid());

    fhir::boolean b7 = "true";
    EXPECT_TRUE(b7.value());
    EXPECT_TRUE(b7.valid());

    fhir::boolean b7a = "false";
    EXPECT_FALSE(b7a.value());
    EXPECT_TRUE(b7a.valid());

    fhir::boolean b8;
    b8 = true;
    EXPECT_TRUE(b8.value());
    EXPECT_TRUE(b8.valid());

    fhir::boolean b9;
    b9 = "true";
    EXPECT_TRUE(b9.value());
    EXPECT_TRUE(b9.valid());

    b9 = "false";
    EXPECT_FALSE(b9.value());
    EXPECT_TRUE(b9.valid());
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

    fhir::integer i5("42");
    EXPECT_EQ(i5.value(), 42);
    EXPECT_TRUE(i5.valid());

    fhir::integer i6 = 42;
    EXPECT_EQ(i6.value(), 42);
    EXPECT_TRUE(i6.valid());

    fhir::integer i7("42");
    EXPECT_EQ(i7.value(), 42);
    EXPECT_TRUE(i7.valid());

    fhir::integer i8 = "42";
    EXPECT_EQ(i8.value(), 42);
    EXPECT_TRUE(i8.valid());

    fhir::integer i9;
    i9 = "42";
    EXPECT_EQ(i9.value(), 42);
    EXPECT_TRUE(i9.valid());
}

TEST(fhircpp_test, primitive_string)
{
    fhir::string s;
    EXPECT_EQ(s.value(), "");
    EXPECT_TRUE(s.valid());

    fhir::string s1("foo");
    EXPECT_EQ(s1.value(), "foo");
    EXPECT_TRUE(s1.valid());

    fhir::string s2 = s1;
    EXPECT_EQ(s2.value(), "foo");
    EXPECT_TRUE(s2.valid());

    fhir::string s3 = std::string("bar");
    EXPECT_EQ(s3.value(), "bar");
    EXPECT_TRUE(s3.valid());

    fhir::string s4 = "baz";
    EXPECT_EQ(s4.value(), "baz");
    EXPECT_TRUE(s4.valid());

    fhir::string s5;
    s5 = "qux";
    EXPECT_EQ(s5.value(), "qux");
    EXPECT_TRUE(s5.valid());
}