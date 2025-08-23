#include "visualizer.h"
#include "sorting.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>

std::vector<int> getRandomNumbers(int num, int max_value){
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> numbers(num);
    std::generate(numbers.begin(), numbers.end(), [max_value]() { return 1 + std::rand() % max_value; });

    return numbers;
}

int main(){

    int num_elements = 30;
    int max_value = 100;
    std::vector<int> numbers = getRandomNumbers(num_elements, max_value);
    std::string algorithm = "bubble"; // Change to "quick" for quick sort

    // if (algorithm == "bubble") {
    //     bubble_sort(numbers);
    // } else if (algorithm == "quick") {
    //     quick_sort(numbers);
    // } else {
    //     std::cerr << "Unknown algorithm: " << algorithm << std::endl;
    //     return 1;
    // }

    visualize(algorithm, numbers, max_value);
}