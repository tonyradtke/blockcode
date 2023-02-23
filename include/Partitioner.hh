#ifndef PARTER_H
#define PARTER_H

#include <thread>
#include <vector>
#include <map>
#include <string>
#include <iostream> 
#include <utility>
#include <chrono>
#include <cmath>

template <typename T>
class Partitioner {
public:

  std::vector<std::thread> m_threads;

  const T& m_data;
  std::vector<std::pair<typename T::const_iterator, typename T::const_iterator>> m_partitions;
  uint32_t m_numPartitions;

  Partitioner(T& f_data, uint32_t f_numPartitions) :
    m_data(f_data) {
    m_numPartitions = f_numPartitions;
   
    if (f_numPartitions > m_data.size()) {
      m_numPartitions = m_data.size();
    }
  
    create_partitions();
  };  


  void execute() {
    for (auto& part : m_partitions) {
      m_threads.push_back(std::thread( &Partitioner::handle_partition, this, part.first, part.second  )); 
    }   
    for (uint32_t i = 0; i < m_threads.size(); ++i) { m_threads[i].join(); }
  }

  virtual void handle_partition(typename T::const_iterator f_begin, typename T::const_iterator f_end) {
    std::cout << "WRONG\n";
    for (auto it = f_begin; it != f_end; ++it) {
    }   
  }

  void create_partitions() {
    const uint32_t mapSize = m_data.size();
    const uint32_t partitionSize = std::ceil(double(double(mapSize) / double(m_numPartitions)));
    const uint32_t regularPartitions = mapSize / partitionSize;
    const uint32_t remainderSize = mapSize % partitionSize;
    const bool bHasRemainder = (remainderSize != 0);

    #if 1
    std::cout << "---------------------------------------\n";
    std::cout << "partition details \n";
    std::cout << "map size       : " << mapSize <<  "\n";
    std::cout << "part size      : " << partitionSize << "\n";
    std::cout << "has remainder  : " << bHasRemainder << "\n";
    std::cout << "num reg parts  : " << regularPartitions << "\n";
    #endif 


    uint32_t lo {0};
    uint32_t hi {0};
    for (uint32_t i = 0; i < regularPartitions; ++i) {
      typename T::const_iterator lo_it = m_data.begin(); 
      typename T::const_iterator hi_it = m_data.begin(); 

      hi = lo + partitionSize - 1;

      #if 1
      std::cout << "[" << lo << "," << hi << "] = " << hi - lo + 1<< "\n";
      #endif 
  
      std::advance(lo_it, lo);
      std::advance(hi_it, hi);
    
      m_partitions.push_back(std::pair<typename T::const_iterator, typename T::const_iterator>(lo_it,hi_it));

      lo = hi + 1;  
    }   

    if (bHasRemainder) {
      typename T::const_iterator lo_it = m_data.begin(); 
      typename T::const_iterator hi_it = m_data.end(); 

      std::advance(lo_it, lo);

      m_partitions.push_back(std::pair<typename T::const_iterator, typename T::const_iterator>(lo_it,hi_it));

    }   
    std::cout << "---------------------------------------\n";
  }


};

#endif
