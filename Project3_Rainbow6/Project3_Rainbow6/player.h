#pragma once
#include "operators.h"
#include "maps.h"
#include <unordered_map>
#include <string>
using namespace std;

class player {
private:
	unordered_map<string, unordered_map<string, float>> operatorWinRate;
	string name;
	int numOfMaps = 20;
public:
	player();
	player(string name, float minWinRate = 0, float maxWinRate = 100); //0-100 is ideal for win rate. But we considered basing skill off k/d earlier and by changing this to .5-2.0 it imitates k/d
	player(string name, unordered_map<string, unordered_map<string, float>> operatorWinRate); //<operator <map, win rate>> || map is not needed since operators and maps array is finite but makes look ups easier to code
	string getName();
	float getOperatorWinRate(string operatorName, int map);
	float getOperatorWinRate(string operatorName); //return the average of each map
};

player::player() {
	name = "";
}
player::player(string name, float minWinRate, float maxWinRate) {
	this->name = name;
	for (int i = 0; i < operatorsSize; i++) { //operators comes from operators.h
		for (int j = 0; j < numOfMaps; j++) {
			float winRate = minWinRate + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxWinRate - minWinRate)));
			operatorWinRate[operators[i]].emplace(maps[j],winRate);
		}
		
	}
}

player::player(string name, unordered_map<string, unordered_map<string, float>> operatorWinRate) {
	this->name = name;
	this->operatorWinRate = operatorWinRate;
}

string player::getName() {
	return this->name;
}

float player::getOperatorWinRate(string operatorName, int map) {
	if (map < numOfMaps) {
		return operatorWinRate[operatorName].at(maps[map]);
	}
	else {
		return 0;
	}
}

float player::getOperatorWinRate(string operatorName) {
	float result = 0;
	int i = 0;

	for (i; i < operatorWinRate[operatorName].size(); i++) {
		result += operatorWinRate[operatorName][maps[i]];
	}
	return result / (i + 1);
}