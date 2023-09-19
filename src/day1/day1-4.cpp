#include <iostream>
using namespace std;

int main() {
	double n = 100, sum = 0;
	for (double i = 1, x = 1; i <= n; i++) sum += x *= i;

	cout << sum << endl;
	return 0;
}
