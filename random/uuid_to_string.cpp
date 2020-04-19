
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/regex.hpp>

#include <string>
#include <iostream>

TEST_CASE ("generate uuid as string") {
    using namespace boost::uuids;

    // 72231f4a-f549-49bb-9e8c-a976c503e19c
    random_generator gen;

    // uuid object can be passed to stream but require the io header
    // cout << id << endl;
    uuid id = gen();
    boost::regex re{R"RE([a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12})RE"};
    std::string s{to_string(id)}; // boost::uuids::to_string
    CHECK(boost::regex_match(s, re));
}

TEST_CASE ("generate nil uuid") {
    using namespace boost::uuids;

    nil_generator nil_gen;
    uuid id = nil_gen();
    std::string s{to_string(id)};
    boost::regex re{R"RE([0\-]+)RE"};
    CHECK(boost::regex_match(s, re));
}

TEST_CASE ("random number generator") {
    using namespace boost::uuids;

    random_generator gen;
    uuid id = gen();
    boost::regex re{R"RE([a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12})RE"};
    std::string s{to_string(id)}; // boost::uuids::to_string
    CHECK(boost::regex_match(s, re));
}
