# Random number generator

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
