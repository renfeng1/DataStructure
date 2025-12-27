#include "postoffice_io.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

namespace postoffice {

// 从文件加载住宅区数据
std::vector<ResidentialArea> PostOfficeIO::loadAreasFromFile(const std::string& filePath) {
    std::vector<ResidentialArea> areas;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return areas; // 返回空集合表示失败
    }

    std::string line;
    while (std::getline(file, line)) {
        // 去除行首尾空白
        size_t firstNonSpace = line.find_first_not_of(" \t\r\n");
        if (firstNonSpace == std::string::npos) {
            continue; // 跳过空行
        }
        line = line.substr(firstNonSpace);
        
        if (line.empty() || line[0] == '#') { // 跳过注释行
            continue;
        }

        std::istringstream iss(line);
        std::string part;
        std::vector<std::string> parts;
        
        // 分割逗号分隔的部分
        while (std::getline(iss, part, ',')) {
            // 去除部分首尾空白
            size_t start = part.find_first_not_of(" \t");
            size_t end = part.find_last_not_of(" \t");
            if (start != std::string::npos && end != std::string::npos) {
                part = part.substr(start, end - start + 1);
            } else {
                part.clear();
            }
            parts.push_back(part);
        }
        
        if (parts.size() < 3 || parts.size() > 4) { // 格式错误
            continue;
        }

        int x = 0, y = 0, weight = 1;
        bool xOk = false, yOk = false;
        
        try {
            x = std::stoi(parts[0]);
            xOk = true;
            
            y = std::stoi(parts[1]);
            yOk = true;
            
            if (parts.size() == 4) {
                weight = std::stoi(parts[3]);
            }
        } catch (...) {
            // 转换失败，跳过该行
            continue;
        }

        if (xOk && yOk) {
            std::string name = parts[2];
            areas.emplace_back(x, y, name, weight);
        }
    }

    file.close();
    return areas;
}

// 将住宅区数据保存到文件
bool PostOfficeIO::saveAreasToFile(const std::string& filePath, const std::vector<ResidentialArea>& areas) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    // 写入文件头部注释
    file << "# 住宅区数据文件\n";
    file << "# 格式：x,y,name,weight\n";
    file << "# 示例：100,200,小区A,10\n\n";

    // 写入所有住宅区数据
    for (const auto& area : areas) {
        file << area.x() << "," << area.y() << "," << area.name() << "," << area.weight() << "\n";
    }

    file.close();
    return true;
}

} // namespace postoffice
