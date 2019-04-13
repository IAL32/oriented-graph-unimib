#include <iostream>
#include "graph.h"
#include "voce.h"
#include <assert.h>


struct _isEqualsChar {
    bool operator()(char a, char b) {
        return a == b;
    }
};

struct _isEqualsVoce {
	bool operator()(const voce &dx, const voce &sx) const {
		return dx.nome == sx.nome && dx.cognome == sx.cognome && dx.ntel == sx.ntel;
	}
};

void test(int unitnumber, int testnumber) {
    std::cout << "[ Test n. " << testnumber << " ]" << std::endl;
}

int main() {

    char labels[] = {'g', 'h'};
    graph<char, _isEqualsChar> g(2, labels);
    graph<char, _isEqualsChar> g2;
    graph<voce, _isEqualsVoce> g3;

    int unitnumber = 1;
    int testnumber = 1;

    test(unitnumber, testnumber++);
    g.setArch('g', 'h', 1);
    assert(g.getArch('g', 'h') == 1);

    test(unitnumber, testnumber++);
    g.setCell(1, 1, 1);
    assert(g.getArch(1, 1) == 1);

    test(unitnumber, testnumber++);
    g.setCell(1, 0, 1);
    assert(g.getArch(1, 0) == 1);

    test(unitnumber, testnumber++);
    g.add_node('a');
    assert(g.getArch(2, 2) == 0);

    test(unitnumber, testnumber++);
    g.remove_node('g');

    test(unitnumber, testnumber++);
    std::cout << g << std::endl;

    test(unitnumber, testnumber++);
    assert(g.exists('h') == true);

    test(unitnumber, testnumber++);
    assert(g.exists('l') == false);

    test(unitnumber, testnumber++);
    assert(g.hasEdge('h', 'h') == true);

    test(unitnumber, testnumber++);
    assert(g.hasEdge('a', 'h') == false);

    test(unitnumber, testnumber++);
    g2 = g;
    assert(g2.getArch(0, 1) == 0);

    test(unitnumber, testnumber++);
    assert(g2[0] == 'h');

    test(unitnumber, testnumber++);
    g.print();

    test(unitnumber, testnumber++);
    assert(g.size() == 2);

    test(unitnumber, testnumber++);
    assert(g.archs() == 1);

    test(unitnumber, testnumber++);
    try {
        g2.getArch(2,2);
    } catch(...) { }

    test(unitnumber, testnumber++);
    try {
        g2.setCell(3, 3, 1);
    } catch(...) { }

    test(unitnumber, testnumber++);
    graph<char, _isEqualsChar>::const_iterator i, ie;

    test(unitnumber, testnumber++);
    for(i = g.begin(), ie = g.end(); i != ie; ++i)
        std::cout << *i << " " << std::endl;

    voce v1("a", "b", "c"), v2("a", "d", "e");

    test(unitnumber, testnumber++);
    g3.add_node(v1);
    assert(g3.getArch(v1, v1) == 0);

    test(unitnumber, testnumber++);
    g3.add_node(v2);
    assert(g3.getArch(v1, v2) == 0);

    test(unitnumber, testnumber++);
    g3.setArch(v2, v1, 1);
    assert(g3.getArch(v2, v1) == 1);

    return 0;
}