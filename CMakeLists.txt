#    fhircpp - C++ Library for FHIR
#
#    Copyright (C) 2017 David Mooney
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#         http:#www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

cmake_minimum_required(VERSION 3.6)
project(fhircpp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp element.hpp element.cpp primitive.hpp)
add_executable(fhircpp ${SOURCE_FILES})
target_link_libraries(fhircpp boost_locale)