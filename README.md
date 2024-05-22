# Graph Operator Overloading Project

**Written by Ido Avraham: 208699181**  
**Email: idoavraham086@gmail.com**

## Project Purpose
The purpose of this project is to implement various graph operators using an adjacency matrix representation. The operators included in this project are:

- `-`: Graph subtraction and unary minus
- `+`: Graph addition and unary plus
- `*`: Graph multiplication and scalar multiplication
- `--`: Decrement each edge in the matrix
- `++`: Increment each edge in the matrix
- Comparison operators: `<`, `<=`, `>`, `>=`, `==`, `!=`

## Graph Representation and Properties
The graph is represented using an adjacency matrix, where an entry `[i][j]` represents the weight of the edge between vertex `i` and vertex `j`. A weight of zero indicates the absence of an edge.

Three main properties of the graph are determined from the adjacency matrix:

- **GraphType**: Directed or Undirected. An undirected graph has a symmetric adjacency matrix.
- **EdgeType**: Weighted or Unweighted. If all entries in the adjacency matrix have a weight of 1, the graph is considered unweighted.
- **EdgeNegativity**: Negative or None. If at least one entry in the adjacency matrix has a negative weight, the graph has negative edges; otherwise, it has none.

## Project Structure
The project consists of seven main classes and one header file for graph properties enumeration. These classes are:

- **Graph**: Represents a graph with an adjacency matrix.
- **Algorithms**: Provides methods for invoking various algorithms.
- **GraphProperties**: Header file defining enums for graph properties.

Additionally, there are separate classes for each algorithm: `ShortestPath`, `DetectNegativeCycle`, `isContainsCycle`, `isBipartite`, and `isConnected`. The decision to divide the `Algorithms` class into separate classes for each algorithm adheres to Object-Oriented Programming (OOP) principles. Each class has a single responsibility, promoting code modularity and adhering to the Open-Closed principle. This design allows for easy extension by adding new algorithm classes without modifying existing code.

## Detailed Description of the Operators
Here's a brief overview of the main operators:

- **+ / - (binary)**: Adds or subtracts each edge of this graph with another graph. This may create or delete edges.
- **+ / - (unary)**: Unary plus or minus operators to increment or decrement each edge by 1.
- **++ / --**: Prefix and postfix increment and decrement operators, performing the operation on each existing edge.
- **< / <= / > / >=**: 
  - `g1 < g2`: `g1` contains `g2` and `g2` does not contain `g1`. If neither contains the other, then `g1 > g2` if `g1` has more edges, or if edges are equal, `g1 > g2` if `g1` has more vertices.
  - `==`: `g1` is equal to `g2` if they have the same number of vertices and exactly the same edges.
  - `!=`: `g1` is not equal to `g2`.

## Usage
 in terminal use the command : " make runtests" to execute the tests
                               " make run" to execute the demo program 
                               
---


