cmake_minimum_required(VERSION 3.10)
project(CACHE_TESTS)

# Включаем поддержку тестирования
enable_testing()

# Находим и подключаем библиотеку Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем исполняемый файл для тестирования
add_executable(run_tests CACHE_TESTS.cpp LFU.h PERFECT_CACHE.h)

# Линкуем Google Test и стандартные библиотеки
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

# Добавляем тесты
add_test(NAME MyTest COMMAND run_tests)

