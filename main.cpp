#include <iostream>
#include "graph.h"

struct _isEqualsChar {
    bool operator()(char a, char b) {
        return a == b;
    }
};

int main() {

    char labels[] = {'a','b','c','d','e','f'};
    graph<char, _isEqualsChar> g(6, labels);

    g.setArch('a', 'b', 1);
    g.setCell(2, 3, 1);
    g.setCell(3, 0, 1);

    g.print();
    graph<char, _isEqualsChar> g2 = g.remove_node('c');
    g2.print();

    graph<char, _isEqualsChar> g3 = g2.add_node('g');

    g3.setCell(5, 0, 1);
    g3.setCell(5, 1, 1);
    g3.setCell(5, 2, 1);
    g3.print();
    g3.print_labels();

    std::cout << "hasEdge(g, a)=" << g3.hasEdge('g', 'a') << std::endl;
    std::cout << "hasEdge(g, f)=" << g3.hasEdge('g', 'f') << std::endl;

    // iterator

    graph<char, _isEqualsChar>::const_iterator it, ite;

    it = g3.begin();
    ite = g3.end();

    for (; it != ite; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}