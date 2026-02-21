# AStar 模块
project(AStar)

# 头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 源文件
set(ASTAR_SOURCES
    src/AStar.cpp
    src/main.cpp
)

# 生成可执行文件
add_executable(AStar ${ASTAR_SOURCES})