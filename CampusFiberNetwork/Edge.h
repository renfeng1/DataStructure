#ifndef EDGE_H
#define EDGE_H

class Edge {
private:
    int src;    // Դ����
    int dest;   // Ŀ�궥��
    int weight; // ��Ȩ��

public:
    // ���캯��
    Edge(int s = 0, int d = 0, int w = 0);

    // ��ȡԴ����
    int getSrc() const;

    // ��ȡĿ�궥��
    int getDest() const;

    // ��ȡ��Ȩ��
    int getWeight() const;

    // ���ù�����
    void setSrc(int s);

    // ���ù�궥��
    void setDest(int d);

    // ���ñ�Ȩ��
    void setWeight(int w);
};

#endif