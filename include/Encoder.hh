#ifndef ERRC_ENCODER_H
#define ERRC_ENCODER_H

#include <iostream>
#include <ctime> 
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include <FileUtil.hh>

class Encoder {
public:

  void encode(std::string in, std::string out);

  std::bitset<8> hamming_encode(std::bitset<4> data);

  std::vector<std::bitset<4>> split_byte(char c); 

  std::vector<std::bitset<8>> data_to_blocks(std::vector<char>&& data);

  std::vector<char> blocks_to_buffer(std::vector<std::bitset<8>>&& blocks);

};


#endif
