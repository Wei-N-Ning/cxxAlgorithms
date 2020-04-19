#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/regex.hpp>

#include <string>
#include <iostream>

TEST_CASE ("create uuid object from string") {
    using namespace boost::uuids;

    // You can pass a UUID without dashes, but if you use dashes, they must be in the right places.
    // Case (upper or lower) is ignored.
    string_generator string_gen;
    auto id = string_gen("CF77C981-F61B-7817-10FF-D916FCC3EAA4");
    std::cout << id << std::endl;

    // throw exception invalid uuid string
    // std::cout << string_gen("CF77C981-F61B-7") << std::endl;
}
