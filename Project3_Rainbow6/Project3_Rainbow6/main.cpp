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
	metaTeamComps metaTeams = metaTeamComps(dbResult);

	for (int i = 0; i < dbResult.size(); i++) {
		cout << dbResult[i].getName() << "\nZero win rate: " << dbResult[i].getOperatorWinRate("Zero") << endl << endl;;
	}

	HashMap table = HashMap();
	for (int i = 0; i < dbResult.size(); i++) {
		table.getHMap() = table.insertPlayer(dbResult.at(i), table.getHMap());
		cout << i << endl;
	}

	//Getting and outputting Player Info
	string p1, p2, p3, p4, p5, map;
	cout << "Enter Map: " << endl;
	cin >> map;
	cout << "Enter Player 1's name: " << endl;
	cin >> p1;
	cout << "Enter Player 2's name: " << endl;
	cin >> p2;
	cout << "Enter Player 3's name: " << endl;
	cin >> p3;
	cout << "Enter Player 4's name: " << endl;
	cin >> p4;
	cout << "Enter Player 5's name: " << endl;
	cin >> p5;

	//Get player info
	player pl1, pl2, pl3, pl4, pl5;
	pl1 = table.retrievePlayerInfo(p1);
	pl2 = table.retrievePlayerInfo(p2);
	pl3 = table.retrievePlayerInfo(p3);
	pl4 = table.retrievePlayerInfo(p4);
	pl5 = table.retrievePlayerInfo(p5);


	return 0;
}