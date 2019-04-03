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

    bool hasEdge(T labelFrom, T labelTo) {
        int index_from = _node_exists(labelFrom);
        int index_to = _node_exists(labelTo);

        if (index_from == -1 || index_to == -1)
            return false;
        
        return _adj_matrix[index_from][index_to] == 1; 
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

    class const_iterator;

    class iterator {
    public:
        typedef std::forward_iterator_tag   iterator_category;
        typedef ptrdiff_t                   difference_type;

        iterator() : ptr(0), position(0) {}

        iterator(const iterator &other)
            : ptr(other.ptr), position(other.position) { }

        iterator& operator=(const iterator &other) {
            ptr = other.ptr;
            position = other.position;
            return *this;
        }

        ~iterator() {
            ptr = 0;
            position = 0;
        }

        int* operator*() const {
            return (*ptr)[position];
        }

        int operator->() const {
            return &((*ptr)[position]);
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++position;
            return tmp;
        }

        iterator& operator++() {
            ++position;
            return *this;
        }

        bool operator==(const iterator &other) const {
            return (ptr == other.ptr) && (position == other.position); 
        }

        bool operator !=(const iterator &other) const {
            return !(*this == other);
        }

        friend class const_iterator;

        bool operator==(const const_iterator &other) const {
            return (ptr == other.ptr) && (position == other.position);
        }

        bool operator !=(const const_iterator &other) const {
            return !(*this == other);
        }
    private:
        graph* ptr;
        int position;

        friend class graph;

        iterator(graph* p, int pos) : ptr(p), position(pos) { }
    };

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, _size);
    }

    class const_iterator {
    
    public:
        typedef std::forward_iterator_tag   iterator_category;
        typedef ptrdiff_t                   difference_type;

        const_iterator() : ptr(0), position(0) { }

        const_iterator(const const_iterator &other)
            : ptr(other.ptr), position(other.position) { }
        
        const_iterator& operator=(const const_iterator &other) {
            ptr = other.ptr;
            position = other.position;
            return *this;
        }

        ~const_iterator() {
            ptr = 0;
            position = 0;
        }

        int& operator*() const {
            return (*ptr)[position];
        }

        int* operator->() const {
            return &((*ptr)[position]);
        }

		const_iterator operator++(int) {
			const_iterator tmp(*this);
			position++;
			return tmp;
		}

		const_iterator& operator++() {
			position++;
			return *this;
		}

		bool operator==(const const_iterator &other) const {
			return (ptr == other.ptr) && (position == other.position);
		}

		bool operator!=(const const_iterator &other) const {
			return !(*this==other);
		}

        friend class iterator;

		bool operator==(const iterator &other) const {
			return (ptr == other.ptr) && (position == other.position);
		}

		bool operator!=(const iterator &other) const {
			return !(*this==other);
		}

		const_iterator(const iterator &other) 
			: ptr(other.ptr), position(other.position) {			
		}

		const_iterator &operator=(const iterator &other) {
			ptr = other.ptr;
			position = other.position;
			return *this;
		}

	private:
		const graph *ptr;
		int position;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class graph; 

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const graph *p, int pos) : ptr(p), position(pos) { }
    };

	const_iterator begin() const {
		return const_iterator(this, 0);
	}
	
	const_iterator end() const {
		return const_iterator(this, _size);
	}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, 
	const graph<T> &db) {

	os << "size: " << db.size() << std::endl;
	for (int i = 0; i < db.size(); ++i)
		os << db[i] << " ";

	return os;
}

#endif