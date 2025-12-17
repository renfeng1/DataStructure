#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
class UnionFind; // 前向声明

class Graph {
private:
    int vertices;     // 顶点数量
    Edge** edgesArray; // 边数组
    int edgeCount;    // 当前边数
    int maxEdges;     // 最大边数
    // MST边集合
    Edge** mstEdges;  // MST边数组
    int mstEdgeCount; // MST边数
    // 堆排序辅助函数
    void heapify(Edge* edges[], int n, int i) const;
    void buildHeap(Edge* edges[], int n)const;

public:
    static const int INF = 2147483647; // 无穷大表示

    Graph(int v);
    ~Graph();

    // 图操作
    void addEdge(int u, int v, int weight);
    void printGraph() const;

    // 算法实现
    void heapSortEdges(Edge* edges[], int n) const;
    void kruskalMST();

    // 辅助方法
    int getVertices() const { return vertices; }
    int getEdgeCount() const { return edgeCount; }
    Edge** getEdges() const { return edgesArray; }
    Edge** getMSTEdges() const { return mstEdges; }
    int getMSTEdgeCount() const { return mstEdgeCount; }
    bool hasEdge(int u, int v) const; // 检查边是否存在
    bool isConnected() const; // 检查图是否连通
};

#endif