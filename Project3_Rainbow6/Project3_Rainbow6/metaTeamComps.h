#pragma once
#include <string>
#include <unordered_map>
using namespace std;

//test
class metaTeamComps {
private:
	unordered_map<string, pair<string*, string*>> metaTeams; // <map, <defense, attack>>

public:
	metaTeamComps();
	metaTeamComps(vector<string> maps, vector<string*> defenseOperators, vector<string*> attackOperators);

	void addMap(string map, string* defenseOperators, string* attackOperators);
	void addDefense(string map, string* defenseOperators);
	void addAttack(string map, string* attackOperators);

	string* idealOperators(string map, int team); //0 = defense; 1 = attack
};

metaTeamComps::metaTeamComps() {
	string bank_D[5] = { "Aruni", "Melusi", "Oryx", "Wamai", "Goyo" };
	string bank_A[5] = { "Zero", "Ace", "Iana", "Kali", "Amaru" };
	metaTeams["Bank_D"] = { bank_D, bank_A };
}

metaTeamComps::metaTeamComps(vector<string> maps, vector<string*> defenseOperators, vector<string*> attackOperators) {
	for (int i = 0; i < maps.size(); i++) {
		metaTeams[maps[i]].first = defenseOperators[i];
		metaTeams[maps[i]].second = attackOperators[i];
	}
}

void metaTeamComps::addMap(string map, string* defenseOperators, string* attackOperators) {
	metaTeams[map] = { defenseOperators, attackOperators };
}

void metaTeamComps::addDefense(string map, string* defenseOperators) {
	metaTeams[map].first = defenseOperators;
}

void metaTeamComps::addAttack(string map, string* attackOperators) {
	metaTeams[map].second = attackOperators;
}

string* metaTeamComps::idealOperators(string map, int team) {
	if (team == 0) {
		return metaTeams[map].first;
	}
	else if (team == 1) {
		return metaTeams[map].second;
	}
	else {
		return nullptr;
	}
}