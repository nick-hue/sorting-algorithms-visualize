#include "visualizer.h"
#include "sorting.h"
#include "my_util.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <functional>

int main(){

    int num_elements = 50;
    int max_value = 100;
    std::vector<int> numbers = getRandomNumbers(num_elements, max_value);
    std::string algorithm = "bubble"; 

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