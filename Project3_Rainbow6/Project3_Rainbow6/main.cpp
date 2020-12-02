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
		examplePlayers.push_back(player(exampleNames[i]));
	}

	int dbSize;
	cout << "Enter size of database: ";
	cin >> dbSize;

	database db = database(examplePlayers, dbSize);
	vector<player> dbResult = db.getDatabase();
	metaTeamComps metaTeams = metaTeamComps(dbResult);

	HashMap table = HashMap();
	for (int i = 0; i < dbResult.size(); i++) {
		table.getHMap() = table.insertPlayer(dbResult.at(i), table.getHMap());
	}

	//Getting and outputting Player Info
	string p1, p2, p3, p4, p5, map;
	cout << endl;
	cout << "Enter Map: ";
	//cin >> map;
	cout << "Bank" << endl;
	map = "Bank";

	cout << "Enter Player 1's name: ";
	//cin >> p1;
	cout << "Charles" << endl;
	p1 = "charles";
	cout << "Enter Player 2's name: ";
	//cin >> p2;
	cout << "Robbie" << endl;
	p2 = "Robbie";
	cout << "Enter Player 3's name: ";
	//cin >> p3;
	cout << "Football" << endl;
	p3 = "Football";
	cout << "Enter Player 4's name: ";
	//cin >> p4;
	cout << "Susurrus" << endl;
	p4 = "Susurrus";
	cout << "Enter Player 5's name: ";
	//cin >> p5;
	cout << "Bob" << endl;
	p5 = "Bob";
	cout << endl;

	//Get player info
	player pl1, pl2, pl3, pl4, pl5;
	pl1 = table.retrievePlayerInfo(p1);
	pl2 = table.retrievePlayerInfo(p2);
	pl3 = table.retrievePlayerInfo(p3);
	pl4 = table.retrievePlayerInfo(p4);
	pl5 = table.retrievePlayerInfo(p5);


	return 0;
}