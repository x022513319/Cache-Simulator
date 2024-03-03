#include <string>
#include <cmath>
#include <list> // doubly linked-list
#include <unordered_map> // hash map
#include <cstdlib>
#include <ctime>
#include <fstream>

const int word = 4; // 4-byte per word by default
const int byte_offset = log2(word);
const int abyte = 8;

class cache{
public:
    int number_of_sets;
    int number_of_tag_bits;
    int number_of_block_size;

    int number_of_offset;
    int number_of_byte_offset;
    int number_of_block_offset;

    int number_of_block;
    int number_of_index;

    int access;
    int hit;
    int miss;
    float hit_rate;
    float miss_rate;
    int number_of_way;
    int capacity;
    std::string way_replacement;

    std::list<std::pair<int, std::list<int>>> cache_first_layer; // index 對應到第幾個block
    std::unordered_map<int, std::list<std::pair<int, std::list<int>>>::iterator> m_; // addr(index) 對應到set

    cache(){};  // constructor
    void cache_init(int _cache_capacity, int block_size, int _number_of_way,
                    int length_mem_addr, std::string _way_replacement);
    void load_trace(std::string filename);
    void put(int addr);

    int index_of_addr(int addr);
    int tag_of_addr(int addr);
    int standarize(std::string addr);
};
