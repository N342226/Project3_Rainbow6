#pragma once
#include "Node.h"

class Edge{
private:
	float weight;
	Node* from;
	Node* to;
public:
	Edge(Node* from, Node* to, float weight);
	float getWeight();
	Node* getFrom();
	Node* getTo();
	float calculateRating();
};

Edge::Edge(Node* from, Node* to, float weight) {
	this->from = from;
	this->to = to;
	this->weight = weight;
}

float Edge::calculateRating() {
	return (from->getSize().first + to->getSize().first) * weight;
}

float Edge::getWeight() {
	return weight;
}

Node* Edge::getFrom() {
	return from;
}

Node* Edge::getTo() {
	return to;
}

/*bool operator<(const struct Edge& left, const struct Edge& right) {
	return left.getWeight() < right.getWeight();
}*/