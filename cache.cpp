#include "cache.h"
#include <algorithm>

void cache::cache_init(int cache_capacity, int block_size, int _number_of_way,
                    int length_mem_addr, std::string _way_replacement)
{
    hit = 0;
    miss = 0;
    number_of_way = _number_of_way;
    capacity = cache_capacity;
    way_replacement = _way_replacement;

    //預設 4-byte per word -> 2-bit byte offset
    //offset
    number_of_byte_offset = byte_offset; // 2-bit by default
    number_of_block_offset = log2(block_size / word); // eg. log2(16) -> 4
    number_of_offset = number_of_byte_offset + number_of_block_offset;

    //index
    number_of_block = capacity / block_size;
    number_of_sets = number_of_block / number_of_way;
    number_of_index = log2(number_of_sets);

    //tag
    number_of_tag_bits = length_mem_addr - (number_of_index + number_of_offset);
}

void cache::put(int addr){

   std::list<int>::iterator itRR;

   const auto it = m_.find(index_of_addr(addr));
   //有該index
  if(it != m_.cend()){
  //繼續找有沒有相符的tag
    std::list<int>::iterator findIter = std::find(it->second->second.begin(), it->second->second.end(), tag_of_addr(addr));
    if(findIter != it->second->second.end()){
      hit++;
      hit_rate = (float)hit / (float)(hit + miss);
      miss_rate = 1.0 - hit_rate;
      if(way_replacement == "LRU"){
        it->second->second.splice(it->second->second.begin(), it->second->second, findIter);
      }
    }
    //tag does not exist
    else{
      miss++;
      hit_rate = (float)hit / (float)(hit + miss);
      miss_rate = 1.0 - hit_rate;
      if(it->second->second.size() == number_of_way){
        const auto& node = it->second->second.back();
        if(way_replacement != "RR"){
          it->second->second.pop_back();
        }
        else{
          itRR = it->second->second.begin();
          std::advance(itRR, rand() % number_of_way);
          it->second->second.erase(itRR);
        }
      }
      it->second->second.emplace_front(tag_of_addr(addr));
    }
  }
  // index does not exist
  else{
    miss++;
    hit_rate = (float)hit / (float)(hit + miss);
    miss_rate = 1.0 - hit_rate;
    cache_first_layer.emplace_front(index_of_addr(addr),NULL);
    cache_first_layer.begin()->second.emplace_front(tag_of_addr(addr));
    m_[index_of_addr(addr)] = cache_first_layer.begin();
  }
  access = hit + miss;
}

void cache::load_trace(std::string filename){
    std::ifstream trace;
    trace.open(filename);
    std::string buffer;
    int addr;
    while(std::getline(trace, buffer)){
        addr = standarize(buffer); // 0x0000 0000 -> 0x00000000 去掉空格
        put(addr);
    }
}

int cache::standarize(std::string addr){
    std::string buf;
    for(int i = 0; i < addr.length(); i++){
        if(addr[i] != ' '){
            buf = buf + addr[i];
        }
    }
    return std::stol(buf,nullptr, 16);
}

int cache::index_of_addr(int addr){
    int s = 0;
    addr = addr >> number_of_offset;
    for(int i = 0; i < number_of_index; i++){
        s = s << 1;
        s += 1;
    }
    return (addr & s);
}

int cache::tag_of_addr(int addr){
    addr = addr >> (number_of_offset + number_of_index);
    return addr;
}
