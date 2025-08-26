#pragma once
#include <vector>
#include <string>
#include <functional>
using VisualizeStepCallback = std::function<void(const std::vector<int>&, bool swapped)>;

void bubble_sort(std::vector<int>& arr, VisualizeStepCallback cb);
void quick_sort(std::vector<int>& arr, VisualizeStepCallback cb);