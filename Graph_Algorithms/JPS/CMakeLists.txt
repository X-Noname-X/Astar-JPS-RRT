# JPS 模块
project(JPS)

# 头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 源文件
set(JPS_SOURCES
    src/jps.cpp
    src/main.cpp
)

# 生成可执行文件
add_executable(JPS ${JPS_SOURCES})