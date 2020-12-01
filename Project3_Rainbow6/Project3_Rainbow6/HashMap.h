#include <iostream>
#include <vector>
#include <cmath>
#include "player.h"

#pragma once

using namespace std;

class HashMap
{
private:
	double bucketsTaken;
	double buckets;
	//Has to stay below .75
	double loadFactor;
	//Each nested vector represents a bucket where each element is a player
	vector<vector<player>> hashMapBuckets;

public:
	HashMap();

	vector<vector<player>>& getHMap();
	vector<vector<player>> insertPlayer(player, vector<vector<player>>);
	bool removePlayer(string name);
	int hashPlayer(player, int);
	player retrievePlayerInfo(string);
	vector<vector<player>> resize();
};

HashMap::HashMap() {
	this->bucketsTaken = 0.0;
	this->buckets = 0.0;
	this->loadFactor = 0.0;
}

vector<vector<player>>& HashMap::getHMap() {
	return this->hashMapBuckets;
}
vector<vector<player>> HashMap::insertPlayer(player insert, vector<vector<player>> hash) {
	int index = hashPlayer(insert, this->buckets); //grabs the index the player should be inserted in
	hash.at(index).push_back(insert); //adds the player into the hashmap
	if (this->bucketsTaken / this->buckets >= loadFactor) // checks if needs to be resized
	{
		hash = resize();
	}
	return hash;
}

bool HashMap::removePlayer(string name) {
	for (int i = 0; i < this->hashMapBuckets.size(); i++){
		for (int z = 0; z < this->hashMapBuckets.at(i).size(); z++) {
			if (this->hashMapBuckets.at(i).at(z).getName() == name)
			{
				this->hashMapBuckets.at(i).erase(this->hashMapBuckets.at(i).begin()+z);
			}
		}	
	}
	return false;
}

int HashMap::hashPlayer(player unHashed, int buckets) {
	long sum = 0;
	long factor = 1;
	for (int i = 0; i < unHashed.getName().length(); i++){
		if (i % 4 == 0){
			factor = 1;
		}
		else{
			factor *= 128;
		}
		sum = sum + unHashed.getName().at(i) * factor;
	}
	sum = abs(sum) % buckets;
	return (int)sum;
}

player HashMap::retrievePlayerInfo(string name) {
	for (int i = 0; i < this->hashMapBuckets.size(); i++){
		for (int z = 0; z < this->hashMapBuckets.at(i).size(); z++){
			string check = hashMapBuckets.at(i).at(z).getName();
			if (check == name)
			{
				return hashMapBuckets.at(i).at(z);
			}
		}
	}
}

vector<vector<player>> HashMap::resize() {
	vector<player> z;
	this->buckets *= 2;
	vector<vector<player>> newHashMap;
	for (int i = 0; i < this->buckets; i++){
		newHashMap.push_back(z);
	}
	for (int i = 0; i < this->hashMapBuckets.size(); i++){
		for (int j = 0; j < this->hashMapBuckets.at(i).size(); j++)
			insertPlayer(this->hashMapBuckets.at(i).at(j), newHashMap);
	}
	return newHashMap;
}