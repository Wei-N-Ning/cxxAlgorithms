//
// Created by wein on 19/09/18.
//

#include "dagraph.hh"

#include <cassert>

void RunTinyTests();

void test_add_edges_from_scratch() {
    using namespace graph;

    Dagraph d;
    assert(! d.node("a"));
    assert(! d.node("b"));

    assert(d.addEdge("a", "b"));

    // expect node a, b created
    assert(d.node("a") && d.node("b"));

    // retrieve edge
    assert(d.tos("a").size() == 1);
    assert(*(d.tos("a").begin()) == d.node("b"));

    // add again, expect no effect (with return status)
    assert(! d.addEdge("a", "b"));

    // add a new edge a->c, expect the number of "Tos" (connections)
    // increases by 1
    assert(d.addEdge("a", "c"));
    assert(d.tos("a").size() == 2);
}

void test_create_graph_from_string() {
    using namespace graph;

    std::string str = R"IDDQD(
 # // is accepted
there is->a //cow

# __ is accepted
de123 -> __d3

# expect node "*4d" is only created once
*4d -> 13d1
*4d -> 13d1
*4d -> iad

# the totally number of nodes should be 7
)IDDQD";
    auto g = graph::createFromString(str);

    // expect number of nodes created
    assert(7 == g.numNodes());

    // expect connection
    assert(2 == g.tos("*4d ").size());
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
