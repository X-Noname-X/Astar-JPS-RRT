# <p align="center">Astar-JPS-RRT</p>
**This is a lightweight path planning algorithm repository that currently supports the following algorithms: graph-based search algorithms (Astar and JPS), and sampling-based algorithms (RRT, RRT_Star, and Informed_RRT_Star).**

## 🔥 Features
1. Lightweight: Minimal dependencies with concise code implementation
2. Visualization: Realize visual visualization of path planning algorithm effects based on the OpenCV library
3. Cross-platform: This project supports both Windows and Linux systems
4. Reusability: The code in this project can be slightly modified for ROS-based path planning algorithm research

## 📦 Installation
### Windows
First, install the OpenCV library from the official website: https://opencv.org/releases/ , select the stable version **OpenCV-4.9.0** for Windows. After installation, you need to configure the environment variables. Follow these steps next:
```bash
git clone https://github.com/X-Noname-X/Astar-JPS-RRT.git
# Modify the OpenCV unzip path in Sample_Algorithms\RRT_Series\CMakeLists.txt to ensure the OpenCVConfig.cmake file can be found under this path
set(OpenCV_DIR "<Fill in your OpenCV unzip path>")
# Create a build directory in the Astar-JPS-RRT directory and navigate into it
mkdir build
cd build
# Generate build files
cmake ..
# Compile the project
cmake --build .
```

### Ubuntu
To be completed

## 🛠️ Running
### Windows
If everything goes well, you will see the following files in the path \Astar-JPS-RRT\build\bin\Debug: Astar.exe, JPS.exe, RRT_Series.exe
**Run directly by double-clicking the .exe files, or enter Astar.exe in the terminal**
**Note:** Switch between RRT, RRT_star, and Informed_RRT_star by modifying the macro definitions (#define) in the main.cpp file under \Astar-JPS-RRT\Sample_Algorithms\RRT_Series\src

### Ubuntu
To be completed