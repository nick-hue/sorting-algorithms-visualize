#pragma once
#include <vector>
#include <string>
#include <functional>

void bubble_sort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> onStep);
void quick_sort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> onStep);
// Add more algorithms as needed
