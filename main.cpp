#include <iostream>
#include "graph.h"

int main() {

    int labels[] = {1,2,3,4,5,6};
    graph<int> g(6, labels);

    g[1][1] = 1;
    g[2][0] = 1;
    g[3][3] = 1;

    g.print();
    graph<int> g2 = g.remove_node(2);
    g2.print();
    return 0;
}