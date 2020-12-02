#pragma once
#include "maps.h"
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

class metaTeamComps {
private:
	unordered_map<string, pair<vector<string>, vector<string>>> metaTeams; // <map, <defense, attack>>

public:
	metaTeamComps();
	metaTeamComps(vector<player> db);
	metaTeamComps(vector<string> maps, vector<vector<string>> defenseOperators, vector<vector<string>> attackOperators);

	void addMap(string map, vector<string> defenseOperators, vector<string> attackOperators);
	void addDefense(string map, vector<string> defenseOperators);
	void addAttack(string map, vector<string> attackOperators);

	vector<string> idealOperators(string map, int team); //0 = defense; 1 = attack
};

metaTeamComps::metaTeamComps() {
	vector<string> bank_D = { "Aruni", "Melusi", "Oryx", "Wamai", "Goyo" };
	vector<string> bank_A = { "Zero", "Ace", "Iana", "Kali", "Amaru" };
	metaTeams["Bank_D"] = { bank_D, bank_A };
}

metaTeamComps::metaTeamComps(vector<player> db) {
	vector<vector<float>> defenseWinRates(mapSize, vector<float>(defenseOperatorSize)); //<maps<operators>>
	vector<vector<float>> attackWinRates(mapSize, vector<float>(attackOperatorSize));

	cout << "Deciding best team compositions..." << endl;

	for (int i = 0; i < db.size(); i++) { //iterate through each player
		for (int m = 0; m < mapSize; m++) { //iterate through each map

			for (int d = 0; d < defenseOperatorSize; d++) {
				defenseWinRates[m][d] += db[i].getOperatorWinRate(defenseOperators[d], m); //get each defence operator on each map of this player
				if (i != 0) {
					defenseWinRates[m][d] /= 2; //skip the first iteration and average results afterwards 
				}
			}

			for (int a = 0; a < attackOperatorSize; a++) {
				attackWinRates[m][a] += db[i].getOperatorWinRate(attackOperators[a], m); //get each attack operator on each map of this player
				if (i != 0) {
					attackWinRates[m][a] /= 2;
				}
			}
		}
	}

	vector<string> max_D(5);
	for (int i = 0; i < defenseWinRates.size(); i++) { //iterate through each map
		for (int j = 0; j < 5; j++) {
			int maxIndex = max_element(defenseWinRates[i].begin(), defenseWinRates[i].end()) - defenseWinRates[i].begin(); //find the operator with the highest win rate
			max_D[j] = defenseOperators[maxIndex];
			defenseWinRates[i][maxIndex] = -1; //set previous highest to -1 to find second highest
		}
		metaTeams[maps[i]].first = max_D;
	}

	vector<string> max_A(5);
	for (int i = 0; i < attackWinRates.size(); i++) { 
		for (int j = 0; j < 5; j++) {
			int maxIndex = max_element(attackWinRates[i].begin(), attackWinRates[i].end()) - attackWinRates[i].begin(); 
			max_D[j] = defenseOperators[maxIndex];
			attackWinRates[i][maxIndex] = -1;
		}
		metaTeams[maps[i]].second = max_A;
	}
}

metaTeamComps::metaTeamComps(vector<string> maps, vector<vector<string>> defenseOperators, vector<vector<string>> attackOperators) {
	for (int i = 0; i < maps.size(); i++) {
		metaTeams[maps[i]].first = defenseOperators[i];
		metaTeams[maps[i]].second = attackOperators[i];
	}
}

void metaTeamComps::addMap(string map, vector<string> defenseOperators, vector<string> attackOperators) {
	metaTeams[map] = { defenseOperators, attackOperators };
}

void metaTeamComps::addDefense(string map, vector<string> defenseOperators) {
	metaTeams[map].first = defenseOperators;
}

void metaTeamComps::addAttack(string map, vector<string> attackOperators) {
	metaTeams[map].second = attackOperators;
}

vector<string> metaTeamComps::idealOperators(string map, int team) {
	if (team == 0) {
		//cout << metaTeams[map].first[0] << endl;

		return metaTeams[map].first;
	}
	else if (team == 1) {
		return metaTeams[map].second;
	}
	else {
		vector<string> result;
		return result;
	}
}