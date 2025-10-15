#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

void print_vector(vector<int> &numbers) {
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
}

void selecting_sort(vector<int> &numbers) {
    cout << "Selecting sort" << endl;
    print_vector(numbers);

    for (int i = 0; i < numbers.size(); i++) {
        int minIdx = i;
        for (int j = i + 1; j < numbers.size(); j++) {
            if (numbers[j] < numbers[minIdx]) {
                minIdx = j;
            }
        }
        swap(numbers[i], numbers[minIdx]);
    }

    print_vector(numbers);
}

void bubble_sort(vector<int> &numbers) {
    cout << "Bubble sort" << endl;
    print_vector(numbers);
    for ( int i = 0; i < numbers.size(); i++) {
        for (int j = 0; j < numbers.size() - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers[j], numbers[j + 1]);
            }
        }
    }
    print_vector(numbers);
}

int main() {
    cout << "Czesc wpisuj liczby a ja je posortuje(Wpisywanie az do wystapienia 0 lub liczby < 0)" << endl;

    vector<int> numbers;
    while (true) {
        int number;
        cout << "Podaj liczbe: ";
        cin>> number;

        if (number < 0 || number == 0){
            break;
        }

        numbers.push_back(number);
    }

    bubble_sort(numbers);
    return 0;
}