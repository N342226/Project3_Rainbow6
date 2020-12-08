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

            insertEdge(operators["Kapkan"], operators["Lesion"], .6);
            insertEdge(operators["Kapkan"], operators["Ela"], .6);
            insertEdge(operators["Kapkan"], operators["Frost"], .4);
            insertEdge(operators["Kapkan"], operators["Jager"], .5);

            insertEdge(operators["Jager"], operators["Tachanka"], 1.0);

            insertEdge(operators["Valk"], operators["Echo"], .8);
            insertEdge(operators["Valk"], operators["Maestro"], .75);

            insertEdge(operators["Maestro"], operators["Mozzie"], .69);

            insertEdge(operators["Mozzie"], operators["Mute"], .69);

            insertEdge(operators["Mute"], operators["Bandit"], .7);
            insertEdge(operators["Mute"], operators["Kaid"], .71);

            insertEdge(operators["Valk"], operators["Tachanka"], 1.0);


            /*insertEdge(operators["Aruni"], operators["Frost"], .5);
            insertEdge(operators["Aruni"], operators["Kapkan"], .6);
            insertEdge(operators["Aruni"], operators["Lesion"], .7);
            insertEdge(operators["Ela"], operators["Kapkan"], .6);
            insertEdge(operators["Ela"], operators["Lesion"], .7);
            insertEdge(operators["Lesion"], operators["Mute"], .55);
            insertEdge(operators["Lesion"], operators["Melusi"], .8);
            insertEdge(operators["Melusi"], operators["Jager"], .8);
            insertEdge(operators["Melusi"], operators["Alibi"], .5);
            insertEdge(operators["Jager"], operators["Mute"], .7);
            insertEdge(operators["Jager"], operators["Wamai"], .8);
            insertEdge(operators["Jager"], operators["Warden"], .1);
            insertEdge(operators["Mute"], operators["Bandit"], .8);
            insertEdge(operators["Mute"], operators["Kaid"], .6);
            insertEdge(operators["Mute"], operators["Mozzie"], .8);
            insertEdge(operators["Mute"], operators["Mira"], .8);
            insertEdge(operators["Mute"], operators["Castle"], .8);
            insertEdge(operators["Mira"], operators["Bandit"], .6);
            
            insertEdge(operators["Mira"], operators["Kaid"], .7);
            insertEdge(operators["Mira"], operators["Smoke"], .7);

            insertEdge(operators["Valk"], operators["Bandit"], .6);



            insertEdge(operators["Valk"], operators["Echo"], .8);
            insertEdge(operators["Valk"], operators["Maestro"], .8);
            insertEdge(operators["Valk"], operators["Pulse"], .7);
            insertEdge(operators["Valk"], operators["Caveira"], .8);
            insertEdge(operators["Valk"], operators["Vigil"], .75);
            
            insertEdge(operators["Maestro"], operators["Smoke"], .8);
            insertEdge(operators["Maestro"], operators["Tachanka"], 1.0);*/
        }
        else { //Attack
            unordered_map<string, Node*> operators;

            for (int i = 0; i < attackOperatorSize; i++) {
                priority_queue<pair<float, string>> winRates = createPyramid(attackOperators[i]);
                Node* operatorNode = new Node(winRates, attackOperators[i]);
                operators[attackOperators[i]] = operatorNode;
            }

            insertEdge(operators["Ash"], operators["Glaz"], .3);
            insertEdge(operators["Ash"], operators["Zofia"], .6);
            insertEdge(operators["Ash"], operators["Twitch"], .5);
            insertEdge(operators["Ash"], operators["Thatcher"], .7);

            insertEdge(operators["Thatcher"], operators["Fuze"], .7);

            insertEdge(operators["Zero"], operators["Iq"], .65);
            insertEdge(operators["Zero"], operators["Nomad"], .8);

            insertEdge(operators["Nomad"], operators["Kali"], .8);

            insertEdge(operators["Kali"], operators["Thermite"], .85);

            insertEdge(operators["Thermite"], operators["Iana"], .69);
            insertEdge(operators["Thermite"], operators["Nokk"], .4598265);

            insertEdge(operators["Zero"], operators["Fuze"], .3141592653589793232);


            /*insertEdge(operators["Zero"], operators["Iana"], .7);
            insertEdge(operators["Zero"], operators["Thatcher"], .6);
            insertEdge(operators["Zero"], operators["Gridlock"], .7);
            insertEdge(operators["Zero"], operators["Nomad"], .55);
            insertEdge(operators["Gridlock"], operators["Nomad"], .8);
            insertEdge(operators["Gridlock"], operators["Ash"], .7);
            insertEdge(operators["Nomad"], operators["Ace"], .8);
            insertEdge(operators["Nomad"], operators["Ash"], .7);
            insertEdge(operators["Ash"], operators["Finka"], .8);
            insertEdge(operators["Ash"], operators["Zofia"], .6);
            insertEdge(operators["Ash"], operators["Jackal"], .7);
            insertEdge(operators["Zofia"], operators["Ying"], .6);
            insertEdge(operators["Finka"], operators["Lion"], .8);
            insertEdge(operators["Finka"], operators["Dokkaebi"], .6);
            insertEdge(operators["Finka"], operators["Amaru"], .8);
            insertEdge(operators["Jackal"], operators["Nokk"], .7);
            insertEdge(operators["Ying"], operators["Capitao"], .6);
            insertEdge(operators["Dokkaebi"], operators["Lion"], .8);
            insertEdge(operators["Dokkaebi"], operators["Amaru"], .6);
            insertEdge(operators["Thatcher"], operators["Ace"], .8);
            insertEdge(operators["Thatcher"], operators["Hibana"], .8);
            insertEdge(operators["Thatcher"], operators["Thermite"], .8);
            insertEdge(operators["Ace"], operators["Buck"], .8);
            insertEdge(operators["Ace"], operators["Montagne"], .8);
            insertEdge(operators["Ace"], operators["Maverick"], .8);
            insertEdge(operators["Ace"], operators["Kali"], .8);
            insertEdge(operators["Ace"], operators["Capitao"], .8);
            insertEdge(operators["Ace"], operators["Glaz"], .8);
            insertEdge(operators["Kali"], operators["Hibana"], .7);
            insertEdge(operators["Kali"], operators["Thermite"], .7);
            insertEdge(operators["Kali"], operators["Blackbeard"], .6);
            insertEdge(operators["Hibana"], operators["Montagne"], .5);
            insertEdge(operators["Hibana"], operators["Maverick"], .8);
            insertEdge(operators["Montagne"], operators["Blitz"], .6);
            insertEdge(operators["Thermite"], operators["Maverick"], .8);
            insertEdge(operators["Thermite"], operators["Buck"], .8);
            insertEdge(operators["Thermite"], operators["Sledge"], .5);*/
        }
	}

    void insertEdge(Node* from, Node* to, float weight) {
        Edge* edge = new Edge(from, to, weight);
        edges.push_back(edge);
    }

    priority_queue<pair<float, string>> createPyramid(string operatorName) {
        priority_queue<pair<float, string>> result;
        for (int j = 0; j < players.size(); j++) {
            //cout << players[j].getOperatorWinRate(operatorName) << endl;
            result.push({ players[j].getOperatorWinRate(operatorName), players[j].getName() });
        }
        return result;
    }
};