#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
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
2. Prim's
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
	sf::RenderWindow window(sf::VideoMode(1600, 1080), "SFML works!"); //Creating the window

	//Getting all the operator icons
	std::map<std::string, sf::Texture> operatorIcons;
	sf::Texture operatorIcon;
	std::string name;
	if (!operatorIcon.loadFromFile("../Pictures/operators/ace.png")) {}
	name = "ace";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/alibi.png")) {}
	name = "alibi";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/amaru.png")) {}
	name = "amaru";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/aruni.png")) {}
	name = "aruni";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/ash.png")) {}
	name = "ash";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/bandit.png")) {}
	name = "bandit";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/blackbeard.png")) {}
	name = "blackbeard";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/blitz.png")) {}
	name = "blitz";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/buck.png")) {}
	name = "buck";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/capitao.png")) {}
	name = "capitao";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/castle.png")) {}
	name = "castle";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/caveira.png")) {}
	name = "caveira";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/clash.png")) {}
	name = "clash";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/doc.png")) {}
	name = "doc";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/dokkaebi.png")) {}
	name = "dokkaebi";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/echo.png")) {}
	name = "echo";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/ela.png")) {}
	name = "ela";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/finka.png")) {}
	name = "finka";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/frost.png")) {}
	name = "frost";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/fuze.png")) {}
	name = "fuze";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/glaz.png")) {}
	name = "glaz";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/goyo.png")) {}
	name = "goyo";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/gridlock.png")) {}
	name = "gridlock";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/hibana.png")) {}
	name = "hibana";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/iana.png")) {}
	name = "iana";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/iq.png")) {}
	name = "iq";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/jackal.png")) {}
	name = "jackal";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/jager.png")) {}
	name = "jager";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/kaid.png")) {}
	name = "kaid";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/kali.png")) {}
	name = "kali";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/kapkan.png")) {}
	name = "kapkan";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/lesion.png")) {}
	name = "lesion";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/lion.png")) {}
	name = "lion";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/maestro.png")) {}
	name = "maestro";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/maverick.png")) {}
	name = "maverick";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/melusi.png")) {}
	name = "melusi";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/mira.png")) {}
	name = "mira";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/montagne.png")) {}
	name = "montagne";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/mozzie.png")) {}
	name = "mozzie";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/mute.png")) {}
	name = "mute";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/nokk.png")) {}
	name = "nokk";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/nomad.png")) {}
	name = "nomad";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/oryx.png")) {}
	name = "oryx";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/pulse.png")) {}
	name = "pulse";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/rook.png")) {}
	name = "rook";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/sledge.png")) {}
	name = "sledge";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/smoke.png")) {}
	name = "smoke";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/tachanka.png")) {}
	name = "tachanka";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/thatcher.png")) {}
	name = "thatcher";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/thermite.png")) {}
	name = "thermite";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/twitch.png")) {}
	name = "twitch";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/valkyrie.png")) {}
	name = "valkyrie";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/vigil.png")) {}
	name = "vigil";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/wamai.png")) {}
	name = "wamai";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/warden.png")) {}
	name = "warden";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/ying.png")) {}
	name = "ying";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/zero.png")) {}
	name = "zero";
	operatorIcons.emplace(name, operatorIcon);
	if (!operatorIcon.loadFromFile("../Pictures/operators/zofia.png")) {}
	name = "zofia";
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
			text.setString("Best Overall Synergies");
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
			text.setCharacterSize(60);
			if (defaultTeam)
			{
				//Draws the default names
				text.setPosition(sf::Vector2f(5.0f, 100.0f));
				text.setString("Robert");
				window.draw(text);
				text.setPosition(sf::Vector2f(5.0f, 260.0f));
				text.setString("Charles");
				window.draw(text);
				text.setPosition(sf::Vector2f(5.0f, 420.0f));
				text.setString("Susurrus");
				window.draw(text);
				text.setPosition(sf::Vector2f(5.0f, 580.0f));
				text.setString("Football");
				window.draw(text);
				text.setPosition(sf::Vector2f(5.0f, 760.0f));
				text.setString("Parrallax");
				window.draw(text);

				sf::Sprite opIcon;
				if (attackDefense == "Attack")
				{
					drawTo(operatorIcons.at("blackbeard"), window, 410, 80, 0.1f);
					drawTo(operatorIcons.at("finka"), window, 410, 240, 0.1f);
					drawTo(operatorIcons.at("twitch"), window, 410, 400, 0.1f);
					drawTo(operatorIcons.at("ash"), window, 410, 560, 0.1f);
					drawTo(operatorIcons.at("thatcher"), window, 410, 740, 0.1f);

					drawTo(operatorIcons.at("blackbeard"), window, 820, 80, 0.1f);
					drawTo(operatorIcons.at("ace"), window, 820, 240, 0.1f);
					drawTo(operatorIcons.at("nomad"), window, 820, 400, 0.1f);
					drawTo(operatorIcons.at("hibana"), window, 820, 560, 0.1f);
					drawTo(operatorIcons.at("iana"), window, 820, 740, 0.1f);

					drawTo(operatorIcons.at("glaz"), window, 1273, 80, 0.1f);
					drawTo(operatorIcons.at("ace"), window, 1273, 240, 0.1f);
					drawTo(operatorIcons.at("thatcher"), window, 1273, 400, 0.1f);
					drawTo(operatorIcons.at("nomad"), window, 1273, 560, 0.1f);
					drawTo(operatorIcons.at("zofia"), window, 1273, 740, 0.1f);
				}
				else
				{
					drawTo(operatorIcons.at("alibi"), window, 410, 80, 0.1f);
					drawTo(operatorIcons.at("jager"), window, 410, 240, 0.1f);
					drawTo(operatorIcons.at("lesion"), window, 410, 400, 0.1f);
					drawTo(operatorIcons.at("doc"), window, 410, 560, 0.1f);
					drawTo(operatorIcons.at("caveira"), window, 410, 740, 0.1f);

					drawTo(operatorIcons.at("rook"), window, 820, 80, 0.1f);
					drawTo(operatorIcons.at("melusi"), window, 820, 240, 0.1f);
					drawTo(operatorIcons.at("valkyrie"), window, 820, 400, 0.1f);
					drawTo(operatorIcons.at("jager"), window, 820, 560, 0.1f);
					drawTo(operatorIcons.at("ela"), window, 820, 740, 0.1f);

					drawTo(operatorIcons.at("valkyrie"), window, 1273, 80, 0.1f);
					drawTo(operatorIcons.at("mute"), window, 1273, 240, 0.1f);
					drawTo(operatorIcons.at("jager"), window, 1273, 400, 0.1f);
					drawTo(operatorIcons.at("maestro"), window, 1273, 560, 0.1f);
					drawTo(operatorIcons.at("smoke"), window, 1273, 740, 0.1f);
				}
			}

			else
			{
				//Get 5 random names from the hashmap

			}

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
				}

				//If Star Over button is pressed, resets back to the original screen
				else if (xval >= 1001 && xval <= 1400 && yval >= 910)
				{
					isMapChosen = false;
					isAttackDefense = false;
					generate = false;
					defaultTeam = false;
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
						}
						else
						{
							attackDefense = "Attack";
						}
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

	vector<string> exampleNames = { "Charles", "Robbie", "Football", "Susurrus", "Bob" };
	vector<player> examplePlayers;

	for (int i = 0; i < exampleNames.size(); i++) {
		examplePlayers.push_back(player(exampleNames[i]));
	}

	int dbSize;
	cout << "Enter size of database: ";
	//cin >> dbSize;
	cout << 10 << endl;
	dbSize = 10;

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

	/*cout << "-----------" << endl << endl;

	while(!winRates[0].second.empty()){
		cout << winRates[0].second.top().second << ": " << winRates[0].second.top().first << endl;
		winRates[0].second.pop();
	}
	cout << endl;*/

	calulateIdealTeam(winRatesMeta);
	calulateIdealTeam(winRatesAll);

	cout << "------------" << endl << endl;

	cout << "Based On Player Win Rates: " << endl; //choses from all operators instead of operators from team (offense / attack)

	float scoreBasic = 0;
	for (int i = 0; i < 5; i++) {
		cout << playerNames[winRatesAll[i].first] << ": " << winRatesAll[i].second.top().second << endl;
		scoreBasic += winRatesAll[i].second.top().first;
	}
	cout << "Team Score: " << scoreBasic / 5 << endl; //doesnt check for meta characters or synergies (could be higher)

	cout << endl <<"Based On Meta Compositions: " << endl;

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
	cout << "Team Score: " << (scoreBruteForce + 4*5) / 4 << endl; //doesnt check meta characters (could be higher) and chose 5 per synergy arbitrarily (always 4 synergies)
	
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