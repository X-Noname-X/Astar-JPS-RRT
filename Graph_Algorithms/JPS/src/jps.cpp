#include "jps.hpp"

void Node::PathCost(Node* currentnode, std::pair<int, int> goal_)
{
	Parents = currentnode;
	H = abs(this->NodePos.first - goal_.first) + abs(this->NodePos.second - goal_.second);
	F = this->H;
}

JPS::JPS(std::pair<int, int> mapsize)
{
	this->MapSize = mapsize;
	for (int i = 0; i < MapSize.first; i++)
	{
		std::vector<int> mapline;
		for (int j = 0; j < MapSize.second; j++)
		{
			mapline.push_back(0);
		}
		Map.push_back(mapline);
	}
}

std::pair<Node, std::list<Node>::iterator> JPS::getfLeastNode() //返回最小F点
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
	return { resNode,iT };
}

bool JPS::isInList(std::list<Node> List, Node searchNode)
{
	for (auto& node : List) {
		if (node.NodePos == searchNode.NodePos)
			return true;
	}
	return false;
}

bool JPS::SearchPath(std::pair<int, int> start, std::pair<int, int> goal)
{
	Node StartNode; StartNode.NodePos = start; StartNode.State = true;
	GoalNode.NodePos = goal; GoalNode.State = true;
	//添加起点的遍历方向（8个方向都要遍历）
	for (auto& motion : motions)
		StartNode.SearchMotion.push_back({motion[0],motion[1]});
	OpenList.push_back(StartNode);  //先将起点放入open表中

	while (!OpenList.empty())
	{
		auto Result = getfLeastNode();
		Node fLeastNode = Result.first;
		OpenList.erase(Result.second); //移除open表首元素
		CloseList.push_back(fLeastNode);
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
		for (auto& motion : fLeastNode.SearchMotion)
		{
			int temp_motion[2] = {motion.first,motion.second};
			Node jumpnode = Jump(fLeastNode, temp_motion,1);
			if (jumpnode.State)
			{
				if (!isInList(OpenList,jumpnode)) //不在open表
				{
					jumpnode.PathCost(&CloseList.back(), goal);
					OpenList.push_back(jumpnode);
				}
			}
		}
	}
	return false;
}

int goal_flag = 0;
Node JPS::Jump(Node currentnode, int motion[],int flag)
{
	Node JumpNode; JumpNode.State = true;
	//节点坐标按方向递增
	JumpNode.NodePos.first = currentnode.NodePos.first + motion[0];
	JumpNode.NodePos.second = currentnode.NodePos.second + motion[1];
	//判断是否边界
	if (JumpNode.NodePos.first < 0 || JumpNode.NodePos.first >= MapSize.first ||
		JumpNode.NodePos.second < 0 || JumpNode.NodePos.second >= MapSize.second)
		return {};
	//判断是否为障碍物或者已在close表
	if (Map[JumpNode.NodePos.first][JumpNode.NodePos.second] || isInList(CloseList,JumpNode))
		return {};
	//判断是否为目标点
	if (JumpNode.NodePos == GoalNode.NodePos)
		return JumpNode;
	//检测强迫邻居
	bool fNeighbor = DelectForceNeighbor(JumpNode,motion,flag);
	if (fNeighbor)
	{
		if (flag) {
			//添加SearchMotion（扩展方向）父节点到该节点的扩展方向
			JumpNode.SearchMotion.push_back({ motion[0],motion[1] });
			//以及该节点到强迫邻居的扩展方向（遍历强迫邻居列表）
			for (std::vector<std::pair<int, int>>::iterator it = JumpNode.ForceNeighborList.begin();
				it != JumpNode.ForceNeighborList.end(); it++)
				JumpNode.SearchMotion.push_back({ it->first,it->second });
		}
		return JumpNode;
	}
	//如果是对角扩展，还需要调用纵向和横向的扩展
	if (motion[0] != 0 && motion[1] != 0)
	{
		int y_motion[2] = {motion[0],0};
		int x_motion[2] = {0,motion[1]};
		if (Jump(JumpNode, x_motion, 0).State || Jump(JumpNode, y_motion, 0).State)
		{
			JumpNode.SearchMotion.push_back({ 0,motion[1] });
			JumpNode.SearchMotion.push_back({ motion[0],0 });
			JumpNode.SearchMotion.push_back({ motion[0],motion[1] });
			return JumpNode;
		}
	}
	return Jump(JumpNode, motion, 1);
}

bool JPS::DelectForceNeighbor(Node &currentnode,int motion[],int flag)
{
	int y = currentnode.NodePos.first;
	int x = currentnode.NodePos.second;
	//横向扩展
	if (motion[0] == 0 && motion[1] != 0)
	{
		//防止数据溢出
		if ((y+1>=0 && y+1<MapSize.first) && (x+motion[1] >= 0 && x+motion[1] < MapSize.second))
		{
			//强迫邻居判断
			if (Map[y + 1][x] != 0 && Map[y + 1][x + motion[1]] == 0)
			{
				if(flag) currentnode.ForceNeighborList.push_back({1,motion[1]}); //添加强迫邻居的方向到列表
				return true;
			}
		}
		//防止数组溢出
		if ((y - 1 >= 0 && y - 1 < MapSize.first) && (x + motion[1] >= 0 && x + motion[1] < MapSize.second))
		{
			//强迫邻居判断
			if (Map[y - 1][x] != 0 && Map[y - 1][x + motion[1]] == 0)
			{
				if(flag) currentnode.ForceNeighborList.push_back({ -1,motion[1] }); //添加强迫邻居的方向到列表
				return true;
			}
		}
	}
	//纵向扩展
	else if (motion[0] != 0 && motion[1] == 0)
	{
		if ((x + 1 >= 0 && x + 1 < MapSize.second) && (y + motion[0] >= 0 && y + motion[0] < MapSize.first))
		{
			if (Map[y][x + 1] != 0 && Map[y + motion[0]][x + 1] == 0)
			{
				if(flag) currentnode.ForceNeighborList.push_back({ motion[0],1 }); //添加强迫邻居的方向到列表
				return true;
			}
		}
		if ((x - 1 >= 0 && x - 1 < MapSize.second) && (y + motion[0] >= 0 && y + motion[0] < MapSize.first))
		{
			if (Map[y][x - 1] != 0 && Map[y + motion[0]][x - 1] == 0)
			{
				if(flag) currentnode.ForceNeighborList.push_back({ motion[0],-1 });
				return true;
			}
		}
	}
	//对角扩展
	else if(motion[0] != 0 && motion[1] != 0)
	{
		if ((x - motion[1]>=0 && x - motion[1]<MapSize.second) && (y + motion[0]>=0 && y + motion[0] < MapSize.first))
		{
			if (Map[y][x - motion[1]] != 0 && Map[y + motion[0]][x - motion[1]] == 0)
			{
				if(flag) currentnode.ForceNeighborList.push_back({ motion[0],-motion[1]}); //添加强迫邻居的方向到列表
				return true;
			}
		}
		if ((x + motion[1] >= 0 && x + motion[1] < MapSize.second) && (y - motion[0] >= 0 && y - motion[0] < MapSize.first))
		{
			if (Map[y - motion[0]][x] != 0 && Map[y - motion[0]][x + motion[1]] == 0)
			{
				if(flag) currentnode.ForceNeighborList.push_back({ -motion[0],motion[1] }); //添加强迫邻居的方向到列表
				return true;
			}
		}
	}
	return false;
}

void JPS::ShowPath()
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