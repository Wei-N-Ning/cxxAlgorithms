//
// Created by wein on 19/09/18.
//

#ifndef CXXALGORITHMS_DAGRAPH_HH
#define CXXALGORITHMS_DAGRAPH_HH

#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <memory>
#include <cassert>

namespace graph {

// node interface
struct Node {
    explicit Node(std::string label)
        : m_label(std::move(label)) {
        ;
    }

    bool operator== (const Node& other) {
        return m_label == other.m_label;
    }

    std::string m_label = "";
};

// dag graph interface
class Dagraph {
public:
    using NodeP = std::shared_ptr<Node>;
    using Nodes = std::unordered_map<std::string, NodeP>;
    using Tos = std::unordered_set<Node*>;
    using Edges = std::unordered_map<Node*, Tos>;

    bool addEdge(const std::string& from, const std::string& to) {
        auto _from = m_nodes.find(from);
        NodeP fromNode = nullptr;
        if (_from == m_nodes.end()) {
            fromNode = std::make_shared<Node>(from);
            m_nodes[from] = fromNode;
        } else {
            fromNode = _from->second;
        }

        NodeP toNode = nullptr;
        auto _to = m_nodes.find(to);
        if (_to == m_nodes.end()) {
            toNode = std::make_shared<Node>(to);
            m_nodes[to] = toNode;
        } else {
            toNode = _to->second;
        }

        // edge from->to exists
        auto exist = m_edges.find(fromNode.get());
        if (exist != m_edges.end()) {
            auto tos = exist->second;
            if (tos.find(toNode.get()) != tos.end()) {
                return false;
            }
        }

        m_edges[fromNode.get()].insert(toNode.get());
        return true;
    }

    Node* node(const std::string& label) {
        auto it = m_nodes.find(label);
        if (it == m_nodes.end()) {
            return nullptr;
        }
        return it->second.get();
    }

    size_t numNodes() const  {
        return m_nodes.size();
    }

    Tos tos(const std::string& from) {
        auto nit = m_nodes.find(from);
        if (nit == m_nodes.end()) {
            return {};
        }
        auto eit = m_edges.find(nit->second.get());
        if (eit == m_edges.end()) {
            return {};
        }
        return eit->second;
    }

private:
    Nodes m_nodes = {};
    Edges m_edges = {};
};

// graph factory
Dagraph createFromString(const std::string& str) {
    Dagraph g;
    std::stringstream ss(str);
    std::string line;

    auto strip = [](std::string& o_str) {
        o_str.erase(0, o_str.find_first_not_of("\t\n\v\f\r "));
        o_str.erase(o_str.find_last_not_of("\t\n\v\f\r ") + 1);
    };

    while (std::getline(ss, line).good()) {
        strip(line);
        if (line.empty() or line[0] == '#') {
            continue;
        }
        auto arrow = line.find("->");
        assert(arrow != std::string::npos);
        auto from = line.substr(0, arrow);
        auto to = line.substr(arrow + 2);
        assert(! (from.empty() or to.empty()));
        g.addEdge(from, to);
    }
    return g;
}

}

#endif //CXXALGORITHMS_DAGRAPH_HH
