#include <iostream>
#include <vector>
#include "player.h"

#pragma once

using namespace std;

class Hashmap
{
private:
	int bucketsTaken;
	int buckets;
	//Has to stay below .75
	double loadFactor;
	//Each nested vector represents a bucket where each element is a player
	vector<vector<player>> hashMapBuckets;

public:
	Hashmap();

	void insertPlayer(player);
	void removePlayer(player);
	int hashPlayer(player);

};

Hashmap::Hashmap() {
	this->bucketsTaken = 0;
	this->buckets = 0;
	this->loadFactor = 0;
}

void Hashmap::insertPlayer(player) {

}

void Hashmap::removePlayer(player) {

}

int Hashmap::hashPlayer(player unHashed) {
	int hashedPlayer = unHashed.getName().size() % buckets;
}

class HashMap
{
};
