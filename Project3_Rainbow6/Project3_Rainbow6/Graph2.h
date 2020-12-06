#pragma once
#include "Node.h"
#include "Edge.h"
#include "WeightedEdges.h"
#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>

class Graph2 {
private:
	vector<Edge*> edges;
	vector<player> players;
	int team;

	map < Node*, vector < tuple<Node*, int, float>>> adjList;

	vector<string> namesAlreadyChecked;
	void checkDuplicateNameEdges(Node* from, Node* to, vector<Node*> traversal);

	void balance(map < Node*, vector < tuple<Node*, int, float>>> adjList, vector<Node*> traversal, Node* from);
public:
	Graph2(vector<player> players, int team) {
		this->players = players;
		this->team = team;

		WeightedEdges _edges = WeightedEdges(players, team);
		vector<Edge*> edges = _edges.edges;
		this->edges = edges;

		for (int i = 0; i < edges.size(); i++) {
			adjList[edges[i]->getFrom()].push_back({ edges[i]->getTo(), edges[i]->getWeight(), edges[i]->calculateRating() });
			adjList[edges[i]->getTo()].push_back({ edges[i]->getFrom(), edges[i]->getWeight(), edges[i]->calculateRating() });
		}
	}

	vector<tuple<Node*, int, float>> bfs(map < Node*, vector < tuple<Node*, int, float>>> _adjList, string src);
	vector<Node*> bruteForce();
};

vector<tuple<Node*, int, float>> Graph2::bfs(map < Node*, vector < tuple<Node*, int, float>>> adjList, string _src) {
	unordered_map<Node*, bool> visited;
	queue<tuple<Node*, int, float>> q;
	vector< tuple<Node*, int, float>> result;
	vector<Node*> traversal;
	Node* src;

	for (auto it : adjList) {
		if (it.first->getOperatorName() == _src) {
			src = it.first;
		}
	}

	int i = 0;
	visited[src] = true;
	q.push({ src, 0, 0 });

	while (!q.empty() && i < 5) {
		i++;
		tuple<Node*, int, int> u = q.front();
		result.push_back(u);
		traversal.push_back(get<0>(u));
		cout << "Node " << i << ": " << get<0>(u)->getOperatorName() << " | " << get<0>(u)->getSize().second << endl;

		if (get<0>(u)->getSize().second != "") {
			namesAlreadyChecked.push_back(get<0>(u)->getSize().second);
		}
		
		balance(adjList, traversal, get<0>(u));
		q.pop();

		for (tuple<Node*, int, int> v : adjList[get<0>(u)]) { //I think changing adjList to a map from unordered map will sort the edges so the largest ones are picked first
			if (!visited[get<0>(v)]) {
				visited[get<0>(v)] = true;
				q.push(v);
			}
		}
	}

	return result;
}

void Graph2::balance(map < Node*, vector < tuple<Node*, int, float>>> adjList, vector<Node*> traversal, Node* from) {
	for (int k = 0; k < adjList[from].size(); k++) {
		Node* to = get<0>(adjList[from][k]);

		//cout << endl << from->getOperatorName() << " -> " << to->getOperatorName() << endl;
		//cout << from->getSize().second << " -> " << to->getSize().second << endl;

		for (int i = 0; i < namesAlreadyChecked.size(); i++) {
			bool changed = false;

			if (namesAlreadyChecked[i] == from->getSize().second && find(traversal.begin(), traversal.end(), from) == traversal.end()) {
				//cout << "resize from: found in names already checked and not in traversal" << endl;
				from->resizeNode();
				changed = true;
			}

			if (namesAlreadyChecked[i] == to->getSize().second && find(traversal.begin(), traversal.end(), to) == traversal.end()) {
				//cout << "resize to: found in names already checked and not in traversal" << endl;
				to->resizeNode();
				changed = true;
			}

			if (changed) {
				i = -1;
			}
		}
		if (from->getSize().second != "") {
			namesAlreadyChecked.push_back(from->getSize().second); //make sure no other node being put in queue has the same name
		}
		if (to->getSize().second != "") {
			namesAlreadyChecked.push_back(to->getSize().second);
		}
	}

	for (auto x : adjList) {
		for (int i = 0; i < x.second.size(); i++) {
			get<2>(x.second[i]) = (x.first->getSize().first + get<0>(x.second[i])->getSize().first) * get<1>(x.second[i]); //(from size + to size) * weight
		}
	}
}

vector<Node*> Graph2::bruteForce() {
	vector<tuple<Node*, int, float>> bestTraversal;
	float bestRating = 0;

	int j = 0;
	for (auto x : this->adjList) {
		cout << endl << "---TRAVERSAL " << j++ << "---" << endl;
		map < Node*, vector < tuple<Node*, int, float>>> adjList;
		WeightedEdges _edges = WeightedEdges(players, team);
		vector<Edge*> edges = _edges.edges;;

		for (int i = 0; i < edges.size(); i++) {
			adjList[edges[i]->getFrom()].push_back({ edges[i]->getTo(), edges[i]->getWeight(), edges[i]->calculateRating() });
			adjList[edges[i]->getTo()].push_back({ edges[i]->getFrom(), edges[i]->getWeight(), edges[i]->calculateRating() });
		}

		vector<tuple<Node*, int, float>> traversal = bfs(adjList, x.first->getOperatorName());
		namesAlreadyChecked.clear();

		float totalRating = 0;
		for (int i = 0; i < traversal.size(); i++) {
			//cout << get<0>(traversal[i])->getOperatorName() << endl;
			totalRating += get<2>(traversal[i]);
		}

		//cout << totalRating << endl << endl;

		if (totalRating > bestRating) {
			bestRating = totalRating;
			bestTraversal = traversal;
		}

	}

	vector<Node*> result;
	for (int i = 0; i < bestTraversal.size(); i++) {
		result.push_back(get<0>(bestTraversal[i]));
	}

	return result;
}
