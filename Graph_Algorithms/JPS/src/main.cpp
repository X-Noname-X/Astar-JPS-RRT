#include "jps.hpp"

int main()
{
	JPS jps({ 10,10 }); //operater{} 
	for (int i = 2; i <= 7; i++) jps.Map[1][i] = 1;
	for (int i = 2; i <= 7; i++) jps.Map[8][i] = 1;
	for (int i = 2; i <= 7; i++) jps.Map[i][7] = 1;
	bool path = jps.SearchPath({ 1,0 }, { 7,8 });
	//JPS jps({ 3,3 });
	//jps.Map[0][1] = 1;
	//bool path = jps.SearchPath({ 0,0 }, { 0,2 });
	if (path) jps.ShowPath();
	system("pause");
	return 0;
}