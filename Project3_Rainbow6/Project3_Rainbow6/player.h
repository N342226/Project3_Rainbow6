#pragma once
#include "operators.h"
#include "maps.h"
#include <unordered_map>
#include <string>
using namespace std;

class player {
private:
	unordered_map<string, unordered_map<string, float>> defenseOperatorWinRate; //<operator <map, win rate>> || map is not needed since operators and maps array is finite but makes look ups easier to code
	unordered_map<string, unordered_map<string, float>> attackOperatorWinRate;
	string name;
	int numOfMaps = 20;
public:
	player();
	player(string name, float minWinRate = 0, float maxWinRate = 100); //0-100 is ideal for win rate. But we considered basing skill off k/d earlier and by changing this to .5-2.0 it imitates k/d
	player(string name, unordered_map<string, unordered_map<string, float>> operatorWinRate);
	string getName();
	float getOperatorWinRate(string operatorName, int map);
	float getOperatorWinRate(string operatorName, string map);
	float getOperatorWinRate(string operatorName); //return the average of each map 
};

player::player() {
	name = "";
}
player::player(string name, float minWinRate, float maxWinRate) {
	this->name = name;

	for (int i = 0; i < defenseOperatorSize; i++) { //operators comes from operators.h
		for (int j = 0; j < numOfMaps; j++) {
			float winRate = minWinRate + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxWinRate - minWinRate)));
			defenseOperatorWinRate[defenseOperators[i]].emplace(maps[j],winRate);
		}
		
	}

	for (int i = 0; i < attackOperatorSize; i++) { //operators comes from operators.h
		for (int j = 0; j < numOfMaps; j++) {
			float winRate = minWinRate + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxWinRate - minWinRate)));
			attackOperatorWinRate[attackOperators[i]].emplace(maps[j], winRate);
		}

	}
}

player::player(string name, unordered_map<string, unordered_map<string, float>> operatorWinRate) {
	this->name = name;
	this->defenseOperatorWinRate = operatorWinRate;
}

string player::getName() {
	return this->name;
}

float player::getOperatorWinRate(string operatorName, int map) {
	if (map < numOfMaps) {
		if (defenseOperatorWinRate.find(operatorName) != defenseOperatorWinRate.end()) {
			return defenseOperatorWinRate[operatorName].at(maps[map]);
		}
		else if (attackOperatorWinRate.find(operatorName) != attackOperatorWinRate.end()) {
			return attackOperatorWinRate[operatorName].at(maps[map]);
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

float player::getOperatorWinRate(string operatorName, string map) {
	if (attackOperatorWinRate[operatorName].find(map) != attackOperatorWinRate[operatorName].end() || defenseOperatorWinRate[operatorName].find(map) != defenseOperatorWinRate[operatorName].end()) {
		if (defenseOperatorWinRate.find(operatorName) != defenseOperatorWinRate.end()) {
			return defenseOperatorWinRate[operatorName].at(map);
		}
		else if (attackOperatorWinRate.find(operatorName) != attackOperatorWinRate.end()) {
			return attackOperatorWinRate[operatorName].at(map);
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

float player::getOperatorWinRate(string operatorName) {
	float result = 0;
	int i = 0;

	if (defenseOperatorWinRate.find(operatorName) != defenseOperatorWinRate.end()) {
		for (i; i < defenseOperatorWinRate[operatorName].size(); i++) {
			result += defenseOperatorWinRate[operatorName][maps[i]];
		}
	}
	else if (attackOperatorWinRate.find(operatorName) != attackOperatorWinRate.end()) {
		for (i; i < attackOperatorWinRate[operatorName].size(); i++) {
			result += attackOperatorWinRate[operatorName][maps[i]];
		}
	}
	else {
		return 0;
	}
	return result / (i + 1);
}