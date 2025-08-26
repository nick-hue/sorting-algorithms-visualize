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

    int num_elements = 20;
    int max_value = 100;
    std::vector<int> numbers = getRandomNumbers(num_elements, max_value);
    std::string algorithm = "quick"; 

    // Instead of using a function pointer, use std::function for sortFunc to allow lambdas
    using VisualizeStepCallback = std::function<void(const std::vector<int>&, bool)>;
    using SortFunc = std::function<void(std::vector<int>&, std::function<void(const std::vector<int>&)>)>;
    SortFunc func;

    if (algorithm == "bubble") {
        func = [](std::vector<int>& arr, std::function<void(const std::vector<int>&)> cb) {
            bubble_sort(arr, [&](const std::vector<int>& state, bool) { cb(state); });
        };
    } else if (algorithm == "quick") {
        func = [](std::vector<int>& arr, std::function<void(const std::vector<int>&)> cb) {
            quick_sort(arr, [&](const std::vector<int>& state, bool) { cb(state); });
        };
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }

    visualize(func, algorithm, numbers, max_value);
}