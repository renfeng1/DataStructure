#include "postoffice_algorithm.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

// 使用postoffice命名空间
namespace postoffice {

// ResidentialArea 构造函数实现
ResidentialArea::ResidentialArea(int x, int y, const std::string& name, int weight)
    : m_x(x), m_y(y), m_name(name), m_weight(weight) {}

// 获取横坐标
int ResidentialArea::x() const {
    return m_x;
}

// 获取纵坐标
int ResidentialArea::y() const {
    return m_y;
}

// 获取住宅区名称
const std::string& ResidentialArea::name() const {
    return m_name;
}

// 获取权重
int ResidentialArea::weight() const {
    return m_weight;
}

// 获取坐标点
Point ResidentialArea::point() const {
    return Point(m_x, m_y);
}

// 获取所有住宅区
const std::vector<ResidentialArea>& PostOfficeLocatorAlgorithm::areas() const {
    return m_areas;
}

// 添加住宅区
void PostOfficeLocatorAlgorithm::addArea(const ResidentialArea& area) {
    m_areas.push_back(area);
}

// 计算最优邮局位置
// 
// 这里实现的是加权中位数算法：
// 1. 分别对所有住宅区的x坐标和y坐标进行排序
// 2. 计算累积权重
// 3. 找到累积权重超过总权重一半的那个点作为加权中位数
// 这种方法可以最小化所有住宅区到邮局的加权曼哈顿距离之和
Point PostOfficeLocatorAlgorithm::calculateOptimalPostOffice() const {
    if (m_areas.empty()) {
        return Point(0, 0);
    }
    
    // 计算总权重
    int totalWeight = 0;
    for (const auto& area : m_areas) {
        totalWeight += area.weight();
    }
    
    // 提取所有x坐标并排序（包含权重信息）
    struct CoordinateWithWeight {
        int coord;
        int weight;
    };
    
    std::vector<CoordinateWithWeight> xCoordsWithWeight;
    for (const auto& area : m_areas) {
        xCoordsWithWeight.push_back({area.x(), area.weight()});
    }
    // 按x坐标排序
    std::sort(xCoordsWithWeight.begin(), xCoordsWithWeight.end(),
              [](const CoordinateWithWeight& a, const CoordinateWithWeight& b) {
                  return a.coord < b.coord;
              });
    
    // 提取所有y坐标并排序（包含权重信息）
    std::vector<CoordinateWithWeight> yCoordsWithWeight;
    for (const auto& area : m_areas) {
        yCoordsWithWeight.push_back({area.y(), area.weight()});
    }
    // 按y坐标排序
    std::sort(yCoordsWithWeight.begin(), yCoordsWithWeight.end(),
              [](const CoordinateWithWeight& a, const CoordinateWithWeight& b) {
                  return a.coord < b.coord;
              });
    
    // 计算加权中位数x坐标
    int cumulativeWeight = 0;
    int medianX = xCoordsWithWeight[0].coord;
    for (const auto& item : xCoordsWithWeight) {
        cumulativeWeight += item.weight;
        if (cumulativeWeight >= totalWeight / 2) {
            medianX = item.coord;
            break;
        }
    }
    
    // 计算加权中位数y坐标
    cumulativeWeight = 0;
    int medianY = yCoordsWithWeight[0].coord;
    for (const auto& item : yCoordsWithWeight) {
        cumulativeWeight += item.weight;
        if (cumulativeWeight >= totalWeight / 2) {
            medianY = item.coord;
            break;
        }
    }
    
    return Point(medianX, medianY);
}

// 计算总费用（所有住宅区到邮局的距离和）
int PostOfficeLocatorAlgorithm::calculateTotalCost(const Point& postOfficePos) const {
    int totalCost = 0;
    for (const auto& area : m_areas) {
        // 计算曼哈顿距离 |x1 - x2| + |y1 - y2|
        int distance = std::abs(area.x() - postOfficePos.x) + std::abs(area.y() - postOfficePos.y);
        // 乘以权重
        totalCost += distance * area.weight();
    }
    return totalCost;
}

// 获取住宅区数量
int PostOfficeLocatorAlgorithm::areaCount() const {
    return static_cast<int>(m_areas.size());
}

// 清空所有住宅区
void PostOfficeLocatorAlgorithm::clearAreas() {
    m_areas.clear();
}

// 获取坐标范围
Rect PostOfficeLocatorAlgorithm::getCoordinateRange() const {
    if (m_areas.empty()) {
        return Rect(0, 0, 100, 100); // 默认范围
    }
    
    int minX = m_areas[0].x();
    int maxX = m_areas[0].x();
    int minY = m_areas[0].y();
    int maxY = m_areas[0].y();
    
    for (const auto& area : m_areas) {
        if (area.x() < minX) minX = area.x();
        if (area.x() > maxX) maxX = area.x();
        if (area.y() < minY) minY = area.y();
        if (area.y() > maxY) maxY = area.y();
    }
    
    // 创建包含所有点的矩形范围
    return Rect(minX, minY, maxX - minX, maxY - minY);
}



} // namespace postoffice