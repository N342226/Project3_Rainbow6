#pragma once
#include "operators.h"
#include <unordered_map>
#include <string>
using namespace std;

class player {
private:
	unordered_map<string, float> operatorKd;
	float minKd, maxKd;
public:
	player();
};

player::player() {
	minKd = .5;
	maxKd = 2;

	for (int i = 0; i < sizeof(operators); i++) { //operators comes from operators.h
		float kd = minKd + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxKd - minKd)));
		operatorKd[operators[i]] = kd;
	}
}