# CampusFiberNetwork

校园光纤网络规划与设计工具

## 项目简介

该项目是一个用于校园光纤网络规划与设计的图形化工具，基于Qt 6框架开发，使用CMake进行构建管理。

## 依赖要求

- Qt 6.0或更高版本（需要包含Core、Widgets和Gui模块）
- CMake 3.16或更高版本
- C++17兼容的编译器（如GCC、Clang、MSVC）

## 构建步骤

### 1. 安装依赖

确保已安装Qt 6开发环境和CMake。可以从以下网站下载：
- Qt: https://www.qt.io/download
- CMake: https://cmake.org/download/

### 2. 配置构建目录

```bash
mkdir build
cd build
cmake ..
```

### 3. 编译项目

#### Windows (MinGW)
```bash
mingw32-make
```

#### Windows (MSVC)
```bash
cmake --build . --config Release
```

#### Linux/macOS
```bash
make
```

## 运行步骤

编译完成后，可执行文件将生成在build目录中。直接运行即可：

```bash
./CampusFiberNetwork
```

## 项目结构

- `main.cpp`: 程序入口点
- `MainWindow.cpp/.h`: 主窗口界面
- `ManualInputDialog.cpp/.h`: 手动输入对话框
- `Graph.cpp/.h`: 图数据结构和算法
- `Edge.cpp/.h`: 边数据结构
- `UnionFind.cpp/.h`: 并查集算法实现
- `GraphFileIO.cpp/.h`: 图文件的读写操作
- `MainWindow.ui`: 主窗口界面设计
- `CMakeLists.txt`: CMake构建配置文件

## 功能特性

- 可视化显示校园光纤网络拓扑
- 支持从文件导入网络数据
- 支持手动输入网络数据
- 实现了相关网络规划算法
- 图形化界面操作便捷

## 注意事项

- 确保Qt环境变量已正确配置
- 首次运行可能需要Qt运行时库支持
- 建议使用Release模式构建以获得更好的性能
