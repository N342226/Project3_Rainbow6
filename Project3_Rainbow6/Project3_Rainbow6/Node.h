#pragma once
#include <queue>
#include <string>

using namespace std;
class Node {
private:
	priority_queue < pair<float, string>> size; //<win rate, name>
	string operatorName;
public:
	Node(priority_queue < pair<float, string>> size);
	pair<float, string> getSize();
	string getOperatorName();
	void resizeNode();
};

Node::Node(priority_queue < pair<float, string>> size) {
	this->size = size;
}

pair<float, string> Node::getSize() {
	return size.top();
}

string Node::getOperatorName() {
	return operatorName;
}

void Node::resizeNode() {
	size.pop();
}