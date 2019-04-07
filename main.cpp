#include <iostream>
#include "graph.h"

struct _isEqualsChar {
    bool operator()(char a, char b) {
        return a == b;
    }
};

int main() {

    char labels[] = {'a','b','c','d','e','f'};
    // graph<char, _isEqualsChar> g(6, labels);
    graph<char, _isEqualsChar> g(2, new char[3] {'g', 'h'});
    graph<char, _isEqualsChar> g2;

    g.setArch('g', 'h', 1);
    g.setCell(1, 1, 1);
    g.setCell(1, 0, 1);
    g.print();

    std::cout << "Adding node 'a': " << std::endl;
    g.add_node('a');
    g.print();
    std::cout << "Removing node 'g': " << std::endl;
    g.remove_node('g');
    g.print();
    std::cout << "labels: ";
    std::cout << g << std::endl;

    std::cout << "hasEdge(h, h)=" << g.hasEdge('h', 'h') << std::endl;
    std::cout << "hasEdge(a, h)=" << g.hasEdge('a', 'h') << std::endl;

    g2 = g;
    std::cout << "Assegnamento: " << std::endl;
    g2.print();
    return 0;
}