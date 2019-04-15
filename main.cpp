#include <iostream>
#include "graph.h"
#include "voce.h"
#include <assert.h>

/**
 * @brief Functor used for educational pourposes.
 * 
 */
struct _isEqualsChar {
    /**
     * @brief Returns true when a and b are the same character
     * 
     * @param a First character
     * @param b Second character
     * @return true a and b are the same character
     * @return false a and b are not the same character
     */
    bool operator()(char a, char b) {
        return a == b;
    }
};

/**
 * @brief Functor used for educational pourposes.
 * 
 */
struct _isEqualsVoce {
    /**
     * @brief Returns true when the first **voce** has the same *nome* and *cognome* as the second **voce**
     * 
     * @param dx First voce
     * @param sx Second voce
     * @return true The first **voce** has the same *nome* and *cognome* as the second **voce**
     * @return false The two **voce** differ
     */
	bool operator()(const voce &dx, const voce &sx) const {
		return dx.nome == sx.nome && dx.cognome == sx.cognome && dx.ntel == sx.ntel;
	}
};

/**
 * @brief Outputs a text separator on the terminal screen
 * 
 * @param unitnumber The
 * @param testnumber 
 */
void test(int unitnumber, int testnumber) {
    std::cout << "[ Test n. " << testnumber << " ]" << std::endl;
}

/**
 * @brief Main function
 * 
 * @return int Exit state code
 */
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
    try {
        g.add_node('a');
    } catch (DuplicateException) { }

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

    unitnumber++;
    testnumber = 1;
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

    unitnumber++;
    testnumber = 1;
    test(unitnumber, testnumber++);
    try {
        g2.getArch(2,2);
    } catch(EdgeNotFoundException) { }

    test(unitnumber, testnumber++);
    try {
        g2.setCell(3, 3, 1);
    } catch(IndexOutOfBoundsException) { }
    catch(NodeValueNotValidException) { }

    test(unitnumber, testnumber++);
    try {
        g2[50];
    } catch (IndexOutOfBoundsException) { }

    test(unitnumber, testnumber++);
    graph<char, _isEqualsChar>::const_iterator i, ie;

    test(unitnumber, testnumber++);
    for(i = g.begin(), ie = g.end(); i != ie; ++i)
        std::cout << *i << " " << std::endl;

    unitnumber++;
    testnumber = 1;
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