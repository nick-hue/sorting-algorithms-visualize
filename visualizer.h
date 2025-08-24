#pragma once
#include <string>
#include <vector>
#include <functional>

void visualize(void(*sortFunc)(std::vector<int>&, std::function<void(const std::vector<int>&)>), std::string algorithm, std::vector<int> list, int max_value);
