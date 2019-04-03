#include <iostream>
#include "graph.h"

int main() {

    char labels[] = {'a','b','c','d','e','f'};
    graph<char> g(6, labels);

    g[1][1] = 1;
    g[2][0] = 1;
    g[3][3] = 1;

    g.print();
    graph<char> g2 = g.remove_node('c');
    g2.print();

    return 0;
}