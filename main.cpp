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
    bool operator()(char a, char b) const {
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
void test(int unitnumber, int testnumber, std::string test) {
    if (testnumber == 1)
        std::cout << "[ --- Module " << unitnumber << " --- ]" << std::endl;
    std::cout << "[ Test n. " << testnumber << " ]" << std::endl;
    std::cout << "[ code: " << test << " ]" << std::endl;
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
    int catchResult = -1;

    test(unitnumber, testnumber++, "g.setArch('g', 'h', 1)");
    g.setArch('g', 'h', 1);
    assert(g.getArch('g', 'h') == 1);

    test(unitnumber, testnumber++, "g.setCell(1, 1, 1)");
    g.setCell(1, 1, 1);
    assert(g.getArch(1, 1) == 1);

    test(unitnumber, testnumber++, "g.setCell(1, 0, 1)");
    g.setCell(1, 0, 1);
    assert(g.getArch(1, 0) == 1);

    test(unitnumber, testnumber++, "g.add_node('a')");
    g.add_node('a');
    assert(g.getArch(2, 2) == 0);
    
    test(unitnumber, testnumber++, "g.addNode('a')");

    catchResult = -1;
    try {
        g.add_node('a');
        catchResult = 0;
    } catch (DuplicateException) { catchResult = 1; }
    assert(catchResult == 1);

    test(unitnumber, testnumber++, "g.remove_node('g')");
    g.remove_node('g');

    test(unitnumber, testnumber++, "std::cout << g << std::endl");
    std::cout << g << std::endl;

    test(unitnumber, testnumber++, "g.exists('h') == true");
    assert(g.exists('h') == true);

    test(unitnumber, testnumber++, "g.exists('l') == false");
    assert(g.exists('l') == false);

    test(unitnumber, testnumber++, "g.hasEdge('h', 'h') == true");
    assert(g.hasEdge('h', 'h') == true);

    test(unitnumber, testnumber++, "g.hasEdge('a', 'h') == false");
    assert(g.hasEdge('a', 'h') == false);
    
    test(unitnumber, testnumber++, "g.hasEdge('b', 'h')");
    catchResult = -1;
    try {
        g.hasEdge('b', 'h');
        catchResult = 0;
    } catch (NodeNotFoundException) { catchResult = 1; }
    assert(catchResult == 1);

    unitnumber++;
    testnumber = 1;
    test(unitnumber, testnumber++, "g2 = g");
    g2 = g;
    assert(g2.getArch(0, 1) == 0);

    test(unitnumber, testnumber++, "g2[0] == 'h'");
    assert(g2[0] == 'h');

    test(unitnumber, testnumber++, "g.print()");
    g.print();

    test(unitnumber, testnumber++, "g.size() == 2");
    assert(g.size() == 2);

    test(unitnumber, testnumber++, "g.archs() == 1");
    assert(g.archs() == 1);

    unitnumber++;
    testnumber = 1;
    test(unitnumber, testnumber++, "g2.getArch(2, 2)");
    
    catchResult = -1;
    try {
        g2.getArch(2, 2);
        catchResult = 0;
    } catch(IndexOutOfBoundsException) { catchResult = 1; }
    assert(catchResult == 1);

    test(unitnumber, testnumber++, "g2.setCell(3, 3, 1)");

    catchResult = -1;
    try {
        g2.setCell(3, 3, 1);
        catchResult = 0;
    } catch(IndexOutOfBoundsException) { catchResult = 1; }
    catch(NodeValueNotValidException) { catchResult = 2; }
    assert(catchResult == 1);

    test(unitnumber, testnumber++, "g2[50]");
    catchResult = -1;
    try {
        g2[50];
        catchResult = 0;
    } catch (IndexOutOfBoundsException) { catchResult = 1; }
    assert(catchResult == 1);


    test(unitnumber, testnumber++, "graph<T, E>::const_iterator");
    graph<char, _isEqualsChar>::const_iterator i, ie;

    test(unitnumber, testnumber++, "for (i, ie; i != ie; ++i)");
    for(i = g.begin(), ie = g.end(); i != ie; ++i)
        std::cout << *i << " " << std::endl;

    unitnumber++;
    testnumber = 1;
    voce v1("a", "b", "c"), v2("a", "d", "e");

    test(unitnumber, testnumber++, "g3.add_node(v1)");
    g3.add_node(v1);
    assert(g3.getArch(v1, v1) == 0);

    test(unitnumber, testnumber++, "g3.add_node(v2)");
    g3.add_node(v2);
    assert(g3.getArch(v1, v2) == 0);

    test(unitnumber, testnumber++, "g3.setArch(v2, v1, 1)");
    g3.setArch(v2, v1, 1);
    assert(g3.getArch(v2, v1) == 1);

    return 0;
}