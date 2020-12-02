#pragma once
#include "player.h"
#include <unordered_set>
using namespace std;

class database {
private:
	vector<player> db;
    unordered_set<string> usedNames; //O(1) search time

    string randomString(int n);
    void fillDb(int size);
public:
	database(int minSize);
	database(vector<player>, int minSize);

	void addPlayer(player player);
	vector<player> getDatabase();
};

string database::randomString(int n)
{
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };

    string res = "";
    for (int i = 0; i < n; i++) {
        res = res + alphabet[rand() % 26];
    }

    return res;
}

void database::fillDb(int size) {
    cout << "Generating random database..." << endl;
    while (db.size() <= size) {
        string name = randomString(rand() % 10 + 5); //random string between 5 and 15 characters
        if (usedNames.find(name) == usedNames.end()) {
            usedNames.insert(name);
            db.push_back(player(name));
        }
    }
}

database::database(int minSize) {
    fillDb(minSize);
}

database::database(vector<player> inputDb, int minSize) { //puts the input in the db then fills it to size
    db = inputDb;
    fillDb(minSize);
}

void database::addPlayer(player player) {
    db.push_back(player);
}

vector<player> database::getDatabase() {
    return db;
}