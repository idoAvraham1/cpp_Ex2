//written by Ido Avraham : 208699181
//EMAIL: idoavraham086@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "GraphProperties.hpp"
#include <cstddef>
#include <limits>
#include <iostream>
#include <stdexcept>

/**
 * A class to represent a graph with adjacency matrix
 */

namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        size_t numVertices;
        size_t numEdges;
        GraphType graphType;
        EdgeType edgeType;
        EdgeNegativity edgeNegativity;

        void clearGraph() ;
        [[nodiscard]] static bool isValidGraph(const std::vector<std::vector<int>>& adjacencyMatrix) ;
        [[nodiscard]] static bool isSymmetricMatrix(const std::vector<std::vector<int>>& matrix) ;

    public:
        Graph();
        Graph(const Graph& other);
        void setWeight(int weight , size_t i , size_t j){
            adjacencyMatrix[i][j]=weight;
        }

        // graph methods
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        [[nodiscard]] bool contains(const Graph& other) const;
        [[nodiscard]] bool isEmpty() const;

        // getters
        [[nodiscard]] size_t V() const;
        [[nodiscard]] GraphType getGraphType() const;
        [[nodiscard]] EdgeType getEdgeType() const;
        [[nodiscard]] EdgeNegativity getEdgeNegativity() const;
        [[nodiscard]] int getEdgeWeight(size_t u, size_t v) const;
        [[nodiscard]] Graph getReversedGraph() const;
        [[nodiscard]] Graph addVertexWithEdges() const;

        // arithmetic operators
        // +
        Graph operator+(const Graph& other) const; // binary
        Graph& operator+(); // unary +
        Graph& operator+=(const Graph& other);

        // assigment operator
        Graph& operator=(const Graph& other);

        //-
        Graph operator-(const Graph& other) const; // binary +
        Graph& operator-(); // unary +
        Graph& operator-=(const Graph& other);

        // comparing operators
        bool operator==(const Graph& other) const;
        bool operator!=(const Graph& other) const;

        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;

        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;

        //multiply operators
        Graph operator*(int scalar) const;
        Graph& operator*=(int scalar);

        Graph operator*(Graph& other) const;
        Graph& operator*=(Graph& other);

        // inc and dec operators
        Graph& operator--() ; // prefix
        Graph& operator++() ; // prefix
        Graph operator++(int); // postfix
        Graph operator--(int); // postfix

        // print the graph in a matrix form
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);



    };
}

#endif // GRAPH_HPP