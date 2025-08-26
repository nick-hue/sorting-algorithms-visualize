#include "my_util.h"

std::vector<int> getRandomNumbers(int num, int max_value){
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> numbers(num);
    std::generate(numbers.begin(), numbers.end(), [max_value]() { return 1 + std::rand() % max_value; });

    return numbers;
}