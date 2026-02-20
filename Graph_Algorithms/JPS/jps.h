#pragma once
#ifndef _JPS_H_
#define _JPS_H_
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
class Node
{
public:
	std::pair<int, int> NodePos; //节点坐标{y,x}
	std::vector<std::pair<int, int>> ForceNeighborList; //强迫邻居列表
	std::vector<std::pair<int, int>> SearchMotion; //探索方向列表
	double G, H, F; //G=起点到当前节点的实际代价，H当前节点到终点的代价（曼哈顿距离），F = G + H
	Node* Parents; //父节点的指针
	bool State; //标志位，用于判断Jump返回的是否为可用节点
	Node() :NodePos(0, 0), G(0), H(0), F(0), Parents(nullptr), State(false) {} //构造函数，成员赋值
	void PathCost(Node* currentnode, std::pair<int, int> goal_);
};

class JPS
{
public:
	std::vector<std::vector<int>> Map; //节点地图
	std::pair<int, int> MapSize; //地图的尺寸 {y,x}
	Node GoalNode; //终点
	std::list<Node> OpenList;
	std::list<Node> CloseList;
	std::vector<Node*> PathNode;

	JPS(std::pair<int, int> mapsize); //构造函数，参数为地图尺寸
	bool SearchPath(std::pair<int, int> start, std::pair<int, int> goal);  //路径搜索
	//递归探索，flag：斜线扩展时调用的横向纵向扩展遇到强迫邻居无需添加，0斜线，1直线
	Node Jump(Node currentnode, int motion[], int flag); 
	bool DelectForceNeighbor(Node &currentnode,int motion[],int flag);   //检测强迫邻居
	void ShowPath(); //显示最短路径
	std::pair<Node, std::list<Node>::iterator> getfLeastNode();
	bool isInList(std::list<Node> List, Node searchNode);

private:
	//探索方向，每个节点探索8个方向   顺时针探索顺序{y,x}
	int motions[8][2] = { {0,1},{-1,0},{0,-1},{1,0},
						  {1,1},{-1,1},{-1,-1},{1,-1} };
};
#endif // !_JPS_H_
