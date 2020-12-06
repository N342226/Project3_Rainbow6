#pragma once
#include "Edge.h"
#include "player.h"

struct WeightedEdges {
public:
    vector<player> players;
    vector<Edge*> edges;
	WeightedEdges(vector<player> players, int team) {
        this->players = players;

        if (team == 0) { //Defense
            unordered_map<string, Node*> operators;

            for (int i = 0; i < defenseOperatorSize; i++) {
                priority_queue<pair<float, string>> winRates = createPyramid(defenseOperators[i]);
                Node* operatorNode = new Node(winRates, defenseOperators[i]);
                operators[defenseOperators[i]] = operatorNode;
            }

            insertEdge(operators["Kapkan"], operators["Lesion"], 8888);
            insertEdge(operators["Kapkan"], operators["Ela"], 8);
            insertEdge(operators["Kapkan"], operators["Frost"], 88888);
            insertEdge(operators["Kapkan"], operators["Jager"], 88888);

            insertEdge(operators["Jager"], operators["Tachanka"], 88888);

            insertEdge(operators["Valk"], operators["Echo"], 8);
            insertEdge(operators["Valk"], operators["Maestro"], 8);

            insertEdge(operators["Maestro"], operators["Mozzie"], 8);

            insertEdge(operators["Mozzie"], operators["Mute"], 8);

            insertEdge(operators["Mute"], operators["Bandit"], 8);
            insertEdge(operators["Mute"], operators["Kaid"], 8);


            //test
            insertEdge(operators["Valk"], operators["Tachanka"], 8);
        }
        else { //Attack

        }
	}

    void insertEdge(Node* from, Node* to, int weight) {
        Edge* edge = new Edge(from, to, weight);
        edges.push_back(edge);
    }

    priority_queue<pair<float, string>> createPyramid(string operatorName) {
        priority_queue<pair<float, string>> result;
        for (int j = 0; j < players.size(); j++) {
            result.push({ players[j].getOperatorWinRate(operatorName), players[j].getName() });
        }
        return result;
    }
};