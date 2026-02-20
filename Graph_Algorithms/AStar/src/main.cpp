#include "AStar.hpp"

int main()
{
	AStar astar({1000,1000}); //operater{}  
	bool path = astar.SearchPath({ 0,0 }, { 900,980 });
	if (path) astar.ShowPath();
	system("pause");
	return 0;
}