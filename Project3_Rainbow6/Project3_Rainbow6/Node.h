#pragma once
#include <queue>
#include <string>

using namespace std;
class Node {
private:
	priority_queue < pair<float, string>> size; //<win rate, player name>
	string operatorName;
public:
	Node();
	Node(priority_queue < pair<float, string>>& size, string operatorName);
	pair<float, string> getSize();
	string getOperatorName();
	void resizeNode();
	int getSizeLength();
};

Node::Node() {
	operatorName = "";
}

Node::Node(priority_queue < pair<float, string>>& size, string operatorName) {
	this->operatorName = operatorName;
	this->size = size;
}

pair<float, string> Node::getSize() {
	if (size.empty()) {
		return {};
	}
	return size.top();
}

int Node::getSizeLength() {
	return size.size();
}

string Node::getOperatorName() {
	return operatorName;
}

void Node::resizeNode() {
	if (!size.empty()) {
		size.pop();
	}
}

/*bool operator<(const struct Node& left, const struct Node& right) {
	return false;//left.getSize().first < right.getSize().first;
}*/