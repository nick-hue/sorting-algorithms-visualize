#include "sorting.h"
#include <algorithm>
#include <functional>
#include <thread>
#include <chrono>

void z(std::vector<int>& arr, std::function<void(const std::vector<int>&)> onStep) {
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
using VisualizeStepCallback = std::function<void(const std::vector<int>&, bool swapped)>;

void bubble_sort(std::vector<int>& a, VisualizeStepCallback cb) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            bool swapped = false;
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
            cb(a, swapped); // 🔔 tell visualize whether a swap occurred
        }
    }
}

void quick_sort_helper(std::vector<int>& arr, int low, int high, VisualizeStepCallback cb) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            bool swapped = false;
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
                swapped = true;
            }
            cb(arr, swapped);
        }
        std::swap(arr[i + 1], arr[high]);
        cb(arr, true);
        int pi = i + 1;
        quick_sort_helper(arr, low, pi - 1, cb);
        quick_sort_helper(arr, pi + 1, high, cb);
    }
}

void quick_sort(std::vector<int>& arr, VisualizeStepCallback cb) {
    quick_sort_helper(arr, 0, arr.size() - 1, cb);
}
