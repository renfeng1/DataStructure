#ifndef POSTOFFICE_IO_H
#define POSTOFFICE_IO_H

#include <string>
#include <vector>
#include "postoffice_algorithm.h"

namespace postoffice {

// 邮局选址算法的IO处理类，负责文件读写操作
// 该类提供与文件系统交互的功能，用于加载和保存住宅区数据
// 与算法核心逻辑分离，便于独立测试和维护
class PostOfficeIO {
public:
    // 从文件加载住宅区数据
    // 文件格式：每行一个住宅区，格式为：x,y,name,weight
    // 例如：100,200,小区A,10
    static std::vector<ResidentialArea> loadAreasFromFile(const std::string& filePath);
    
    // 将住宅区数据保存到文件
    static bool saveAreasToFile(const std::string& filePath, const std::vector<ResidentialArea>& areas);
};

} // namespace postoffice

#endif // POSTOFFICE_IO_H
