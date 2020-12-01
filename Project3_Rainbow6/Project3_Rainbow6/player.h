#pragma once
#include "operators.h"
#include <unordered_map>
#include <string>
using namespace std;

class player {
private:
	unordered_map<string, float> operatorKd;
	string name;
public:
	player(string name, float minKd = .5, float maxKd = 2);
	player(string name, unordered_map<string, float> operatorKd);
	string getName();
	float getOperatorKd(string operatorName);
};

player::player(string name, float minKd, float maxKd) {
	this->name = name;
	for (int i = 0; i < sizeof(operators); i++) { //operators comes from operators.h
		float kd = minKd + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxKd - minKd)));
		operatorKd[operators[i]] = kd;
	}
}

player::player(string name, unordered_map<string, float> operatorKd) {
	this->name = name;
	this->operatorKd = operatorKd;
}

string player::getName() {
	return this->name;
}

float player::getOperatorKd(string operatorName) {
	return operatorKd[operatorName];
}