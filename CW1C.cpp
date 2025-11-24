#include <iostream>
#include <vector>
#include <algorithm>    

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};

    // Sort the vector in ascending order
    std::sort(numbers.begin(), numbers.end());

    // Print the sorted vector
    std::cout << "Sorted numbers: ";
    for (const int& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

