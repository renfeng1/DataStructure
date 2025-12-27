#ifndef POSTOFFICE_ALGORITHM_H
#define POSTOFFICE_ALGORITHM_H

#include <vector>
#include <string>
#include <iostream>

// 定义算法库的命名空间
namespace postoffice {

// 坐标点结构
struct Point {
    int x;  ///< 横坐标
    int y;  ///< 纵坐标
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// 矩形范围结构
struct Rect {
    int left;   ///< 左边界
    int top;    ///< 上边界
    int width;  ///< 宽度
    int height; ///< 高度
    Rect(int left = 0, int top = 0, int width = 0, int height = 0)
        : left(left), top(top), width(width), height(height) {}
};

// 住宅区类
class ResidentialArea {
public:
    ResidentialArea(int x, int y, const std::string& name, int weight = 1);
    int x() const;
    int y() const;
    const std::string& name() const;
    int weight() const;
    Point point() const;
private:
    int m_x;              ///< 横坐标
    int m_y;              ///< 纵坐标
    std::string m_name;   ///< 住宅区名称
    int m_weight;         ///< 权重
};

// 邮局选址算法类，包含核心逻辑与IO
class PostOfficeLocatorAlgorithm {
public:
    const std::vector<ResidentialArea>& areas() const;
    void addArea(const ResidentialArea& area);
    Point calculateOptimalPostOffice() const; // 最优位置算法
    int calculateTotalCost(const Point& postOfficePos) const;
    int areaCount() const;
    void clearAreas();
    Rect getCoordinateRange() const;
private:
    std::vector<ResidentialArea> m_areas;   ///< 住宅区集合
};

} // namespace postoffice

#endif // POSTOFFICE_ALGORITHM_H