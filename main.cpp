#include <iostream>
#include "cache.h"
#include <cstring>

int main(int argc, char *argv[]){
    srand(time(NULL));

    int capacity, block_size, number_of_way, length_mem_addr;
    std::string way_replacement, filename;

    for(int i = 0; i < argc; i++){
        if(std::strcmp(argv[i],"-capacity") == 0){
            capacity = std::stoi(argv[i+1], nullptr, 10);
        }
        else if(std::strcmp(argv[i],"-block_size") == 0){
            block_size = std::stoi(argv[i+1],nullptr,10);
        }
        else if(std::strcmp(argv[i],"-#_of_way") == 0){
            number_of_way = std::stoi(argv[i+1], nullptr, 10);
        }
        else if(std::strcmp(argv[i],"-length_mem_addr") == 0){
            length_mem_addr = std::stoi(argv[i+1], nullptr, 10);
        }
        else if(std::strcmp(argv[i], "-way_replacement")){
            std::string tmp(argv[10]);
            way_replacement = tmp;
        }
        else if(std::strcmp(argv[i], "-file")){
            std::string tmp(argv[12]);
            filename = tmp;
        }
    }

    cache C;
    C.cache_init(capacity, block_size, number_of_way, length_mem_addr, way_replacement);

    C.load_trace(filename);

    std::cout << "# of tag bits: " << C.number_of_tag_bits   << std::endl;
    std::cout << "# of sets: "     << C.number_of_sets       << std::endl;
    std::cout << "# of hit: "      << C.hit                  << std::endl;
    std::cout << "# of miss: "     << C.miss                 << std::endl;
    std::cout << "# of access: "   << C.access               << std::endl;
    std::cout << "hit_rate: "      << C.hit_rate*100 << "%"  << std::endl;
    std::cout << "miss_rate: "     << C.miss_rate*100 << "%" << std::endl;

    std::cout << std::endl;
    std::cout << "capacity: "        << capacity        << std::endl;
    std::cout << "block_size: "      << block_size      << std::endl;
    std::cout << "number_of_way: "   << number_of_way   << std::endl;
    std::cout << "length_mem_addr: " << length_mem_addr << std::endl;
    std::cout << "way_replacement: " << way_replacement << std::endl;
    std::cout << "filename: " << filename << std::endl;
}
