#include <iostream>
#include <vector>
#include <functional>
#include <array>

using namespace std;


int main()
{

	int *p = new int(23);
	int *p1 = p;

	delete[] p; // detatching the pointer

	p = new int(35);

	cout <<*p1 <<*p;


	return 0;
}
