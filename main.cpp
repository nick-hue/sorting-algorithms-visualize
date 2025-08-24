#include "visualizer.h"
#include "sorting.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <functional>

std::vector<int> getRandomNumbers(int num, int max_value){
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> numbers(num);
    std::generate(numbers.begin(), numbers.end(), [max_value]() { return 1 + std::rand() % max_value; });

    return numbers;
}

int main(){

    int num_elements = 50;
    int max_value = 100;
    std::vector<int> numbers = getRandomNumbers(num_elements, max_value);
    std::string algorithm = "quick"; 

    // Define a function pointer type for sorting functions
    using SortFunc = void(*)(std::vector<int>&, std::function<void(const std::vector<int>&)>);

    SortFunc func = nullptr;

    if (algorithm == "bubble") {
        func = bubble_sort;
    } else if (algorithm == "quick") {
        func = quick_sort;
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }

    visualize(func, algorithm, numbers, max_value);
}