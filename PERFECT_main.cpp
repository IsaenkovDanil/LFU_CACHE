
#include <vector>
#include <iostream>
#include "PERFECT_CACHE.h"
#include <cassert>


int main(int argc, char* argv[])
{


    size_t cache_capactiy;
    size_t input_size;
    std::vector<int> input_data;

    std::cin >> cache_capactiy>>input_size;
    if (!std::cin.good())
        throw std::runtime_error{ "Bad input: cache capacity" };

    PERFECT_CACHE::IdealCache<int, int> IDEAL_CACHE(cache_capactiy , input_size, input_data);

    IDEAL_CACHE.GetInput();
    //IDEAL_CACHE.Dump();
    IDEAL_CACHE.parse_data(slow_get_page1);
    //IDEAL_CACHE.Dump();

    size_t TOTAL_HITS= IDEAL_CACHE.CheckCache(slow_get_page1,get_data);
    //IDEAL_CACHE.Dump();

    std::cout << TOTAL_HITS << '\n';
}
