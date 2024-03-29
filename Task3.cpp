#include <iostream> 
using namespace std;

int main() {
	cout << "Enter a three-digit number\n";

	int number;
	cin >> number;

	if (number <= 100 || number >= 999) {
		cout << "Error!, invalid number\n";
		return 1;
	}

	int digit_first, digit_last;
	digit_first = number / 100;
	digit_last = number % 10;


	if (digit_first == digit_last)
	{
		cout << "is palindrom\n";
	}
	else {
		cout << "is not palindrom\n";
	}
	return 0;
}
