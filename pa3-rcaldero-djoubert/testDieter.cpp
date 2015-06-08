#include "UndirectedGraph.hpp"
#include "Vertex.cpp"
#include <string>
#include <iostream>

using namespace std;

int main() {
    cout << "--------------TESTERFILE-----------------" << endl;
    UndirectedGraph testG1 = UndirectedGraph();
    Vertex* testV1 = new Vertex("Google");
    cout << "Name of first vertex: ";    
    cout << testV1->getName() << endl;

    testV1->setDistance(200);
    cout << "Distance of first vertex: ";
    cout << testV1->getDistance() << endl;

    cout << "Default wasVisited bool: ";
    cout << testV1->wasVisited() << endl;
    cout << "Was visited after being set: ";
    testV1->setVisited(true);
    cout << testV1->wasVisited() << endl;

    Vertex* testV2 = new Vertex("Yahoo");
    testV2->addEdge(testV1, 2, 5);

    cout << "Total edge cost of first vertex: ";
    cout << testV1->totalEdgeCost() << endl;
    cout << "Total edge cost of second vertex: ";
    cout << testV2->totalEdgeCost() << endl;

    Vertex* testV3 = new Vertex("Microsoft");

    cout << "ADDING NEW EDGES" << endl;
    testV3->addEdge(testV1, 13, 10);
    testV3->addEdge(testV2, 7, 15);

    cout << "PRINTING OUT TOTAL EDGE COSTS" << endl;
    cout << testV1->getName() + ": ";   
    cout << testV1->totalEdgeCost() << endl;
    cout << testV2->getName()  + ": ";    
    cout << testV2->totalEdgeCost() << endl;  
    cout << testV3->getName() + ": ";   
    cout << testV3->totalEdgeCost() << endl;

    cout << "ADDING PRE-EXISTING EDGE" << endl;
    testV3->addEdge(testV1, 200, 25);
    cout << testV1->getName() + ": ";   
    cout << testV1->totalEdgeCost() << endl;
    cout << testV2->getName()  + ": ";    
    cout << testV2->totalEdgeCost() << endl;  
    cout << testV3->getName() + ": ";   
    cout << testV3->totalEdgeCost() << endl;

    cout << "CLEARING ALL EDGES, SHOULD PRINT ALL ZEROES" << endl;
    testV3->clearEdges();
    testV1->clearEdges();
    testV2->clearEdges();
    cout << testV1->totalEdgeCost() << endl;
    cout << testV2->totalEdgeCost() << endl;
    cout << testV3->totalEdgeCost() << endl;

    //testG.addEdge(std::string("Google"),std::string("Yahoo"),4,10);    

    return 1;
}