# fhircpp
fhircpp - C++ API for HL7 FHIR

# Status
Currently working on primitive FHIR data types. Just getting started really.

Primitive Type | C++ Representation | typedef | unit test
---------|----------|---------|----------
boolean | bool | done | done
integer | std::int32_t | done | done
string | std::string | done | done
decimal | boost::multiprecision::cpp_dec_float_50 | done | done
uri | std::string | done |
base64Binary | std::string | done |
instant | boost::locale::date_time | done |
date | boost::locale::date_time | done |
dateTime | boost::locale::date_time | done |
time | std::chrono::seconds | done |
code | std::string with regex validation | done |
oid | std::string with regex validation | done |
id | std::string with regex validation | done |
markdown | std::string | done |
unsignedInt | std::uint32_t | done |
positiveInt | std::int32_t with validation | done |

