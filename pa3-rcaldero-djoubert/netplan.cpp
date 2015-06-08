#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "UndirectedGraph.hpp"

using namespace std;

/**
 * Entry point into the netplan program.
 *
 * -Reads a file from the filesystem according to the specification for
 *  PA3, creating an UndirectedGraph.
 * -Finds the total cost & ping time of the graph as presented in the input
 *  file.
 * -Determines the minimum cost graph from the original graph.
 * -Finds the total cost & ping time of the minimum cost graph.
 * -Finds the change of cost & ping time from the original graph to the
 *  minimum cost graph.
 * -Prints the results to stdout.
 *
 * Usage:
 *   ./netplan infile
 *
 */
int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
    return EXIT_FAILURE;
  }
    
  std::ifstream in(argv[1]);
  if (!in) {
    std::cerr << "Unable to open file for reading." << std::endl;
    return EXIT_FAILURE;
  }
    
  // Create empty graph
  UndirectedGraph * graph = new UndirectedGraph();

  string vertex0, vertex1;
  int cost, length;

  //read in single line to handle empty file
  in >> vertex0 >> vertex1 >> cost >> length;
  graph->addEdge(vertex0, vertex1, cost, length);

  // Read lines and add in edges and vertices
  while(in >> vertex0 >> vertex1 >> cost >> length){
    graph->addEdge(vertex0, vertex1, cost, length);
  }
    
  // Close file
  in.close();

  // STEP 1: Output total cost of edges in graph
  unsigned int graphTotalEdgeCost = graph->totalEdgeCost();
  cout << graphTotalEdgeCost << endl;

  //calculate totaledgecost while still non-MST, for step 6
  unsigned int graphTotalDistance = graph->totalDistance();

  // Find minimum spanning tree of graph
  graph->minSpanningTree();

  // Output total cost of edges in minimum spanning tree
  unsigned int mstTotalEdgeCost = graph->totalEdgeCost();
  cout << mstTotalEdgeCost << endl;

  // STEP 3: Output Difference in total cost of edges of graph and mst
  cout << graphTotalEdgeCost - mstTotalEdgeCost << endl;

  // STEP 4: Total Distance of original graph
  //unsigned int graphTotalDistance = graphCopy->totalDistance();
  cout << graphTotalDistance << endl;

  // Step 5: Total Distance of MST
  unsigned int mstTotalDistance = graph->totalDistance();
  cout << mstTotalDistance << endl;

  // Step 6: Increase in total time from regular graph to MST
  cout << mstTotalDistance - graphTotalDistance << endl;

  delete graph;
  return EXIT_SUCCESS;
}
