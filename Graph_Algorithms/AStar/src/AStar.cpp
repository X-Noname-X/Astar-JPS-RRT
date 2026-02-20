#include "AStar.hpp"

//路径代价计算
void Node::PathCost(Node *currentnode,std::pair<int,int> goal_,float G_cost)
{
	Parents = currentnode;
	G = currentnode->G + G_cost;
	H = abs(NodePos.first - goal_.first) + abs(NodePos.second - goal_.second);
	F = G + H;
}

//A*的构造函数，用于初始化地图
AStar::AStar(std::pair<int, int> mapsize)
{
	MapSize = mapsize;
	for (int i = 0; i < MapSize.first; i++)
	{
		std::vector<int> mapline;
		for (int j = 0; j < MapSize.second; j++)
		{
			mapline.push_back(0);
		}
		Map_Data.push_back(mapline);
	}
}

std::pair<Node, std::list<Node>::iterator> AStar::getfLeastNode() //返回最小F的点
{
	Node resNode = OpenList.front();  //返回第一个元素
	std::list<Node>::iterator iT = OpenList.begin();
	for (std::list<Node>::iterator it = OpenList.begin(); it != OpenList.end(); it++) {
		if (it->F < resNode.F)
		{
			resNode = *it;
			iT = it;
		}
	}
	return {resNode,iT};
}

bool AStar::isInList(std::list<Node> List, Node searchNode)
{
	for (auto &node : List) {
		if (node.NodePos == searchNode.NodePos)
			return true;
	}
	return false;
}

bool AStar::SearchPath(std::pair<int, int> start, std::pair<int, int> goal)
{
	Node StartNode;
	StartNode.NodePos = start;
	OpenList.push_back(StartNode);  //先将起点放入open表中
	
	while(!OpenList.empty()) //open表不为空就继续搜索
	{
		//open表排序，F值小的节点在前
		auto Result = getfLeastNode();
		//取出F值最小的节点，即open表首元素
		Node fLeastNode = Result.first;
		OpenList.erase(Result.second); //移除open表中F最小的元素
		CloseList.push_back(fLeastNode); //添加到close表中
		//判断该节点是否为终点，是返回true，否则继续
		if (fLeastNode.NodePos == goal)
		{
			Node tmp_node;
			tmp_node = fLeastNode;
			PathNode.push_back(&CloseList.back());
			while (tmp_node.Parents != nullptr) //起点的父节点指针指向nullptr
			{
				PathNode.push_back(tmp_node.Parents);
				tmp_node = *(tmp_node.Parents);
			}
			return true;
		}

		for (auto& motion : motions)
		{
			Node SearchNode;
			SearchNode.NodePos.first = fLeastNode.NodePos.first + motion[0];
			SearchNode.NodePos.second = fLeastNode.NodePos.second + motion[1];
			
			//判断搜索节点是否在地图内，不在则跳出此次搜索
			if (SearchNode.NodePos.first < 0 || SearchNode.NodePos.first >= MapSize.first ||
				SearchNode.NodePos.second < 0 || SearchNode.NodePos.second >= MapSize.second)
				continue;
			//判断搜索节点是否是障碍物100(或者是不明情况的区域-1，可通行0)，或者在close表内
			if (Map_Data[SearchNode.NodePos.first][SearchNode.NodePos.second] || isInList(CloseList,SearchNode))
				continue;
			
			//判断是否在open表内
			if (!isInList(OpenList,SearchNode))//不在open表
			{
				SearchNode.PathCost(&(CloseList.back()), goal, motion[2]);
				OpenList.push_back(SearchNode);
			}
			else
			{
				if (fLeastNode.G + motion[2] < SearchNode.G)
					SearchNode.PathCost(&(CloseList.back()), goal, motion[2]);
			}
		}
	}
	//open表为空后，还没有搜索结果，则返回false
	return false;
}

void AStar::ShowPath()
{
	std::cout << "----------显示路径----------" << std::endl;
	for (int i = PathNode.size() - 1; i >= 0; --i) {
		if (i != 0)
			std::cout << "(" << PathNode[i]->NodePos.first << "," << PathNode[i]->NodePos.second << ")" << "->";
		else
			std::cout << "(" << PathNode[i]->NodePos.first << "," << PathNode[i]->NodePos.second << ")";
	}
	std::cout << std::endl;
}