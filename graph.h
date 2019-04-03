#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <assert.h>

/**
 * @brief Template per il tipo dei label
 * 
 * @tparam T=int 
 */
template <typename T=int>

class graph {

private:
    int _size;
    int** _adj_matrix;
    T* _labels;

    /**
     * @brief Initializes everything in the graph class
     * 
     * @param size The graph size
     */
    void init(int size, T* labels) {
        _adj_matrix = new int*[size];
        _labels = new T[size];
        for (int i = 0; i < size; i++) {
            _adj_matrix[i] = new int[size];
            _labels[i] = labels[i];
            for (int j = 0; j < size; j++)
                _adj_matrix[i][j] = 0;
        }
        _size = size;
    }

    /**
     * @brief 
     * 
     */
    void _del() {
        for (int i = 0; i < _size; i++) {
            delete[] _adj_matrix[i];
            _adj_matrix[i] = 0;
        }
        delete[] _adj_matrix;
        delete[] _labels;
        _adj_matrix = 0;
        _labels = 0;
        _size = 0;
    }

    bool _is_node_value_valid(int value) {
        return (value == 0 || value == 1);
    }

    int _node_exists(T label) {
        for (int i = 0; i < _size; i++) {
            if (_labels[i] == label)
               return i; 
        }
        return -1;
    }

public:
    /**
     * @brief Construct a new graph object
     * 
     */
    graph() : _size(0), _adj_matrix(0), _labels(0) {
        #ifndef NDEBUG
        std::cout << "graph()" << std::endl;
        #endif
    }

    /**
     * @brief Construct a new graph object
     * 
     * @param size 
     */
    explicit graph(int size, T* labels) : _size(0), _adj_matrix(0), _labels(0) {
        #ifndef NDEBUG
        std::cout << "graph(size, labels)" << std::endl;
        #endif
        init(size, labels);
    }

    graph& operator=(const graph &other) {
        return *this;
    }

    /**
     * @brief 
     * 
     * @param index 
     * @return int*& 
     */
    int* &operator[](int index) {
        assert(index < _size);
        return _adj_matrix[index];
    }

    /**
     * @brief Distruttore
     *
     * Distruttore. Rimuove la memoria allocata da graph.
    **/
    ~graph() {
        #ifndef NDEBUG
        std::cout << "~graph()" << std::endl;
        #endif
        _del();
    }

    /**
     * @brief Copy constructor for graph object
     * 
     * @param other
     */
    graph(const graph &other) : _size(0), _adj_matrix(0), _labels(0) {
        #ifndef NDEBUG
        std::cout << "graph(graph, labels)" << std::endl;
        #endif

        init(other._size, other._labels);
        /* TODO: aggiornare con iterator
        for (int i = 0; i < _size; i++)
            for (int j = 0; j < _size; j++)
                _adj_matrix[i][j] = other[i][j];
        */
    }

    /**
     * @brief Dimensione del grafo
     * 
     * Ritorna la dimensione del grafo
     * @return La dimensione del grafo
    **/
    int size(void) const {
        return _size;
    }

    /**
     * @brief Number of archs in the graph
     * 
     * Returns the number of archs inside the graph
     * @return int 
     */
    int archs(void) const {
        int count = 0;
        for (int i = 0; i < _size; i++)
            for (int j = 0; j < _size; j++)
                count += _adj_matrix[i][j];

        return count;
    }

    /**
     * @brief Checks if a node exists already in the adjacency matrix
     * 
     * @param label The label to search
     * @return true If the node is present
     * @return false If the node is absent
     */
    bool exists(T label) {
        return _node_exists(label) > -1;
    }

    /**
     * @brief Creates a new graph with the new node
     * 
     * @param label The node unique label
     * @return graph<T> 
     */
    graph<T> add_node(T label) {
        if (exists(label)) {
            #ifndef NDEBUG
            std::cout << "Node exists! Error." << std::endl;
            #endif
            throw;
        }

        T* labels = new T[_size + 1];

        for (int i = 0; i < _size; i++)
            labels[i] = _labels[i];
        labels[_size] = label;

        graph<T> newGraph(_size + 1, labels);

        for (int i = 0; i < _size + 1; i++) {
            for (int j = 0; j < _size + 1; j++) {
                if (i < _size && j < _size)
                    newGraph[i][j] = _adj_matrix[i][j];
                else
                    newGraph[i][j] = 0;
            }
        }
        
        delete[] labels;
        return newGraph;
    }

    /**
     * @brief Removes a node from the grap
     * 
     * @param label The node to remove from the graph
     * @return graph<T> The new graph without the node
     */
    graph<T> remove_node(T label) {
        int node_index = _node_exists(label);
        if (node_index == -1) {
            throw;
        }

        T* labels = new T[_size - 1];
        int i, j;

        for (i = 0; i < node_index; i++)
            labels[i] = _labels[i];
        if (node_index < _size - 1) {
            for (i = node_index + 1; i < _size; i++)
                labels[i - 1] = _labels[i];
        }

        graph<T> newGraph(_size -1, labels);
        delete[] labels;
        for (i = 0; i < _size - 1; i++)
            newGraph[i] = new int[_size - 1];
        
        /**
         *   a b c d e f
         * a 0 1 0 1 0 0
         * b 0 0 0 1 0 1
         * c 0 1 0 0 0 0
         * d 1 0 0 1 1 0
         * e 0 0 1 0 0 0
         * f 1 0 0 0 0 1
         * 
         * We want to remove node c, thus:
         *   a b | d e f
         * a 0 1 | 1 0 0 ] -> First, we focus on the a,b matrix
         * b 0 0 | 1 0 1 ] -> Second, we fill the right part
         * -------------
         * d 1 0 | 1 1 0 ] -> third, we focus on a,b and d,e,f
         * e 0 0 | 0 0 0 ] -> lastly, we fill everything else left
         * f 1 0 | 0 0 1 ]
         */

        // we're lucky, and we shall only copy everything until the node_index row and column
        if (node_index == _size - 1) {
            for (i = 0; i < _size - 1; i++)
                for (j = 0; j < _size - 1; j++)
                    newGraph[i][j] = _adj_matrix[i][j];
        } else {
            // first step
            for (i = 0; i < node_index; i++)
                for (j = 0; j < node_index; j++)
                    newGraph[i][j] = _adj_matrix[i][j];
            // fourth step
            for (i = node_index + 1; i < _size; i++)
                for (j = node_index + 1; j < _size; j++)
                    newGraph[i - 1][j - 1] = _adj_matrix[i][j];
        
            // second step
            for (i = 0; i < node_index; i++)
                for (j = node_index + 1; j < _size; j++)
                    newGraph[i][j - 1] = _adj_matrix[i][j];

            // third step
            for (i = node_index + 1; i < _size; i++)
                for (j = 0; j < node_index; j++)
                    newGraph[i - 1][j] = _adj_matrix[i][j];
        }
        return newGraph;
    }

    void print() {
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) 
                std::cout << _adj_matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    void print_labels() {
        for(int i = 0; i < _size; i++)
            std::cout << _labels[i] << " ";
        std::cout << std::endl;
    }
};

#endif