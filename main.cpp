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

    graph<char> g3 = g2.add_node('g');

    g3[5][0] = 1;
    g3[5][1] = 1;
    g3[5][2] = 1;
    g3.print();
    g3.print_labels();
    return 0;
}