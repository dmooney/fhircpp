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

#ifndef FHIRCPP_ELEMENT_HPP
#define FHIRCPP_ELEMENT_HPP

/// Namespace for all fhircpp library code
namespace fhir
{
    /// The base definition for all elements contained inside a resource.
    class element
    {
    public:
        /// Default constructor for element
        element();

        /// Copy constructor for element
        /// \param other Object to be copied from
        element(const element& other);

        /// Assignment operator for element
        /// \param other Object to be copied from
        /// \return *this
        element& operator=(const element& other);

        /// Destructor for element
        virtual ~element();
    };
}
#endif //FHIRCPP_ELEMENT_HPP
