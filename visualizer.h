#pragma once
#include <string>
#include <vector>
#include <functional>

using VisualizeStepCallback = std::function<void(const std::vector<int>&, bool)>;
using SortFunc = std::function<void(std::vector<int>&, std::function<void(const std::vector<int>&)>)>;

void visualize(SortFunc sortFunc, std::string algorithm, std::vector<int> list, int max_value);
