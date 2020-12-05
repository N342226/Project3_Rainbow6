#pragma once
#include "player.h"
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <tuple>
#include <iostream>
#include <set>

using namespace std;
class Graph {
private:
    priority_queue <pair<float, Edge*>> U; //<calculated rating, edge>
    unordered_set<Node*> K;

    priority_queue<pair<float, string>> createPyramid(string operatorName);

    vector<string> namesAlreadyChecked;
    vector<player> players;

    void checkDuplicateNameEdges(Node* from, Node* to);
public:
    Graph(vector<player> players, int team);
    void insertEdge(Node* from, Node* to, int weight);
    int getWeight(Node from, Node to);

    void primsDeviation();
    void balance();
};

Graph::Graph(vector<player> players, int team) { 
    this->players = players;

    if (team == 0) { //Defense
        unordered_map<string, Node*> operators;

        for (int i = 0; i < defenseOperatorSize; i++) {
            priority_queue<pair<float, string>> winRates = createPyramid(defenseOperators[i]);
            Node* operatorNode = new Node(winRates, defenseOperators[i]);
            operators[defenseOperators[i]] = operatorNode;
        }

        insertEdge(operators["Kapkan"], operators["Lesion"], 8);
        insertEdge(operators["Kapkan"], operators["Ela"], 8);
        insertEdge(operators["Kapkan"], operators["Frost"], 8);
        insertEdge(operators["Kapkan"], operators["Jager"], 8);

        insertEdge(operators["Jager"], operators["Tachanka"], 8);

        insertEdge(operators["Valk"], operators["Echo"], 8);
        insertEdge(operators["Valk"], operators["Maestro"], 8);

        insertEdge(operators["Maestro"], operators["Mozzie"], 8);

        insertEdge(operators["Mozzie"], operators["Mute"], 8);

        insertEdge(operators["Mute"], operators["Bandit"], 8);
        insertEdge(operators["Mute"], operators["Kaid"], 8);
    }
    else { //Attack

    }
}

void Graph::insertEdge(Node* from, Node* to, int weight) {
    Edge* edge = new Edge(from, to, weight);
    float calulatedRating = edge->calculateRating();
    U.push({ calulatedRating, edge });
}

priority_queue<pair<float, string>> Graph::createPyramid(string operatorName) {
    priority_queue<pair<float, string>> result;
    for (int j = 0; j < players.size(); j++) {
        result.push({ players[j].getOperatorWinRate(operatorName), players[j].getName() });
    }
    return result;
}

void Graph::checkDuplicateNameEdges(Node* from, Node* to) {
    if (from->getSize().second == to->getSize().second) { //if two nodes connected are owned by the same player
        if (K.find(from) != K.end()) {
            cout << "resize to: adjacent player names and from is in K" << endl;
            to->resizeNode();
        }
        else if (K.find(to) != K.end()) {
            cout << "resize from: adjacent player names and to is in K" << endl;
            from->resizeNode();
        }
        else if (from->getSize().first > to->getSize().first) {
            cout << "resize to: adjacent player names, from nor to are in K, from > to" << endl;
            to->resizeNode();
        }
        else if (from->getSize().first < to->getSize().first) {
            cout << "resize to: adjacent player names, from nor to are in K, from < to" << endl;
            from->resizeNode();
        }
    }
}

void Graph::balance() {
    priority_queue <pair<float, Edge*>> temp;

    while (!U.empty()) {
        Edge* edge = U.top().second;
        Node* from = edge->getFrom();
        Node* to = edge->getTo();
        checkDuplicateNameEdges(from, to);

        for (int i = 0; i < namesAlreadyChecked.size(); i++) {

            bool changed = false;

            if (namesAlreadyChecked[i] == from->getSize().second && find(K.begin(), K.end(), from) == K.end()) {
                cout << "resize from: found in names already checked and not in K" << endl;
                from->resizeNode();
                changed = true;
            }

            if (namesAlreadyChecked[i] == to->getSize().second && find(K.begin(), K.end(), to) == K.end()) {
                cout << "resize to: found in names already checked and not in K" << endl;
                to->resizeNode();
                changed = true;
            }

            if (changed) {
                checkDuplicateNameEdges(from, to);
                i = -1;
            }
        }
        temp.push(U.top());
        U.pop();
    }
    U = temp;

    priority_queue <pair<float, Edge*>> temp2;
    while (!U.empty()) {
        pair<float, Edge*> topEdge = U.top();
        topEdge.first = topEdge.second->calculateRating();

        U.pop();
        temp2.push(topEdge);
    }
    U = temp2;
}

void Graph::primsDeviation() {
    cout << endl << "-----------" << endl;
    while (K.size() < 5) {
        if (K.size() == 4) {
            cout << "---Last Insertion---" << endl;
            priority_queue <pair<float, Edge*>> temp;
            while (!U.empty()) {
                cout << U.top().second->getFrom()->getOperatorName() << " -> " << U.top().second->getTo()->getOperatorName() << endl;
                if (K.find(U.top().second->getFrom()) != K.end() || K.find(U.top().second->getTo()) != K.end()) { //if the from or to node is found in list of added nodes
                    cout << "possible edge" << endl;
                    temp.push(U.top());
                }
                U.pop();
            }
            U = temp;
        }
        pair<float, Edge*> largestEdge = U.top();
        string fromPlayer = largestEdge.second->getFrom()->getSize().second;
        string toPlayer = largestEdge.second->getTo()->getSize().second;
        cout << endl <<fromPlayer << " -> " << toPlayer << endl;
        namesAlreadyChecked.push_back(fromPlayer);
        namesAlreadyChecked.push_back(toPlayer);

        cout << "Edge pushed: " << largestEdge.second->getFrom()->getOperatorName() << " -> " << largestEdge.second->getTo()->getOperatorName() << endl << endl;

        K.insert(largestEdge.second->getFrom());
        K.insert(largestEdge.second->getTo());

        U.pop();
        if (K.size() < 4) {
            balance();
        }
    }

    for(auto it : K){
        cout << it->getSize().second << ": "<< it->getOperatorName() << endl;
    }
    cout << endl << "-----------" << endl << endl;
}