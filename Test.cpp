#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Graph subtraction"){
    // test the binary "-"
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 - g2;

    vector<vector<int>> expectedGraph = {
            {0, 0, -1},
            {0, 0, 0},
            {-1, 0, 0}};
    CHECK(g3.printGraph() == "[0, 0, -1]\n[0, 0, 0]\n[-1, 0, 0]");

    // test the "-="
    g1-=g2;
    CHECK(g1.printGraph() == "[0, 0, -1]\n[0, 0, 0]\n[-1, 0, 0]");
}

TEST_CASE("Increment and Decrement"){

    // test prefix --
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 2},
            {1, 0, 3},
            {2, 3, 0}};
    g.loadGraph(graph);

    ariel::Graph g2= --g;
    CHECK(g2.printGraph() == "[0, 0, 1]\n[0, 0, 2]\n[1, 2, 0]");
    CHECK(g.printGraph() == "[0, 0, 1]\n[0, 0, 2]\n[1, 2, 0]");

    //test prefix ++
    ariel::Graph g3 = ++g;
    CHECK(g3.printGraph() == "[0, 0, 2]\n[0, 0, 3]\n[2, 3, 0]");
    CHECK(g.printGraph() == "[0, 0, 2]\n[0, 0, 3]\n[2, 3, 0]");

    // test postfix --
    ariel::Graph g4 = g--;
    CHECK(g3.printGraph() == "[0, 0, 2]\n[0, 0, 3]\n[2, 3, 0]");
    CHECK(g.printGraph() == "[0, 0, 1]\n[0, 0, 2]\n[1, 2, 0]");


    // test postfix ++
    ariel::Graph g5 = g++;
    CHECK(g3.printGraph() == "[0, 0, 2]\n[0, 0, 3]\n[2, 3, 0]");
    CHECK(g.printGraph() == "[0, 0, 2]\n[0, 0, 3]\n[2, 3, 0]");

}

TEST_CASE("Test graph comparison and relational operators") {
    // Test == and !=
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
            {0, 1, 2},
            {1, 0, 3},
            {2, 3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
            {0, 1, 2},
            {1, 0, 3},
            {2, 3, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);
    CHECK_FALSE(g1 != g2);

    // Test g1 < g2 and g1 > g2
    vector<vector<int>> graph3 = {   // g1 contains g2
            {0, 1},
            {1, 0}};
    g2.loadGraph(graph3);

    CHECK_FALSE(g1 < g2);
    CHECK(g2 < g1);
    CHECK(g1 > g2);
    CHECK_FALSE(g2 > g1);

    // Test g1 <= g2 and g1 >= g2
    CHECK_FALSE(g1 <= g2);
    CHECK(g2 <= g1);

    CHECK(g1 >= g2);
    CHECK_FALSE(g2 >= g1);

    // g1 don't contain g1 and g2 don't contain g1, g1 has more edges
    vector<vector<int>> graph6 = {
            {0, 0, 2},
            {0, 0, 3},
            {2, 3, 0}};
    g1.loadGraph(graph6);
    vector<vector<int>> graph7 = {
            {0, 1},
            {1, 0}};
    g2.loadGraph(graph7);
    CHECK(g2 < g1) ;
    CHECK(g2 <= g1);
    CHECK(g1 > g2);
    CHECK(g1 >= g2);

    // g1 don't contain g1 and g2 don't contain g1, the same amount of edges, g1 has more vertices
    vector<vector<int>> graph8 = {
            {0, 0, 0},
            {0, 0, 0},
            {2, 3, 0}};
    g1.loadGraph(graph8);
    vector<vector<int>> graph9 = {
            {0, 1},
            {1, 0}};
    g2.loadGraph(graph9);
     CHECK(g1 > g2);

}

TEST_CASE("unary operator"){
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
            {0, 1, 2},
            {1, 0, 3},
            {2, 3, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2= -g1;
    ariel::Graph g3= +g1;
    g1=-g1;


    CHECK(g3.printGraph() == "[0, -1, -2]\n[-1, 0, -3]\n[-2, -3, 0]");
    CHECK(g1.printGraph()=="[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");
    CHECK(g3==g2);


}

TEST_CASE("Test graph addition")
{
    // test binary +
    ariel::Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    // test the +=
    g1+=g2;
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");


}

TEST_CASE("Test graph multiplication")
{
    // test the binary * (graph)
    ariel::Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
            {0, 0, 2},
            {1, 0, 1},
            {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");

    // test the *= (graph)
    ariel::Graph g3;
    vector<vector<int>> graph3 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g3.loadGraph(graph3);

    g3 *= g2;

    vector<vector<int>> expectedGraph2 = {
            {0, 0, 2},
            {1, 0, 1},
            {1, 0, 0}};

    CHECK(g3.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");

    //test the  *= (scalar)
    vector<vector<int>> graph5 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g3.loadGraph(graph5);
    g3 *= 2;
    vector<vector<int>> expectedGraph5 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
    CHECK(g3.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    // test the binary * (scalar)
    ariel::Graph g5=g3*-1;
    vector<vector<int>> expectedGraph6 = {
            {0, -2, 0},
            {-2, 0, -2},
            {0, -2, 0}};
    CHECK(g5.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1, 1},
            {1, 0, 2, 1},
            {1, 2, 0, 1},
            {0, 1, 1, 0},
    };
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);

    // subtraction of two graphs with different dimensions
    CHECK_THROWS(g1-g6);
}