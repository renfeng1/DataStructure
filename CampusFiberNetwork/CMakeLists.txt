cmake_minimum_required(VERSION 3.16)

project(CampusFiberNetwork VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# 添加源文件
set(SOURCES
    main.cpp
    Edge.cpp
    Graph.cpp
    GraphFileIO.cpp
    UnionFind.cpp
    MainWindow.cpp
    ManualInputDialog.cpp
    Node.cpp
)

# 添加头文件
set(HEADERS
    Edge.h
    Graph.h
    GraphFileIO.h
    UnionFind.h
    MainWindow.h
    ManualInputDialog.h
    Node.h
)

# 添加UI文件
set(UI_FILES
    MainWindow.ui
)

# 创建可执行文件
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
)

# 链接Qt库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
)
