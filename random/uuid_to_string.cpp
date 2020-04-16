/*
 *         // uuid to string,
        // see: https://theboostcpplibraries.com/boost.uuid
        using namespace boost::uuids;
        using namespace boost::filesystem;
        random_generator gen;
        uuid id = gen();
        return temp_directory_path() / to_string( id );
 *
 * */
