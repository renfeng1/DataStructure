#ifndef POSTOFFICE_H
#define POSTOFFICE_H

#include <vector>
#include <QPoint>
#include <QString>
#include <QRect>
#include "postoffice_algorithm.h" // 引入与Qt无关的算法库

// 住宅区类，Qt封装，用于界面显示
class ResidentialArea {
public:
    // 构造函数
    
    ResidentialArea(int x, int y, const QString& name, int weight = 1);
    
    // 从算法库的ResidentialArea构造
    ResidentialArea(const postoffice::ResidentialArea& algorithmArea);
    
    // 获取横坐标

    int x() const;
    
    // 获取纵坐标

    int y() const;
    
    // 获取住宅区名称

    QString name() const;
    
    // 获取权重

    int weight() const;
    
    // 获取坐标点

    QPoint point() const;
    
    // 转换为算法库的ResidentialArea
    postoffice::ResidentialArea toAlgorithmArea() const;
    
private:
    int m_x;              ///< 横坐标
    int m_y;              ///< 纵坐标
    QString m_name;       ///< 住宅区名称
    int m_weight;         ///< 权重
};

// 邮局选址器类，Qt封装，负责与界面交互
class PostOfficeLocator {
public:
    // 获取所有住宅区

    const std::vector<ResidentialArea>& areas() const;
    
    // 添加住宅区

    void addArea(const ResidentialArea& area);
    
    // 计算最优邮局位置

    QPoint calculateOptimalPostOffice() const;
    
    // 计算总费用（所有住宅区到邮局的距离和）

    int calculateTotalCost(const QPoint& postOfficePos) const;
    
    // 获取住宅区数量

    int areaCount() const;
    
    // 清空所有住宅区
    void clearAreas();
    
    // 查找最优位置（与calculateOptimalPostOffice功能相同）

    QPoint findOptimalLocation() const;
    
    // 获取坐标范围

    QRect getCoordinateRange() const;
    
    // 从文件加载住宅区数据

    // 
    // 文件格式：每行一个住宅区，格式为：x,y,name,weight
    // 例如：100,200,小区A,10
    bool loadAreasFromFile(const QString& filePath);
    
private:
    std::vector<ResidentialArea> m_areas;   ///< 住宅区集合（Qt版本）
    postoffice::PostOfficeLocatorAlgorithm m_algorithm; ///< 与Qt无关的算法核心
};

#endif // POSTOFFICE_H
