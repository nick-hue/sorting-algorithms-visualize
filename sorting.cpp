#include "sorting.h"
#include <algorithm>
#include <functional>
#include <thread>
#include <chrono>

void bubble_sort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> onStep) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                if (onStep) onStep(arr);
            }
        }
    }
}

void quick_sort_helper(std::vector<int>& arr, int low, int high, std::function<void(const std::vector<int>&)> onStep) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
                if (onStep) onStep(arr);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        if (onStep) onStep(arr);
        int pi = i + 1;
        quick_sort_helper(arr, low, pi - 1, onStep);
        quick_sort_helper(arr, pi + 1, high, onStep);
    }
}

void quick_sort(std::vector<int>& arr, std::function<void(const std::vector<int>&)> onStep) {
    quick_sort_helper(arr, 0, arr.size() - 1, onStep);
}
