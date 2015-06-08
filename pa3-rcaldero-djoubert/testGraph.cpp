#include "UndirectedGraph.cpp"
#include "Vertex.hpp"
#include <string>
#include <iostream>

using namespace std;

int main() {
    cout << "--------------GRAPHTESTERFILE-----------------" << endl;

    cout << "CREATING GRAPH" << endl;
    UndirectedGraph testG = UndirectedGraph();

    cout << "ADDING EDGE WITHOUT ANY VERTICES EXISTING" << endl;
    testG.addEdge("Yahoo","Google",13,13);

    cout << "total edge cost: ";
    cout << testG.totalEdgeCost() << endl;

    cout << "ADDING DUPLICATE" << endl;
    testG.addEdge("Yahoo","Google",9,9);

    cout << "total edge cost: ";
    cout << testG.totalEdgeCost() << endl;

    cout << "ADDING REVERSED DUPLICATE" << endl;
    testG.addEdge("Google","Yahoo",7,7);

    cout << "total edge cost: ";
    cout << testG.totalEdgeCost() << endl;    

    cout << "ADDING EDGE" << endl;
    testG.addEdge("Yahoo","Microsoft",71,71);
    cout << "total edge cost: ";    
    cout << testG.totalEdgeCost() << endl;

    cout << "ADDING UNCONNECTED EDGE" << endl;
    testG.addEdge("Netflix","Yelp",21,21);
    cout << "total edge cost: ";    
    cout << testG.totalEdgeCost() << endl;

    cout << "SETTING UP NON-MST" << endl;
    testG.addEdge("Google","Yahoo",2,2);
    testG.addEdge("Yahoo","Microsoft",3,3);
    testG.addEdge("Microsoft","Netflix",5,5);
    testG.addEdge("Netflix","Yelp",7,7);
    testG.addEdge("Yelp","Google",11,11);
    testG.addEdge("Netflix","Google",13,13);
    testG.addEdge("Google","Microsoft",17,17);

    cout << "total edge cost: ";    
    cout << testG.totalEdgeCost() << endl;

    cout << "CREATING MST" << endl;
    testG.minSpanningTree();
    cout << "total edge cost: ";        
    cout << testG.totalEdgeCost() << endl;

    cout << "TEST TOTAL DISTANCE" << endl;
    cout << "total distance: ";
    cout << testG.totalDistance("Google") << endl;

    cout << "TEST TOTAL DISTANCE NEW GRAPH" << endl;
    UndirectedGraph graphTwo = UndirectedGraph();
    graphTwo.addEdge("Google","Yahoo",2,2);
    graphTwo.addEdge("Yahoo","Microsoft",3,3);    
    cout << graphTwo.totalDistance("Google") << endl;
    cout << graphTwo.totalDistance("Yahoo") << endl;
    cout << graphTwo.totalDistance("Microsoft") << endl;
    cout << graphTwo.totalDistance() << endl;

    return 1;
}
