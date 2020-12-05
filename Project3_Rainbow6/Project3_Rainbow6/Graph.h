#pragma once
#include "player.h"
#include "Node.h"
#include <vector>
#include <tuple>

using namespace std;
class Graph {
private:
    vector <tuple<Node, Node, int>> U; //<from, to, weight>
public:
    Graph(player players[], int numOfPlayers);
    void insertEdge(Node from, Node to, int weight);
    int getWeight(Node from, Node to);
};

Graph::Graph(player players[], int numOfPlayers) { 
    for (int i = 0; i < operatorsSize; i++) {
        string operatorName = operators[i];
        if (operatorName == "Zero") {
            priority_queue<pair<float, string>> ZeroWinRates;
            priority_queue<pair<float, string>> AceWinRates;
            for (int j = 0; j < numOfPlayers; j++) {
                ZeroWinRates.push({ players[j].getOperatorWinRate(operatorName), operatorName });
            }
            for (int j = 0; j < numOfPlayers; j++) {
                AceWinRates.push({ players[j].getOperatorWinRate(operatorName), operatorName });
            }
            Node from = Node(ZeroWinRates);
            Node to1 = Node(AceWinRates);

            insertEdge(from, to1, 2);
        }
    }
}