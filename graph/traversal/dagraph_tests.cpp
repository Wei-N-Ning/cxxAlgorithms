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



int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
