#include <iostream>

using namespace std;

int main()
{
	int x, y, z, w;
	
	/* For single input */
	cout << "Enter a number (x): ";
	cin >> x;
	
	/* For multiple inputs*/
	cout << "Enter 3 numbers (y, z, w): ";
	cin >> y >> z >> w;
	
	cout << "x: " << x;
    cout << "\ny: " << y;
    cout << "\nz: " << z;
    cout << "\nw: " << w << "\n";

	return 0;
}