#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream file;

	file.open("tester.txt");
	
	if (file.is_open())
	{	
		cout << "Success!!!" << endl;		

		file << "Test Text" << endl;

		file.close();
	}
	else
		cout << "Failure!!!" << endl;

	return 0;
}
