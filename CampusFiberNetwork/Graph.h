#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <cmath>
#include <vector>
class UnionFind; // 前向声明
class Node;
class Graph {
private:
    int vertices;     // 顶点数量
    int** adjMatrix;  // 邻接矩阵
    Edge** edgesArray; // 边数组
    int edgeCount;    // 当前边数
    int maxEdges;     // 最大边数
    // MST相关
    Edge** mstEdgesArray; // 最小生成树边数组
    int mstEdgeCount;    // MST边数
    double mstTotalWeight; // MST总权重
    // 节点坐标
    std::vector<double> xCoords; // 节点X坐标
    std::vector<double> yCoords; // 节点Y坐标
    // 堆排序相关函数
    void heapify(Edge* edges[], int n, int i) const;
    void buildHeap(Edge* edges[], int n)const;

public:
    static const int INF = 2147483647; // 无穷大表示

    Graph(int v);
    ~Graph();

    // 图操作
    void addEdge(int u, int v, int weight);
    void printGraph() const;
    bool hasEdge(int u, int v) const;

    // 算法实现
    void heapSortEdges(Edge* edges[], int n) const;
    void kruskalMST();

    // 辅助函数
    int getVertices() const { return vertices; }
    int getEdgeCount() const { return edgeCount; }
    Edge** getEdges() const { return edgesArray; }
    Edge** getMSTEdges() const { return mstEdgesArray; }
    int getMSTEdgeCount() const { return mstEdgeCount; }
    double getMSTTotalWeight() const { return mstTotalWeight; } // 获取MST总权重
    
    // 节点坐标方法
    double getNodeX(int index) const; // 获取节点X坐标
    double getNodeY(int index) const; // 获取节点Y坐标
    void setNodeCoordinates(int index, double x, double y); // 设置节点坐标
};

// 外部函数声明
void NodesToEdges(Graph& graph, Node* nodes[], int nodes_n);

#endif
