#include "Edge.h"

// ���캯��
Edge::Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}

int Edge::getSrc() const { return src; }
int Edge::getDest() const { return dest; }
int Edge::getWeight() const { return weight; }
void Edge::setSrc(int s) { src = s; }
void Edge::setDest(int d) { dest = d; }
void Edge::setWeight(int w) { weight = w; }