#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	if(argc > 1)
	{
		for(int i = 1 ; i < argc ; i++)

			cout << argv[i] << endl;
	}
	else
	{
		cerr << "No arguments given" << endl;
	}

	return 0;
}
