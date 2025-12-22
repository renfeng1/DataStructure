#include "Node.h"


// ���캯��
Node::Node(float x, float y) : x(x), y(y){}

float Node::getX() const { return x; }
float Node::getY() const { return y; }

void Node::setX(float x) { this->x = x; }
void Node::setY(float y) { this->y = y; }
