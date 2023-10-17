#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include <iostream>
#include <cassert>


namespace PERFECT_CACHE
{
        template<typename T, typename KeyT>
        class IdealCache
        {

                struct MyPair {
                        KeyT first;
                        T second;

                        MyPair() : first(), second() {}
                        MyPair(const KeyT& key, const T& value) : first(key), second(value) {}
                };


        public:

                size_t input_size_;
                size_t cache_capacity_ = 0;

                using DataListIt = typename std::list<KeyT>;
                using ListIt = typename std::list<MyPair>::iterator;
                using DataAppearIt = typename std::unordered_map<KeyT, DataListIt>::iterator;


                std::list<MyPair> cache_{};
                std::unordered_map<KeyT, ListIt> hashtable_{};
                std::unordered_map<KeyT, DataListIt> AppearanceHashTable{};


                std::vector<KeyT>& input_data_;
                IdealCache(size_t cache_capacity, size_t input_size, std::vector<KeyT>& input_data) : cache_capacity_(cache_capacity), input_size_(input_size), input_data_(input_data) {
                        input_data_.reserve(input_size_);
                }


                void erase_farthest_elem() {
                        size_t max = 0;

                        ListIt     CacheIt{};
                        DataAppearIt elem_occurrence{};

                        for (ListIt it = cache_.begin(); it != cache_.end(); it++) {



                                if (AppearanceHashTable.find(it->first) == AppearanceHashTable.end()) {

                                        hashtable_.erase(it->first);
                                        cache_.erase(it);

                                        return;
                                }

                                auto index = *(AppearanceHashTable.find(it->first))->second.begin();

                                if (index > max) {
                                        max = index;
                                        CacheIt = it;                                }
                        }

                        if (max) {

                                hashtable_.erase(CacheIt->first);
                                cache_.erase(CacheIt);

                        }
                        else {
               //delete last element

                                hashtable_.erase(cache_.back().first);
                                cache_.pop_back();

                        }


                }
                bool DataAgain(const KeyT key)
                {
                        return AppearanceHashTable[key].size() == 1;
                }
                template<typename F>
                bool LookUpdate(const KeyT& key, F get_data_) {

                        auto find = hashtable_.find(key);//get pointer to the element with key
                        if (find == hashtable_.end()) {//if find is the end of the hash table then the element is not found
                                /*
                                  if (!DataAgain(key)) {//if the data will meet again with key
                                          return false;
                                  }*/

                                if (Full()) {
                                        erase_farthest_elem();
                                }


                                //there is an empty seat here already
                                cache_.emplace_front(key, get_data_(key));
                                hashtable_.emplace(key, cache_.begin());//here chache_.begin() a new key relation already

                                AppearanceHashTable[key].pop_front();
                                if (AppearanceHashTable[key].begin() == AppearanceHashTable[key].end())
                                        AppearanceHashTable.erase(key);

                                return false;
                        }


                        if (find->second != cache_.begin())
                        {
                                cache_.splice(cache_.begin(), cache_, find->second, std::next(find->second));
                        }

                        AppearanceHashTable[key].pop_front();
                        if (AppearanceHashTable[key].begin() == AppearanceHashTable[key].end())
                                AppearanceHashTable.erase(key);





                        return true;
                }



                template<typename F>
                void parse_data(F slow_get_page1_)
                {
                        DataAppearIt occurrence_iter{};

                        for (auto it = this->input_data_.cbegin(); it != this->input_data_.cend(); it++) {                                occurrence_iter = AppearanceHashTable.find(slow_get_page1_(*it));
                                this->AppearanceHashTable[slow_get_page1_(*it)].emplace_back(it - this->input_data_.cbegin());
                        }


                }
                template<typename F1, typename F2>
                size_t CheckCache(F1 slow_get_page1_, F2 get_data_)
                {
                        size_t hits = 0;

                        for (auto it = this->input_data_.cbegin(); it != this->input_data_.cend(); it++) {                                hits += this->LookUpdate(slow_get_page1_(*it), get_data_);
                                //this->Dump();


                        }

                        return hits;
                }



                void Dump() {

                        std::cout << "------- Dump of Class: IdealCache -------\n";
                        std::cout << "Capacity: " << input_size_ << "\n";
                        std::cout << "Size: " << cache_.size() << "\n";

                        std::cout << "Elements in cache: \n";
                        for (auto it = cache_.cbegin(); it != cache_.cend(); it++) {
                                std::cout << "[" << it->second << "] ";
                        }


                        std::cout << "------- End of dump --------------\n";
                }

                bool Full() const {
                        return cache_.size() == cache_capacity_;
                }

                void GetInput() {
                        KeyT NewElem;
                        std::cout << "Input Elements";
                        for (size_t i = 0; i < input_size_; i++) {
                                std::cin >> NewElem;
                                if (!std::cin.good())                                        throw std::runtime_error{ "Bad input: wrong Key" };
                                input_data_.push_back(NewElem);
                        }
                }







        }; // IdealCache







};//PERFECT_CACHE












int slow_get_page1(int data)//slow_get_page1
{
        return data;
}
int get_data(int key)
{
        return key;
}

