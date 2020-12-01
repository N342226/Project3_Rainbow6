#pragma once
#include "operators.h"
#include <unordered_map>
#include <string>
using namespace std;

class player {
private:
	unordered_map<string, float> operatorWinRate;
	string name;
public:
	player(string name, float minWinRate = 0, float maxWinRate = 100);
	player(string name, unordered_map<string, float> operatorWinRate);
	string getName();
	float getOperatorWinRate(string operatorName);
};

player::player(string name, float minWinRate, float maxWinRate) {
	this->name = name;
	for (int i = 0; i < (sizeof(operators) / sizeof(operators[0])); i++) { //operators comes from operators.h
		float winRate = minWinRate + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxWinRate - minWinRate)));
		operatorWinRate[operators[i]] = winRate;
	}
}

player::player(string name, unordered_map<string, float> operatorWinRate) {
	this->name = name;
	this->operatorWinRate = operatorWinRate;
}

string player::getName() {
	return this->name;
}

float player::getOperatorWinRate(string operatorName) {
	return operatorWinRate[operatorName];
}