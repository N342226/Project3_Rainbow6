#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <chrono>
#include "database.h"
#include "metaTeamComps.h"
#include "HashMap.h"
#include "Graph.h"
#include "Graph2.h"
/*
DATA STRUCTURES USED:
1. unordered_map
2. priority_queue
3. unorder_set
5. edge list graph

ALGORITHMS USED:
1. Bubble sort
2. Kruskal's
3. bfs
*/

void drawTo(sf::Texture, sf::RenderWindow&, int, int, float);

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
	vector<string> exampleNames = { "Charles", "Robert", "Football", "Susurrus", "Parrallax" };
	vector<player> examplePlayers;

	for (int i = 0; i < exampleNames.size(); i++) {
		examplePlayers.push_back(player(exampleNames[i]));
	}

	int dbSize;
	cout << "Enter size of database: ";
	cin >> dbSize;
	//dbSize = 10;
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	database db = database(examplePlayers, dbSize);

	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	cout << "Time elapsed = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

	vector<player> dbResult = db.getDatabase();
	metaTeamComps metaTeams = metaTeamComps(dbResult);

	/*HashMap table = HashMap();
	for (int i = 0; i < dbResult.size(); i++) {
		table.getHMap() = table.insertPlayer(dbResult.at(i), table.getHMap());
	}*/

	cout << "Hashing default map..." << endl;
	begin = chrono::steady_clock::now();
	unordered_map<string, player> autoMap;
	for (int i = 0; i < dbResult.size(); i++) {
		autoMap[dbResult[i].getName()] = dbResult[i];
	}

	end = chrono::steady_clock::now();
	cout << "Time elapsed = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

	string playerNames[5];
	string map;
	int team;
	cout << endl;

	//cout << "Enter Team (0 = Defense, 1 = Attack): " << endl;
	//cin >> team;
	//cout << "0" << endl;
	//team = 0;

	//cout << "Enter Map: " << endl;
	//cin >> map;
	//cout << "Bank" << endl;
	//map = "Bank";

	//START SFML
	sf::RenderWindow window(sf::VideoMode(1600, 1080), "SFML works!"); //Creating the window

	//Getting all the operator icons
	std::map<std::string, sf::Texture> operatorIcons;
	sf::Texture operatorIcon;
	std::string name;
	if (!operatorIcon.loadFromFile("../Pictures/operators/ace.png")) {}
	name = "Ace";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/alibi.png")) {}
	name = "Alibi";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/amaru.png")) {}
	name = "Amaru";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/aruni.png")) {}
	name = "Aruni";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/ash.png")) {}
	name = "Ash";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/bandit.png")) {}
	name = "Bandit";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/blackbeard.png")) {}
	name = "Blackbeard";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/blitz.png")) {}
	name = "Blitz";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/buck.png")) {}
	name = "Buck";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/capitao.png")) {}
	name = "Capitao";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/castle.png")) {}
	name = "Castle";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/caveira.png")) {}
	name = "Caveira";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/clash.png")) {}
	name = "Clash";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/doc.png")) {}
	name = "Doc";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/dokkaebi.png")) {}
	name = "Dokkaebi";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/echo.png")) {}
	name = "Echo";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/ela.png")) {}
	name = "Ela";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/finka.png")) {}
	name = "Finka";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/frost.png")) {}
	name = "Frost";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/fuze.png")) {}
	name = "Fuze";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/glaz.png")) {}
	name = "Glaz";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/goyo.png")) {}
	name = "Goyo";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/gridlock.png")) {}
	name = "Gridlock";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/hibana.png")) {}
	name = "Hibana";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/iana.png")) {}
	name = "Iana";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/iq.png")) {}
	name = "Iq";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/jackal.png")) {}
	name = "Jackal";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/jager.png")) {}
	name = "Jager";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/kaid.png")) {}
	name = "Kaid";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/kali.png")) {}
	name = "Kali";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/kapkan.png")) {}
	name = "Kapkan";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/lesion.png")) {}
	name = "Lesion";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/lion.png")) {}
	name = "Lion";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/maestro.png")) {}
	name = "Maestro";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/maverick.png")) {}
	name = "Maverick";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/melusi.png")) {}
	name = "Melusi";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/mira.png")) {}
	name = "Mira";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/montagne.png")) {}
	name = "Montagne";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/mozzie.png")) {}
	name = "Mozzie";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/mute.png")) {}
	name = "Mute";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/nokk.png")) {}
	name = "Nokk";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/nomad.png")) {}
	name = "Nomad";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/oryx.png")) {}
	name = "Oryx";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/pulse.png")) {}
	name = "Pulse";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/rook.png")) {}
	name = "Rook";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/sledge.png")) {}
	name = "Sledge";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/smoke.png")) {}
	name = "Smoke";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/tachanka.png")) {}
	name = "Tachanka";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/thatcher.png")) {}
	name = "Thatcher";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/thermite.png")) {}
	name = "Thermite";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/twitch.png")) {}
	name = "Twitch";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/valkyrie.png")) {}
	name = "Valk";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/vigil.png")) {}
	name = "Vigil";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/wamai.png")) {}
	name = "Wamai";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/warden.png")) {}
	name = "Warden";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/ying.png")) {}
	name = "Ying";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/zero.png")) {}
	name = "Zero";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/zofia.png")) {}
	name = "Zofia";
	operatorIcons.emplace(name, operatorIcon);

	//Getting all the map icons
	std::vector<sf::Texture> mapIcons;
	sf::Texture mapIcon;
	if (!mapIcon.loadFromFile("../Pictures/Maps/Bank.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Border.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Chalet.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Clubhouse.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Coastline.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Consulate.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Favela.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Fortress.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/HerefordBase.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/House.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/KafeDostoyevsky.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Kanal.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Oregon.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Outback.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/PresidentialPlane.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Skyscraper.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/ThemePark.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Tower.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Villa.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);
	if (!mapIcon.loadFromFile("../Pictures/Maps/Yacht.png", sf::IntRect(0, 75, 370, 120))) {}
	mapIcons.push_back(mapIcon);

	//Creates a map with all map names and their corressponding icon number
	std::map<int, std::string>mapKeys;
	mapKeys.emplace(1, "Bank");
	mapKeys.emplace(2, "Border");
	mapKeys.emplace(3, "Chalet");
	mapKeys.emplace(4, "Clubhouse");
	mapKeys.emplace(5, "Coastline");
	mapKeys.emplace(6, "Consulate");
	mapKeys.emplace(7, "Favela");
	mapKeys.emplace(8, "Fortress");
	mapKeys.emplace(9, "HerefordBase");
	mapKeys.emplace(10, "House");
	mapKeys.emplace(11, "KafeDostoyevsky");
	mapKeys.emplace(12, "Kanal");
	mapKeys.emplace(13, "Oregon");
	mapKeys.emplace(14, "Outback");
	mapKeys.emplace(15, "PresidentialPlane");
	mapKeys.emplace(16, "Skyscraper");
	mapKeys.emplace(17, "ThemePark");
	mapKeys.emplace(18, "Tower");
	mapKeys.emplace(19, "Villa");
	mapKeys.emplace(20, "Yacht");

	//Loads the Attack/Defense icon
	sf::Texture attackDefenseIcon;
	if (!attackDefenseIcon.loadFromFile("../Pictures/AttackDefense.png")) {}

	//Creates variables that will be used to determine which screen to show as well as map / Attack defense choice
	bool isMapChosen = false, isAttackDefense = false, generate = false, defaultTeam = false;
	std::string mapChose = "", attackDefense = "";

	vector<string> idealTeam;
	bool metaTeamMade = false;

	unordered_map<string, string> allResult;
	unordered_map<string, string> metaResult;
	unordered_map<string, string> kruskalsResult;
	unordered_map<string, string> bfsResult;
	bool teamsMade = false;

	float scoreBasic = 0;
	float scoreMeta = 0;
	float scoreKruskal = 0;
	int numSynergies = 0;
	float scoreBruteForce = 0;

	bool generatedRandomNames = false;

	while (window.isOpen())
	{
		//Makes the background
		sf::RectangleShape backgroundRect;
		backgroundRect.setSize(sf::Vector2f(1600.f, 1200.f));
		backgroundRect.setFillColor(sf::Color::White);
		window.draw(backgroundRect);

		//Creates the text
		sf::Text text;
		sf::Font font;
		if (!font.loadFromFile("../Pictures/arial.ttf")) {}
		text.setFont(font);
		text.setCharacterSize(90);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2.0f);
		text.setFillColor(sf::Color::Red);
		text.setPosition(80.0f, 0.0f);
		text.setStyle(sf::Text::Bold);

		//Displays the screen if it was generated
		if (isMapChosen && isAttackDefense && generate)
		{
			/*window.setSize(sf::Vector2u(1920, 1080));
			window.setPosition(sf::Vector2i(0, 0));
			backgroundRect.setSize(sf::Vector2f(1920.f, 1080.f));
			window.draw(backgroundRect);*/

			if (!metaTeamMade) {
				cout << endl << "----------------" << endl << endl;
				cout << "Map: " << map << endl;
				cout << "Team: " << team << endl;
				cout << endl << "Meta Team Composition:" << endl;
				idealTeam = metaTeams.idealOperators(map, team);
				for (int i = 0; i < 5; i++) {
					cout << idealTeam[i] << endl;
				}
				cout << endl;

				scoreBasic = 0;
				scoreMeta = 0;
				scoreKruskal = 0;
				numSynergies = 0;
				scoreBruteForce = 0;

				/*cout << "Enter Player 1's name: " << endl;
				//cout << "Charles" << endl;
				//playerNames[0] = "Charles";
				cout << "Enter Player 2's name: " << endl;
				//cout << "Robbie" << endl;
				//playerNames[1] = "Robbie";
				cout << "Enter Player 3's name: " << endl;
				//cout << "Football" << endl;
				//playerNames[2] = "Football";
				cout << "Enter Player 4's name: " << endl;
				//cout << "Susurrus" << endl;
				//playerNames[3] = "Susurrus";
				cout << "Enter Player 5's name: " << endl;
				//cout << "Bob" << endl;
				//playerNames[4] = "Bob";
				cout << endl;*/

				metaTeamMade = true;
			}

			//Generates all of the base info on the screen
			text.setCharacterSize(40);
			text.setString("Players:");
			text.setPosition(sf::Vector2f(50.0f, 0.0f));
			window.draw(text);
			text.setString("Best Player Winrates");
			text.setPosition(300.0f, 0.0f);
			window.draw(text);
			text.setString("Best Operator Winrates");
			text.setPosition(710.0f, 0.0f);
			window.draw(text);
			text.setString("Best Overall Synergies\n Kruskal's     BFS");
			text.setPosition(1163.0f, 0.0f);
			window.draw(text);
			sf::RectangleShape box;
			box.setFillColor(sf::Color::Transparent);
			box.setSize(sf::Vector2f(415.0f, 900.0f));
			box.setPosition(sf::Vector2f(285.0f, 5.0f));
			box.setOutlineColor(sf::Color::Black);
			box.setOutlineThickness(5.0f);
			window.draw(box);
			box.setSize(sf::Vector2f(460.0f, 900.0f));
			box.setPosition(sf::Vector2f(700.0f, 5.0f));
			window.draw(box);
			box.setSize(sf::Vector2f(435.0f, 900.0f));
			box.setPosition(sf::Vector2f(1160.0f, 5.0f));
			window.draw(box);
			box.setSize(sf::Vector2f(280.0f, 900.0f));
			box.setPosition(sf::Vector2f(5.0f, 5.0f));
			window.draw(box);
			text.setString("Start Over");
			text.setCharacterSize(80);
			text.setPosition(sf::Vector2f(1001.0f, 910.0f));
			window.draw(text);
			text.setCharacterSize(50);
			text.setString("Generate Default Team");
			text.setPosition(sf::Vector2f(0.0f, 910.0f));
			window.draw(text);

			//Checks whether to display the default team or a random one
			text.setCharacterSize(40);
			if (defaultTeam)
			{
				//Draws the default names
				text.setPosition(sf::Vector2f(5.0f, 100.0f));
				text.setString("Robert");
				//cout << "Player 1: Robert" << endl;
				playerNames[0] = "Robert";
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 260.0f));
				text.setString("Charles");
				//cout << "Player 2: Charles" << endl;
				playerNames[1] = "Charles";
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 420.0f));
				text.setString("Susurrus");
				//cout << "Player 3: Susurrus" << endl;
				playerNames[2] = "Susurrus";
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 580.0f));
				text.setString("Football");
				//cout << "Player 4: Football" << endl;
				playerNames[3] = "Football";
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 760.0f));
				text.setString("Parrallax");
				//cout << "Player 5: Parrallax" << endl;
				playerNames[4] = "Parrallax";
				window.draw(text);

				sf::Sprite opIcon;
					
			}

			else
			{
				if (!generatedRandomNames) {
					set<string> checkedNames;

					while (checkedNames.size() < 5) {
						auto it = autoMap.begin();
						std::advance(it, rand() % autoMap.size());
						checkedNames.insert(it->first);
					}

					int i = 0;
					for (auto it : checkedNames) {
						playerNames[i] = it;
						i++;

						//cout << "Random Player: " << it << endl;
					}

					generatedRandomNames = true;
				}
				

				//Draws the default names
				text.setPosition(sf::Vector2f(5.0f, 100.0f));
				text.setString(playerNames[0]);
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 260.0f));
				text.setString(playerNames[1]);
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 420.0f));
				text.setString(playerNames[2]);
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 580.0f));
				text.setString(playerNames[3]);
				window.draw(text);

				text.setPosition(sf::Vector2f(5.0f, 760.0f));
				text.setString(playerNames[4]);
				window.draw(text);

				sf::Sprite opIcon;

			}

			if (!teamsMade) {
				cout << endl << "Based on players:" << endl << endl;
				/*----BASED ON PLAYER------*/
				begin = chrono::steady_clock::now();
				vector<pair<int, priority_queue<pair<float, string>>>> winRatesAll(5); //I hate myself
				for (int i = 0; i < 5; i++) { //players
					if (team == 0) { //all defense operators
						for (int j = 0; j < defenseOperatorSize; j++) { //all operators
							winRatesAll[i].first = i;
							winRatesAll[i].second.push({ autoMap[playerNames[i]].getOperatorWinRate(defenseOperators[j]), defenseOperators[j] });
							//cout << idealTeam[j] << ": ";
							//cout << autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j], map) << endl;
						}
					}
					else if (team == 1) { //all attack operators
						for (int j = 0; j < attackOperatorSize; j++) { //all operators
							winRatesAll[i].first = i;
							winRatesAll[i].second.push({ autoMap[playerNames[i]].getOperatorWinRate(attackOperators[j]), attackOperators[j] });
							//cout << idealTeam[j] << ": ";
							//cout << autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j], map) << endl;
						}
					}

					//cout << endl;
				}

				calulateIdealTeam(winRatesAll);

				for (int i = 0; i < 5; i++) {
					allResult[playerNames[winRatesAll[i].first]] = winRatesAll[i].second.top().second;
					cout << playerNames[winRatesAll[i].first] << ": " << winRatesAll[i].second.top().second << endl;
					scoreBasic += winRatesAll[i].second.top().first;
				}
				cout << "Team Score: " << scoreBasic / 5 << endl; //doesnt check for meta characters or synergies (could be higher)

				end = chrono::steady_clock::now();
				cout << "Time elapsed = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;




				/*-------BASED ON OPERATOR------*/
				begin = chrono::steady_clock::now();
				cout << endl << "Based on operators:" << endl << endl;
				vector<pair<int, priority_queue<pair<float, string>>>> winRatesMeta(5);
				for (int i = 0; i < 5; i++) { //players
					for (int j = 0; j < 5; j++) { //meta operators
						winRatesMeta[i].first = i;
						winRatesMeta[i].second.push({ autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j]), idealTeam[j] });
						//cout << idealTeam[j] << ": ";
						//cout << autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j], map) << endl;
					}
					//cout << endl;
				}

				calulateIdealTeam(winRatesMeta);

				for (int i = 0; i < 5; i++) {
					metaResult[playerNames[winRatesMeta[i].first]] = winRatesMeta[i].second.top().second;
					cout << playerNames[winRatesMeta[i].first] << ": " << winRatesMeta[i].second.top().second << endl;
					scoreMeta += winRatesMeta[i].second.top().first;
				}
				cout << "Team Score: " << (scoreMeta + 50) / 5 << endl; //doesnt check for synergies (could be higher) and 50 was chosen as an abitrary bonus for using meta comp

				end = chrono::steady_clock::now();
				cout << "Time elapsed = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;




				/*----BASED ON SYNERGIES (KRUSKALS)-----*/
				begin = chrono::steady_clock::now();
				cout << endl << "Based on kruskal's: " << endl << endl;
				vector<player> players(5);
				for (int i = 0; i < 5; i++) {
					players[i] = autoMap[playerNames[i]];
				}

				Graph testGraph = Graph(players, team);
				numSynergies = 0; //can either be 3 or 4 depending on how which edges are picked
				unordered_set<Node*> kruskal = testGraph.kruskalDeviation(numSynergies, scoreKruskal);

				for (auto it : kruskal) {
					kruskalsResult[it->getSize().second] = it->getOperatorName();
					cout << it->getSize().second << ": " << it->getOperatorName() << endl;
				}
				cout << "Team Score: " << (scoreKruskal + numSynergies * 5) / numSynergies << endl; //doesnt check meta characters (could be higher) and chose 5 per synergy arbitrarily

				end = chrono::steady_clock::now();
				cout << "Time elapsed = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;




				/*----BASED ON SYNERGIES (BFS)-----*/
				begin = chrono::steady_clock::now();
				cout << endl << "based on bfs:" << endl << endl;
				Graph2 testGraph2 = Graph2(players, team);
				auto bruteForce = testGraph2.bruteForce(scoreBruteForce);

				for (int i = 0; i < bruteForce.size(); i++) {
					bfsResult[bruteForce[i]->getSize().second] = bruteForce[i]->getOperatorName();
					cout << bruteForce[i]->getSize().second << ": " << bruteForce[i]->getOperatorName() << endl;
				}
				cout << "Team Score: " << (scoreBruteForce + 4 * 5) / 4 << endl; //doesnt check meta characters (could be higher) and chose 5 per synergy arbitrarily (always 4 synergies)*/

				end = chrono::steady_clock::now();
				cout << "Time elapsed = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;



				teamsMade = true;
			}

			drawTo(operatorIcons.at(allResult[playerNames[0]]), window, 410, 80, 0.1f);
			drawTo(operatorIcons.at(allResult[playerNames[1]]), window, 410, 240, 0.1f);
			drawTo(operatorIcons.at(allResult[playerNames[2]]), window, 410, 400, 0.1f);
			drawTo(operatorIcons.at(allResult[playerNames[3]]), window, 410, 560, 0.1f);
			drawTo(operatorIcons.at(allResult[playerNames[4]]), window, 410, 740, 0.1f);

			//OPERATOR WIN RATES
			drawTo(operatorIcons.at(metaResult[playerNames[0]]), window, 820, 80, 0.1f);
			drawTo(operatorIcons.at(metaResult[playerNames[1]]), window, 820, 240, 0.1f);
			drawTo(operatorIcons.at(metaResult[playerNames[2]]), window, 820, 400, 0.1f);
			drawTo(operatorIcons.at(metaResult[playerNames[3]]), window, 820, 560, 0.1f);
			drawTo(operatorIcons.at(metaResult[playerNames[4]]), window, 820, 740, 0.1f);

			//KRUSKALS
			drawTo(operatorIcons.at(kruskalsResult[playerNames[0]]), window, 1173, 80, 0.1f);
			drawTo(operatorIcons.at(kruskalsResult[playerNames[1]]), window, 1173, 240, 0.1f);
			drawTo(operatorIcons.at(kruskalsResult[playerNames[2]]), window, 1173, 400, 0.1f);
			drawTo(operatorIcons.at(kruskalsResult[playerNames[3]]), window, 1173, 560, 0.1f);
			drawTo(operatorIcons.at(kruskalsResult[playerNames[4]]), window, 1173, 740, 0.1f);

			//BFS
			drawTo(operatorIcons.at(bfsResult[playerNames[0]]), window, 1373, 80, 0.1f);
			drawTo(operatorIcons.at(bfsResult[playerNames[1]]), window, 1373, 240, 0.1f);
			drawTo(operatorIcons.at(bfsResult[playerNames[2]]), window, 1373, 400, 0.1f);
			drawTo(operatorIcons.at(bfsResult[playerNames[3]]), window, 1373, 560, 0.1f);
			drawTo(operatorIcons.at(bfsResult[playerNames[4]]), window, 1373, 740, 0.1f);

			text.setCharacterSize(25);
			text.setPosition(sf::Vector2f(410.0f, 864.0f));
			text.setString(to_string(scoreMeta / 5));
			window.draw(text);
			text.setCharacterSize(25);
			text.setPosition(sf::Vector2f(820.0f, 864.0f));
			text.setString(to_string((scoreMeta + 50) / 5));
			window.draw(text);
			text.setCharacterSize(25);
			text.setPosition(sf::Vector2f(1188.0f, 864.0f));
			text.setString(to_string((scoreKruskal + numSynergies * 5) / numSynergies));
			window.draw(text);
			text.setCharacterSize(25);
			text.setPosition(sf::Vector2f(1388.0f, 864.0f));
			text.setString(to_string((scoreBruteForce + 4 * 5) / 4));
			window.draw(text);

			//Creates the event loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				int xval = event.mouseButton.x;
				int yval = event.mouseButton.y;

				//If default team button is pressed, alternates between a random team and a default team
				if (xval >= 0 && xval <= 500 && yval >= 910)
				{
					defaultTeam = true;
					teamsMade = false;
					generatedRandomNames = false;
					scoreBasic = 0;
					scoreMeta = 0;
					scoreKruskal = 0;
					numSynergies = 0;
					scoreBruteForce = 0;
				}

				//If Star Over button is pressed, resets back to the original screen
				else if (xval >= 1001 && xval <= 1400 && yval >= 910)
				{
					isMapChosen = false;
					isAttackDefense = false;
					generate = false;
					defaultTeam = false;
					metaTeamMade = false;
					teamsMade = false;
					generatedRandomNames = false;
				}
			}
		}

		//Displays the screen if not yet generated
		else
		{
			drawTo(attackDefenseIcon, window, 632, 120, 1.0f); // Draws the attack / defense icon

			//Draws the title and the generate button
			text.setString("Rainbow Six Siege Team Generator");
			window.draw(text);
			text.setString("Generate");
			text.setPosition(600.0f, 900.0f);
			window.draw(text);

			//A loop that draws all the map icons
			for (int i = 0; i <= 3; i++)
			{
				for (int z = 0; z <= 4; z++)
				{
					drawTo(mapIcons[5 * i + z], window, 370 * i + 60, 120 * z + 300, 1.0f);
				}
			}
			//Checks the event being done
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				else if (event.type == sf::Event::MouseButtonPressed)//checks if the mouse button is pressed
				{
					int xval = event.mouseButton.x;
					int yval = event.mouseButton.y;

					if (yval >= 120 && yval <= 287 && xval >= 632 && xval <= 967) //checks if the attack defense icon is clicked
					{
						isAttackDefense = true;
						if (xval <= 800)
						{
							attackDefense = "Defense";
							team = 0;
						}
						else
						{
							attackDefense = "Attack";
							team = 1;
						}

						//cout << team << endl;
					}

					else if (yval >= 300 && yval <= 900) //checks if the mouse click y coordinate is in the map icon range
					{
						isMapChosen = true;
						if (xval <= 370)
						{
							mapChose = mapKeys.at(1 * (1 + (yval - 300) / 120));
						}
						else if (xval <= 740)
						{
							mapChose = mapKeys.at(2 * (1 + (yval - 300) / 120));
						}
						else if (xval <= 1110)
						{
							mapChose = mapKeys.at(3 * (1 + (yval - 300) / 120));
						}
						else
						{
							mapChose = mapKeys.at(4 * (1 + (yval - 300) / 120));
						}

						map = mapChose;
						//cout << mapChose << endl;
					}

					else if (yval >= 900 && yval <= 1080 && xval >= 600 && xval <= 1000)
					{
						generate = true;
					}
				}
			}
		}

		window.display();
	}

	/*cout << "Enter Player 1's name: ";
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

	vector<pair<int, priority_queue<pair<float, string>>>> winRatesAll(5);
	for (int i = 0; i < 5; i++) { //players
		if (team == 0) { //all defense operators
			for (int j = 0; j < defenseOperatorSize; j++) { //all operators
				winRatesAll[i].first = i;
				winRatesAll[i].second.push({ autoMap[playerNames[i]].getOperatorWinRate(defenseOperators[j]), defenseOperators[j] });
				//cout << idealTeam[j] << ": ";
				//cout << autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j], map) << endl;
			}
		}
		else if (team == 1) { //all attack operators
			for (int j = 0; j < attackOperatorSize; j++) { //all operators
				winRatesAll[i].first = i;
				winRatesAll[i].second.push({ autoMap[playerNames[i]].getOperatorWinRate(attackOperators[j]), attackOperators[j] });
				//cout << idealTeam[j] << ": ";
				//cout << autoMap[playerNames[i]].getOperatorWinRate(idealTeam[j], map) << endl;
			}
		}

		//cout << endl;
	}

	calulateIdealTeam(winRatesAll);

	cout << "------------" << endl << endl;

	cout << "Based On Player Win Rates: " << endl; //choses from all operators instead of operators from team (offense / attack)

	float scoreBasic = 0;
	for (int i = 0; i < 5; i++) {
		cout << playerNames[winRatesAll[i].first] << ": " << winRatesAll[i].second.top().second << endl;
		scoreBasic += winRatesAll[i].second.top().first;
	}
	cout << "Team Score: " << scoreBasic / 5 << endl; //doesnt check for meta characters or synergies (could be higher)







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

	calulateIdealTeam(winRatesMeta);

	cout << endl << "Based On Meta Compositions: " << endl;

	float scoreMeta = 0;
	for (int i = 0; i < 5; i++) {
		cout << playerNames[winRatesMeta[i].first] << ": " << winRatesMeta[i].second.top().second << endl;
		scoreMeta += winRatesMeta[i].second.top().first;
	}
	cout << "Team Score: " << (scoreMeta + 50) / 5 << endl; //doesnt check for synergies (could be higher) and 50 was chosen as an abitrary bonus for using meta comp








	vector<player> players(5);
	for (int i = 0; i < 5; i++) {
		players[i] = autoMap[playerNames[i]];
	}

	Graph testGraph = Graph(players, team);
	int numSynergies = 0; //can either be 3 or 4 depending on how which edges are picked
	float scoreKruskal = 0;
	unordered_set<Node*> kruskal = testGraph.kruskalDeviation(numSynergies, scoreKruskal);

	for (auto it : kruskal) {
		cout << it->getSize().second << ": " << it->getOperatorName() << endl;
	}
	cout << "Team Score: " << (scoreKruskal + numSynergies*5) / numSynergies << endl; //doesnt check meta characters (could be higher) and chose 5 per synergy arbitrarily
	






	cout << endl << "-----------" << endl;

	Graph2 testGraph2 = Graph2(players, team);
	float scoreBruteForce = 0;
	vector<Node*> bruteForce = testGraph2.bruteForce(scoreBruteForce);

	cout << endl << "-----------" << endl << endl;
	for (int i = 0; i < bruteForce.size(); i++) {
		cout << bruteForce[i]->getSize().second << ": " << bruteForce[i]->getOperatorName() << endl;
	}
	cout << "Team Score: " << (scoreBruteForce + 4*5) / 4 << endl; //doesnt check meta characters (could be higher) and chose 5 per synergy arbitrarily (always 4 synergies)*/
	
	return 0;
}

void drawTo(sf::Texture drawing, sf::RenderWindow& window, int x, int y, float scale)
{
	sf::Sprite blankSprite;
	blankSprite.setTexture(drawing);
	blankSprite.move(sf::Vector2f((float)x, (float)y));
	blankSprite.setScale(sf::Vector2f(scale, scale));
	window.draw(blankSprite);
}