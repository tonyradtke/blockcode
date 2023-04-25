#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <fstream>

class FileUtil {
public: 

  static std::vector<char> read_all_bytes(std::string filename) {
      std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
      std::ifstream::pos_type pos = ifs.tellg();

      if (pos <= 0) {
          std::cout << "empty file cant read\n";
          return std::vector<char>{};
      }   

      std::vector<char>  result(pos);

      ifs.seekg(0, std::ios::beg);
      ifs.read(&result[0], pos);

      return result;
  }

  static void write_file(std::string filename, std::vector<char>& buffer) {
    std::ofstream disk;
    disk.open(filename);
    for (auto c : buffer) {
      disk << c;
    }   
  }

static void murphy(std::string filename) {
  std::vector<char> file_buffer = read_all_bytes(filename);
  uint32_t counter {0};
  for (auto& byte : file_buffer) {

    std::bitset<8> bs = std::bitset<8>(byte);

    for (uint32_t i = 0; i < 8; ++i) {
      unsigned seed = time(0) + clock();
      srand(seed); 
      int p = rand() % 1000 + 1;

      if (p > 500) {
        //std::cout << " block " << counter << " changed from : " << bs << "\n";
        bs.flip(i);
        //std::cout << "         "          << "                " << bs << "\n";
        byte = static_cast<char>(bs.to_ulong());
        break; //can only change one bit per block..
      }   
    }   

    ++counter;
  }

  write_file(filename, file_buffer); 

}

};


#endif 
