#include "postoffice.h"
#include "postoffice_io.h"
#include <algorithm>

// ResidentialArea 构造函数实现

ResidentialArea::ResidentialArea(int x, int y, const QString& name, int weight)
    : m_x(x), m_y(y), m_name(name), m_weight(weight) {}

// 从算法库的ResidentialArea构造
ResidentialArea::ResidentialArea(const postoffice::ResidentialArea& algorithmArea)
    : m_x(algorithmArea.x()),
      m_y(algorithmArea.y()),
      m_name(QString::fromStdString(algorithmArea.name())),
      m_weight(algorithmArea.weight()) {}

// 获取横坐标

int ResidentialArea::x() const {
    return m_x;
}

// 获取纵坐标

int ResidentialArea::y() const {
    return m_y;
}

// 获取住宅区名称

QString ResidentialArea::name() const {
    return m_name;
}

// 获取权重

int ResidentialArea::weight() const {
    return m_weight;
}

// 获取坐标点

QPoint ResidentialArea::point() const {
    return QPoint(m_x, m_y);
}

// 转换为算法库的ResidentialArea
postoffice::ResidentialArea ResidentialArea::toAlgorithmArea() const {
    return postoffice::ResidentialArea(m_x, m_y, m_name.toStdString(), m_weight);
}

// 获取所有住宅区

const std::vector<ResidentialArea>& PostOfficeLocator::areas() const {
    return m_areas;
}

// 添加住宅区

void PostOfficeLocator::addArea(const ResidentialArea& area) {
    m_areas.push_back(area);
    m_algorithm.addArea(area.toAlgorithmArea());
}

// 计算最优邮局位置

QPoint PostOfficeLocator::calculateOptimalPostOffice() const {
    postoffice::Point optimalPoint = m_algorithm.calculateOptimalPostOffice();
    return QPoint(optimalPoint.x, optimalPoint.y);
}

// 计算最优邮局位置（别名方法）

QPoint PostOfficeLocator::findOptimalLocation() const {
    return calculateOptimalPostOffice();
}

// 获取坐标范围

QRect PostOfficeLocator::getCoordinateRange() const {
    postoffice::Rect range = m_algorithm.getCoordinateRange();
    return QRect(range.left, range.top, range.width, range.height);
}

// 清空所有住宅区
void PostOfficeLocator::clearAreas() {
    m_areas.clear();
    m_algorithm.clearAreas();
}

// 计算总费用（所有住宅区到邮局的距离和）

int PostOfficeLocator::calculateTotalCost(const QPoint& postOfficePos) const {
    postoffice::Point pos(postOfficePos.x(), postOfficePos.y());
    return m_algorithm.calculateTotalCost(pos);
}

// 获取住宅区数量

int PostOfficeLocator::areaCount() const {
    return m_algorithm.areaCount();
}

// 从文件加载住宅区数据

bool PostOfficeLocator::loadAreasFromFile(const QString& filePath) {
    // 使用PostOfficeIO类加载数据
    std::vector<postoffice::ResidentialArea> algorithmAreas = 
        postoffice::PostOfficeIO::loadAreasFromFile(filePath.toStdString());
    
    // 清空现有数据
    clearAreas();
    
    // 添加新加载的住宅区数据
    for (const auto& algorithmArea : algorithmAreas) {
        addArea(ResidentialArea(algorithmArea));
    }
    
    return !algorithmAreas.empty();
}