//
// Created by weining on 18/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <cassert>
#include <iostream>

#include "doctest/doctest.h"

// c++ boost app dev P/320

using vertex_t = std::string;
using graph_t = boost::adjacency_list<
    // structure for edge list
    boost::vecS,
    // structure for verts
    boost::vecS,
    // edge/graph type
    boost::bidirectionalS,
    // vert type
    vertex_t >;
using descriptor_t = boost::graph_traits< graph_t >::vertex_descriptor;
using vert_it_t = boost::graph_traits< graph_t >::vertex_iterator;

template < typename GraphT >
void find_and_print( const GraphT &g, const std::string &name )
{
    vert_it_t it, end;
    boost::tie( it, end ) = boost::vertices( g );
    for ( ; it != end; ++it )
    {
        // dereferencing returns a vert descriptor
        descriptor_t desc = *it;
        if ( boost::get( boost::vertex_bundle, g )[ desc ] == name )
        {
            break;
        }
    }
    if ( it != end ) std::cout << name << '\n';
}

TEST_CASE( "add verts, edges, find-and-print" )
{
    graph_t graph;
    constexpr std::size_t vertex_count = 5;

    // this is NOT portable!!
    // graph.m_vertices.reserve(vertex_count);

    descriptor_t cpp = boost::add_vertex( vertex_t( "C++" ), graph );
    descriptor_t stl = boost::add_vertex( vertex_t( "STL" ), graph );
    descriptor_t boost = boost::add_vertex( vertex_t( "Boost" ), graph );
    descriptor_t guru = boost::add_vertex( vertex_t( "C++ guru" ), graph );
    descriptor_t ansic = boost::add_vertex( vertex_t( "C" ), graph );

    // connect verts
    boost::add_edge( cpp, stl, graph );
    boost::add_edge( stl, boost, graph );
    boost::add_edge( boost, guru, graph );
    boost::add_edge( ansic, guru, graph );

    find_and_print(graph, "STL");
    find_and_print(graph, "xxx");
}
