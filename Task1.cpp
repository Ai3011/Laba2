#include <iostream>
#include <string>
using namespace std;

int main() {
    string stroka;
    cout << "Enter the string:  ";
    cin >> stroka;

    string vowels = "aeioyuAEIOYU";
    string consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    int num_vowels = 0;
    int num_consonants = 0;

    for (char c : stroka) {
        if (vowels.find(c) != string::npos) {
            num_vowels++;
        }
    }
    for (char c : stroka) {
        if (consonants.find(c) != string::npos) {
            num_consonants++;
        }
    }

    if (num_vowels > num_consonants) {
        cout << "Yes" << endl;
    }
    else if (num_vowels < num_consonants) {
        cout << "No" << endl;
    }
    else {
        cout << "Identical" << endl;
    }

    return 0;
}
