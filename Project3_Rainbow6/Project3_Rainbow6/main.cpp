#include <iostream>
#include <queue>
#include "database.h"
#include "metaTeamComps.h"
#include "HashMap.h"
/*
DATA STRUCTURES USED:
1. unordered_map
2. priority_queue
3. unorder_set
4. bubbleSort
*/

void bubbleSort(vector<pair<int, priority_queue<pair<float, string>>>>& data) {
	for (int i = 0; i < data.size() - 1; i++) {
		int swapped = 0;
		for (int j = 0; j < data.size() - i - 1; j++) {
			if (data[j].second.top() < data[j + 1].second.top()) {
				auto temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				swapped = 1;
			}
		}
		if (swapped == 0) {
			break;
		}
	}
}

void calulateIdealTeam(vector<pair<int, priority_queue<pair<float, string>>>>& winRates) {
	bubbleSort(winRates);
	for (int i = 0; i < 4; i++) { //alot of loops are happening here and it's not very efficient but it only runs a finite number of times since winRates always has a size of 5 so it's O(1)

		/*for (int j = 0; j < 5; j++) {
			cout << playerNames[winRates[j].first] << " | " << winRates[j].second.top().second << ": " << winRates[j].second.top().first << endl;
		}
		cout << endl;*/

		int k = i + 1;
		bool changed = false;
		while (k < 5) {
			if (winRates[i].second.top().second == winRates[k].second.top().second) {
				winRates[k].second.pop();
				bubbleSort(winRates);
				k = i + 1;
				changed = true;
			}
			k++;
		}

		if (changed) {
			i = -1; //changes to 0 at end of iteration
		}
	}
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

	/*HashMap table = HashMap();
	for (int i = 0; i < dbResult.size(); i++) {
		table.getHMap() = table.insertPlayer(dbResult.at(i), table.getHMap());
	}*/

	cout << "Hashing default map..." << endl;
	unordered_map<string, player> autoMap;
	for (int i = 0; i < dbResult.size(); i++) {
		autoMap[dbResult[i].getName()] = dbResult[i];
	}

	//Getting and outputting Player Info
	string playerNames[5];
	string map;
	int team;
	cout << endl;
	cout << "Enter Map: ";
	//cin >> map;
	cout << "Bank" << endl;
	map = "Bank";

	cout << "Enter Team (0 = Defense, 1 = Attack): ";
	//cin >> team;
	cout << "0" << endl;
	team = 0;

	cout << endl << "Meta Team Composition:" << endl;
	vector<string> idealTeam = metaTeams.idealOperators(map, team);
	for (int i = 0; i < 5; i++) {
		cout << idealTeam[i] << endl;
	}
	cout << endl;

	cout << "Enter Player 1's name: ";
	cout << "Charles" << endl;
	playerNames[0] = "Charles";
	cout << "Enter Player 2's name: ";
	cout << "Robbie" << endl;
	playerNames[1] = "Robbie";
	cout << "Enter Player 3's name: ";
	cout << "Football" << endl;
	playerNames[2] = "Football";
	cout << "Enter Player 4's name: ";
	cout << "Susurrus" << endl;
	playerNames[3] = "Susurrus";
	cout << "Enter Player 5's name: ";
	cout << "Bob" << endl;
	playerNames[4] = "Bob";
	cout << endl;

	/*for (int i = 0; i < 5; i++) {
		cout << "Enter Player " << i + 1 << "'s name: ";
		cin >> playerNames[i];
	}*/

	//Get player info
	/*player pl1, pl2, pl3, pl4, pl5;
	pl1 = table.retrievePlayerInfo(p1);
	pl2 = table.retrievePlayerInfo(p2);
	pl3 = table.retrievePlayerInfo(p3);
	pl4 = table.retrievePlayerInfo(p4);
	pl5 = table.retrievePlayerInfo(p5);*/

	vector<pair<int, priority_queue<pair<float, string>>>> winRatesMeta(5); //I hate myself
	for (int i = 0; i < 5; i++) { //players
		for (int j = 0; j < 5; j++) { //meta operators
			winRatesMeta[i].first = i;
			winRatesMeta[i].second.push({ autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j]), idealTeam[j] });
			//cout << idealTeam[j] << ": ";
			//cout << autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j], map) << endl;
		}
		//cout << endl;
	}

	vector<pair<int, priority_queue<pair<float, string>>>> winRatesAll(5);
	for (int i = 0; i < 5; i++) { //players
		for (int j = 0; j < operatorsSize; j++) { //all operators
			winRatesAll[i].first = i;
			winRatesAll[i].second.push({ autoMap[playerNames[i]].getOperatorWinRate(operators[j]), operators[j] });
			//cout << idealTeam[j] << ": ";
			//cout << autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j], map) << endl;
		}
		//cout << endl;
	}

	/*cout << "-----------" << endl << endl;

	while(!winRates[0].second.empty()){
		cout << winRates[0].second.top().second << ": " << winRates[0].second.top().first << endl;
		winRates[0].second.pop();
	}
	cout << endl;*/

	calulateIdealTeam(winRatesMeta);
	calulateIdealTeam(winRatesAll);

	cout << "------------" << endl << endl;

	cout << "Based On Player Win Rates: " << endl;

	for (int i = 0; i < 5; i++) {
		cout << playerNames[winRatesAll[i].first] << ": " << winRatesAll[i].second.top().second << endl;
	}

	cout << endl <<"Based On Meta Compositions: " << endl;

	for (int i = 0; i < 5; i++) {
		cout << playerNames[winRatesMeta[i].first] << ": " << winRatesMeta[i].second.top().second << endl;
	}

	return 0;
}