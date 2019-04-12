#include <iostream>
#include "graph.h"
#include <assert.h>
#include <string.h>

class Persona {

private:
    char* _nome;
    char* _cognome;
    bool _sesso;
    int _eta;

    void init(char* nome, char* cognome, bool sesso, int eta) {
        strcpy(_nome, nome);
        strcpy(_cognome, cognome);
        _sesso = sesso;
        _eta = eta;
    }

public:

    ~Persona() {
        delete[] _nome;
        delete[] _cognome;
        _nome = 0;
        _cognome = 0;
        _sesso = 0;
        _eta = 0;
    }

    explicit Persona(char* nome, char* cognome, bool sesso, int eta): _nome(0), _cognome(0), _sesso(0), _eta(0) {
        init(nome, cognome, sesso, eta);
    }

    char* getNome() { return _nome; }

    char* getCognome() { return _cognome; }

    bool getSesso() { return _sesso; }

    int getEta() { return _eta; }
};

struct _isEqualsChar {
    bool operator()(char a, char b) {
        return a == b;
    }
};

struct _isEqualsPersona {
    bool operator()(Persona anna, Persona bob) {

        if (strcmp(anna.getNome(), bob.getNome()) != 0) return false;
        if (strcmp(anna.getCognome(), bob.getCognome()) != 0) return false;
        if (anna.getSesso() != bob.getSesso()) return false;
        if (anna.getEta() != bob.getEta()) return false;

        return true;
    }
};


void test(int unitnumber, int testnumber) {
    std::cout << "[ Test n. " << testnumber << " ]" << std::endl;
}

int main() {

    char labels[] = {'g', 'h'};
    graph<char, _isEqualsChar> g(2, labels);
    graph<char, _isEqualsChar> g2;

    Persona
        anna("Anna", "Lisa", true, 25),
        bob("Bob", "Aggiustatutto", false, 35);

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
    assert(g.hasEdge('h', 'h') == true);

    test(unitnumber, testnumber++);
    assert(g.hasEdge('a', 'h') == false);

    test(unitnumber, testnumber++);
    g2 = g;
    assert(g2.getArch(0, 1) == 0);

    test(unitnumber, testnumber++);
    graph<char, _isEqualsChar>::const_iterator i, ie;

    test(unitnumber, testnumber++);
    for(i = g.begin(), ie = g.end(); i != ie; ++i)
        std::cout << *i << " " << std::endl;

    return 0;
}