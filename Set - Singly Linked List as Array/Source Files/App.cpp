#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <crtdbg.h>
using namespace std;




int main() {

	testAll();
	//testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	_CrtDumpMemoryLeaks();
	cout << "That's all!" << endl;
	system("pause");
	return 0;
}



