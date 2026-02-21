#include "AStar.hpp"

int main()
{
	// AStar astar({1000,1000}); //operater{}  
	// bool path = astar.SearchPath({ 0,0 }, { 900,980 });
	AStar astar({ 10,10 });
	for (int i = 2; i <= 7; i++) astar.Map_Data[1][i] = 1;
	for (int i = 2; i <= 7; i++) astar.Map_Data[8][i] = 1;
	for (int i = 2; i <= 7; i++) astar.Map_Data[i][7] = 1;
	bool path = astar.SearchPath({ 1,0 }, { 7,8 });
	if (path) astar.ShowPath();
	system("pause");
	return 0;
}