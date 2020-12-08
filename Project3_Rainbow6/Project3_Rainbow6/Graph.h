#pragma once
#include "player.h"
#include "Node.h"
#include "Edge.h"
#include "WeightedEdges.h"
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
    vector<Edge> edges;

    void checkDuplicateNameEdges(Node* from, Node* to);
public:
    Graph(vector<player> players, int team);
    void insertEdge(Node* from, Node* to, int weight);
    float getWeight(Node from, Node to);
    vector<Edge> getEdges();

    unordered_set<Node*> kruskalDeviation(int& numSynergies, float& score);
    void bruteForce();
    void balance();
};

Graph::Graph(vector<player> players, int team) { 
    WeightedEdges edges = WeightedEdges(players, team);

    for (int i = 0; i < edges.edges.size(); i++) {
        float calulatedRating = edges.edges[i]->calculateRating();
        U.push({ calulatedRating, edges.edges[i] });
    }
}

void Graph::checkDuplicateNameEdges(Node* from, Node* to) {
    if (from->getSize().second == to->getSize().second) { //if two nodes connected are owned by the same player
        if (K.find(from) != K.end()) {
            //cout << "resize to: adjacent player names and from is in K" << endl;
            to->resizeNode();
        }
        else if (K.find(to) != K.end()) {
            //cout << "resize from: adjacent player names and to is in K" << endl;
            from->resizeNode();
        }
        else if (from->getSize().first > to->getSize().first) {
            //cout << "resize to: adjacent player names, from nor to are in K, from > to" << endl;
            to->resizeNode();
        }
        else if (from->getSize().first < to->getSize().first) {
            //cout << "resize to: adjacent player names, from nor to are in K, from < to" << endl;
            from->resizeNode();
        }
    }
}

void Graph::balance() {
    priority_queue <pair<float, Edge*>> temp;
    //cout << "test1" << endl;
    while (!U.empty()) {
       // cout << "test2" << endl;
        Edge* edge = U.top().second;
        Node* from = edge->getFrom();
        Node* to = edge->getTo();

        checkDuplicateNameEdges(from, to);

        for (int i = 0; i < namesAlreadyChecked.size(); i++) {
            //cout << "test3" << endl;

            bool changed = false;

            if (namesAlreadyChecked[i] == from->getSize().second && find(K.begin(), K.end(), from) == K.end()) {
                //cout << "resize from: found in names already checked and not in K" << endl;
                from->resizeNode();
                changed = true;
            }

            if (namesAlreadyChecked[i] == to->getSize().second && find(K.begin(), K.end(), to) == K.end()) {
                //cout << namesAlreadyChecked[i] << endl;
               // cout << "resize to: found in names already checked and not in K" << endl;
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

unordered_set<Node*> Graph::kruskalDeviation(int& numSynergies, float& score) {
    //cout << endl << "-----------" << endl;
    unordered_map<Node*, float> calulatedWeightPerNode;
    unordered_set<Edge*> traversedEdges;
    while (K.size() < 5) {
        //cout << "test" << endl;
        numSynergies++;

        if (K.size() < 5) {
            balance();
        }

        if (K.size() == 4) {
            //cout << "---Last Insertion---" << endl;
            priority_queue <pair<float, Edge*>> temp;
            while (!U.empty()) {
                //cout << U.top().second->getFrom()->getOperatorName() << " -> " << U.top().second->getTo()->getOperatorName() << endl;
                if (K.find(U.top().second->getFrom()) != K.end() || K.find(U.top().second->getTo()) != K.end()) { //if the from or to node is found in list of added nodes
                    //cout << "possible edge" << endl;
                    temp.push(U.top());
                }
                U.pop();
            }
            U = temp;
        }
        pair<float, Edge*> largestEdge = U.top();
        score += largestEdge.first;
        traversedEdges.insert(largestEdge.second);
        string fromPlayer = largestEdge.second->getFrom()->getSize().second;
        string toPlayer = largestEdge.second->getTo()->getSize().second;
        //cout << endl <<fromPlayer << " -> " << toPlayer << endl;

        namesAlreadyChecked.push_back(fromPlayer);
        namesAlreadyChecked.push_back(toPlayer);

        //cout << "Edge pushed: " << largestEdge.second->getFrom()->getOperatorName() << " -> " << largestEdge.second->getTo()->getOperatorName() << endl << endl;

        K.insert(largestEdge.second->getFrom());
        K.insert(largestEdge.second->getTo());

        calulatedWeightPerNode[largestEdge.second->getFrom()] = largestEdge.first;
        calulatedWeightPerNode[largestEdge.second->getTo()] = largestEdge.first;


        U.pop();
    }

    /*if (numSynergies == 3) { //disconnected edges
        cout << "only 3 synergies" << endl;
        //find disconnected nodes
        unordered_map<Node*, int> checkedNodes;
        vector<vector<Node*>> connectedNodes;
        int group = -1;
        for (auto it : traversedEdges) {
            //if from or to is in vector
            auto foundFromNode = checkedNodes.find(it->getFrom());
            auto foundToNode = checkedNodes.find(it->getTo());

            if (foundFromNode == checkedNodes.end() && foundToNode == checkedNodes.end()) {
                connectedNodes.push_back({ it->getFrom(), it->getTo() });
                group++;
            }
            else {
                if (foundFromNode != checkedNodes.end()) {
                    connectedNodes[foundFromNode->second].push_back(it->getFrom());
                }
                else if (foundToNode != checkedNodes.end()) {
                    connectedNodes[foundToNode->second].push_back(it->getTo());
                }
            }

            checkedNodes[it->getFrom()] = group;
            checkedNodes[it->getTo()] = group;
        }

        //find vector with 2 nodes
        for (int i = 0; i < connectedNodes.size(); i++) {
            if (connectedNodes[i].size() == 2) {
                score += calulatedWeightPerNode[connectedNodes[i][0]];
                cout << "found unconnected nodes weight: " << calulatedWeightPerNode[connectedNodes[i][0]] << endl << endl;
            }
        }

        //add their edge value again
    }*/

    return K;
    /*for(auto it : K){
        cout << it->getSize().second << ": "<< it->getOperatorName() << endl;
    }
    cout << endl << "-----------" << endl << endl;*/
}