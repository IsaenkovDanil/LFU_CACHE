#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include <iostream>
#include <cassert>


namespace LFU {

	template<typename KeyT, typename PageT>
	struct Elem
	{
		KeyT Key;
		int Freq;
		PageT Page;
	};
    template<typename KeyT, typename PageT>

    class LFU_CACHE {

        size_t CacheSize = 0;
        long int  TotalHit = 0;
        int count = 0;
        using ListIt = typename std::list<Elem<KeyT, PageT>>::iterator;

        std::list<Elem<KeyT, PageT>> ActualCache;
        std::unordered_map<KeyT, ListIt> HashTable;


    public:
        LFU_CACHE(int capacity) :CacheSize(capacity) {}
        ~LFU_CACHE() {}

        bool LookUpdate(KeyT key, Elem<KeyT, PageT> slow_get_page(KeyT)) {
            auto hit = HashTable.find(key);
            if (hit == HashTable.end()) { // not found
                if (Full()) {
                    HashTable.erase(ActualCache.back().Key); // cleanup least recently used
                    ActualCache.pop_back();
                }
                ActualCache.push_front(slow_get_page(key)); // fallback to slow method
                HashTable[key] = ActualCache.begin();
                return false;
            }
            auto eltit = hit->second;
            if (eltit != ActualCache.begin())
                ActualCache.splice(ActualCache.begin(), ActualCache, eltit, std::next(eltit));
            return true;
        }

      
    private:

        void Add(const KeyT& key, Elem<KeyT, PageT> slow_get_page(KeyT)) {
            if (count == CacheSize) {//if(Full()){}
                HashTable.erase(ActualCache.back().Key);
                ActualCache.pop_back();
            }
            else
                count++;

            ActualCache.push_back(slow_get_page(key));
            HashTable[key] = std::prev(ActualCache.end());
        }
    public:

        bool Full() const {
            return HashTable.size() == CacheSize;
        }
        long int HitСount() const {
            return TotalHit;
        }


        void Dump() {
            std::cout << "_______Dump of Class: LFU_CACHE_______\n\n";
            std::cout << "Сache size:         " << CacheSize << '\n';
            std::cout << "Count of elements:  " << HashTable.size() << '\n';
            std::cout << "Elements in cache:  ";
            std::cout << '[';
            for (ListIt i = ActualCache.begin(); i != ActualCache.end(); i++) {
                std::cout << " (" << i->Key << "," << i->Freq << ") ";
            }
            std::cout << "]\n";
            std::cout << "_____________End of Dump_____________\n\n";
        }

        template<typename F>
        size_t InputData(const std::vector<int>& vec,F slow_get_page_) {
            int hits_count = 0;
            for (const int& element : vec) {
                hits_count += this->LookUpdate(element, slow_get_page_);
                //this->Dump();
            }
            return hits_count;
        }
    };
}

LFU::Elem<int, int> slow_get_page(int key) {
    LFU::Elem<int, int> Page{ key, key };
    return Page;
}
