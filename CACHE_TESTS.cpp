#include <gtest/gtest.h>
#include "LFU.h"
#include "PERFECT_CACHE.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace LFU;
using namespace PERFECT_CACHE;





TEST(cache, isFull) {
    std::cout << "TEST:isFull" <<std:: endl;
    std::vector<int> test{ 1, 2, 1, 2, 1, 2 };
    int capaicity = 2;
    LFU_CACHE<int, int> lfu(capaicity);
    size_t TOTAL_HITS1 =lfu.InputData(test, slow_get_page);
    IdealCache<int, int> perf(capaicity, test.size(), test);
    perf.parse_data(slow_get_page1);
    size_t TOTAL_HITS2 = perf.CheckCache(slow_get_page1, get_data);
   // perf.Dump();
    std::cout << "\n TOTAL_HITS1 LFU = " << TOTAL_HITS1 << '\n';
    std::cout << "\n TOTAL_HITS2 Perfect = " << TOTAL_HITS2 << '\n';

    ASSERT_TRUE( lfu.Full() && perf.Full());
}




TEST(cache, checkhits1) {
    std::cout << "TEST:checkhits1" << std::endl;

    std::vector<int> test{ 1, 2, 1, 2, 1, 2 };
    int capaicity = 2;
    LFU_CACHE<int, int> lfu(capaicity);
    size_t TOTAL_HITS1 = lfu.InputData(test, slow_get_page);
    IdealCache<int, int> perf(capaicity, test.size(), test);
    perf.parse_data(slow_get_page1);
    size_t TOTAL_HITS2 = perf.CheckCache(slow_get_page1, get_data);
    //perf.Dump();
    std::cout << "\n TOTAL_HITS1 LFU = " << TOTAL_HITS1 << '\n';
    std::cout << "\n TOTAL_HITS2 Perfect = " << TOTAL_HITS2 << '\n';

    ASSERT_EQ(TOTAL_HITS1, 4);
    ASSERT_EQ(TOTAL_HITS2, 4);

}

TEST(cache, checkhits2) {
    std::cout << "TEST:checkhits2" << std::endl;

    std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7 };
    int capaicity = 3;
    LFU_CACHE<int, int> lfu(capaicity);
    size_t TOTAL_HITS1 = lfu.InputData(test, slow_get_page);
    IdealCache<int, int> perf(capaicity, test.size(), test);
    perf.parse_data(slow_get_page1);
    size_t TOTAL_HITS2 = perf.CheckCache(slow_get_page1, get_data);
    //perf.Dump();
    std::cout << "\n TOTAL_HITS1 LFU = " << TOTAL_HITS1 << '\n';
    std::cout << "\n TOTAL_HITS2 Perfect = " << TOTAL_HITS2 << '\n';

    ASSERT_EQ(TOTAL_HITS1, 0);
    ASSERT_EQ(TOTAL_HITS2, 0);
}

TEST(cache, checkhits3) {
    std::vector<int> test{ 2, 3, 1, 4, 1, 4, 2, 4, 5, 1, 3, 2 };
    std::cout << "TEST:checkhits3" << std::endl;


    int capaicity = 4;
    LFU_CACHE<int, int> lfu(capaicity);
    size_t TOTAL_HITS1 = lfu.InputData(test, slow_get_page);
    IdealCache<int, int> perf(capaicity, test.size(), test);
    perf.parse_data(slow_get_page1);
    size_t TOTAL_HITS2 = perf.CheckCache(slow_get_page1, get_data);
    //perf.Dump();
    std::cout << "\n TOTAL_HITS1 LFU = " << TOTAL_HITS1 << '\n';
    std::cout << "\n TOTAL_HITS2 Perfect = " << TOTAL_HITS2 << '\n';


    ASSERT_EQ(TOTAL_HITS1, 5);
    ASSERT_EQ(TOTAL_HITS2, 7);

}
TEST(cache, checkhits4) {
    std::vector<int> test{ 2, 2, 1, 5, 9, 6, 0, 1, 2, 4, 3, 2, 4, 5, 10, 10, 2, 10, 4, 2, 7, 2, 5, 1, 1, 10, 9, 5, 4, 6, 2, 9,
        2, 7, 5, 10, 2, 6, 1, 0, 1, 2, 4, 10, 5, 9, 10, 2, 5, 9, 2, 7, 5, 10, 2, 6, 1, 0, 1, 2, 4, 10, 5, 9, 10, 2, 5 };
    std::cout << "TEST:checkhits4" << std::endl;


    int capaicity = 4;
    LFU_CACHE<int, int> lfu(capaicity);
    size_t TOTAL_HITS1 = lfu.InputData(test, slow_get_page);
    IdealCache<int, int> perf(capaicity, test.size(), test);
    perf.parse_data(slow_get_page1);
    size_t TOTAL_HITS2 = perf.CheckCache(slow_get_page1, get_data);
    //perf.Dump();
    std::cout << "\n TOTAL_HITS1 LFU = " << TOTAL_HITS1 << '\n';
    std::cout << "\n TOTAL_HITS2 Perfect = " << TOTAL_HITS2 << '\n';


    ASSERT_EQ(TOTAL_HITS1, 25);
    ASSERT_EQ(TOTAL_HITS2, 39);

}
std::vector<int> fillVector(int N) {
    std::vector<int> myVector(N);


    for (int i = 0; i < 100; ++i) {
        myVector[i] = i + 1;
    }


    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 100; i < 1000; ++i) {
        myVector[i] = rand() % 1000;
    }

    return myVector;
}
TEST(cache, comparisonhits) {
    std::vector<int> test = fillVector(1000);
    std::cout << "TEST:comparisonhits" << std::endl;


    int capaicity = 3;
    LFU_CACHE<int, int> lfu(capaicity);
    size_t TOTAL_HITS1 = lfu.InputData(test, slow_get_page);
    IdealCache<int, int> perf(capaicity, test.size(), test);
    perf.parse_data(slow_get_page1);
    size_t TOTAL_HITS2 = perf.CheckCache(slow_get_page1, get_data);
    //perf.Dump();
    std::cout << "\n TOTAL_HITS1 LFU = " << TOTAL_HITS1 << '\n';
    std::cout << "\n TOTAL_HITS2 Perfect = " << TOTAL_HITS2 << '\n';
    ASSERT_TRUE(TOTAL_HITS1 <= TOTAL_HITS2);

}




int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
