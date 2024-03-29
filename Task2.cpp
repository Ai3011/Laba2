#include <iostream>
#include <vector>

using namespace std;

bool isOddDigits(int num) {
    int count = 0;
    while (num != 0) {
        count++;
        num /= 10;
    }
    return count % 2 != 0;
}

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int count = 0;
    for (int num : nums) {
        if (isOddDigits(num)) {
            count++;
        }
    }

    cout << "The number of elements with odd number of digits is: " << count << endl;

    return 0;
}
