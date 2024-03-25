#include <iostream>
#include <cassert>
#include "LFU.h"
int main() {
    setlocale(LC_ALL, "Russian");

    size_t capactiy;
    size_t InputSize;

    std::cin >> capactiy >> InputSize;
    LFU::LFU_CACHE<int, int> cache(capactiy);

    if (!std::cin.good())
        throw std::runtime_error{ "Bad input: cache capacity" };


    int id;
    int hits_count = 0;
    for (int i = 0; i < InputSize; i++) {
        std::cin >> id;
        if (!std::cin.good())
            throw std::runtime_error{ "Bad input: wrong Key" };
        hits_count += cache.LookUpdate(id, slow_get_page);
        //cache.Dump();
    }

    std::cout<< hits_count << '\n';
}
