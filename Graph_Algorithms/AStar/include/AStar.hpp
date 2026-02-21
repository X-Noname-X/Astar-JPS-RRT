#pragma once
#ifndef _ASTAR_H_
#define _ASTAR_H_
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class Node
{
public:
	std::pair<int, int> NodePos; //节点坐标{y,x}
	float G, H, F; //G=起点到当前节点的实际代价，H当前节点到终点的代价（曼哈顿距离），F = G + H
	Node* Parents; //父节点的指针
	Node() :NodePos(0, 0),G(0),H(0),F(0),Parents(nullptr){} //构造函数，成员赋值
	void PathCost(Node* currentnode, std::pair<int, int> goal_, float G_cost); //路径代价
};

class AStar
{
public:
	std::vector<std::vector<int>> Map_Data; //存储地图的障碍物信息
	std::pair<int, int> MapSize; //地图的尺寸 {y,x}

	std::list<Node> OpenList;
	std::list<Node> CloseList;
	std::vector<Node*> PathNode;

	AStar(std::pair<int, int> mapsize); //构造函数，参数为地图尺寸
	std::pair<Node, std::list<Node>::iterator> getfLeastNode();
	bool isInList(std::list<Node> List,Node searchNode); //判断探索节点是否已经在OpenList或者CloseList里
	bool SearchPath(std::pair<int, int> start, std::pair<int, int> goal);  //路径搜索
	void ShowPath(); //显示最短路径

private:
	//探索方向，每个节点支持探索8个方向   顺时针探索顺序{y,x}
	float motions[8][3] = { {0,1,1},{-1,0,1},{0,-1,1},{1,0,1},
						  {1,1,1.4},{-1,1,1.4},{-1,-1,1.4},{1,-1,1.4} };
};

#endif