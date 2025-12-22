#ifndef NODE_H
#define NODE_H

class Node {
private:
    float x;
    float y;

public:
    // ���캯��
    Node(float x = 0, float y = 0);

    // ��ȡԴ����
    float getX() const;

    // ��ȡĿ�궥��
    float getY() const;
    
    // 设置X坐标
    void setX(float x);
    
    // 设置Y坐标
    void setY(float y);
};

#endif