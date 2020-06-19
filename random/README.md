# Random number generator

## portable hardware-backed random device is hard

see: c++ boost app dev P/327

OS may have more than one such type of random number generators;

POSIX have `/dev/random` and `/dev/urandom`; the former is more secure but blocking
when waiting for entropy and thate could take seconds, which is usually unsuitable
for applications.

use `/dev/random` to create long-lifetime GPG/SSL/SSH keys

## Boost UUID

can generate uuid in std::string format. see uuid_to_string.cpp

source: <https://theboostcpplibraries.com/boost.uuid>

(NOTE, the random generator is broken in the example, use this: <https://en.cppreference.com/w/cpp/numeric/random/random_device>)

see also: <https://www.boost.org/doc/libs/1_72_0/libs/multiprecision/doc/html/boost_multiprecision/tut/random.html>

boost provides string_generator that creates a UUID object from plain string, see: string_to_uuid.cpp 

## Random Number Generator using standard library

### Using Ranges library

see: many_random_nums.cpp

range lib repo: <https://github.com/ericniebler/range-v3>

source: <https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/>

## A walk-through of C++11 random generators

c++ stl cookbook P/387

see: rand_histogram.cpp

- usually std::default_random_engine is a good default choice for the average app
- if we really need non-deterministic numbers, std::random_device does that
- we can feed the ctor of any random engine with a real random number from std::random_device (or timestamp) - seeding

## STL random distribution

c++ stl cookbook P/394

see: stl_distribution.cpp
