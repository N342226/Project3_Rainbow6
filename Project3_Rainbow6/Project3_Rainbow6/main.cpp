#include <iostream>
#include "database.h"
#include "metaTeamComps.h"
#include "HashMap.h"

pair<string*, string*> findTeamComp(string map, int team, string* usernames) { //<usernames, operators>
	metaTeamComps metaTeams = metaTeamComps();
	string* operators = metaTeams.idealOperators(map, team);

	return { usernames, operators };
}

int main() {
	vector<string> exampleNames = { "Charles", "Robbie", "Football", "Susurrus", "Bob" };
	vector<player> examplePlayers;

	for (int i = 0; i < exampleNames.size(); i++) {
		examplePlayers.push_back(player(exampleNames[i], .5, 2));
	}

	database db = database(examplePlayers, 10);
	
	vector<player> dbResult = db.getDatabase();

	for (int i = 0; i < dbResult.size(); i++) {
		cout << dbResult[i].getName() << "\nZero win rate: " << dbResult[i].getOperatorWinRate("Zero") << endl << endl;;
	}

	HashMap table;
	for (int i = 0; i < dbResult.size(); i++) {
		table.getHMap() = table.insertPlayer(dbResult.at(i), table.getHMap());
	}
	return 0;
}