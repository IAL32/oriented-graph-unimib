#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <exception>
#include <stddef.h>

/**
 * @brief Attempt to insert a duplicate node
 * 
 */
class DuplicateException: public std::exception {
    virtual const char* what() const throw() {
        return "Attempt to insert a duplicate node";
    }
};

/**
 * @brief Attempt to get an index from the matrix out of bounds
 * 
 */
class IndexOutOfBoundsException: public std::exception {
    virtual const char* what() const throw() {
        return "Attempt to get an index from the matrix out of bounds";
    }
};

/**
 * @brief Matrix values can only be either 0 or 1
 * 
 */
class NodeValueNotValidException: public std::exception {
    virtual const char* what() const throw() {
        return "Matrix values can only be either 0 or 1";
    }
};

/**
 * @brief A node was not found
 * 
 */
class NodeNotFoundException: public std::exception {
    virtual const char* what() const throw() {
        return "The node was not found";
    }
};

/**
 * @brief Graph
 * 
 * @tparam T Type for node indentifiers
 * @tparam E Functor for node comparison
 */
template <typename T, typename E>
class graph {

private:

    /**
     * @brief The total number of nodes in the matrix
     * 
     */
    int _size;
    /**
     * @brief Matrix used for storing arch values
     * 
     */
    int** _adj_matrix;
    /**
     * @brief The node identifiers
     * 
     */
    T* _labels;
    /**
     * @brief Functor for comparing two nodes
     * 
     */
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
     * @brief Deletes the current graph instance
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
     * @brief Checks if *value* is either 0 or 1
     * 
     * @param value Value to check
     * @return true The value is either 0 or 1
     * @return false Value is not either 0 or 1
     */
    bool _is_node_value_valid(int value) const {
        return (value == 0 || value == 1);
    }

    /**
     * @brief Returns the given identifier position. Internal use.
     * 
     * @param label The identifier to check
     * @return int -1 when the label is not present in the list of identifiers. The position when it is present.
     */
    int _node_index(const T label) const {
        for (int i = 0; i < _size; i++)
            if (_isEqual(_labels[i], label))
                return i;
        return -1;
    }

    /**
     * @brief 
     * 
     * @param node 
     * @return int 
     */
    bool _node_exists(int node) const {
        return node >= 0 && node < _size;
    }

    /**
     * @brief Checks if an arch axists two nodes given their instances
     * 
     * @param labelFrom The starting node
     * @param labelTo The ending node
     * @return true The arch exists
     * @return false The arch does not exists
     */
    bool _arch_exists(const T labelFrom, const T labelTo) const {
        int indexFrom = _node_index(labelFrom);
        int indexTo = _node_index(labelTo);
        return _arch_exists(indexFrom, indexTo);
    }

    /**
     * @brief Checks if an arch axists two nodes given their position
     * 
     * @param labelFrom The starting node position
     * @param labelTo The ending node position
     * @return true The arch exists
     * @return false The arch does not exists
     */
    bool _arch_exists(const int indexFrom, const int indexTo) const {
        if (!_node_exists(indexFrom) || !_node_exists(indexTo))
            throw IndexOutOfBoundsException();
        return _adj_matrix[indexFrom][indexTo] == 1;
    }

public:
    /**
     * @brief Construct a new graph object with no elements.
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
     * @param size The size of the matrix
     * @param T* labels A default list of elements.
     */
    explicit graph(int size, T* labels) : _size(0), _adj_matrix(0), _labels(0) {
        #ifndef NDEBUG
        std::cout << "graph(size, labels)" << std::endl;
        #endif
        init(size, labels);
    }

    /**
     * @brief Copy operator
     * 
     * @param other The graph instance to copy from
     * @return graph& A pointer to the graph instance
     */
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
     * @brief Operator for getting a node using its index
     * 
     * @param index Node index in the node list
     * @return T& The node
     */
    T &operator[](int index) {
        if (!_node_exists(index))
            throw IndexOutOfBoundsException();
        return _labels[index];
    }

    /**
     * @brief Operator for getting a node using its index
     * 
     * @param index Node index in the node list
     * @return T& The node
     */
    const T &operator[](const unsigned int index) const {
        if(_node_exists(index) == false)
            throw IndexOutOfBoundsException();
        return _labels[index];
    }

    /**
     * @brief Graph disctructor
     *
     * Removes all memory allocated by this graph instance
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
     * @param other The other graph to copy from
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
     * @brief Graph size.
     * 
     * @return Graph size.
    **/
    int size(void) const {
        return _size;
    }

    /**
     * @brief Number of archs in the graph
     *
     * @return int The number of archs inside the graph
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
    bool exists(T label) const {
        return _node_index(label) > -1;
    }

    bool hasEdge(T labelFrom, T labelTo) const {
        if (!exists(labelFrom) || !exists(labelTo))
            throw NodeNotFoundException();
        return _arch_exists(labelFrom, labelTo) == 1;
    }

    /**
     * @brief Creates a new graph with the new node
     * 
     * @param label The node unique label
     */
    void add_node(T label) {
        if (exists(label)) {
            #ifndef NDEBUG
            std::cout << "Node exists! Error." << std::endl;
            #endif
            throw DuplicateException();
        }

        int i, j;
        T* labels;
        int** adj_matrix;
        try {
            labels = new T[_size + 1];
            adj_matrix = new int*[_size + 1];

            for (i = 0; i < _size; i++) {
                labels[i] = _labels[i];
                adj_matrix[i] = new int[_size + 1];
                for (j = 0; j < _size; j++)
                    adj_matrix[i][j] = _adj_matrix[i][j];
            }
            labels[_size] = label;
            adj_matrix[_size] = new int[_size + 1];
        } catch (...) {
            #ifndef NDEBUG
            std::cout << "~ Error while trying to allocate memory" << std::endl;
            #endif
            _del();
            throw std::bad_alloc();
        }
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
     */
    void remove_node(T label) {
        int node_index = _node_index(label);
        if (node_index == -1) {
            throw NodeNotFoundException();
        }

        int i, j;
        T* labels;
        int** adj_matrix;
        try {
            labels = new T[_size - 1];
            adj_matrix = new int*[_size - 1];
            for (i = 0; i < node_index; i++) {
                labels[i] = _labels[i];
                adj_matrix[i] = new int[_size -1];
            }
            for (i = node_index + 1; i < _size; i++) {
                    labels[i - 1] = _labels[i];
                    adj_matrix[i - 1] = new int[_size -1];
            }
        } catch (...) {
            #ifndef NDEBUG
            std::cout << "~ Error while trying to allocate memory" << std::endl;
            #endif
            _del();
            throw std::bad_alloc();
        }

        /**
         * / a b c d e f\n
         * a 0 1 0 1 0 0\n
         * b 0 0 0 1 0 1\n
         * c 0 1 0 0 0 0\n
         * d 1 0 0 1 1 0\n
         * e 0 0 1 0 0 0\n
         * f 1 0 0 0 0 1\n
         * 
         * We want to remove node c, thus:
         *   a b | d e f\n
         * a 0 1 | 1 0 0 ] -> First, we focus on the a,b matrix\n
         * b 0 0 | 1 0 1 ] -> Second, we fill the right part\n
         * \-\-\-\-\-\-\-\-\-\-\-\-\-\n
         * d 1 0 | 1 1 0 ] -> third, we focus on a,b and d,e,f\n
         * e 0 0 | 0 0 0 ] -> lastly, we fill everything else left\n
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
     * @param labelFrom The node the archs starts from
     * @param labelTo The node the archs ends to
     * @param value 1 if there is no arch between **labelFrom** and **labelTo**, 0 otherwise
     */
    void setArch(T labelFrom, T labelTo, int value) {
        int index_from = _node_index(labelFrom);
        int index_to = _node_index(labelTo);
        setCell(index_from, index_to, value);
    }

    /**
     * @brief Sets a matrix cell to a certain value, 0 or 1.
     * 
     * @param indexFrom Row position in the matrix
     * @param indexTo Column position in the matrix
     * @param value Value to insert, either 0 or 1
     */
    void setCell(int indexFrom, int indexTo, int value) {
        if (!_node_exists(indexFrom) || !_node_exists(indexTo))
            throw IndexOutOfBoundsException();
        if (!_is_node_value_valid(value))
            throw NodeValueNotValidException();
        _adj_matrix[indexFrom][indexTo] = value;
    }

    /**
     * @brief Gets the cell value from the matrix given its position. Either 0 or 1.
     * 
     * @param i Row position
     * @param j Column position
     * @return int The value held at i, j
     */
    int getArch(int i, int j) {
        if (!_node_exists(i) || !_node_exists(j))
            throw IndexOutOfBoundsException();
        return _adj_matrix[i][j];
    }

    /**
     * @brief Gets the cell value from the matrix given its starting node **labelFrom** and ending node **labelTo**. Either 0 or 1.
     * 
     * @param labelFrom The start node
     * @param labelTo The ending node
     * @return int The value held from the arch **labelFrom** and **labelTo**
     */
    int getArch(T labelFrom, T labelTo) {
        int indexFrom = _node_index(labelFrom);
        int indexTo = _node_index(labelTo);
        return getArch(indexFrom, indexTo);
    }

    /**
     * @brief Prints the matrix
     * 
     */
    void print() {
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) 
                std::cout << _adj_matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    /**
     * @brief Prints the labels
     * 
     */
    void print_labels() {
        for(int i = 0; i < _size; i++)
            std::cout << _labels[i] << " ";
        std::cout << std::endl;
    }

    /**
     * @brief Iterator used to iterate over the node elments of the matrix
     * 
     */
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
         * @param other the iterator instance to copy frm
         */
		const_iterator(const const_iterator &other) : ptr(other.ptr), position(other.position) {}

        /**
         * @brief Equals operator
         * 
         * @param other the instance to copy from
         * @return const_iterator& a pointer to the current instance with the updated position and pointer
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
		 * @brief Pointer operator
		 * 
		 * @return reference 
		 */
		reference operator*() const {
			return (*ptr)[position];
		}

		/**
		 * @brief Arrow operator
		 * 
		 * @return pointer 
		 */
		pointer operator->() const {
			return &((*ptr)[position]);
		}
		
		/**
		 * @brief Increment operator
		 * 
		 * @return const_iterator 
		 */
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			position++;
			return tmp;
		}

		/**
		 * @brief Increment operator
		 * 
		 * @return const_iterator& 
		 */
		const_iterator& operator++() {
			position++;
			return *this;
		}

		/**
		 * @brief Equals operator
		 * 
		 * @param other Other iterator to compare with
		 * @return true The iterators point to the same element
		 * @return false The iterators do not point to the same element
		 */
		bool operator==(const const_iterator &other) const {
			return (ptr == other.ptr) && (position == other.position);
		}
		
		/**
		 * @brief Inequality operator
		 * 
		 * @param other the instance to compare from
		 * @return true if the two instances are equal
		 * @return false if the two instances differ
		 */
		bool operator!=(const const_iterator &other) const {
			return !(*this == other);
		}


	private:
        /**
         * @brief A pointer to the graph object
         * 
         */
		const graph *ptr;
        /**
         * @brief The current iterator position within the graph object
         * 
         */
		int position;

        /**
         * @brief Friends class with graph
         * 
         */
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
	 * @brief Returns an iterator pointing at the start of the node list
	 * 
	 * @return const_iterator Pointer to the start of the list
	 */
	const_iterator begin() const {
		return const_iterator(this, 0);
	}
	
	/**
	 * @brief Returns an iterator pointing at the end of the node list
	 * 
	 * @return const_iterator Pointer to the end of the list
	 */
	const_iterator end() const {
		return const_iterator(this, _size);
	}

};

/**
 * @brief Stream operator for the graph
 * 
 * @tparam T the graph template
 * @tparam E the functor for T equality/inequality
 * @param os the stream
 * @param g the graph
 * @return std::ostream& a pointer to the stream
 */
template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, 
	const graph<T, E> &g) {

    typename graph<T, E>::const_iterator i, ie;
	for (i = g.begin(), ie = g.end(); i != ie; ++i)
		os << *i << " ";
	return os;
}

#endif