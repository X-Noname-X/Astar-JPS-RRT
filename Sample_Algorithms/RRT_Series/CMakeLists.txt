# RRT_Series 模块
project(RRT_Series)

# 手动指定 OpenCV 路径：替换为解压路径
set(OpenCV_DIR "D:/OpenCV/opencv/build/x64/vc16/lib")
# 查找OpenCV库
find_package(OpenCV REQUIRED)

# 头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

# 源文件
set(RRT_SOURCES
    src/common.cpp
    src/rrt.cpp
    src/rrt_star.cpp
    src/informed_rrt_star.cpp
    src/main.cpp
)

# 生成可执行文件
add_executable(RRT_Series ${RRT_SOURCES})

# 链接 OpenCV 库
target_link_libraries(RRT_Series ${OpenCV_LIBS})