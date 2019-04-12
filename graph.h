#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <assert.h>

class EdgeNotFoundException {};

class DuplicateException {};

/**
 * @brief Template per il tipo dei label
 * 
 * @tparam T=int 
 */
template <typename T, typename E>

class graph {

private:
    int _size;
    int** _adj_matrix;
    T* _labels;
    E _isEqual;

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
        for (int i = 0; i < _size; i++)
            delete[] _adj_matrix[i];
        delete[] _adj_matrix;
        delete[] _labels;
        _adj_matrix = 0;
        _labels = 0;
        _size = 0;
    }

    /**
     * @brief 
     * 
     * @param value 
     * @return true 
     * @return false 
     */
    bool _is_node_value_valid(int value) {
        return (value == 0 || value == 1);
    }

    /**
     * @brief 
     * 
     * @param label 
     * @return int 
     */
    int _node_exists(const T label) {
        for (int i = 0; i < _size; i++)
            if (_isEqual(_labels[i], label))
                return i;
        return -1;
    }

    bool _arch_exists(const T labelFrom, const T labelTo) const {
        return (_node_exists(labelFrom) && _node_exists(labelTo));
    }

    bool _arch_exists(const int indexFrom, const int indexTo) const {
        return (indexFrom >= 0 && indexFrom < _size && indexTo >= 0 && indexTo < _size);
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
        if (&other != this) {
            graph tmp(other);
            std::swap(tmp._adj_matrix, _adj_matrix);
            std::swap(tmp._labels, _labels);
            std::swap(tmp._size, _size);
        }
        return *this;
    }

    /**
     * @brief 
     * 
     * @param index 
     * @return int*& 
     */
    T &operator[](int index) {
        assert(index < _size);
        return _labels[index];
    }

    const T &operator[](const unsigned int index) const {
        assert(index < _size);
        assert(index >= 0);
        return _labels[index];
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
        for (int i = 0; i < _size; i++)
            for (int j = 0; j < _size; j++)
                _adj_matrix[i][j] = other._adj_matrix[i][j];
        
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
        return getArch(labelFrom, labelTo) == 1; 
    }

    /**
     * @brief Creates a new graph with the new node
     * 
     * @param label The node unique label
     * @return graph<T, E> 
     */
    void add_node(T label) {
        if (exists(label)) {
            #ifndef NDEBUG
            std::cout << "Node exists! Error." << std::endl;
            #endif
            throw DuplicateException();
        }

        int i, j;
        T* labels = new T[_size + 1];
        int** adj_matrix = new int*[_size + 1];

        for (i = 0; i < _size; i++) {
            labels[i] = _labels[i];
            adj_matrix[i] = new int[_size + 1];
            for (j = 0; j < _size; j++)
                adj_matrix[i][j] = _adj_matrix[i][j];
        }
        labels[_size] = label;
        adj_matrix[_size] = new int[_size + 1];
        for (i = 0; i < _size + 1; i++)
            adj_matrix[i][_size] = 0;
        for (j = 0; j < _size + 1; j++)
            adj_matrix[_size][j] = 0;

        std::swap(labels, _labels);
        std::swap(adj_matrix, _adj_matrix);

        delete[] labels;
        for (i = 0; i < _size; i++)
            delete[] adj_matrix[i];
        delete[] adj_matrix;
        labels = 0;
        adj_matrix = 0;

        _size = _size + 1;
    }

    /**
     * @brief Removes a node from the grap
     * 
     * @param label The node to remove from the graph
     * @return graph<T, E> The new graph without the node
     */
    void remove_node(T label) {
        int node_index = _node_exists(label);
        if (node_index == -1) {
            throw;
        }

        int i, j;
        T* labels = new T[_size - 1];
        int** adj_matrix = new int*[_size - 1];
        for (i = 0; i < node_index; i++) {
            labels[i] = _labels[i];
            adj_matrix[i] = new int[_size -1];
        }
        for (i = node_index + 1; i < _size; i++) {
                labels[i - 1] = _labels[i];
                adj_matrix[i - 1] = new int[_size -1];
        }

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
                    adj_matrix[i][j] = _adj_matrix[i][j];
        } else {
            // first step
            for (i = 0; i < node_index; i++)
                for (j = 0; j < node_index; j++)
                    adj_matrix[i][j] = _adj_matrix[i][j];

            // fourth step
            for (i = node_index + 1; i < _size; i++)
                for (j = node_index + 1; j < _size; j++)
                    adj_matrix[i - 1][j - 1] = _adj_matrix[i][j];
        
            // second step
            for (i = 0; i < node_index; i++)
                for (j = node_index + 1; j < _size; j++)
                    adj_matrix[i][j - 1] = _adj_matrix[i][j];

            // third step
            for (i = node_index + 1; i < _size; i++)
                for (j = 0; j < node_index; j++)
                    adj_matrix[i - 1][j] = _adj_matrix[i][j];
        }
        std::swap(labels, _labels);
        std::swap(adj_matrix, _adj_matrix);

        delete[] labels;
        for (i = 0; i < _size; i++)
            delete[] adj_matrix[i];
        delete[] adj_matrix;

        _size = _size - 1;
    }

    /**
     * @brief Set the Arch object
     * 
     * @param labelFrom 
     * @param labelTo 
     * @param value 
     */
    void setArch(T labelFrom, T labelTo, int value) {
        int index_from = _node_exists(labelFrom);
        int index_to = _node_exists(labelTo);
        
        setCell(index_from, index_to, value);
    }

    /**
     * @brief Set the Cell object
     * 
     * @param indexFrom 
     * @param indexTo 
     * @param value 
     */
    void setCell(int indexFrom, int indexTo, int value) {
        assert(indexFrom < _size && indexTo < _size);
        assert(_is_node_value_valid(value));
        _adj_matrix[indexFrom][indexTo] = value;
    }

    int getArch(int i, int j) {
        if (i < 0 || i > _size - 1 || j < 0 || j > _size - 1)
            throw EdgeNotFoundException();
        return _adj_matrix[i][j];
    }

    int getArch(T labelFrom, T labelTo) {
        int indexFrom, indexTo;
        indexFrom = _node_exists(labelFrom);
        indexTo = _node_exists(labelTo);
        return getArch(indexFrom, indexTo);
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

	class const_iterator {	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

        /**
         * @brief Construct a new const iterator object
         * 
         */
		const_iterator() : ptr(0), position(0) {}
		
        /**
         * @brief Construct a new const iterator object
         * 
         * @param other 
         */
		const_iterator(const const_iterator &other) : ptr(other.ptr), position(other.position) {}

        /**
         * @brief 
         * 
         * @param other 
         * @return const_iterator& 
         */
		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
			position = other.position;
			return *this;
		}

        /**
         * @brief Destroy the const iterator object
         * 
         */
		~const_iterator() {
			ptr = 0;
			position = 0;
		}

		/**
		 * @brief 
		 * 
		 * @return reference 
		 */
		reference operator*() const {
			return (*ptr)[position];
		}

		/**
		 * @brief 
		 * 
		 * @return pointer 
		 */
		pointer operator->() const {
			return &((*ptr)[position]);
		}
		
		/**
		 * @brief 
		 * 
		 * @return const_iterator 
		 */
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			position++;
			return tmp;
		}

		/**
		 * @brief 
		 * 
		 * @return const_iterator& 
		 */
		const_iterator& operator++() {
			position++;
			return *this;
		}

		/**
		 * @brief 
		 * 
		 * @param other 
		 * @return true 
		 * @return false 
		 */
		bool operator==(const const_iterator &other) const {
			return (ptr == other.ptr) && (position == other.position);
		}
		
		/**
		 * @brief 
		 * 
		 * @param other 
		 * @return true 
		 * @return false 
		 */
		bool operator!=(const const_iterator &other) const {
			return !(*this == other);
		}


	private:
		const graph *ptr;
		int position;

		friend class graph; 

		/**
		 * @brief Construct a new const iterator object
		 * 
		 * @param p 
		 * @param pos 
		 */
		const_iterator(const graph *p, int pos) : ptr(p), position(pos) { }
				
	};

	/**
	 * @brief 
	 * 
	 * @return const_iterator 
	 */
	const_iterator begin() const {
		return const_iterator(this, 0);
	}
	
	/**
	 * @brief 
	 * 
	 * @return const_iterator 
	 */
	const_iterator end() const {
		return const_iterator(this, _size);
	}

};


/**
	@brief Operatore di stream

	Permette di spedire su uno stream di output il contenuto dell'array generico.
	E' una funzione templata perche' il parametro relativo a dbufferT e' templato

	@param os stream di output
	@param g graph da utilizzare
	@return Il riferimento allo stream di output
**/
template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, 
	const graph<T, E> &g) {

    typename graph<T, E>::const_iterator i, ie;
	for (i = g.begin(), ie = g.end(); i != ie; ++i)
		os << *i << " ";
	return os;
}

#endif