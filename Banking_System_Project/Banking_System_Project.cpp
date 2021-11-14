#include "Logic.h"

using namespace std;
int main()
{
	Logic logic;
	try {
		logic.Run();
	}
	catch(exception e)
	{
		std::cout << e.what() << endl;
	}
	return 0;
}
