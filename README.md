# <p align="center">Astar-JPS-RRT</p>
<p align="center">
  🌏 English | <a href="README_zh.md">🇨🇳 中文</a>
</p>

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
1.Install OpenCV dependencies via the official Ubuntu repository/apt: No need to configure the path manually; the system will automatically recognize it during compilation:
```bash
# Update package sources
sudo apt update
# Install the OpenCV development package (includes header files and libraries)
sudo apt install -y libopencv-dev
```
2.Installation and compilation of the project:
```bash
git clone https://github.com/X-Noname-X/Astar-JPS-RRT.git
# Comment out the line "set(OpenCV_DIR "<Fill in your OpenCV unzipped path>")" in CMakeLists.txt
set(OpenCV_DIR "<Fill in your OpenCV unzipped path>") ## Comment out this line
# The following steps are the same as those on the Windows system
mkdir build
cd build
cmake ..
# Compile the project
cmake --build .
# Alternatively, you can use the following command to compile:
# make
```

## 🛠️ Running
### Windows
- If everything goes well, you will see the following files in the path \Astar-JPS-RRT\build\bin\Debug: Astar.exe, JPS.exe, RRT_Series.exe
- **Run directly by double-clicking the .exe files, or enter Astar.exe in the terminal**
```bash
# Run Astar
\path\to\Astar-JPS-RRT\build\bin\Debug>Astar.exe
# Run JPS
\path\to\Astar-JPS-RRT\build\bin\Debug>JPS.exe
# Run RRT
\path\to\Astar-JPS-RRT\build\bin\Debug>RRT_Series.exe
```
- **Note:** Switch between RRT, RRT_star, and Informed_RRT_star by modifying the macro definitions (#define) in the main.cpp file under \Astar-JPS-RRT\Sample_Algorithms\RRT_Series\src

### Ubuntu
After completing the installation and compilation, there are three executable files—Astar, JPS, and RRT_Series—in the path /Astar-JPS-RRT/build/bin. Run the following commands in the terminal:
```bash
cd /path/to/Astar-JPS-RRT/build/bin
./Astar
./JPS
./RRT_Series
```

## 🎮 Results
Visualization for the Astar and JPS algorithms is currently not implemented.
| Astar | ![Astar](./assets/astar.jpg) |
|:---:|:---:|

| JPS | ![JPS](./assets/jps.jpg) |
|:---:|:---:|

| RRT | RRT* | Informed RRT* |
|:---:|:---:|:---:|
| ![RRT](./assets/rrt.gif) | ![RRT*](./assets/rrtstar.gif) | ![Informed RRT*](./assets/infrrt.gif) |