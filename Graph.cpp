//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#include <ntdef.h>
#include "Graph.hpp"
namespace ariel {

    /**
    * Constructs an empty graph with default attributes.
    */
    Graph::Graph() : numVertices(0), numEdges(0), graphType(GraphType::UNDIRECTED),
                     edgeType(EdgeType::UNWEIGHTED), edgeNegativity(EdgeNegativity::NONE) {}

    // Copy constructor
    Graph::Graph(const Graph& other) {
        this->numVertices = other.numVertices;
        this->numEdges = other.numEdges;
        this->graphType = other.graphType;
        this->edgeType = other.edgeType;
        this->edgeNegativity = other.edgeNegativity;
        this->adjacencyMatrix = other.adjacencyMatrix; // Deep copy of the adjacency matrix
    }


    /**
    * Loads a graph from an adjacency matrix, setting properties such as number of vertices, number of edges,
    * graph type, edge type, and edge negativity based on the loaded data.
    * @param matrix The adjacency matrix representing the graph.
    * @throws std::invalid_argument if the matrix is not square.
     */
    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
        if (!isValidGraph(matrix)) {
            throw std::invalid_argument("Invalid graph: Graph is not valid.");
        }

        clearGraph();

        this->numVertices = matrix.size();
        this->adjacencyMatrix = matrix;
        this->numEdges = 0;

        // Count edges and check for weighted and negative edges
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    this->numEdges++;
                    if (adjacencyMatrix[i][j] != 1) {
                        this->edgeType = EdgeType::WEIGHTED;
                        if (adjacencyMatrix[i][j] < 0) {
                            this->edgeNegativity = EdgeNegativity::NEGATIVE;
                        }
                    }
                }
            }
        }

        // Check if the graph is directed
        if (!isSymmetricMatrix(matrix)) {
            this->graphType = GraphType::DIRECTED;
        }
    }



    /**
     * Clears the graph data, resetting it to an empty state.
     */
    void Graph::clearGraph() {
        this->numVertices = 0;
        this->numEdges = 0;
        this->adjacencyMatrix.clear();
        this->graphType = GraphType::UNDIRECTED;
        this->edgeType = EdgeType::UNWEIGHTED;
        this->edgeNegativity = EdgeNegativity::NONE;
    }

    bool Graph::isValidGraph(const std::vector<std::vector<int>>& adjacencyMatrix) {
        for(const auto& row : adjacencyMatrix) {
            if (row.size() != adjacencyMatrix.size()) {
                return false;
            }
        }
        return true;
    }

    bool Graph::isSymmetricMatrix(const std::vector<std::vector<int>>& matrix) {
        size_t n = matrix.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    std::string Graph::printGraph() const {
        std::string ans;
        for (size_t i=0; i<numVertices; i++) {
            ans += "[";
            for (size_t j = 0; j <numVertices; ++j) {
                ans += std::to_string(adjacencyMatrix[i][j]);
                if (j < numVertices - 1)
                    ans += ", ";
            }
            ans += "]";
            if (i < numVertices - 1) {
                ans += "\n";
            }
        }
        return ans;
    }

    
    GraphType Graph::getGraphType() const {
        return graphType;
    }

    EdgeType Graph::getEdgeType() const {
        return edgeType;
    }

    EdgeNegativity Graph::getEdgeNegativity() const {
        return edgeNegativity;
    }

    size_t Graph::V() const {
        return numVertices;
    }

    int Graph::getEdgeWeight(size_t u, size_t v) const {
        return adjacencyMatrix[u][v];
    }

    Graph Graph::getReversedGraph() const {
        // Create a new graph
        Graph reversedGraph;

        // Reverse the adjacency matrix
        std::vector<std::vector<int>> reversedAdjacencyMatrix(numVertices, std::vector<int>(numVertices, 0));

        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    reversedAdjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                }
            }
        }

        // Load the reversed adjacency matrix into the reversed graph
        reversedGraph.loadGraph(reversedAdjacencyMatrix);

        return reversedGraph;
    }

    /**
     * @brief Adds a new vertex to the graph with outgoing edges to existing vertices.
     *
     * This method creates a new graph with an additional vertex compared to the original graph.
     * Outgoing edges are added from the new vertex to each existing vertex in the original graph.
     *
     * @return A new graph with the added vertex and outgoing edges.
       */
    Graph Graph::addVertexWithEdges() const {
        // Create a new graph
        Graph modifiedGraph;

        // Increase the size of the adjacency matrix to accommodate the new vertex
        size_t newSize = numVertices + 1;
        std::vector<std::vector<int>> modifiedAdjacencyMatrix(newSize, std::vector<int>(newSize, 0));

        // Copy existing adjacency matrix to modified adjacency matrix
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                modifiedAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
            }
        }

        // assign max value possible for each new outgoing edge
        int outgoingEdgeWeight = MAX_WEIGHT;

        // For directed graphs, add outgoing edges from the new vertex to each existing vertex
        for (size_t i = 0; i < numVertices; ++i) {
            modifiedAdjacencyMatrix[newSize - 1][i] = outgoingEdgeWeight;
        }

        // For undirected graphs, connect the new vertex to every existing vertex
        if (graphType == GraphType::UNDIRECTED) {
            for (size_t i = 0; i < numVertices; ++i) {
                modifiedAdjacencyMatrix[i][newSize - 1] = outgoingEdgeWeight;
            }
        }

        // Set the weight of the self-loop of the new vertex to 0
        modifiedAdjacencyMatrix[newSize - 1][newSize - 1] = 0;

        // Load the modified adjacency matrix into the modified graph
        modifiedGraph.loadGraph(modifiedAdjacencyMatrix);

        return modifiedGraph;
    }


    bool Graph::isEmpty() const {
        return numVertices<=0;
    }

    // returns true if "this" contains the other graphs
    bool Graph::contains(const Graph& other) const {
        if(other.numVertices > this->numVertices)
            return false;

        for(size_t i=0; i<other.numVertices; i++){
            for(size_t j=0; j<other.numVertices; j++){
                if( other.adjacencyMatrix[i][j] != 0 && this->adjacencyMatrix[i][j]
                        != other.adjacencyMatrix[i][j] )
                        return false;
            }
        }
        return true;
    }


    // assignment operator
    Graph& Graph::operator=(const Graph& other) {
        if (this != &other) { // Avoid self-assignment
            // Copy other attributes
            this->numVertices = other.numVertices;
            this->numEdges = other.numEdges;
            this->graphType = other.graphType;
            this->edgeType = other.edgeType;
            this->edgeNegativity = other.edgeNegativity;

            // Deep copy of the adjacency matrix
            this->adjacencyMatrix = other.adjacencyMatrix;
        }
        return *this;
    }

    // arithmetic operators
    // +
    Graph Graph::operator+(const Graph &other) const {
        // Check if the graphs have different dimensions
        if( this->numVertices != other.numVertices || adjacencyMatrix.size() != other.adjacencyMatrix.size())
                 throw std::invalid_argument("Graphs have different dimensions");

        // new adjacency matrix to apply changes may occur in the graph
         std::vector<std::vector<int>> resAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                // add corresponding elements of the adjacency matrices
                resAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }
        Graph result;
        result.loadGraph(resAdjacencyMatrix);
        return result;


    }

    Graph& Graph::operator+=(const Graph &other)  {
        // Check if the graphs have different dimensions
        if (numVertices != other.numVertices || adjacencyMatrix.size() != other.adjacencyMatrix.size()) {
            throw std::invalid_argument("Graphs have different dimensions");
        }
        // new adjacency matrix to apply changes may occur in the graph
        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                // add corresponding elements of the adjacency matrices
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }
        this->loadGraph(newAdjacencyMatrix);
        return *this; // Return a reference to the modified object
    }
    // -
    Graph Graph::operator-(const Graph &other) const {
             // Check if the graphs have different dimensions
             if( this->numVertices != other.numVertices || adjacencyMatrix.size() != other.adjacencyMatrix.size())
                 throw std::invalid_argument("Graphs have different dimensions");

             // new adjacency matrix to apply changes may occur in the graph
             std::vector<std::vector<int>> resAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

             for (size_t i = 0; i < numVertices; ++i) {
                 for (size_t j = 0; j < numVertices; ++j) {
                     // Subtract corresponding elements of the adjacency matrices
                     resAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
                 }
             }
             Graph result;
             result.loadGraph(resAdjacencyMatrix);
             return result;


         }

    Graph& Graph::operator-=(const Graph &other)  {
        if (numVertices != other.numVertices || adjacencyMatrix.size() != other.adjacencyMatrix.size()) {
            throw std::invalid_argument("Graphs have different dimensions");
        }

        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                // Subtract corresponding elements of the adjacency matrices
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
        }
        this->loadGraph(newAdjacencyMatrix);
        return *this; // Return a reference to the modified object
    }

    //comparing operators
    bool Graph::operator==(const Graph &other) const {
        if (numVertices != other.numVertices || adjacencyMatrix.size() != other.adjacencyMatrix.size()
                 || numEdges != other.numEdges)
            return false;

        for(size_t i=0; i<numVertices;i++){
            for(size_t j=0; j<numVertices; j++){
                if( adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j])
                    return false;
            }
        }
        return true;
    }

    bool Graph::operator!=(const Graph &other) const {
        return !(*this == other);
    }

    bool Graph::operator<(const Graph &other) const {
        return other > *this;
    }

    bool Graph::operator<=(const Graph &other) const {
        return other > *this || other == *this;
    }

    bool Graph::operator>(const Graph &other) const {
        // If the graphs are equal, return false
        if (*this == other) {
            return false;
        }

        // If this graph contains the other graph, return true
        if (this->contains(other)) {
            return true;
        }

        // If the other graph contains this graph, return false
        if (other.contains(*this)) {
            return false;
        }

        // If the other graph has more edges, return false
        if (this->numEdges < other.numEdges) {
            return false;
        }

        // If the other graph has fewer edges, return true
        if (this->numEdges > other.numEdges) {
            return true;
        }

        // If they have the same number of edges, compare vertices
        // If the other graph has more vertices, return false
        if (other.numVertices > this->numVertices) {
            return false;
        }

        // If the other graph has fewer vertices, return true
        if (other.numVertices < this->numVertices) {
            return true;
        }

        // If they have the same number of vertices, return false
        return false;
    }


    bool Graph::operator>=(const Graph &other) const {
        return *this > other || *this == other;
    }

    // multiplication operators
    // matrix multiply
    Graph Graph::operator*(Graph &other) const {

        // check for a valid input
        if (adjacencyMatrix[0].size() != other.adjacencyMatrix.size()) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

       std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        // matrix multiply
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                int sum = 0;
                for (size_t k = 0; k < numVertices; ++k) {
                    sum += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
                newAdjacencyMatrix[i][j] = sum;
            }
        }
        // zero the diagonal elements
        for(size_t i = 0; i < numVertices; ++i)
            newAdjacencyMatrix[i][i]=0;

        Graph result;
        result.loadGraph(newAdjacencyMatrix);
        return result;
    }

    Graph& Graph::operator*=(Graph& other)  {
        // check for a valid input
        if (adjacencyMatrix.size() != other.adjacencyMatrix[0].size()) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        // matrix multiply
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                int sum = 0;
                for (size_t k = 0; k < numVertices; ++k) {
                    sum += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
                newAdjacencyMatrix[i][j] = sum;
            }
        }

        // zero the diagonal elements
        for(size_t i = 0; i < numVertices; ++i)
            newAdjacencyMatrix[i][i]=0;

        this->loadGraph(newAdjacencyMatrix);
        return *this;
    }

    // scalar multiply
    Graph Graph::operator*(int scalar) const {
        if(this->isEmpty())
            throw std::invalid_argument("Graph is empty");


        std::vector<std::vector<int>> resAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                resAdjacencyMatrix[i][j] = adjacencyMatrix[i][j]* scalar;
            }
        }
        Graph result;
        result.loadGraph(resAdjacencyMatrix);
        return result;

    }

    Graph& Graph::operator*=(int scalar) {
        if( this->isEmpty())
            throw std::invalid_argument("Graph is empty");


        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j]*scalar;
            }
        }
        this->loadGraph(newAdjacencyMatrix);
        return *this; // Return a reference to the modified object
    }

    // dec and inc operators
    Graph& Graph::operator--()  {
        if( this->isEmpty())
            throw std::invalid_argument("Graph is empty");

        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        // Decrement every entry in the adjacency matrix
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if( adjacencyMatrix[i][j] != 0 )
                    newAdjacencyMatrix[i][j]= adjacencyMatrix[i][j]-1;
                else
                    newAdjacencyMatrix[i][j]=0;
            }
        }
        this->loadGraph(newAdjacencyMatrix);
        return *this; // Return a reference to the modified object
    }

    Graph& Graph::operator++()  {
        if( this->isEmpty())
            throw std::invalid_argument("Graph is empty");

        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        // Increment every entry in the adjacency matrix
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if( adjacencyMatrix[i][j] != 0 )
                    newAdjacencyMatrix[i][j]= adjacencyMatrix[i][j]+1;
                else
                    newAdjacencyMatrix[i][j]=0;
            }
        }
        this->loadGraph(newAdjacencyMatrix);
        return *this; // Return a reference to the modified object
    }

    Graph Graph::operator--(int)  {
        if( this->isEmpty())
            throw std::invalid_argument("Graph is empty");

        // Make a copy of the current object
        Graph result(*this);

        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        // Decrement every entry in the adjacency matrix of the current object
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if( adjacencyMatrix[i][j] != 0 )
                     newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j]-1;
                else
                    adjacencyMatrix[i][j]=0;
            }
        }
        // Return the copy of the original object before the decrement
        this->loadGraph(newAdjacencyMatrix);
        return result;
    }

    Graph Graph::operator++(int)  {
        if( this->isEmpty())
            throw std::invalid_argument("Graph is empty");

        // Make a copy of the current object
        Graph result(*this);

        std::vector<std::vector<int>> newAdjacencyMatrix(numVertices, std::vector<int>(numVertices));

        // Decrement every entry in the adjacency matrix of the current object
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if( adjacencyMatrix[i][j] != 0 )
                    newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j]+1;
                else
                    adjacencyMatrix[i][j]=0;
            }
        }
        // Return the copy of the original object before the decrement
        this->loadGraph(newAdjacencyMatrix);
        return result;
    }

    // unary operators
    Graph& Graph::operator+()  {
        if( this->isEmpty())
            throw std::invalid_argument("Graph is empty");

        return *this;
    }

    Graph& Graph::operator-()  {
         if( this->isEmpty())
             throw std::invalid_argument("Graph is empty");
        return *this *=-1;
    }

    // stream of the Graph
    std::ostream &operator<<(std::ostream &os, const Graph &graph) {
        for (size_t i = 0; i < graph.numVertices; ++i) {
            os << "[";
            for (size_t j = 0; j < graph.numVertices; ++j) {
                os << graph.adjacencyMatrix[i][j];
                if (j < graph.numVertices - 1) {
                    os << ", ";
                }
            }
            os << "]" << std::endl;
        }
        return os;
    }




} // namespace ariel